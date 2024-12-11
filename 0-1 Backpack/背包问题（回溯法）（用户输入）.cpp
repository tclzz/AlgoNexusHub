#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 1

typedef struct {
    int weights;
    int values;
} Item;

void getData(Item items[], int *capacity, int num_items) {
    // This function is modified to accept user input instead of generating random data
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", capacity);

    printf("Enter the weights and values for each item:\n");
    for (int i = 0; i < num_items; i++) {
        printf("Item %d weight: ", i + 1);
        scanf("%d", &items[i].weights);
        printf("Item %d value: ", i + 1);
        scanf("%d", &items[i].values);
    }
}

void knapsack(Item items[], int capacity, int index, int current_weight, int current_value, int *max_value, int num_items) {
    if (index == num_items) { // Check if all items have been considered
        if (current_value > *max_value) { // Update max_value if current solution is better
            *max_value = current_value;
        }
        return;
    }

    if (current_weight + items[index].weights <= capacity) {
        // Include current item if it doesn't exceed capacity
        current_weight += items[index].weights;
        current_value += items[index].values;
        knapsack(items, capacity, index + 1, current_weight, current_value, max_value, num_items);
        current_weight -= items[index].weights; // Backtrack
        current_value -= items[index].values; // Backtrack
    }

    // Explore without including current item
    knapsack(items, capacity, index + 1, current_weight, current_value, max_value, num_items);
}

int main() {
    srand(time(NULL)); // Initialize random number generator
    int num_items = 0;

    printf("Enter the number of items: ");
    scanf("%d", &num_items);

    Item items[num_items];
    int capacity;

    for (int i = 0; i < NUM_TESTS; i++) {
        getData(items, &capacity, num_items);

        int max_value = 0;
        knapsack(items, capacity, 0, 0, 0, &max_value, num_items);

        printf("\nTest %d: Capacity: %d, Max Value: %d\n", i + 1, capacity, max_value);
        for (int j = 0; j < num_items; j++) {
            printf("Item %d: Value: %d, Weight: %d\n", j + 1, items[j].values, items[j].weights);
        }
        printf("\n");
    }

    return 0;
}

