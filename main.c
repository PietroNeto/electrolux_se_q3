#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------------
* DEFINES
*-----------------------------------------------------------------------------*/

// To prevente overflow
#define MAX_EVEN_ARRAY_SIZE     100

// TEST 1
#define EXEMPLE1                {1, 2, 3, 4, 5, 6, 7, 8}

// TEST 2
#define EXEMPLE2                {1, 3, 5, 7, 9, 1, 5, 3}

// TEST 3
#define EXEMPLE3                {2, 4, 6, 8, 2, 4, 6, 8}

/**
 * Function: calculateStats
 * Description: Calculates the average, maximum, and minimum values of an array.
 *              It also returns a new array containing only even numbers.
 *
 * Parameters:
 * - inputArray: Pointer to the input array.
 * - n: Number of elements in the input array.
 * - average: Pointer to store the average value.
 * - max: Pointer to store the maximum value.
 * - min: Pointer to store the minimum value.
 * - evenArray: Pointer to the output array containing even numbers.
 * - evenArraySize: Pointer to store the size of the evenArray.
 */
void calculateStats( const int *inputArray, int n, double *average,
                     int *max, int *min, int **evenArray, int *evenArraySize) 
{
    if (n <= 0 || !inputArray) {
        // Handle invalid input
        *average = 0.0;
        *max = *min = 0;
        *evenArray = NULL;
        *evenArraySize = 0;
        return;
    }

    int sum = 0;
    *max = inputArray[0];
    *min = inputArray[0];

    // Temporary array for even numbers
    int *tempEvenArray = (int *)malloc(n * sizeof(int));
    int evenCount = 0;

    for (int i = 0; i < n; i++) {
        // Update sum, max, and min
        sum += inputArray[i];
        if (inputArray[i] > *max) {
            *max = inputArray[i];
        }
        if (inputArray[i] < *min) {
            *min = inputArray[i];
        }

        // Collect even numbers, ensuring we don't exceed the max size
        if (inputArray[i] % 2 == 0 && evenCount < MAX_EVEN_ARRAY_SIZE) {
            tempEvenArray[evenCount++] = inputArray[i];
        }
    }

    // Calculate average
    *average = (double)sum / n;

    // Allocate exact memory for the even array
    *evenArray = (int *)malloc(evenCount * sizeof(int));
    for (int i = 0; i < evenCount; i++) {
        (*evenArray)[i] = tempEvenArray[i];
    }

    // Update even array size
    *evenArraySize = evenCount;

    // Free temporary array
    free(tempEvenArray);
}

/**
 * Main function to demonstrate usage of the calculateStats function.
 */
int main(void) {
    int inputArray[] = EXEMPLE2;
    int n = sizeof(inputArray) / sizeof(inputArray[0]);

    double average;
    int max, min;
    int *evenArray;
    int evenArraySize;

    // Call the function
    calculateStats(inputArray, n, &average, &max, &min, &evenArray, &evenArraySize);

    // Print results
    printf("Average: %.2f\n", average);
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);
    printf("Even numbers:");
    for (int i = 0; i < evenArraySize; i++) {
        printf(" %d", evenArray[i]);
    }
    printf("\n");

    // Free allocated memory for the even array
    free(evenArray);

    return 0;
}
