#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int metric_count = 0;

// Define a simple Metric type for sending off the amount of power used by the CoffeMachine for a given sequence
typedef struct Metric {
    int sequence_number;
    float power_used;
} Metric;

// Define our CoffeeMachine type!
typedef struct CoffeeMachine {
    int (*pour)(int, struct CoffeeMachine*);
    Metric **metrics;
    int pour_duration;
} CoffeeMachine;

// CoffeeMachine Create/Destroy API
int init_coffee_machine(CoffeeMachine**);
void cleanup_machine(CoffeeMachine*);

// Different PourHandler Function Declarations
int pour_decaf(int, CoffeeMachine*);
int pour_classic(int, CoffeeMachine*);
int pour_rich(int, CoffeeMachine*);

// Metric API
Metric* create_metric(float);
int send_metrics(Metric**, size_t metric_size);

// This 'main' function is here to simply test and make use of the API functions below
int main(int argc, char* argv[]) {
    // Instantiate a test coffee machine
    CoffeeMachine *my_machine;
    if(init_coffee_machine(&my_machine)) {
        printf("System does not have enough memory to allocate a CoffeeMachine structure\n");
        return 1;
    }

    // A pour mode (one of 'decaf', 'rich', or 'classic') is required along with a pour duration
    if (argc > 2) {
        printf("\nMachine Activated\n");
        char *user_pour_mode = argv[1];
        int duration = strtol(argv[2], NULL, 10);

        my_machine->pour_duration = duration;

        // Set the 'pour' function pointer based on the pour mode argument
        if (!strcmp("decaf", user_pour_mode)) {
            my_machine->pour = pour_decaf;
        } else if (!strcmp("rich", user_pour_mode)) {
            my_machine->pour = pour_rich;
        } else {
            my_machine->pour = pour_classic;
        }

        printf("\nBeginning Pour With Duration: %d\n", duration);

        my_machine->pour(duration, my_machine);

        printf("\nPour Complete. Sending Metrics...\n");
        send_metrics(my_machine->metrics, duration);

        printf("\nPerforming Cleanup...\n");
        cleanup_machine(my_machine);

    } else {
        printf("Please pass pour mode and duration arguments!\n");
        return 1;
    }

    return 0;
}

int init_coffee_machine(CoffeeMachine **machine) {
    if ((*machine = (CoffeeMachine*)malloc(sizeof(CoffeeMachine)))) {
        return 0;
    } else {
        return 1;
    }
}

// Pours a decaf cup of coffee
int pour_decaf(int duration, CoffeeMachine* machine) {
    int start = 0;
    Metric **metrics_ptr = (Metric**)malloc(duration * sizeof(Metric));
    machine->metrics = metrics_ptr;

    while(start < duration) {
        // Do some processing of pouring here....
        float power_used = 4.4;

        Metric *metric = create_metric(power_used);
        *(metrics_ptr + start) = metric;

        start++;
    }

    return 0;
}

// Pours a classic cup of coffee
int pour_classic(int duration, CoffeeMachine *machine) {
    int start = 0;
    Metric **metrics_ptr = (Metric**)malloc(duration * sizeof(Metric));
    machine->metrics = metrics_ptr;

    while (start < duration) {
        // Do some processing of pouring here....
        float power_used = 5.6;

        Metric *metric = create_metric(power_used);
        *(metrics_ptr + start) = metric;
        start++;
    }

    return 0;
}

// Pours a rich cup of coffee
int pour_rich(int duration, CoffeeMachine *machine) {
    int start = 0;
    Metric **metrics_ptr = (Metric**)malloc(duration * sizeof(Metric));
    machine->metrics = metrics_ptr;

    while (start < duration) {
        // Do some processing of pouring here....
        float power_used = 3.7;
        Metric *metric = create_metric(power_used);
        *(metrics_ptr + start) = metric;

        start++;
    }

    return 0;

}

// Dynamically allocates memory for a new Metric while coffee is being poured
Metric* create_metric(float power_used) {
    Metric *metric = (Metric*)malloc(sizeof(Metric));
    metric->sequence_number = ++metric_count;
    metric->power_used = power_used;

    return metric;
}

// Sends a dynamically allocated array of Metrics to an external API
int send_metrics(Metric **metrics, size_t metric_count) {
    if (metrics == NULL) {
        return 1;
    }

    for(int i = 0; i < metric_count; i++) {
        Metric *metric = metrics[i];
        printf("\nMetric Count: %d\n", metric->sequence_number);
        printf("Metric Power Used: %f\n", metric->power_used);
        // Here we could send each metric to the cloud via an external service.
    }

    return 0;
}

// Frees up resources that were allocated in relation to a CoffeeMachine
void cleanup_machine(CoffeeMachine *machine) {
    for(int i = 0; i < machine->pour_duration; i++) {
        Metric *metric = machine->metrics[i];
        printf("\nFreeing Metric At Count: %d\n", metric->sequence_number);
        free(metric);
    }

    free(machine->metrics);
    free(machine);
}
