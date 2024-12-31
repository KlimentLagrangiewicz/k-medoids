#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "help.h"
#include "kmedoids.h"


int main(int argc, char **argv) {
	if (argc < 6) {
		puts("Not enough parameters...");
		exit(1);
	}
	const int n = atoi(argv[2]), m = atoi(argv[3]), k = atoi(argv[4]);
	if (n < 1 || m < 1 || k < 1 || k > n) {
		puts("Values of input parameters are incorrect...");
		exit(1);
	}
	double *x = (double*)malloc(n * m * sizeof(double));
	int *y = (int*)malloc(n * sizeof(int));
	fscanfData(argv[1], x, n * m);
	double t1 = clock();
	kmedoids(x, y, n, m, k);
	t1 = (clock() - t1) / CLOCKS_PER_SEC;
	if (argc > 6) {
		int *ideal = (int*)malloc(n * sizeof(int));
		fscanfPartition(argv[6], ideal, n);
		const double p = getPrecision(ideal, y, n);
		printf("Precision of k-medoids clustering = %.5lf\n", p);
		fprintfFullResult(argv[5], y, n, p);
		free(ideal);
	} else fprintfResult(argv[5], y, n);
	printf("Time for k-medoids clustering = %.6lf s.\nThe work of the program is completed\n", (double)t1);
	free(x);
	free(y);
	return 0;
}
