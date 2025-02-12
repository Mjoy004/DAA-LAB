#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Structure to represent a subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Find function using path compression
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union function using rank
void unionSets(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Compare function for sorting edges by weight
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Kruskal’s Algorithm to find MST
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // Stores the MST edges
    int e = 0; // Edge count in MST
    int i = 0; // Edge index

    // Step 1: Sort edges by weight
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    // Step 2: Create V subsets with single elements
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 3: Pick the smallest edge and check for cycles
    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = graph->edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge doesn't form a cycle, include it in MST
        if (x != y) {
            result[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    // Print the MST
    printf("Minimum Spanning Tree (MST) Edges:\n");
    for (i = 0; i < e; i++)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    
    free(subsets);
}

// Main function
int main() {
    int V = 4, E = 5; // Number of vertices and edges
    struct Graph* graph = createGraph(V, E);

    // Adding edges (source, destination, weight)
    graph->edges[0] = (struct Edge){0, 1, 10};
    graph->edges[1] = (struct Edge){0, 2, 6};
    graph->edges[2] = (struct Edge){0, 3, 5};
    graph->edges[3] = (struct Edge){1, 3, 15};
    graph->edges[4] = (struct Edge){2, 3, 4};

    // Run Kruskal's algorithm
    kruskalMST(graph);

    free(graph->edges);
    free(graph);
    return 0;
}
