#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>

using namespace std;

int* generate_array(int len) {
	int *a = (int*)malloc(sizeof(int)*len);
	srand(time(0));
	for (int i=0; i<len; i++) a[i] = rand();
	return a;
}

void swap(int *d, int x, int y) {
	int c;
	c = d[x];
	d[x] = d[y];
	d[y] = c;
}

float qp = 0;
int qc = 0;
void qsort(int *d, int x, int y) {
	int a = x, b = y, c;
	while (a < b) {
		while (a < b && d[a] <= d[b]) a++;
		if (a < b) swap(d, a, b);
		while (a < b && d[a] <= d[b]) b--;
		if (a < b) swap(d, a, b);
	}
	//printf("sort [%d, %d] %d %.2f\n", x, y, a, (a-x)/(float)(y-x));
	qp += (a-x)/(float)(y-x);
	qc++;
	if (x < a-1) qsort(d, x, a-1);
	if (b+1 < y) qsort(d, b+1, y);
}

int randomized_partition(int *d, int x, int y) {
	int i=x-1, j=x, ax = rand() % (y-x+1) + x;
	swap(d, ax, y);
	while (j < y) {
		if (d[j] < d[y]) swap(d, ++i, j);
		j++;
	}
	swap(d, ++i, y);
	return i;
}

void randomized_qsort(int *d, int x, int y) {
	int q = randomized_partition(d, x, y);
	if (x < q-1) randomized_qsort(d, x, q-1);
	if (q+1 < y) randomized_qsort(d, q+1, y);
}

int main(int argc, char **argv) {
	int T = 1;
	int len = 20000;
	long sumQ = 0, sumR = 0, sumS = 0;
	if (argc > 1) len = atoi(argv[1]);
	if (argc > 2) T = atoi(argv[2]);

	for (int t=0; t<T; t++) {
		printf("Test time %d\n", t);
		int *a = generate_array(len);
		int *b = (int*)malloc(sizeof(int)*len);
		int *c = (int*)malloc(sizeof(int)*len);
		memcpy(b, a, sizeof(int)*len);
		memcpy(c, a, sizeof(int)*len);

		clock_t c1 = clock();
		qsort(a, 0, len-1);
		clock_t c2 = clock();
		sumQ += c2-c1;
		printf("Qsort Time: %ld\n", c2-c1);

		c1 = clock();
		randomized_qsort(b, 0, len-1);
		c2 = clock();
		sumR += c2-c1;
		printf("Randomized-Qsort Time: %ld\n", c2-c1);

		c1 = clock();
		sort(c, c+len);
		c2 = clock();
		sumS += c2-c1;
		printf("System-Qsort Time: %ld\n", c2-c1);

		free(a);
		free(b);
		free(c);
		printf("\n");
	}

	printf("Average time: Q=%ld R=%ld S=%ld\n", sumQ/T, sumR/T, sumS/T);
	return 0;
}
