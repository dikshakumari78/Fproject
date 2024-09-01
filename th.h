#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <vector>

class ThreadPool {
public:
    ThreadPool(int thread_count, int queue_size);
    ~ThreadPool();

    void add_task(void (*function)(void *), void *arg);

private:
    static void *thread_pool_worker(void *arg);

    int thread_count;
    std::vector<pthread_t> threads;
    class TaskQueue; // Forward declaration
    TaskQueue queue;
};

#endif // THREADPOOL_H
