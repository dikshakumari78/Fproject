// threadpool.h
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <queue>
#include <functional>

// Task class
class Task {
public:
    std::function<void(void*)> function;
    void *arg;
};

// TaskQueue class
class TaskQueue {
private:
    std::queue<Task> queue;
    pthread_mutex_t lock;
    pthread_cond_t notify;
    bool shutdown;

public:
    TaskQueue();
    ~TaskQueue();
    void add_task(const Task& task);
    bool get_task(Task& task);
    void set_shutdown();
};

// ThreadPool class
class ThreadPool {
private:
    std::vector<pthread_t> threads;
    TaskQueue taskQueue;

    static void* thread_pool_worker(void* arg);

public:
    ThreadPool(int threadCount);
    ~ThreadPool();
    void add_task(const std::function<void(void*)>& func, void* arg);
};

#endif // THREADPOOL_H
