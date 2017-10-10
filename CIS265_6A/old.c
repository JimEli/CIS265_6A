/*************************************************************************
* Title: (CIS265_6A) inner_product
* File: main.c
* Author: James Eli
* Date: 9/2/2017
*
* Write the following function:
*    double inner_product(const double *a, const double *b, int n);
* a and b both point to arrays of length n. The function should return 
* a[0]*b[0] + a[1]*b[1] + ... + a[n-1]*b[n-1]. Use pointer arithmetic-not 
* subscripting-to visit array elements.
* Your program should prompt the user to enter two lists of double types 
* of equal size (list "a" and list "b").
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/02/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

// Definitions.
#define NUM_LISTS              2      // Number of lists.
#define MAX_ELEMENTS           10     // Maximum number of elements per list.
#define MAX_CHARS              36     // Max number of characters for list entry (7 chars per x 5) + 1
#define MIN_INPUT              -100.0 // Min acceptable  input value.
#define MAX_INPUT              100.0  // Max accetable input value.
#define MAXIMUM_INPUT_ATTEMPTS 3      // Max input attempts before aborting.

// Retrieves a list of n elements of double values as entered by user.
// Returns true if successful.
bool getRow(const char listTitle, double list[], const unsigned int n) {
	unsigned int count = 0; // Count of elements in row.
	bool retVal = false;    // Function return value, ture = success (assumed false).

	assert(n > 0);
	assert(list != NULL);

	// reserve temporary space for the input string.
	char *s = (char *)malloc(sizeof(char) * MAX_CHARS);
	// Check valid.
	if (s == NULL)
		return retVal;

	// Prompt and grab string input.
	fprintf(stdout, "Enter list %c: ", listTitle);
	if (!fgets(s, MAX_CHARS, stdin)) {
		free(s);
		return retVal;
	}
	else if (!strchr(s, '\n')) {
		// input too long, eat it.
		while (fgets(s, MAX_CHARS, stdin) && !strchr(s, '\n'));
		fputs("Too many characters input.\n", stdout);
	}
	else if (strlen(s) > 1) {
		// Iterate string and convert to integer.
		char *context = NULL, *end = NULL;
		char *number = strtok_s(s, " \n", &context);

		// Loop through string, attempting conversion to double.
		while (number != NULL) {
			double d;

			d = strtod(number, &end);

			// Check valid strtod conversion: no error, no remaining input & not empty.
			if (*end == 0 && number != end) {
				if (d >= MIN_INPUT && d <= MAX_INPUT)
					list[count++] = d;
				else {
					printf("Value must be between %0.2f and %0.2f.\n", MIN_INPUT, MAX_INPUT);
					break;
				}
			} else {
				puts("Input not a valid floating point number.\n");
				break;
			}
			// Repeat...
			number = strtok_s(NULL, " \n", &context);

		}
		// Confirm correct number of integers.
		if (count > n)
			fprintf(stdout, "Too many elements entered for list %c.\n", listTitle);
		else if (count < n)
			fprintf(stdout, "Too few valid elements in list %c.\n", listTitle);
		else
			retVal = true; // Success.
	}

	// Free memory and return.
	free(s);
	return retVal;
}

// Function returns a[0] * b[0] + a[1] * b[1] + ... + a[n - 1] * b[n - 1]
// Using pointer arithmetic to visit array elements.
double inner_product(const double *a, const double *b, int n) {
	double product = 0.0;
	int feRaised;

	assert(n > 0);

	// Calculate inner product.
	for (int i = 0; i < n; i++, a++, b++) 
		product = product + *a * *b;

	return product;
}

// Program starts here.
int main(void) {
	unsigned int numElements = 0; // Number of elements in parallel arrays (1 to MAX_EMLEMENTS).
	
	// Display program instructions.
	fputs("Enter two lists of double types of equal size.\n", stdout);
	fputs("The program will calculate a[0]*b[0] + a[1]*b[1] + ... + a[n-1]*b[n-1].\n\n", stdout);

	// Input attempt counter.
	int attempts = MAXIMUM_INPUT_ATTEMPTS;
	assert(attempts > 0); // Assert attempts valid non-zero, positive number.

	// Attempt only so many inputs.
	while (attempts--) {
		char input[4];  // Holds user input as string.
		unsigned int n; // Holds converted string to integer.

		// Prompt and grab user input.
		fputs("Enter number of elements per list (1 to 10): ", stdout);
		if (!fgets(input, sizeof input, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(input, '\n')) {
			// input too long, eat remainder.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			// Catch special case of null input.
			if (strlen(input) <= 1)
				continue;
			// Attempt to convert from string to intger, and validate.
			if (sscanf_s(input, "%d", &n)) {
				if (n >= 1 && n <= MAX_ELEMENTS) {
					numElements = n;
					break; // Success, so exit.
				}
				else
					fprintf(stdout, "Entry is outside allowable range (1 - %d)\n", MAX_ELEMENTS);
			}
			else
				fputs("Invalid input.\n", stdout);
		}
	}

	// Check for input failure.
	if (numElements == 0) {
		fputs("Program terminating.\n", stderr);
		exit(EXIT_FAILURE);
	}

	// Attempt to size parallel arrays.
	double *a = malloc(sizeof(double) * numElements);
	double *b = malloc(sizeof(double) * numElements);
	if (a == NULL || b == NULL) {
		fputs("Program terminating.\n", stderr);
		exit(EXIT_FAILURE);
	}

	// Enter the 2 lists of doubles.
	if (getRow('A', a, numElements) == false) {
		fputs("Program terminating.\n", stderr);
		exit(EXIT_FAILURE);
	}
	if (getRow('B', b, numElements) == false) {
		fputs("Program terminating.\n", stderr);
		exit(EXIT_FAILURE);
	}

	// Calculate inner product and display answer.
	fprintf(stdout, "Inner product = %0.3lf\n", inner_product(a, b, numElements));
}

