/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <string.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm

    // Binary Search (Integer) T(n) = O(log n)

    int start = 0;
    int end = n - 1;
    int med = (end + start)/2;

    // Start and End have not crossed yet
    while(end >= start){
        // Determine if med contains the value
        if(values[med] == value){
            return true;
        } else {
            // Check if the value is greater or lesser than the med
            if(value > values[med]){
                start = med + 1;
            } else if(value < values[med]) {
                end = med - 1;
            }

            med = (end + start)/2;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    // Set the count array which has a range of 0 - 65535 needed for counting sort
    int count[65536];
    // allocate all elements of count to zero
    memset(count, 0, sizeof(count));

    // Set frequency distribution to count array
    for(int i = 0; i < n; i++){
        ++count[values[i]];
    }

    // Add elements to previous element
    for(int i = 0; i < 65535; i++){
        count[i+1] += count[i];
    }

    // Lets do dis
    int output[n];
    for(int i = (n-1); i > -1; i--){
        output[count[values[i]] - 1] = values[i];
        --count[values[i]];
    }

    memcpy(values, output, n*sizeof(int));

    return;
}
