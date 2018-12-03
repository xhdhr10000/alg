#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG

int** generate_data(int n) {
	srand(time(0));
	int **g = (int**)malloc(sizeof(int*)*n);
	int ans = rand() % 2;

	for (int i=0; i<n; i++) g[i] = (int*)malloc(sizeof(int)*n);
	if (ans) {
		printf("Input bipartite\n");
		int *part = (int*)malloc(sizeof(int)*n);
		for (int i=0; i<n; i++) part[i] = rand() % 2;
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				if (i == j) continue;
				if (part[i] != part[j]) {
					int e = rand() % 2;
					g[i][j] = g[j][i] = e;
				}
			}
		}
		free(part);
	} else {
		printf("Input not bipartite\n");
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				if (i == j) continue;
				int e = rand() % 2;
				g[i][j] = g[j][i] = e;
			}
		}
	}
	return g;
}

int bfs(int **g, int n) {
	int *part = (int*)malloc(sizeof(int)*n);
	int *queue = (int*)malloc(sizeof(int)*n);
	int head = -1, tail = -1;
	int ret = 0;

	memset(part, 0, sizeof(int)*n);
	while (tail < n-1) {
		for (int i=0; i<n; i++) {
			if (!part[i]) {
				tail++;
				queue[tail] = i;
				part[i] = 1;
				break;
			}
		}
		while (head < tail) {
			head++;
			int v = queue[head];
			for (int i=0; i<n; i++) {
				if (g[v][i]) {
					if (part[i] == 0) {
						part[i] = 3 - part[v];
						tail++;
						queue[tail] = i;
					} else if (part[i] > 0 && part[i] == part[v]) {
						ret = -1;
						goto out;
					}
				}
			}
		}
	}

out:
	printf("Result: ");
	for (int i=0; i<n; i++) printf("%d ", part[i]);
	printf("\n");
	free(part);
	return ret;
}

int main(int argc, char **argv) {
	int n = 10;
	int **g = generate_data(n);
#ifdef DEBUG
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) printf("%d ", g[i][j]);
		printf("\n");
	}
#endif
	int ret = bfs(g, n);
	if (ret) printf("Not bipartite\n");
	else printf("Bipartite\n");

	for (int i=0; i<n; i++) free(g[i]);
	free(g);
	return 0;
}
