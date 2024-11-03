/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: This is my implementation of a Minesweeper game board. I've created functions to count mines
around cells and display the game board. It was challenging to work with pointer arithmetic and 2D arrays, but
I managed to get it working well. The program reads board dimensions and mine positions from input and creates
a playable Minesweeper board.
*/

#include "ex4q1.h"  // I'm including my header file with function declarations

// This is my function to count mines around a specific cell
void countMines(int w, int h, const int (*grid)[w], int r, int c, int *count) {
    *count = 0;  // I start with zero mines
    
    // I'm checking all 8 cells around my target cell
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            // Skip the center cell - I only want to count neighbors
            if (dr == 0 && dc == 0) continue;
            
            // Calculate neighbor coordinates
            int nr = r + dr;
            int nc = c + dc;
            
            // I make sure I'm not checking outside my grid bounds
            if (nr >= 0 && nr < h && nc >= 0 && nc < w) {
                // If I find a mine (value -1), increment my counter
                if (*(*(grid + nr) + nc) == -1) {
                    (*count)++;
                }
            }
        }
    }
}

// This function prints my Minesweeper board with a nice grid layout
void printBoard(int w, int h, const int (*grid)[w]) {
    // I'm going through each row of my board
    for (int r = 0; r < h; r++) {
        // Print the top border of each row
        printf("+");
        for (int c = 0; c < w; c++) {
            printf("---+");
        }
        printf("\n|");
        
        // Now I print the contents of each cell in this row
        for (int c = 0; c < w; c++) {
            int cellValue = *(*(grid + r) + c);
            
            if (cellValue == -1) {
                // If it's a mine, I show an X
                printf(" X |");
            } else {
                // For empty cells, I count nearby mines
                int count = 0;
                countMines(w, h, grid, r, c, &count);
                
                // Print either a blank space or the number of nearby mines
                if (count == 0) {
                    printf("   |");
                } else {
                    printf(" %d |", count);
                }
            }
        }
        printf("\n");
    }
    
    // I need to print the bottom border of my grid
    printf("+");
    for (int c = 0; c < w; c++) {
        printf("---+");
    }
    printf("\n");
}

int main() {
    int w, h;
    // I'm reading the width and height of my board
    if (scanf("%d %d", &w, &h) != 2 || w <= 0 || h <= 0) {
        return 1;  // Exit if I get invalid input
    }
    
    // I'm allocating memory for my grid
    int (*grid)[w] = calloc(h, sizeof(*grid));
    if (grid == NULL) {
        return 1;  // Exit if memory allocation fails
    }
    
    // Now I'm reading mine coordinates until I get -1
    int r, c;
    while (scanf("%d", &r) == 1 && r != -1) {
        if (scanf("%d", &c) != 1 || r < 0 || r >= h || c < 0 || c >= w) {
            free(grid);
            return 1;  // Exit if coordinates are invalid
        }
        // Place a mine at the specified location
        *(*(grid + r) + c) = -1;
    }
    
    // Display my completed Minesweeper board
    printBoard(w, h, grid);
    
    // Clean up my allocated memory
    free(grid);
    return 0;
}