#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>

#define MIN(X,Y) ((X)<(Y)?(X):(Y))
#define DEBUG

using namespace std;

class Heap {
	int *points;
	unsigned int *values;
	int n, p;

public:
	Heap(int n) {
		this->n = n;
		this->p = 0;
		this->points = (int*)malloc(sizeof(int)*n*10);
		this->values = (unsigned int*)malloc(sizeof(unsigned int)*n*10);
	}

	~Heap() {
		free(this->points);
		free(this->values);
	}

	void insert(int p, int v) {
		this->p++;
		this->points[this->p] = p;
		this->values[this->p] = v;
		int i = this->p;
		while (i > 1 && this->values[i] > this->values[i/2]) {
			this->swap(i, i/2);
			i /= 2;
		}
	}

	void modify(int p, int v) {
		int i;
		for (i=1; i<=this->p; i++) {
			if (this->points[i] == p) {
				this->values[i] = v;
				break;
			}
		}
		while (i > 1 && this->values[i] > this->values[i/2]) {
			this->swap(i, i/2);
			i /= 2;
		}
	}

	int extract() {
		int ret = this->points[1];
		this->points[1] = this->points[this->p];
		this->values[1] = this->values[this->p];
		this->p--;
		int i = 1;
		while (i*2+1 <= this->p && (this->values[i] < this->values[i*2] || this->values[i] < this->values[i*2+1])) {
			if (i*2+1 > this->p || this->values[i*2] > this->values[i*2+1]) {
				this->swap(i, i*2);
				i *= 2;
			} else {
				this->swap(i, i*2+1);
				i = i*2+1;
			}
		}
		return ret;
	}

	void dump() {
		printf("Points: ");
		for (int i=1; i<=this->p; i++) printf("%d ", this->points[i]);
		printf("\nValues: ");
		for (int i=1; i<=this->p; i++) printf("%d ", this->values[i]);
		printf("\n");
	}

	void swap(int x, int y) {
		int c;
		c = this->points[x];
		this->points[x] = this->points[y];
		this->points[y] = c;

		c = this->values[x];
		this->values[x] = this->values[y];
		this->values[y] = c;
	}
};

int** generate_data(int n) {
	srand(time(0));
	int **g = (int**)malloc(sizeof(int*)*(n+1));
	
	for (int i=1; i<=n; i++) g[i] = (int*)malloc(sizeof(int)*(n+1));
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			if (i == j) continue;
			int e = rand() % n;
			g[i][j] = g[j][i] = e;
		}
	}
	return g;
}

int main(int argc, char **argv) {
	int n = 10;
	int **g = generate_data(n);
	int s = rand() % n + 1;
	int t = rand() % n + 1;
	unsigned int *dist = (unsigned int*)malloc(sizeof(int)*(n+1));
	int *prev = (int*)malloc(sizeof(int)*(n+1));
	Heap *h = new Heap(n);

#ifdef DEBUG
	printf("Input:\n");
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) printf("%d ", g[i][j]);
		printf("\n");
	}
	printf("\n\n");
	printf("s=%d t=%d\n", s, t);
#endif
	memset(dist, 0, sizeof(dist));
	dist[s] = -1;
	prev[s] = -1;
	for (int i=1; i<=n; i++) {
		//dist[i] = -1;
		h->insert(i, dist[i]);
	}
	h->dump();
	while (1) {
		int p = h->extract();
		if (p == t) {
			printf("\nAnswer: %d\n", dist[t]);
			int i = t;
			printf("Path: ");
			while (i != -1) {
				printf("%d ", i);
				i = prev[i];
			}
			printf("\n");
			break;
		}
		printf("Current: %d\n", p);
		for (int i=1; i<=n; i++) {
			if (i == p) continue;
			if (!g[p][i]) continue;
			int v = MIN(dist[p], g[p][i]);
			if (v > dist[i]) {
				dist[i] = v;
				prev[i] = p;
				h->modify(i, dist[i]);
			}
		}
		h->dump();
	}

	delete h;
	free(prev);
	free(dist);
	for (int i=0; i<n; i++) free(g[i]);
	free(g);
	return 0;
}
