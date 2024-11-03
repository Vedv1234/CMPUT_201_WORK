/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: This is my header file for Conway's Game of Life implementation. I've declared the main functions
needed to calculate the next state of cells and advance the game to the next generation. This was a fascinating
project that helped me understand cellular automata and state management in C.
*/

#include <stdio.h>   // I need this for input/output operations
#include <stdlib.h>  // This helps me with memory management

// This function will determine the next state of a single cell
void nextCellState(int w, int h, const int (*grid)[w], int r, int c, int *state);

// This function will update the entire grid to its next generation
void nextGeneration(int w, int h, int (*grid)[w]);