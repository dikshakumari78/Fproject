#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// TaskQueue implementation
TaskQueue::TaskQueue(int size) : tasks(size), front(0), rear(0), task_count(size), shutdown(false) {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&notify, NULL);
}

TaskQueue::~TaskQueue() {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&notify);
}

void TaskQueue::add_task(void (*function)(void *), void *arg) {
    pthread_mutex_lock(&lock);

    if (shutdown) {
        pthread_mutex_unlock(&lock);
        return;
    }

    tasks[rear].function = function;
    tasks[rear].arg = arg;
    rear = (rear + 1) % task_count;

    pthread_cond_signal(&notify);
    pthread_mutex_unlock(&lock);
}

bool TaskQueue::get_task(Task &task) {
    pthread_mutex_lock(&lock);

    while (front == rear && !shutdown) {
        pthread_cond_wait(&notify, &lock);
    }

    if (shutdown) {
        pthread_mutex_unlock(&lock);
        return false;
    }

    task = tasks[front];
    front = (front + 1) % task_count;

    pthread_mutex_unlock(&lock);
    return true;
}

void TaskQueue::shutdown_queue() {
    pthread_mutex_lock(&lock);
    shutdown = true;
    pthread_cond_broadcast(&notify);
    pthread_mutex_unlock(&lock);
}

// ThreadPool implementation
ThreadPool::ThreadPool(int thread_count, int queue_size) : thread_count(thread_count), queue(queue_size) {
    threads.resize(thread_count);

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, thread_pool_worker, this);
    }
}

ThreadPool::~ThreadPool() {
    queue.shutdown_queue();
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
}

void ThreadPool::add_task(void (*function)(void *), void *arg) {
    queue.add_task(function, arg);
}

void *ThreadPool::thread_pool_worker(void *arg) {
    ThreadPool *pool = static_cast<ThreadPool *>(arg);
    Task task;

    while (pool->queue.get_task(task)) {
        (*(task.function))(task.arg);
    }

    return NULL;
}
