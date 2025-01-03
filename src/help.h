#ifndef HELP_H_
#define HELP_H_

#include <stdlib.h>
#include <stdio.h>


int fscanfData(const char *fn, double* const x, const int n);
int fprintfResult(const char *fn, const int* const y, const int n, const double t);
int fprintfFullResult(const char *fn, const int* const y, const int n, const double p, const double t);
int fscanfPartition(const char *fn, int* const y, const int n);
double getPrecision(const int* const x, const int* const y, const int n);

#endif
