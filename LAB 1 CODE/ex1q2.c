/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)

Functionality of code:
In this program, I created a year-to-days converter that takes into account leap years. What makes it interesting is how I handle the special rules for leap years - like the century rule and the 400-year rule. I initially tried a different approach with direct division, but after some research and help from Stack Overflow, I implemented a more elegant solution using a for loop to check each year individually.
*/

#include <stdio.h>
#include <locale.h>

int main (void) 
{
        // I'm setting up the locale for proper formatting of large numbers with commas
        setlocale(LC_ALL, "");
        
        // Declaring my variables for storing years, days and leap year count
        int UserYears, NumberDays, leap_years;
        UserYears = 0; // Initialize user input to 0
        NumberDays = 0; // Initialize day count to 0

        // Prompting the user for input
        printf("Enter number of days since Jan 1, 2001: \n");

        // I'm checking if the input is valid - must be a number
        if (scanf("%d", &UserYears) != 1) 
        {
                printf("Error: Invalid Input\n");
                return 1; // I exit with error code 1 if input is invalid
        }

        // This is my main loop that checks each year from 2001 to the target year
        for (int year = 2001; year < 2001 + UserYears; year = year + 1) 
        {
                // Here's my leap year check with all the special rules:
                // 1. Must be divisible by 4 AND not divisible by 100, OR
                // 2. Must be divisible by 400
                if (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) 
                {
                        NumberDays += 366; // Add 366 days for leap years
                        leap_years += 1; // Keep track of how many leap years we've found
                }
                else 
                { 
                        NumberDays += 365; // Regular years get 365 days
                }
        }

        // Finally, I print the total days with comma formatting for readability
        printf("%'d Days \n", NumberDays);
        return 0;
}