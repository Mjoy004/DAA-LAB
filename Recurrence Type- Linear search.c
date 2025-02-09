#include <stdio.h>

// Recursive Linear Search function
int linearSearch(int arr[], int size, int key) {
    if (size == 0) 
        return -1; // Base case: element not found
    if (arr[size - 1] == key) 
        return size - 1; // Found at index size - 1
    return linearSearch(arr, size - 1, key); // Recur for the rest of the array
}

// Driver code
int main() {
    int arr[] = {3, 5, 2, 9, 8, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 9;

    int result = linearSearch(arr, size, key);
    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");

    return 0;
}
