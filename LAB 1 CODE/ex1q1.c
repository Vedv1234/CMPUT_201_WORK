/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)

Functionality of code:
This program is my implementation of an orbital calculator that helps determine satellite orbits. I wrote it to calculate either the velocity, radius, or time period of a satellite's orbit when given the other two parameters. What makes it special is that it can also identify if the orbital characteristics match known objects like Earth, Moon, or the ISS. I used mathematical formulas and range comparisons to make these determinations.
*/

#include <stdio.h>

int main(void) {
    // I'm declaring my variables for orbital calculations and counter variables for matching characteristics
    int Velocity, Radius, Time, earth_match_count, moon_match_count, iss_match_count;
    
    // I initialize my match counters to zero - these will help me track how many characteristics match each celestial body
    earth_match_count=0;
    moon_match_count=0;
    iss_match_count=0;
    
    // I'm using 3.14 as an approximation for Pi in my orbital calculations
    float Pi = 3.14;

    // Here I'm getting the input values from the user for my calculations
    printf("Enter an orbital speed (km/h):\n");
    scanf("%d", &Velocity);
    printf("Enter an orbital radius (km):\n");
    scanf("%d", &Radius);
    printf("Enter an orbital time (h):\n");
    scanf("%d", &Time);

    // This section handles my calculations based on which value is unknown (marked as -1)
    if (Velocity == -1) { // If velocity is unknown, I calculate it using the orbital circumference formula
        Velocity = (2 * Pi * Radius) / Time;
        printf("A satellite in orbit at %.2f km and completing an orbit in %.2f hours will be moving at: %.2f km/h\n", (float)Radius, (float)Time, (float)Velocity);
    } else if (Radius == -1) { // If radius is unknown, I solve the orbital formula for radius
        Radius = (Velocity * Time) / (2 * Pi);
        printf("A satellite in orbit moving at %.2f km/h and completing an orbit in %.2f hours will be at a radius of: %.2f km\n", (float)Velocity, (float)Time, (float)Radius);
    } else if (Time == -1) { // If time period is unknown, I calculate it using the circumference and velocity
        Time = (2 * Pi * Radius) / Velocity;
        printf("A satellite in orbit at %.2f km and moving at %.2f km/h will complete an orbit in: %.2f h\n", (float)Radius, (float)Velocity, (float)Time);
    }

    // Now I check if the values match Earth's characteristics
    if (148000 <= Radius && Radius <= 151000) {
        printf("radius is close to Earth\n");
        earth_match_count= earth_match_count+1;
    }
    if (8700 <= Time && Time <= 8800) {
        printf("period is close to Earth\n");
        earth_match_count=earth_match_count+1;
    }
    if (100000 <= Velocity && Velocity <= 110000) {
        printf("speed is close to Earth\n");
        earth_match_count=earth_match_count+1;
    }

    // I determine if it's likely Earth based on how many characteristics match
    if (earth_match_count == 3) {
        printf("This object is likely Earth\n");
    } else if (earth_match_count == 2) {
        printf("This object is likely Earth\n");
    }
    else {printf("This object is likely not Earth\n"); }

    // Similar checks for the Moon's characteristics
    if (360000 <= Radius && Radius <= 400000) {
        printf("radius is close to Moon\n");
        moon_match_count=moon_match_count+1;
    }
    if (624 <= Time && Time <= 672) {
        printf("period is close to Moon\n");
        moon_match_count=moon_match_count+1;
    }
    if (3600 <= Velocity && Velocity <= 3800) {
        printf("speed is close to Moon\n");
        moon_match_count=moon_match_count+1;
    }

    // Determining if it's likely the Moon based on matches
    if (moon_match_count == 3) {
        printf("This object is likely Moon\n");
    } else if (moon_match_count == 2) {
        printf("This object is likely Moon\n");
    }
    else {printf("However, this is likely not International Space Station\n"); }

    // Checking against ISS characteristics
    if (6700 <= Radius && Radius <= 6900) {
        printf("radius is close to International Space Station\n");
        iss_match_count=iss_match_count+1;
    }
    if (1.4 <= Time && Time <= 1.6) {
        printf("period is close to International Space Station\n");
        iss_match_count=iss_match_count+1;
    }
    if (3600 <= Velocity && Velocity <= 3800) {
        printf("speed is close to International Space Station\n");
        iss_match_count=iss_match_count+1;
    }

    // Making final determination about ISS likelihood
    if (iss_match_count == 3) {
        printf("This object is likely International Space Station\n");
    } else if (iss_match_count == 2) {
        printf("This object is likely similar to International Space Station\n");
    } else if (iss_match_count == 1) {
        printf("However, this is likely not International Space Station\n");
    }

    return 0;
}