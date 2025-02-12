#include <stdio.h>
#include <limits.h>

#define V 5 // Number of vertices

// Function to find the vertex with the minimum key value
int minKey(int key[], int selected[]) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < V; v++)
        if (!selected[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }

    return minIndex;
}

// Function to print the MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge   Weight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d    %d\n", parent[i], i, graph[i][parent[i]]);
}

// Prim's algorithm function
void primMST(int graph[V][V]) {
    int parent[V];    // Stores the MST
    int key[V];       // Key values to pick the minimum edge
    int selected[V];  // To represent set of vertices included in MST

    // Initialize all keys as INFINITE and selected[] as false
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        selected[i] = 0;
    }

    // Start from the first vertex
    key[0] = 0;
    parent[0] = -1; // First node is always the root of MST

    // Construct the MST
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, selected);
        selected[u] = 1; // Include u in MST

        // Update key values and parent index
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !selected[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph);
}

// Main function
int main() {
    // Example graph as an adjacency matrix
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    primMST(graph);

    return 0;
}
