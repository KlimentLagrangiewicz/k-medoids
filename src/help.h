#ifndef HELP_H_
#define HELP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void fscanfData(const char *fn, double *x, const int n);
void fprintfResult(const char *fn, const int* const y, const int n);
void fprintfFullResult(const char *fn, const int* const y, const int n, const double a);
void fscanfSplitting(const char *fn, int *y, const int n);
int getNumOfClass(const int *y, const int n);
double getCurAccuracy(const int *x, const int *y, const int *a, const int n);
void solve(const int *x, const int *y, int *items, int size, int l, const int n, double *eps);
double getAccuracy(const int *ideal, const int *r, const int n);

#endif
