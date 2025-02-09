#include <stdio.h>

// Recursive Binary Search function
int binarySearchRecursive(int arr[], int left, int right, int key) {
    if (left > right)
        return -1; // Base case: not found

    int mid = left + (right - left) / 2;

    if (arr[mid] == key)
        return mid; // Found at mid
    else if (arr[mid] > key)
        return binarySearchRecursive(arr, left, mid - 1, key); // Search left half
    else
        return binarySearchRecursive(arr, mid + 1, right, key); // Search right half
}

// Iterative Binary Search function
int binarySearchIterative(int arr[], int size, int key) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] > key)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1; // Not found
}

// Function to print result
void printResult(int result) {
    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");
}

// Driver code
int main() {
    int arr[] = {2, 3, 4, 10, 14, 18, 20};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 10;

    printf("Recursive Binary Search:\n");
    int resultRecursive = binarySearchRecursive(arr, 0, size - 1, key);
    printResult(resultRecursive);

    printf("Iterative Binary Search:\n");
    int resultIterative = binarySearchIterative(arr, size, key);
    printResult(resultIterative);

    return 0;
}
