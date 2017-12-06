/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm

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
    //Implementing bubblesort with a T(n) = O(n^2)

    //If length is 1 then return the array
    if(n <= 1){
        return;
    }

    //Initializing swap counter
    int sc = -1;
    // Initializing the limit, to be decremented
    int lim = n - 1;
    //If swap counter is not equal to zero
    while(sc != 0){
        // set swap counter to zero for evaluation
        sc = 0;
        for(int i = 0; i < lim; lim--){
            // Check if the limit reaches zero, it means that all elements are sorted at the worst case scenario, it happens
            if(lim == 0){
                break;
            }

            // BETA - NESTED FOR LOOP TO INCREMENT i
            // Nested works!
            for(int i = 0; i < lim; i++){
                if(values[i] > values[i+1]){
                    int tmp = values[i+1];
                    values[i+1] = values[i];
                    values[i] = tmp;
                    // Elements are swapped

                    // increment swap counter
                    sc++;
                }
            }
        }
    }


    return;
}
