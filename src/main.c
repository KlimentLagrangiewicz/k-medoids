#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "help.h"
#include "kmedoids.h"

unsigned long long timeValue = 0;

unsigned long long time_RDTSC() {
	union ticks {
		unsigned long long tx;
		struct dblword {
			long tl, th;
		} dw;
	} t;
	__asm__ ("rdtsc\n"
	  : "=a" (t.dw.tl), "=d"(t.dw.th)
	  );
	return t.tx;
}

void time_start() { timeValue = time_RDTSC(); }

long long time_stop() { return time_RDTSC() - timeValue; }

int main(int argc, char **argv) {
	if (argc < 6) {
		puts("Not enough parameters...");
		exit(1);
	}
	const int n = atoi(argv[2]), m = atoi(argv[3]), k = atoi(argv[4]);
	if ((n <= 0) || (m <= 0) || (k <= 0) || (k > n)) {
		puts("Values of input parameters are incorrect...");
		exit(1);
	}
	double *x = (double*)malloc(n * m * sizeof(double));
	int *y = (int*)malloc(n * sizeof(int));
	fscanfData(argv[1], x, n * m);
	long long t;
	clock_t cl = clock();
	time_start();
	kmedoids(x, y, n, m, k);
	t = time_stop();
	cl = clock() - cl;
	if (argc > 6) {
		int *ideal = (int*)malloc(n * sizeof(int));
		fscanfSplitting(argv[6], ideal, n);
		const double a = getAccuracy(ideal, y, n);
		printf("Accuracy of k-medoids clustering = %.5lf;\n", a);
		fprintfFullResult(argv[5], y, n, a);
		free(ideal);
	} else {
		fprintfResult(argv[5], y, n);
	}
	if (t < 0) {
		printf("Time for k-medoids clustering = %.6lf s.;\nThe work of the program is completed...\n", (double)cl);
	} else {
		printf("Time for k-medoids clustering = %lld CPU clocks;\nThe work of the program is completed...\n", t);
	}
	free(x);
	free(y);
	return 0;
}
