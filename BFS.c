#include <stdio.h>
#include <stdbool.h>

#define MAX 10 // Maximum number of vertices

int queue[MAX], front = -1, rear = -1;

// Function to enqueue an element
void enqueue(int value) {
    if (rear == MAX - 1) return; // Queue is full
    if (front == -1) front = 0;
    queue[++rear] = value;
}

// Function to dequeue an element
int dequeue() {
    if (front > rear || front == -1) return -1; // Queue is empty
    return queue[front++];
}

// Function to perform BFS
void bfs(int graph[MAX][MAX], int n, int start) {
    bool visited[MAX] = {false};

    printf("BFS Traversal: ");
    enqueue(start);
    visited[start] = true;

    while (front <= rear) {
        int current = dequeue();
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                enqueue(i);
                visited[i] = true;
            }
        }
    }
    printf("\n");
}

int main() {
    int graph[MAX][MAX] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    int n = 5; // Number of vertices
    int start = 0; // Starting vertex

    bfs(graph, n, start);

    return 0;
}
