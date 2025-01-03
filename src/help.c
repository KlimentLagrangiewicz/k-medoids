#include "help.h"

int fscanfData(const char *fn, double* const x, const int n) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		printf("Error in opening %s file..\n", fn);
		return 1;
	}
	int i = 0;
	while (i < n && !feof(fl)) if (fscanf(fl, "%lf", x + i++) == 0) {
		return 1;
	}
	fclose(fl);
	return 0;
}

int fprintfResult(const char *fn, const int* const y, const int n, const double t) {
	FILE *fl = fopen(fn, "a");
	if (!fl) {
		printf("Error in opening %s file for write results\n", fn);
		return 1;
	}
	fprintf(fl, "Result of k-medoids clustering...\nTime for k-medoids clustering = %lf s.\n", t);
	int i;
	for (i = 0; i < n; i++)
		fprintf(fl, "Object [%d] = %d;\n", i + 1, y[i]);
	fputc('\n', fl);
	fclose(fl);
	return 0;
}

int fprintfFullResult(const char *fn, const int* const y, const int n, const double p, const double t) {
	FILE *fl = fopen(fn, "a");
	if (!fl) {
		fprintf(stderr, "Error in opening %s file for write results\n", fn);
		return 1;
	}
	fprintf(fl, "Result of k-medoids clustering...\nTime for k-medoids clustering = %lf s.\nPrecision of k-medoids clustering = %.5lf;\n", t, p);
	int i;
	for (i = 0; i < n; i++)
		fprintf(fl, "Object [%d] = %d;\n", i + 1, y[i]);
	fputc('\n', fl);
	fclose(fl);
	return 0;
}

int fscanfPartition(const char *fn, int* const y, const int n) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		fprintf(stderr, "Can't access %s file with ideal partition for reading\n", fn);
		return 1;
	}
	int i = 0;
	while (i < n && !feof(fl)) if (fscanf(fl, "%d", y + i++) == 0) return 1;
	fclose(fl);
	return 0;
}

double getPrecision(const int* const x, const int* const y, const int n) {
	unsigned long long yy = 0llu, ny = 0llu;
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (x[i] == x[j] && y[i] == y[j]) yy++;
			if (x[i] != x[j] && y[i] == y[j]) ny++;
		}
	}
	return yy == 0llu && ny == 0llu ? 0.0 : (double)yy / (double)(yy + ny);
}

