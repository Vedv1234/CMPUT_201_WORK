/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: This is my implementation of Conway's Game of Life. I've created functions to calculate
the next state of cells and advance the game state. The program reads initial cell positions and number of
generations to simulate, then shows the final state. Working with wraparound grid edges was particularly
interesting, as it made me think about modular arithmetic in a practical context.
*/

#include "ex4q2.h"  // Including my header file

// This function calculates the next state of a single cell
void nextCellState(int w, int h, const int (*grid)[w], int r, int c, int *state) {
    int liveNeighbors = 0;
    
    // I'm checking all 8 neighboring cells
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;  // Skip the cell itself
            
            // I use modulo to wrap around the grid edges
            int nr = (r + dr + h) % h;
            int nc = (c + dc + w) % w;
            
            // Count live neighbors
            liveNeighbors += *(*(grid + nr) + nc);
        }
    }
    
    // Get current cell's state
    int currentState = *(*(grid + r) + c);
    
    // Apply Conway's Game of Life rules
    if (currentState == 1) {
        // Live cell survives if it has 2 or 3 neighbors
        *state = (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
    } else {
        // Dead cell becomes alive if it has exactly 3 neighbors
        *state = (liveNeighbors == 3) ? 1 : 0;
    }
}

// This function advances the entire grid to the next generation
void nextGeneration(int w, int h, int (*grid)[w]) {
    // I need a temporary grid to store the next generation
    int newGrid[h][w];
    
    // Calculate new state for each cell
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            int state;
            nextCellState(w, h, grid, r, c, &state);
            *(*(newGrid + r) + c) = state;
        }
    }
    
    // Copy the new generation back to the original grid
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            *(*(grid + r) + c) = *(*(newGrid + r) + c);
        }
    }
}

// This function displays my grid
void printGrid(int w, int h, const int (*grid)[w]) {
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            // I use # for live cells and space for dead ones
            printf("%c", *(*(grid + r) + c) ? '#' : ' ');
        }
        printf("\n");
    }
}

int main() {
    int w, h, generations;
    // Reading grid dimensions and number of generations
    if (scanf("%d %d %d", &w, &h, &generations) != 3 || w <= 0 || h <= 0 || generations < 0) {
        return 1;  // Exit if input is invalid
    }
    
    // Allocating memory for my grid
    int (*grid)[w] = calloc(h, sizeof(*grid));
    if (grid == NULL) {
        return 1;  // Exit if memory allocation fails
    }
    
    // Reading initial live cell positions
    int r, c;
    while (scanf("%d", &r) == 1 && r != -1) {
        if (scanf("%d", &c) != 1 || r < 0 || r >= h || c < 0 || c >= w) {
            free(grid);
            return 1;  // Exit if coordinates are invalid
        }
        *(*(grid + r) + c) = 1;  // Mark cell as alive
    }
    
    // Run the simulation for specified number of generations
    for (int gen = 0; gen < generations; gen++) {
        nextGeneration(w, h, grid);
    }
    
    // Display the final state
    printGrid(w, h, grid);
    
    // Clean up my allocated memory
    free(grid);
    return 0;
}