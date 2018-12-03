#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>

#define DEBUG

int* generate_data(int n) {
	srand(time(0));
	int *s = (int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++) s[i] = rand() % (n*10);
	return s;
}

int main(int argc, char **argv) {
	int n = 20;
	int *s = generate_data(n);
	int *m = (int*)malloc(sizeof(int)*n);
	int *p = (int*)malloc(sizeof(int)*n);
	int max = 0, maxp;

	printf("Input: ");
	for (int i=0; i<n; i++) printf("%d ", s[i]);
	printf("\n");

	m[0] = 1;
	p[0] = -1;
	for (int i=1; i<n; i++) {
		m[i] = 1;
		p[i] = -1;
		for (int j=0; j<i; j++) {
			if (s[i]>s[j] && m[j]+1>m[i]) {
				m[i] = m[j] + 1;
				p[i] = j;
			}
		}
		if (m[i] > max) {
			max = m[i];
			maxp = i;
		}
	}

	for (int i=0; i<n; i++) printf("%d ", m[i]);
	printf("\n\n");
	printf("Length: %d\n", max);
	while (maxp >= 0) {
		printf("%d ", s[maxp]);
		maxp = p[maxp];
	}
	printf("\n");


	free(s);
	return 0;
}
