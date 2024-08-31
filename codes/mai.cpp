#include "threadpool.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// Example task function
void example_task(void* arg) {
    int num = *static_cast<int*>(arg);
    printf("Task %d is being processed.\n", num);
    sleep(1); // Simulate task processing
    free(arg); // Free allocated memory
}

int main() {
    try {
        ThreadPool pool(4); // Create a pool with 4 threads

        for (int i = 0; i < 10; ++i) {
            int* arg = static_cast<int*>(malloc(sizeof(int)));
            *arg = i + 1;
            pool.add_task(example_task, arg);
        }

        sleep(5); // Wait for tasks to complete
    } catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
