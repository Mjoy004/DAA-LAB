#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct Item {
    int weight;
    int value;
    double ratio;  // Value-to-weight ratio
};

// Comparison function for sorting items in descending order of value/weight ratio
int compare(const void* a, const void* b) {
    double r1 = ((struct Item*)a)->ratio;
    double r2 = ((struct Item*)b)->ratio;
    return (r2 > r1) - (r2 < r1);  // Sort in descending order
}

// Function to solve the fractional knapsack problem
double fractionalKnapsack(int capacity, struct Item items[], int n) {
    // Sort items by value-to-weight ratio
    qsort(items, n, sizeof(struct Item), compare);

    double totalValue = 0.0; // Total value in the knapsack

    for (int i = 0; i < n; i++) {
        // If the full item can be taken
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
        // Take a fraction of the remaining item
        else {
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break; // Knapsack is full
        }
    }
    return totalValue;
}

// Main function
int main() {
    struct Item items[] = {
        {10, 60, 0},  // weight, value
        {20, 100, 0},
        {30, 120, 0}
    };
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 50;

    // Calculate value-to-weight ratio
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    double maxValue = fractionalKnapsack(capacity, items, n);
    printf("Maximum value in Knapsack = %.2f\n", maxValue);

    return 0;
}
