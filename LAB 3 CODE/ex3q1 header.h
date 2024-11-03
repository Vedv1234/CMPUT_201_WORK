/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: This is my header file for the fractal generation program. I've defined the key
function prototype and the image height constant here. I kept this file minimal since most of the 
implementation details are in the main C file. The header helps me organize my code better by 
separating declarations from implementations.
*/

// I'm including these standard libraries for basic input/output and memory allocation
#include <stdio.h>
#include <stdlib.h>

// I've defined my image height as a constant of 720 pixels - this will be used throughout my program
int imageH = 720;

// Here's my function prototype for the recursive version of the fractal sequence calculator
// I'm not using this in my current implementation, but kept it for future reference
int recursiveFractalSeq(double ReC, double ImC, double ReZ, double ImZ, int depth, int maxIterations);