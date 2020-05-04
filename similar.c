#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int compareSubString(char *doc1, char *doc2, int k) {
	int i;
	for (i = 0; i < k; i++) {
		if ( *(doc1 + i) != *(doc2 + i) ) {
			return 0;
		}
	}
	return 1;
}


float similarityScore(char *doc1, int n1, char *doc2, int n2, int k) {
	float ctr = 0, score;
	int i, j, sub1, sub2;
	char subdoc1[k], subdoc2[k];


	// // Check substrings of doc1 and doc2
	// starting element of doc1
	for (i = 0; i < n1 - k + 1; i++) {
		// intialize subarray1 of size k with elements from doc1
		for (sub1 = 0; sub1 < k; sub1++) {
			*(subdoc1 + sub1) = *(doc1 + i + sub1);
		}

		// starting element of doc2
		for (j = 0; j < n2 - k + 1; j++) {
			// initalize subarray2 of size k with elements from doc2
			for (sub2 = 0; sub2 < k; sub2++) {
				*(subdoc2 + sub2) = *(doc2 + j + sub2);
			}
			// if k-substring1 == k-substring2 increment counter
			// stop checking the rest of doc2
			// move to next starting element of doc1
			if (compareSubString(subdoc1, subdoc2, k) == 1) {
				ctr++;
				break;
			} 
		}
	}
	
	score = (ctr / (n1 - k + 1));
	return score;
}

void preProcess(char *doc, int *n) {
	int i, j;

	// remove space at end
	if (isspace(*(doc + *n - 1))) { 
		*(doc + *n - 1) = '\0';
		*n = *n - 1;
	}
	// remove space at beginning
	while (isspace(*(doc))) {
		for (i = 0; i < *n; i++) {
			*(doc + i) = *(doc + i + 1);
		}
		*n = *n - 1;
	}

	// make lower case
	// replace whitespace characters with ' '
	for (i = 0; i < *n; i++) {
		*(doc + i) = tolower(*(doc + i));
		if (isspace(*(doc + i))) {
			*(doc + i) = ' ';
		}
	}

	// remove double spaces
	for (i = 0; i < *n - 1;) {
		if (*(doc + i) == *(doc + i + 1) && isspace(*(doc + i))) {
			for (j = i + 1; j < *n; j++) {
				*(doc + j) = *(doc + j + 1);
			}
		} else {
			i++;
		}
	}

}

int main(int argc, char *argv[]) {
	FILE *fptr1, *fptr2;
	float score;
	int n1, n2, k, i;
	char *document1, *document2;

	// Assign command line integers
	k = atoi(*(argv + 1));
	n1 = atoi(*(argv + 3));
	n2 = atoi(*(argv + 5));

	// dyanmicly allocate memory for character pointers
	document1 = (char *)malloc(n1);
	document2 = (char *)malloc(n2);

	// open file 1
	fptr1 = fopen("file1", "r");
	if (fptr1 == NULL) {
		printf("File 'file1' did not open.\n");
	}
	// load contents of file 1 into characters 1
	for (i = 0; i < n1; i++) {
		fscanf(fptr1, "%c", (document1 + i));	
	}
	fclose(fptr1);

	// open file 2
	fptr2 = fopen("file2", "r");
	if (fptr2 == NULL) {
		printf("File 'file2' did not open.\n");
	}
	// load contents of file 2 into characters 2
	for (i = 0; i < n2; i++) {
		fscanf(fptr2, "%c", (document2 + i));	
	}
	fclose(fptr2);

	// preprocess documents
	preProcess(document1, &n1);
	preProcess(document2, &n2);

	// calculate similarity score
	// int subscore = compareSubString( &*(document1 + 2), &*(document2 + 2), 2);
	score = similarityScore(document1, n1, document2, n2, k);

	printf("The similarity score is %f\n", score);

	// free memory
	free(document1);
	free(document2);

}









