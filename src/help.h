#ifndef HELP_H_
#define HELP_H_

#include <stdlib.h>
#include <stdio.h>


void fscanfData(const char *fn, double* const x, const int n);
void fprintfResult(const char *fn, const int* const y, const int n);
void fprintfFullResult(const char *fn, const int* const y, const int n, const double p);
void fscanfPartition(const char *fn, int* const y, const int n);
double getPrecision(const int* const x, const int* const y, const int n);

#endif
