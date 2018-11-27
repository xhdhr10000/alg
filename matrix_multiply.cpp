#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define DEBUG

int* generate_data(int n) {
	srand(time(0));
	int *p = (int*)malloc(sizeof(int)*(n+1));
	for (int i=0; i<=n; i++) p[i] = rand() % 10 + 1;
	return p;
}

void output(int **s, int x, int y) {
	if (x == y) {
		printf("%d", x);
		return;
	}
	printf("(");
	output(s, x, s[x][y]);
	output(s, s[x][y]+1, y);
	printf(")");
}

int main(int argc, char **argv) {
	int n = 6;
	int *p = generate_data(n);
	int **m = (int**)malloc(sizeof(int*)*(n+1));
	int **s = (int**)malloc(sizeof(int*)*(n+1));

	printf("Input: ");
	for (int i=0; i<=n; i++) printf("%d ", p[i]);
	printf("\n\n");

	for (int i=0; i<=n; i++) {
		m[i] = (int*)malloc(sizeof(int)*(n+1));
		s[i] = (int*)malloc(sizeof(int)*(n+1));
	}
	for (int i=1; i<=n; i++) m[i][i] = 0;
	for (int l=2; l<=n; l++) {
		for (int i=1; i<=n-l+1; i++) {
			int j = i + l - 1;
			m[i][j] = 10000000;
			for (int k=i; k<j; k++) {
				int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
#ifdef DEBUG
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) printf("%d ", m[i][j]);
		printf("\n");
	}
	printf("\n");
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) printf("%d ", s[i][j]);
		printf("\n");
	}
	printf("\n");
#endif

	printf("%d\n", m[1][n]);
	output(s, 1, n);
	printf("\n\n");

	for (int i=0; i<=n; i++) {
		free(m[i]);
		free(s[i]);
	}
	free(m);
	free(s);
	free(p);
	return 0;
}
