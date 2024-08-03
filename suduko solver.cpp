#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 9; // Size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(const vector<vector<int> >& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed at grid[row][col]
bool isSafe(const vector<vector<int> >& grid, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < SIZE; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < SIZE; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int> >& grid) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) { // Empty cell found
                for (int num = 1; num <= SIZE; ++num) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;

                        // Recursively try to solve the rest of the grid
                        if (solveSudoku(grid)) {
                            return true;
                        }

                        // If no solution found, reset the cell
                        grid[row][col] = 0;
                    }
                }
                return false; // Trigger backtracking
            }
        }
    }
    return true; // Puzzle solved
}

int main() {
    vector<vector<int> > grid(SIZE, vector<int>(SIZE, 0));

    // Example input grid (0 represents empty cells)
    cout << "Enter the Sudoku puzzle (9x9 grid, use 0 for empty cells):" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku grid:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}

