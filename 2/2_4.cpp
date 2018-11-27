#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG
#define MAX_INT 0x7fffffff

struct TreeNode {
	int value;
	int max;
	int start, end;
};

unsigned int m2(unsigned int x) {
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return x;
}

void swap(int *x, int *y) {
	*x += *y;
	*y = *x - *y;
	*x -= *y;
}

int* generate_data(int n) {
	int *d = (int*)malloc(sizeof(int)*(n+1));
	for (int i=1; i<=n; i++) d[i] = rand() % (n*10);
	return d;
}

void create_tree(int *d, TreeNode *t, int p, int x, int y) {
	int c = (x+y)/2;
	t[p].value = d[c];
	t[p].max = d[c];
	t[p].start = x;
	t[p].end = y;
	if (x < c) create_tree(d, t, p*2, x, c-1);
	if (c < y) create_tree(d, t, p*2+1, c+1, y);
}

void create_max(TreeNode *t, int n, int x) {
	if (x >= n || x*2 >= n) return;
	create_max(t, n, x*2);
	create_max(t, n, x*2+1);
	if (t[x*2].max > t[x].max) t[x].max = t[x*2].max;
	if (x*2+1 < n && t[x*2+1].max > t[x].max) t[x].max = t[x*2+1].max;
}

int find_max(TreeNode *t, int x, int p, int q) {
	//printf("%d:[%d, %d] in [%d, %d]\n", x, t[x].start, t[x].end, p, q);
	if (t[x].start >= p && t[x].end <= q) return t[x].max;
	if (t[x].start > q || t[x].end < p) return -MAX_INT;
	int m = -MAX_INT, v, c = (t[x].start+t[x].end)/2;
	if (c >= p && c <= q) m = t[x].value;
	if (c > p && c > t[x].start) {
		v = find_max(t, x*2, p, q);
		if (v > m) m = v;
	}
	if (c < q && c < t[x].end) {
		v = find_max(t, x*2+1, p, q);
		if (v > m) m = v;
	}
	return m;
}

int main(int argc, char **argv) {
	int T = 1;
	unsigned int n = 15;
	if (argc > 1) n = atoi(argv[1]);
	if (argc > 2) T = atoi(argv[2]);

	srand(time(0));
	for (int t=0; t<T; t++) {
		int *d = generate_data(n);
#ifdef DEBUG
		printf("Data: ");
		for (int i=1; i<=n; i++) printf("%d ", d[i]);
		printf("\n");
#endif

		/* create tree */
		TreeNode *tree = (TreeNode*)malloc(sizeof(TreeNode)*m2(n));
		create_tree(d, tree, 1, 1, n);
		create_max(tree, m2(n), 1);
#ifdef DEBUG
		printf("Tree: ");
		for (int i=1; i<m2(n); i++) printf("%d ", tree[i].value);
		printf("\nMax:  ");
		for (int i=1; i<m2(n); i++) printf("%d ", tree[i].max);
		printf("\n");
#endif

		/* query */
		for (int tt=0; tt<T; tt++) {
			int p = rand() % n + 1;
			int q = rand() % n + 1;
			if (p > q) swap(&p, &q);
			int r = find_max(tree, 1, p, q);
#ifdef DEBUG
			printf("max in [%d, %d] is %d\n", p, q, r);
#endif

			/* verify */
			int m = -MAX_INT;
			for (int i=p; i<=q; i++)
				if (d[i] > m) m = d[i];
			if (m != r) printf("Error %d, actual is %d\n", r, m);
		}
		free(tree);
		free(d);
	}

	return 0;
}
