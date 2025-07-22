#include <stdio.h>
// A simple integer min function for two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    int size = 2 * n - 1;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // Calculate distances from all four borders
            int dist_top = row;
            int dist_bottom = size - 1 - row;
            int dist_left = col;
            int dist_right = size - 1 - col;

            // Find the minimum of these distances
            int min_dist_rc = min(min(dist_top, dist_bottom), min(dist_left, dist_right));

            // The value at (row, col) is n minus this minimum distance
            int value_to_print = n - min_dist_rc;

            printf("%d ", value_to_print);
        }
        printf("\n"); // Newline after each row
    }

    return 0;
}
