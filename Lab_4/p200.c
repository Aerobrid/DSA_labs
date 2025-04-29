#include <stdio.h>          // for input/output like printf() function
#include <stdlib.h>         // for memory functions like malloc() and free()

// recursive depth-first-search to explore the 2d binary grid and mark visited land
void dfs(char** grid, int gridSize, int* gridColSize, int r, int c) {
    if (r < 0 || c < 0 || r >= gridSize || c >= gridColSize[r] || grid[r][c] == '0')
        return;

    grid[r][c] = '0';                                                       // mark the space as visited by turning it into a 0 (land to water)

    // recursively explore the grid in all 4 directions to visit connected land
    dfs(grid, gridSize, gridColSize, r + 1, c);                             // down
    dfs(grid, gridSize, gridColSize, r - 1, c);                             // up
    dfs(grid, gridSize, gridColSize, r, c + 1);                             // right
    dfs(grid, gridSize, gridColSize, r, c - 1);                             // left
}

// function to actually count the # of islands
int numIslands(char** grid, int gridSize, int* gridColSize) {
    // base case
    if (gridSize == 0) return 0;

    int count = 0;
    // iterate through grid, if 1 is found:
    // it is a new island so increment count (# of islands to be returned)
    // call dfs function to mark the entire island as visited
    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < gridColSize[r]; c++) {
            if (grid[r][c] == '1') {
                count++;
                dfs(grid, gridSize, gridColSize, r, c);
            }
        }
    }
    return count;
}

// to test the code
int main() {

    int rows = 4, cols = 5;

    // Create grid (an array of string literals)
    // cannot be modified since stored in read-only memory (typically in data segment)
    // if you try to modify the grid it will lead to errors, so we cannot use this with our dfs function (remember it can change value to '0')
    char* raw_grid[] = {
        "11000",
        "11000",
        "00100",
        "00011"
    };

    // to modify raw_grid, copy it and allocate it space
    // if you know your grid dimensions everytime, implementing program to use static 2d grids is a better choice
    // dynamically allocate a grid to point to an array of strings (char* types)
    char** grid = (char**)malloc(rows * sizeof(char*));
    // dynamically allocate space to all rows within grid (since we need space for the strings)
    for (int i = 0; i < rows; i++) {
        grid[i] = (char*)malloc((cols + 1) * sizeof(char));                 // +1 for null-terminator, even if not used
        // for each row now with mallocated space, copy over the string from raw_grid
        for (int j = 0; j < cols; j++) {
            grid[i][j] = raw_grid[i][j];
        }
    }

    // to tell numIslands() how many columns each row has
    // this is only needed because C doesn’t store that metadata automatically
    int gridColSize[] = {cols, cols, cols, cols};

    // Use function
    int result = numIslands(grid, rows, gridColSize);
    printf("Number of islands: %d\n", result);  

    // Free the memory for each row allocated on heap
    // then free the memory allocated on heap for grid itself
    for (int i = 0; i < rows; i++) 
        free(grid[i]);
    free(grid);

    return 0;
}
