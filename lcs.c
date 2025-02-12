#include <stdio.h>
#include <string.h>

// Function to find LCS length and print the sequence
void LCS(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[m + 1][n + 1];

    // Build LCS table using Dynamic Programming
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    // Length of LCS
    int lcs_length = dp[m][n];
    printf("Length of LCS: %d\n", lcs_length);

    // Reconstruct LCS
    char lcs[lcs_length + 1];
    lcs[lcs_length] = '\0'; // Null-terminate the LCS string
    int i = m, j = n, index = lcs_length - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index--] = X[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS: %s\n", lcs);
}

// Main function
int main() {
    char X[] = "ACDBE";
    char Y[] = "ABCDE";

    LCS(X, Y);

    return 0;
}
