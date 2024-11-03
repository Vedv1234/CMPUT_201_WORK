/*
Author: Ved Vyas
Co-Author / Exercise provided by: / Resources provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: 
In this program, I'm building a retail management system that helps track product sales and calculate profits. 
I first take in product details like IDs, sale prices, and retail prices. Then I've implemented a system 
where I can continuously add sales for different products and view sales reports. When generating reports, 
I calculate important metrics like profit margins and sort everything by gross margin percentage. I've also 
added error handling for invalid product IDs to make the program more robust.
*/

#include <stdio.h> // I'm including the standard input/output library that I'll need for reading and printing

int main(void) {
    int num_products, index, code;  // Here I'm declaring my main variables that I'll use throughout the program
    
    // I'm reading the total number of products first - this helps me allocate my arrays properly
    scanf("%d", &num_products);
    
    // I'm creating all the arrays I need to store my product information
    int product_id[num_products];       // This will store all my product IDs
    int sale_price[num_products];       // Here I'll keep track of what I paid for each product
    int retail_price[num_products];     // This stores what I'm selling each product for
    int sales_account[num_products];    // I'll use this to count how many times each product is sold
    
    // Now I'm reading in all the initial product information
    for (index = 0; index < num_products; index+=1) {
        sales_account[index] = 0;  // I'm initializing each product's sales count to 0
        // Reading in the product details - ID, what I paid, and what I'm selling it for
        scanf("%d %d %d", &product_id[index], &sale_price[index], &retail_price[index]);
    }
    
    // I created this function to search for products by their ID
    int binary_search(int product_id[], int size, int code) {
        for (int i = 0; i < size; i+=1) {
            if (product_id[i] == code) {  // When I find a matching ID
                return i;                  // I return its position in my array
            }
        }
        return -1;  // If I don't find the product, I return -1 to show it wasn't found
    }
    
    // This is my main program loop where I handle all the operations
    while (1) {
        scanf("%d", &code);  // I'm reading in what operation the user wants to do
        
        // If they enter 0, I'm done with the program
        if (code == 0) {
            break;
        }
        
        // If they enter -1 or -2, I need to show them a sales report
        if (code == -1 || code == -2) {
            printf("\nSales:\n");
            // I'm printing my nice formatted table header
            printf("+---------+---------+------------+--------+\n");
            printf("| ID      | Sold    | Profit ($) | GM (%%) |\n");
            printf("+---------+---------+------------+--------+\n");
            
            // Setting up my variables for calculations
            int total_profit = 0;
            int total_sales = 0;
            float profit_margin[num_products];
            int profit[num_products];
            int sorted_indices[num_products];
            
            // I'm storing the original indices so I can sort them later
            for (int i = 0; i < num_products; i+=1) {
                sorted_indices[i] = i;
            }
            
            // Now I'm calculating profits and margins for each product
            for (int i = 0; i < num_products; i+=1) {
                if (sales_account[i] > 0) {  // Only if the product has sales
                    profit[i] = (retail_price[i] - sale_price[i]) * sales_account[i];
                    profit_margin[i] = ((float)(retail_price[i] - sale_price[i]) / retail_price[i]) * 100;
                    total_profit += profit[i];
                    total_sales++;
                } else {
                    profit_margin[i] = 0.0;
                }
            }
            
            // I'm using bubble sort to arrange everything by profit margin
            for (int i = 0; i < num_products - 1; i+=1) {
                for (int j = 0; j < num_products - i - 1; j+=1) {
                    if (profit_margin[sorted_indices[j]] < profit_margin[sorted_indices[j + 1]]) {
                        int temp = sorted_indices[j];
                        sorted_indices[j] = sorted_indices[j + 1];
                        sorted_indices[j + 1] = temp;
                    }
                }
            }
            
            // Now I'm printing all my sorted data in a nice table
            for (int i = 0; i < num_products; i+=1) {
                int sorted_index = sorted_indices[i];
                if (sales_account[sorted_index] > 0) {
                    printf("| %-7d | %-7d | %-10d | %6.2f |\n", 
                           product_id[sorted_index], 
                           sales_account[sorted_index], 
                           profit[sorted_index], 
                           profit_margin[sorted_index]);
                }
            }
            
            // Finishing up my table with totals
            printf("+---------+---------+------------+--------+\n");
            printf("Total profit: $%d\n", total_profit);
            
            // Calculating my weighted average gross margin
            float sum_M = 0.0, sum_Q = 0.0;
            for (int i = 0; i < num_products; i+=1) {
                if (sales_account[i] > 0) {
                    sum_M += sales_account[i] * profit_margin[i];
                    sum_Q += sales_account[i];
                }
            }
            
            // Computing and printing the average margin
            float avg_M = (sum_Q > 0) ? (sum_M / sum_Q) : 0;
            printf("Average GM: %.2f%%\n", avg_M);
            
            // If they entered -2, I'm done after showing the report
            if (code == -2) {
                break;
            }
            continue;
        }
        
        // If they entered a product ID, I'm trying to record a sale
        int product_index = binary_search(product_id, num_products, code);
        if (product_index != -1) {  // If I found the product
            sales_account[product_index]+=1;  // I increment its sales count
        } else {  // If I didn't find it
            printf("Invalid code %d is not a valid product ID. Ignoring.\n", code);
        }
    }
    
    return 0;  // All done! My program ran successfully
}