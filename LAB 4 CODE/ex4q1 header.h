/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: This is my header file for the Minesweeper game implementation. I've declared the main function 
that counts mines around a cell in the grid. This project was really interesting as it helped me understand 
2D array manipulation and pointer arithmetic in C.
*/

#include <stdio.h>   // I'm including this for input/output operations
#include <stdlib.h>  // I need this for memory allocation functions

// Here I'm declaring my function that counts mines around a cell
// w and h are width and height, grid is my 2D array, r and c are row and column coordinates
// count is where I'll store how many mines I found
void countMines(int w, int h, const int (*grid)[w], int r, int c, int *count);