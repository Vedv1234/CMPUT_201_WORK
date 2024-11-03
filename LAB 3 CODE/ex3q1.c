/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: This is my implementation of a fractal generator that can create both 
Mandelbrot and Julia sets. I've used complex number arithmetic to generate these fascinating 
mathematical patterns. My program takes user input to determine which type of fractal to generate
and various parameters like iteration count and zoom factors. The output is in PPM format, which
creates a visual representation of the fractals using different colors based on how quickly points
escape the set.
*/

// I'm including my header file which contains the function prototypes and constants
#include "ex3q1.h"

// I needed to define this again because I was having some issues reading it from the header
#define IMG_HEIGHT 720

// I'm creating a structure to handle complex numbers - makes my life easier when doing calculations
typedef struct {
    double real;    // This represents the real part (a) in a + bi
    double imag;    // This represents the imaginary part (b) in a + bi
} Complex;

// My function to add two complex numbers together
Complex add_complex(Complex a, Complex b) {
    return (Complex){a.real + b.real, a.imag + b.imag};  // Adding real and imaginary parts separately
}

// My function to multiply complex numbers using the (ac-bd) + i(ad+bc) formula
Complex multiply_complex(Complex a, Complex b) {
    return (Complex){
        a.real * b.real - a.imag * b.imag,  // Real part: ac - bd
        a.real * b.imag + a.imag * b.real    // Imaginary part: ad + bc
    };
}

// I'm calculating the absolute value squared of a complex number (a² + b²)
double abs_complex_squared(Complex z) {
    return z.real * z.real + z.imag * z.imag;  // I don't need sqrt since I'm comparing to 4.0
}

// My iterative implementation of the fractal sequence calculator
int iterativeFractalSeq(double ReC, double ImC, double ReZ, double ImZ, int maxIterations) {
    Complex z = {ReZ, ImZ};  // Initial z value
    Complex c = {ReC, ImC};  // Constant c value
    
    for (int i = 0; i < maxIterations; i++) {
        // If magnitude exceeds 2 (which means squared exceeds 4), the sequence escapes
        if (abs_complex_squared(z) > 4.0) {
            return i;
        }
        z = add_complex(multiply_complex(z, z), c);  // z = z² + c
    }
    return maxIterations;  // If we get here, the point is in the set
}

// My main function to generate either Mandelbrot or Julia set
void generate_fractal(int fractal_type, int maxIterations, double centerX, double centerY, double zoomFactor) {
    double planeW, planeH;
    double ReC, ImC;
    
    // Setting up dimensions based on fractal type
    if (fractal_type == 0) {  // For Mandelbrot set
        planeW = 3.0 / zoomFactor;
        planeH = 2.0 / zoomFactor;
    } else {  // For Julia set
        planeW = 4.0;
        planeH = 3.0;
        ReC = centerX;  // In Julia set, these values stay constant
        ImC = centerY;
    }

    // Calculating image width to maintain aspect ratio
    int imgW = (int)((double)IMG_HEIGHT * planeW / planeH + 0.5);

    // Writing PPM header
    printf("P3\n%d %d\n255\n", imgW, IMG_HEIGHT);
    
    // Looping through each pixel in my image
    for (int y = 0; y < IMG_HEIGHT; y++) {
        for (int x = 0; x < imgW; x++) {
            // Converting pixel coordinates to complex plane coordinates
            double real = (x / (double)(imgW - 1)) * planeW - planeW / 2.0;
            double imag = ((IMG_HEIGHT - 1 - y) / (double)(IMG_HEIGHT - 1)) * planeH - planeH / 2.0;

            // Different handling for Mandelbrot vs Julia sets
            if (fractal_type == 0) {  // Mandelbrot
                ReC = real + centerX;
                ImC = imag + centerY;
                real = imag = 0;  // Starting z at 0+0i for Mandelbrot
            }

            // Calculating iterations for this point
            int iterations = iterativeFractalSeq(ReC, ImC, real, imag, maxIterations);

            // Coloring the pixel based on iteration count
            if (iterations == maxIterations) {
                printf("255 255 255 ");  // Points in the set are white
            } else {
                // Creating a smooth color gradient for points outside the set
                double alpha = (double)iterations / maxIterations;
                int g = (int)(alpha * 255);
                int b = (int)(alpha * 153);
                printf("0 %d %d ", g, b);
            }
        }
        printf("\n");  // New line after each row
    }
}

// My main function where I handle user input and error checking
int main(void) {
    int fractal_type, maxIterations;
    double param1, param2, param3;

    // Reading basic parameters with error checking
    if (scanf("%d %d", &fractal_type, &maxIterations) != 2) {
        printf("Error reading fractal type and max iterations\n");
        return 1;
    }

    // Validating fractal type
    if (fractal_type != 0 && fractal_type != 1) {
        printf("Invalid fractal type\n");
        return 1;
    }

    // Making sure iterations are within reasonable bounds
    if (maxIterations <= 0 || maxIterations > 1000000) {
        printf("Invalid maximum iterations\n");
        return 1;
    }

    // Reading parameters specific to each fractal type
    if (fractal_type == 0) {  // Mandelbrot parameters
        if (scanf("%lf %lf %lf", &param1, &param2, &param3) != 3) {
            printf("Error reading Mandelbrot parameters\n");
            return 1;
        }
        if (param3 <= 0) {  // Checking zoom factor
            printf("Invalid zoom factor\n");
            return 1;
        }
        generate_fractal(fractal_type, maxIterations, param1, param2, param3);
    } else {  // Julia parameters
        if (scanf("%lf %lf", &param1, &param2) != 2) {
            printf("Error reading Julia parameters\n");
            return 1;
        }
        generate_fractal(fractal_type, maxIterations, param1, param2, 0);
    }

    return 0;
}