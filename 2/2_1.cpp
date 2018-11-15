#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>

#include "heap.h"
#include "heap2.h"

//#define DEBUG

using namespace std;

int* generate_data(int n) {
	int *a = (int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++) a[i] = rand() % 2000000000;
	return a;
}

int* alg1(int *a, int n, int k) {
	int *ret = (int*)malloc(sizeof(int)*k);
	sort(a, a+n);
	memcpy(ret, a, sizeof(int)*k);
	return ret;
}

int* alg2(int *a, int n, int k) {
	int *ret = (int*)malloc(sizeof(int*)*k);
	Heap *heap = new Heap(n);
	for (int i=0; i<n; i++) heap->push(a[i]);
	for (int i=0; i<k; i++) ret[i] = heap->pop();
	return ret;
}

int* alg3(int *a, int n, int k) {
	int *ret = (int*)malloc(sizeof(int*)*k);
	Heap2 *heap = new Heap2(a, n);
	for (int i=0; i<k; i++) ret[i] = heap->pop();
	return ret;
}

void qselect(int *d, int k, int x, int y) {
	int a = x, b = y, c;
	while (a < b) {
		while (a < b && d[a] <= d[b]) a++;
		if (a < b) {
			c = d[a];
			d[a] = d[b];
			d[b] = c;
		}
		while (a < b && d[a] <= d[b]) b--;
		if (a < b) {
			c = d[a];
			d[a] = d[b];
			d[b] = c;
		}
	}
#ifdef DEBUG
	printf("x=%d y=%d a=%d k=%d\n", x, y, a, k);
	for (int i=x; i<=y; i++) printf("%d,", d[i]);
	printf("\n");
#endif
	if (a-x > k && x < a-1) qselect(d, k, x, a-1);
	if (a-x < k-1 && a+1 < y) qselect(d, k-a+x-1, a+1, y);
}

int* alg4(int *a, int n, int k) {
	int *ret = (int*)malloc(sizeof(int*)*k);
	qselect(a, k, 0, n-1);
	memcpy(ret, a, sizeof(int)*k);
	return ret;
}

int main(int argc, char **argv) {
	int T = 1;
	srand(time(0));
	int n = 20;
	if (argc > 1) n = atoi(argv[1]);
	if (argc > 2) T = atoi(argv[2]);
	int k = rand() % n + 1;

	long d[4] = { 0, 0, 0, 0 };
	clock_t c1, c2;
	for (int t=0; t<T; t++) {
		printf("Test time %d\n", t);
		int *a1 = generate_data(n);
		int *a2 = (int*)malloc(sizeof(int)*n);
		int *a3 = (int*)malloc(sizeof(int)*n);
		int *a4 = (int*)malloc(sizeof(int)*n);
		memcpy(a2, a1, sizeof(int)*n);
		memcpy(a3, a1, sizeof(int)*n);
		memcpy(a4, a1, sizeof(int)*n);
#ifdef DEBUG
		printf("Data:\n");
		for (int i=0; i<n; i++) printf("%d,", a1[i]);
		printf("\n");
#endif
    
		c1 = clock();
		int *r1 = alg1(a1, n, k);
		c2 = clock();
		d[0] += c2 - c1;
		printf("Alg 1 time: %lf\n", (c2-c1)/1000.0f);
#ifdef DEBUG
		printf("Result 1:\n");
		for (int i=0; i<k; i++) printf("%d,", r1[i]);
		printf("\n");
#endif

		c1 = clock();
		int *r2 = alg2(a2, n, k);
		c2 = clock();
		d[1] += c2 - c1;
		printf("Alg 2 time: %lf\n", (c2-c1)/1000.0f);
#ifdef DEBUG
		printf("Result 2:\n");
		sort(r2, r2+k);
		for (int i=0; i<k; i++) printf("%d,", r2[i]);
		printf("\n");
#endif

		c1 = clock();
		int *r3 = alg3(a2, n, k);
		c2 = clock();
		d[2] += c2 - c1;
		printf("Alg 3 time: %lf\n", (c2-c1)/1000.0f);
#ifdef DEBUG
		printf("Result 3:\n");
		sort(r3, r3+k);
		for (int i=0; i<k; i++) printf("%d,", r3[i]);
		printf("\n");
#endif

		c1 = clock();
		int *r4 = alg4(a2, n, k);
		c2 = clock();
		d[3] += c2 - c1;
		printf("Alg 4 time: %lf\n", (c2-c1)/1000.0f);
#ifdef DEBUG
		printf("Result 4:\n");
		sort(r4, r4+k);
		for (int i=0; i<k; i++) printf("%d,", r4[i]);
		printf("\n");
#endif

		printf("\n");

		free(r1);
		free(r2);
		free(r3);
		free(r4);

		free(a1);
		free(a2);
		free(a3);
		free(a4);
	}

#ifdef DEBUG
	c1 = clock();
	for (int i=0; i<n; i++) k++;
	c2 = clock();
	printf("O(n): %ld\n", c2-c1);
#endif
	printf("Average time: %lf %lf %lf %lf\n", d[0]/T/1000.0f, d[1]/T/1000.0f, d[2]/T/1000.0f, d[3]/T/1000.0f);

	return 0;
}
