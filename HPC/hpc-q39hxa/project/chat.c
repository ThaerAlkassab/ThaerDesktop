#include <stdio.h>

const int N = 15;  // Maximum number of items
const int W = 75;  // Maximum knapsack capacity

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsackUtil(int capacity, int wt[], int val[], int n, int memo[N][W + 1]) {
    if (n == 0 || capacity == 0)
        return 0;

    // If the result is already computed, return it from the memo table
    if (memo[n][capacity] != -1)
        return memo[n][capacity];

    // If the current item's weight exceeds the remaining capacity, skip it
    if (wt[n - 1] > capacity)
        return knapsackUtil(capacity, wt, val, n - 1, memo);

    // Consider two cases: including the current item or excluding it
    int include = val[n - 1] + knapsackUtil(capacity - wt[n - 1], wt, val, n - 1, memo);
    int exclude = knapsackUtil(capacity, wt, val, n - 1, memo);

    // Store the result in the memo table and return it
    memo[n][capacity] = max(include, exclude);
    return memo[n][capacity];
}

int knapsack(int capacity, int wt[], int val[], int n) {
    // Create a memoization table and initialize it with -1
    int memo[N][W + 1];
    int i,j;
    for (i = 0; i <= n; ++i) {
        for (j = 0; j <= W; ++j) {
            memo[i][j] = -1;
        }
    }

    int result = knapsackUtil(capacity, wt, val, n, memo);

    return result;
}

int main() {
    int val[] = {100, 60, 120, 89, 67, 90, 2, 170, 200, 300, 320, 88, 55, 32};
    int wt[] = {20, 10, 30, 40, 50, 44, 22, 23, 12, 9, 0, 1, 3, 4};
    int n = sizeof(val) / sizeof(val[0]);
    printf("\nValue = %d", knapsack(W, wt, val, n));
    return 0;
}
