#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>

#define DEBUG

using namespace std;

int main(int argc, char **argv) {
	srand(time(0));
	int n = 20;
	int k = rand() % (n*10);
	int *m = (int*)malloc(sizeof(int)*n);
	int *p = (int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++) {
		m[i] = rand() % (n*10);
		p[i] = rand() % n;
	}
	sort(m, &m[n]);

	printf("Input: ");
	for (int i=0; i<n; i++) printf("%d\t", m[i]);
	printf("\nProfit:");
	for (int i=0; i<n; i++) printf("%d\t", p[i]);
	printf("\nk=%d\n\n", k);

	int *t = (int*)malloc(sizeof(int)*n);
	int *l = (int*)malloc(sizeof(int)*n);
	int max = 0, maxp;
	t[0] = p[0];
	l[0] = -1;
	for (int i=1; i<n; i++) {
		t[i] = p[i];
		l[i] = -1;
		for (int j=0; j<i; j++) {
			if (m[i]-m[j]>=k && t[j]+p[i]>t[i]) {
				t[i] = t[j]+p[i];
				l[i] = j;
			}
		}
		if (t[i] > max) {
			max = t[i];
			maxp = i;
		}
	}

#ifdef DEBUG
	printf("t=     ");
	for (int i=0; i<n; i++) printf("%d\t", t[i]);
	printf("\nl=     ");
	for (int i=0; i<n; i++) printf("%d\t", l[i]);
	printf("\n");
#endif

	printf("Result: %d\n", max);
	while (maxp >= 0) {
		printf("%d ", m[maxp]);
		maxp = l[maxp];
	}
	printf("\n");

	free(m);
	free(p);
	free(t);
	free(l);
	return 0;
}
