#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

// Function to find the point with the lowest y-coordinate
int bottomMostPoint(Point points[], int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minIndex].y ||
            (points[i].y == points[minIndex].y && points[i].x < points[minIndex].x)) {
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to swap two points
void swap(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

// Function to compute cross product to check orientation
int orientation(Point a, Point b, Point c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // 1 = Clockwise, 2 = Counterclockwise
}

// Comparison function for sorting by polar angle
int compare(const void *p1, const void *p2) {
    Point *a = (Point *)p1;
    Point *b = (Point *)p2;

    Point pivot = *(Point *)p1;  // The pivot point
    int orient = orientation(pivot, *a, *b);

    if (orient == 0) {
        return ((pivot.x - a->x) * (pivot.x - a->x) + 
                (pivot.y - a->y) * (pivot.y - a->y)) -
               ((pivot.x - b->x) * (pivot.x - b->x) + 
                (pivot.y - b->y) * (pivot.y - b->y));
    }
    return (orient == 2) ? -1 : 1;
}

// Function to find the convex hull
void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        return;
    }

    // Find the bottom-most point
    int minIndex = bottomMostPoint(points, n);
    swap(&points[0], &points[minIndex]);

    // Sort points by polar angle with the base point
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Stack for hull points
    Point hull[n];
    int hullSize = 0;

    // Process points
    for (int i = 0; i < n; i++) {
        while (hullSize >= 2 && orientation(hull[hullSize - 2], hull[hullSize - 1], points[i]) != 2) {
            hullSize--;  // Remove last point (right turn)
        }
        hull[hullSize++] = points[i];
    }

    // Print the convex hull
    printf("Convex Hull Points:\n");
    for (int i = 0; i < hullSize; i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }
}

// Driver code
int main() {
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);

    return 0;
}
