#include "threadpool.h"
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// Utility function to check pthread errors
void check_pthread_error(int result, const char* msg) {
    if (result != 0) {
        throw std::runtime_error(msg);
    }
}

// TaskQueue implementation
TaskQueue::TaskQueue() : shutdown(false) {
    check_pthread_error(pthread_mutex_init(&lock, NULL), "Failed to initialize mutex");
    check_pthread_error(pthread_cond_init(&notify, NULL), "Failed to initialize condition variable");
}

TaskQueue::~TaskQueue() {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&notify);
}

void TaskQueue::add_task(const Task& task) {
    pthread_mutex_lock(&lock);
    if (!shutdown) {
        queue.push(task);
        pthread_cond_signal(&notify);
    }
    pthread_mutex_unlock(&lock);
}

bool TaskQueue::get_task(Task& task) {
    pthread_mutex_lock(&lock);
    while (queue.empty() && !shutdown) {
        pthread_cond_wait(&notify, &lock);
    }
    if (shutdown) {
        pthread_mutex_unlock(&lock);
        return false;
    }
    task = queue.front();
    queue.pop();
    pthread_mutex_unlock(&lock);
    return true;
}

void TaskQueue::set_shutdown() {
    pthread_mutex_lock(&lock);
    shutdown = true;
    pthread_cond_broadcast(&notify);
    pthread_mutex_unlock(&lock);
}

// ThreadPool implementation
void* ThreadPool::thread_pool_worker(void* arg) {
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    Task task;
    while (pool->taskQueue.get_task(task)) {
        task.function(task.arg);
    }
    return NULL;
}

ThreadPool::ThreadPool(int threadCount) {
    for (int i = 0; i < threadCount; ++i) {
        pthread_t thread;
        int result = pthread_create(&thread, NULL, thread_pool_worker, this);
        check_pthread_error(result, "Failed to create thread");
        threads.push_back(thread);
    }
}

ThreadPool::~ThreadPool() {
    taskQueue.set_shutdown();
    for (auto& thread : threads) {
        pthread_join(thread, NULL);
    }
}

void ThreadPool::add_task(const std::function<void(void*)>& func, void* arg) {
    Task task = { func, arg };
    taskQueue.add_task(task);
}
