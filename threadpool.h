#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <vector>

// Task structure
struct Task {
    void (*function)(void *);
    void *arg;
};

// TaskQueue class definition
class TaskQueue {
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

// ThreadPool class definition
class ThreadPool {
public:
    ThreadPool(int thread_count, int queue_size);
    ~ThreadPool();

    void add_task(void (*function)(void *), void *arg);

private:
    static void *thread_pool_worker(void *arg);

    int thread_count;
    std::vector<pthread_t> threads;
    TaskQueue queue;
};

#endif // THREADPOOL_H
