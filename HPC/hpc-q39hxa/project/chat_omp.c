#include <stdio.h>
#include <omp.h>

#define N 15  // Maximum number of items
#define W 75  // Maximum knapsack capacity

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[N + 1][W + 1];

    // Build table K[][] in parallel using OpenMP
    #pragma omp parallel for private(i, w) shared(K)
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

int main() {
    int val[] = {100, 60, 120, 89, 67, 90, 2, 170, 200, 300, 320, 88, 55, 32};
    int wt[] = {20, 10, 30, 40, 50, 44, 22, 23, 12, 9, 0, 1, 3, 4};
    int n = sizeof(val) / sizeof(val[0]);

    // Set the number of threads for OpenMP (optional)
    omp_set_num_threads(4);

    printf("\nValue = %d", knapsack(W, wt, val, n));
    return 0;
}
