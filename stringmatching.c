#include <stdio.h>
#include <string.h>

// Brute Force String Matching Algorithm
void bruteForceSearch(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    printf("Pattern found at positions: ");
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) 
                break;
        }
        if (j == m) 
            printf("%d ", i);
    }
    printf("\n");
}

int main() {
    char text[] = "ABABABACABA";
    char pattern[] = "ABA";

    bruteForceSearch(text, pattern);

    return 0;
}
