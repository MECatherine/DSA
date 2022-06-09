#include <iostream>
using namespace std;

const int MAX_M = 1e7;
int set[MAX_M];

void merge(int lo, int mi, int hi) {
	int i = 0, j = 0, k = 0, lb = mi - lo, lc = hi - mi;
	int* A = set + lo;
	int* B = new int[lb];
	int* C = set + mi;
	for (int i = 0; i < lb; i++) B[i] = A[i];

	while ((j < lb) && (k < lc))
		A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
	while (j < lb)
		A[i++] = B[j++];
}

void mergeSort(int lo, int hi) {
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}


int searchA(int n, int a) {
	int lo = 0, hi = n, mi;
	while (lo < hi) {
		mi = (lo + hi) >> 1;
		set[mi] < a ? lo = mi + 1 : hi = mi;
	}
	return lo;
}


int searchB(int n, int b) {
	int lo = 0, hi = n, mi;
	while (lo < hi) {
		mi = (lo + hi) >> 1;
		b < set[mi] ? hi = mi : lo = mi + 1;
	}
	return lo;
}

int Range(int n, int a, int b) {
    int r = searchB(n, b) - searchA(n, a);
    if (r < 0) r = 0;
    return r;
}

int main()
{
	int n, m;
	scanf( "%d%d", &n, &m );

	for (int i = 0; i < n; i++)
	{ scanf( "%d", &set[i] ); }
	
	mergeSort(0, n);
    
    int lb, ub;
	for (int i = 0; i < m; i++) { 
		int lb, ub;
		scanf( "%d%d", &lb, &ub);
        printf( "%d\n", Range(n, lb, ub));
	}

	return 0;	
}
