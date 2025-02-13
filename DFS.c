#include <stdio.h>
#include <stdbool.h>

#define MAX 10 // Maximum number of vertices

int stack[MAX], top = -1;

// Function to push an element onto the stack
void push(int value) {
    if (top == MAX - 1) return; // Stack is full
    stack[++top] = value;
}

// Function to pop an element from the stack
int pop() {
    if (top == -1) return -1; // Stack is empty
    return stack[top--];
}

// Function to perform DFS
void dfs(int graph[MAX][MAX], int n, int start) {
    bool visited[MAX] = {false};

    printf("DFS Traversal: ");
    push(start);

    while (top != -1) {
        int current = pop();
        
        if (!visited[current]) {
            printf("%d ", current);
            visited[current] = true;
        }

        for (int i = n - 1; i >= 0; i--) {
            if (graph[current][i] && !visited[i]) {
                push(i);
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

    dfs(graph, n, start);

    return 0;
}
