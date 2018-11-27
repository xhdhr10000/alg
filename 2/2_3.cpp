#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define DEBUG

int *generate_data(int n) {
	int *d = (int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++) d[i] = rand() % 3 + 1;
	return d;
}

int swap(int *d, int x, int y) {
	int c = d[x];
	d[x] = d[y];
	d[y] = c;
}

int sort(int *d, int x, int y) {
	int a=x, b=y, c;
	while (a < b) {
		while (a < b && d[a] <= 2) a++;
		while (a < b && d[b] >= 2) b--;
		swap(d, a, b);
	}
	if (d[b] > 2) b--;
	c = b + 1;
	a = x;
	while (a < b) {
		while (a < b && d[a] == 1) a++;
		while (a < b && d[b] == 2) b--;
		swap(d, a, b);
	}
	a = c;
	b = y;
	while (a < b) {
		while (a < b && d[a] == 2) a++;
		while (a < b && d[b] == 3) b--;
		swap(d, a, b);
	}
}

int verify(int *d, int n) {
	for (int i=0; i<n-1; i++)
		if (d[i] > d[i+1]) return -1;
	return 0;
}

int main(int argc, char **argv) {
	srand(time(0));
	int T = 1;
	int n = 20;
	if (argc > 1) n = atoi(argv[1]);
	if (argc > 2) T = atoi(argv[2]);

	for (int t=0; t<T; t++) {
		int *d = generate_data(n);
#ifdef DEBUG
		for (int i=0; i<n; i++) printf("%d,", d[i]); printf("\n");
#endif
		sort(d, 0, n-1);
#ifdef DEBUG
		for (int i=0; i<n; i++) printf("%d,", d[i]); printf("\n");
#endif
		if (verify(d, n)) printf("ERROR\n");
	}
	return 0;
}
