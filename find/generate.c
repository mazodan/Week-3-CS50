/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // If the arguments passed are more than 2 or less than 1, print the proper usage.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // since by default arguments are passed as a string datatype, atoi() function converts it into a numerical datatype and asssigns it to n
    int n = atoi(argv[1]);

    // checks if seed is specified, it seems that the string from the command line argument is converted to integer and converted to Long int, if no seed then, current time is used as seed
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // from the first argument, it is passed as the iteration, then drand48 gets input bet 0 and 1, then multiplies to limit to get the theoretical percentage, converted to int which causes it to lose precision and prints it to std output
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
