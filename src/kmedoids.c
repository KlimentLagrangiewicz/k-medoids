#include "kmedoids.h"

double getDistance(const double *x1, const double *x2, int m) {
	double d, r = 0.0;
	while (m--) {
		d = *(x1++) - *(x2++);
		r += d * d;
	}
	return sqrt(r);
}

void autoscaling(double* const x, const int n, const int m) {
	const int s = n * m;
	int j;
	for (j = 0; j < m; j++) {
		double sd, Ex = 0.0, Exx = 0.0, *ptr;
		for (ptr = x + j; ptr < x + s; ptr += m) {
			sd = *ptr;
			Ex += sd;
			Exx += sd * sd;
		}
		Exx /= n;
		Ex /= n;
		sd = sqrt(Exx - Ex * Ex);
		for (ptr = x + j; ptr < x + s; ptr += m) {
			*ptr = (*ptr - Ex) / sd;
		}
	}
}

int getCluster(const double* const x, const double* const c, const int m, int k) {
	int res = --k;
	double minD = getDistance(x, c + k * m, m);
	while (k--) {
		const double curD = getDistance(x, c + k * m, m);
		if (curD < minD) {
			minD = curD;
			res = k;
		}
	}
	return res;
}

char constr(const int *y, const int val, int s) {
	while (s--) if (*(y++) == val) return 1;
	return 0;
}

int* startCoreNums(const int k, const int n) {
	srand((unsigned)clock());
	int *y = (int*)malloc(k * sizeof(int));
	int i = 0, val;	
	while (i < k) {
		do val = rand() % n;
		while (constr(y, val, i));
		y[i] = val;
		i++;
	}
	return y;
}

void detCores(const double* const x, double* const c, const int* const sn, int k, const int m) {
	while (k--) memcpy(c + k * m, x + sn[k] * m, m * sizeof(double));
}

void detStartPartition(const double* const x, const double* const c, int* const y, int* const nums, int n, const int m, const int k) {
	memset(nums, 0, k * sizeof(int));
	while (n--) {
		const int l = getCluster(x + n * m, c, m, k);
		y[n] = l;
		nums[l]++;
	}
}

void calcCores(const double* const x, double* const c, const int* const y, const int* const nums, const int n, const int m, const int k) {
	memset(c, 0, k * m * sizeof(double));
	int i, j;
	for (i = 0; i < n; i++) {
		const int f = y[i] * m, l = i * m;
		for (j = 0; j < m; j++)
			c[f + j] += x[l + j];
	}
	for (i = 0; i < k; i++) {
		const int l = nums[i], f = i * m;
		for (j = 0; j < m; j++)
			c[f + j] /= l;
	}
}

int getMedoidNum(const double* const x, const double* const c, const int* const y, const int n, const int m, const int id) {
	int i, res = 0;
	while (res < n && y[res] != id) res++;
	double minD = getDistance(x + res * m, c, m);
	for (i = res + 1; i < n; i++) {
		if (y[i] == id) {
			const double curD = getDistance(x + i * m, c, m);
			if (curD < minD) {
				minD = curD;
				res = i;
			}
		}
	}
	return res;
}

void setMedoids(const double *x, double * const c, const int* const y, const int n, const int m, int k) {
	while (k--) {
		const int id = getMedoidNum(x, c + k * m, y, n, m, k);
		memcpy(c + k * m, x + id * m, m * sizeof(double));
	}
}

char checkPartition(const double* const x, const double* const c, int* const y, int* const nums, int n, const int m, const int k) {
	memset(nums, 0, k * sizeof(int));
	char flag = 0; 
	while (n--) {
		const int f = getCluster(x + n * m, c, m, k);
		if (y[n] != f) flag = 1;
		y[n] = f;
		nums[f]++;
	}
	return flag;
}

char cyclicRecalc(const double* const x, double* const c, int* const y, int* const nums, const int n, const int m, const int k) {
	calcCores(x, c, y, nums, n, m, k);
	setMedoids(x, c, y, n, m, k);
	return checkPartition(x, c, y, nums, n, m, k);
}

void kmedoids(const double* const X, int* const y, const int n, const int m, const int k) {
	double *x = (double*)malloc(n * m * sizeof(double));
	memcpy(x, X, n * m * sizeof(double));
	autoscaling(x, n, m);
	int *nums = startCoreNums(k, n);
	double *c = (double*)malloc(k * m * sizeof(double));
	detCores(x, c, nums, k, m);
	detStartPartition(x, c, y, nums, n, m, k);
	while (cyclicRecalc(x, c, y, nums, n, m, k));
	free(x);
	free(c);
	free(nums);
}
