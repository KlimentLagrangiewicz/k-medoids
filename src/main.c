#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "help.h"
#include "kmedoids.h"


int main(int argc, char **argv) {
	if (argc < 6) {
		perror("Not enough parameters");
		exit(1);
	}
	const int n = atoi(argv[2]), m = atoi(argv[3]), k = atoi(argv[4]);
	if (n < 1 || m < 1 || k < 1 || k > n) {
		perror("Values of input parameters are incorrect");
		exit(1);
	}
	double *x = (double*)malloc(n * m * sizeof(double));
	if (!x) {
		perror("Memory allocation error for instances");
		exit(1);
	}
	int *y = (int*)malloc(n * sizeof(int));
	if (!y) {
		perror("Memory allocation error for partition");
		free(x);
		exit(1);
	}
	if (fscanfData(argv[1], x, n * m)) {
		perror("Can't read data from file for clustering");
		free(x);
		free(y);
		exit(1);
	}
	double t1 = clock();
	kmedoids(x, y, n, m, k);
	t1 = (clock() - t1) / CLOCKS_PER_SEC;
	if (argc > 6) {
		int *ideal = (int*)malloc(n * sizeof(int));
		if (!ideal) {
			puts("Memory allocation error for perfect partition");
			if (fprintfResult(argv[5], y, n, t1)) printf("Can't write results in %s file\n", argv[5]);
		} else if (fscanfPartition(argv[6], ideal, n)) {
			puts("Can't read perfect partition from file");
			if (fprintfResult(argv[5], y, n, t1)) printf("Can't write results in %s file\n", argv[5]);
			free(ideal);
		} else {
			const double p = getPrecision(ideal, y, n);
			printf("Precision of k-medoids clustering = %.5lf\n", p);
			if (fprintfFullResult(argv[5], y, n, p, t1)) printf("Can't write all results in %s file\n", argv[5]);
			free(ideal);
		}		
	} else if (fprintfResult(argv[5], y, n, t1)) printf("Can't write results in %s file\n", argv[5]);
	printf("Time for k-medoids clustering = %.6lf s.\nThe work of the program is completed\n", t1);
	free(x);
	free(y);
	return 0;
}
