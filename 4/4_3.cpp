#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define DEBUG

char* generate_data(int n) {
	const char dic[4] = { 'A', 'T', 'G', 'C' };
	char *s = (char*)malloc(sizeof(char)*n);

	srand(time(0));
	for (int i=0; i<n; i++) s[i] = dic[rand()%4];

	return s;
}

int m[100][100];
int p[100][100];

void output(char *s, int x, int y) {
	if (x > y) return;
	if (x == y) {
		printf("%c", s[x]);
		return;
	}
	if (p[x][y] == 1) {
		printf("%c", s[x]);
		output(s, x+1, y-1);
		printf("%c", s[y]);
	} else if (p[x][y] == 2) {
		output(s, x+1, y);
	} else {
		output(s, x, y-1);
	}
}

int main(int argc, char **argv) {
	int n = 20;
	char *s = generate_data(n);

	printf("Input: ");
	for (int i=0; i<n; i++) printf("%c", s[i]);
	printf("\n");

	for (int i=0; i<n; i++) {
		m[i][i] = 1;
		m[i+1][i] = 0;
		p[i][i] = 0;
	}
	for (int l=2; l<=n; l++) {
		for (int i=0; i<=n-l; i++) {
			int j=i+l-1;
			if (s[i]==s[j]) {
				m[i][j] = m[i+1][j-1] + 2;
				p[i][j] = 1;
			} else if (m[i+1][j] > m[i][j-1]) {
				m[i][j] = m[i+1][j];
				p[i][j] = 2;
			} else {
				m[i][j] = m[i][j-1];
				p[i][j] = 3;
			}
		}
	}
#ifdef DEBUG
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) printf("%d ", m[i][j]);
		printf("\n");
	}
	printf("\n");
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) printf("%d ", p[i][j]);
		printf("\n");
	}
	printf("\n");
#endif

	printf("Result: %d\n", m[0][n-1]);
	output(s, 0, n-1);
	printf("\n");

	free(s);
	return 0;
}
