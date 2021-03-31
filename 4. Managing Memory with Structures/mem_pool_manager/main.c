#include <stdio.h>
#include <stdlib.h>
#include "mem_pool_manager.h"

typedef struct TestMetrics {
    int pour_mode;
    int pour_duration;
    float flow;
    double heat;
} TestMetrics;

int send_metrics(TestMetrics*);

int main() {
//    int needed_metric_objects = 100000000;
//    for(int i = 0; i < needed_metric_objects; i++) {
//        TestMetrics *metrics = (TestMetrics*)malloc(sizeof(TestMetrics));
//        send_metrics(metrics);
//    }

    MemoryPoolManager *my_mem_pool = NULL;
    mem_pool_init(&my_mem_pool, 20000000 * sizeof(TestMetrics), 5);

    printf("Blocks after instantiation \n");
    print_mem_blocks(my_mem_pool);

    MemoryPoolBlock *block, *block_2;

    mem_pool_alloc(my_mem_pool, &block);
    TestMetrics *my_data = block->data;
    my_data->pour_mode = 200;
    my_data->pour_duration = 300;
    my_data->flow = 2.3;
    my_data->heat = 23.4345;

    printf("Blocks after 1st alloc \n");
    print_mem_blocks(my_mem_pool);

    mem_pool_alloc(my_mem_pool, &block_2);
    printf("Blocks after 2nd alloc \n");
    print_mem_blocks(my_mem_pool);

    mem_pool_free(my_mem_pool, block);
    printf("Blocks after 1st free \n");
    print_mem_blocks(my_mem_pool);

    mem_pool_destroy(my_mem_pool);
    my_mem_pool = NULL;

    return 0;
}

int send_metrics(TestMetrics *metrics) {
    // Simulate some metrics processing here
    free(metrics);
    return 0;
}
