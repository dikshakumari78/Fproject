#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Task structure
struct Task {
    void (*function)(void *);
    void *arg;
};

// TaskQueue class definition
class ThreadPool::TaskQueue {
public:
    TaskQueue(int size);
    ~TaskQueue();

    void add_task(void (*function)(void *), void *arg);
    bool get_task(Task &task);
    void shutdown_queue();

private:
    std::vector<Task> tasks;
    int front, rear, task_count;
    bool shutdown;
    pthread_mutex_t lock;
    pthread_cond_t notify;
};

// Implementations of TaskQueue methods and ThreadPool methods here...

// Example task function
void example_task(void *arg) {
    int num = *(int *)arg;
    printf("Task %d is being processed.\n", num);
    sleep(1); // Simulate task processing
}

// ThreadPool constructor and destructor implementations
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
