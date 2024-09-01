#include "threadpool.h"
#include <unistd.h>

void example_task(void *arg) {
    int num = *(int *)arg;
    printf("Task %d is being processed.\n", num);
    sleep(1); // Simulate task processing
}

int main() {
    ThreadPool pool(4, 10);

    for (int i = 0; i < 10; i++) {
        int *arg = new int(i + 1);
        pool.add_task(example_task, arg);
    }

    sleep(5); // Wait for tasks to complete
    return 0;
}
