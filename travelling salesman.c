#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define N 4 // Number of cities

int minCost = INT_MAX; // Store the minimum cost
int bestPath[N]; // Store the best path

// Function to print the best path
void printPath(int path[]) {
    printf("Optimal Path: ");
    for (int i = 0; i < N; i++)
        printf("%d -> ", path[i]);
    printf("%d\n", path[0]); // Returning to the starting city
    printf("Minimum Cost: %d\n", minCost);
}

// Function to find the shortest route using backtracking
void tsp(int graph[N][N], int path[], bool visited[], int pos, int cost, int count) {
    if (count == N && graph[pos][0]) { // If all cities visited & returning path exists
        cost += graph[pos][0]; // Add cost to return to start
        if (cost < minCost) {  // Update minimum cost and best path
            minCost = cost;
            for (int i = 0; i < N; i++)
                bestPath[i] = path[i];
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i] && graph[pos][i]) { // If not visited and edge exists
            visited[i] = true;
            path[count] = i;
            tsp(graph, path, visited, i, cost + graph[pos][i], count + 1);
            visited[i] = false; // Backtrack
        }
    }
}

int main() {
    int graph[N][N] = { 
        { 0, 10, 15, 20 }, 
        { 10, 0, 35, 25 }, 
        { 15, 35, 0, 30 }, 
        { 20, 25, 30, 0 } 
    };

    int path[N];
    bool visited[N] = { false };

    visited[0] = true; // Start from city 0
    path[0] = 0;

    tsp(graph, path, visited, 0, 0, 1); // Start TSP from city 0

    printPath(bestPath); // Print the best path and cost

    return 0;
}
