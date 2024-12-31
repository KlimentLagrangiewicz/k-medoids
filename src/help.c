#include "help.h"

void fscanfData(const char *fn, double* const x, const int n) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		printf("Error in opening %s file..\n", fn);
		exit(1);
	}
	int i = 0;
	while (i < n && !feof(fl)) if (fscanf(fl, "%lf", x + i++) == 0);
	fclose(fl);
}

void fprintfResult(const char *fn, const int* const y, const int n) {
	FILE *fl = fopen(fn, "a");
	if (!fl) {
		printf("Error in opening %s result file...\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of k-medoids clustering...\n");
	int i;
	for (i = 0; i < n; i++)
		fprintf(fl, "Object [%d] = %d;\n", i + 1, y[i]);
	fputc('\n', fl);
	fclose(fl);
}

void fprintfFullResult(const char *fn, const int* const y, const int n, const double p) {
	FILE *fl = fopen(fn, "a");
	if (!fl) {
		printf("Error in opening %s result file...\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of k-medoids clustering...\nPrecision of k-medoids clustering = %.5lf;\n", p);
	int i;
	for (i = 0; i < n; i++)
		fprintf(fl, "Object [%d] = %d;\n", i + 1, y[i]);
	fputc('\n', fl);
	fclose(fl);
}

void fscanfPartition(const char *fn, int* const y, const int n) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		printf("Can't access %s file with ideal splitting for reading...\n", fn);
		exit(1);
	}
	int i = 0;
	while (i < n && !feof(fl)) if (fscanf(fl, "%d", y + i++) == 0);
	fclose(fl);
}

double getPrecision(const int* const x, const int* const y, const int n) {
	long long yy = 0ll, ny = 0ll;
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (x[i] == x[j] && y[i] == y[j]) yy++;
			if (x[i] != x[j] && y[i] == y[j]) ny++;
		}
	}
	return yy == 0 && ny == 0 ? 0.0 : (double)yy / (double)(yy + ny);
}

