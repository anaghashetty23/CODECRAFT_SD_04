#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

// Check if placing num at grid[row][col] is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// Solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool emptyFound = false;

    // Find the first empty cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                emptyFound = true;
                goto foundEmpty; 
            }
        }
    }
foundEmpty:

    if (!emptyFound) 
        return true; 
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0; 
        }
    }

    return false; 
}

int main() {
    int grid[N][N];

    printf("Enter the Sudoku puzzle (use 0 for empty cells):\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &grid[i][j]);

    if (solveSudoku(grid)) {
        printf("\nSolved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("No solution exists for the given puzzle.\n");
    }

    return 0;
}