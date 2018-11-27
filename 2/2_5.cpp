#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG

struct Node {
	int x;
	struct Node *next;
};

Node* generate_data(int n, int *degree, int *count) {
	Node *d = (Node*)malloc(sizeof(Node)*n);
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			int e = rand() % 2;
			if (e) {
				Node *n = (Node*)malloc(sizeof(Node));
				n->x = j;
				n->next = NULL;
				if (d[i].next) n->next = d[i].next;
				d[i].next = n;

				n = (Node*)malloc(sizeof(Node));
				n->x = i;
				if (d[j].next) n->next = d[j].next;
				d[j].next = n;

				degree[i]++;
				degree[j]++;
				(*count)++;
			}
		}
	}
	return d;
}

void find(int x, Node *d, int *degree, int *path, int *p) {
	while (degree[x] > 0) {
		Node *n = d[x].next;
		d[x].next = n->next;
		degree[x]--;
		find(n->x, d, degree, path, p);
		free(n);
	}
	path[(*p)++] = x;
}

int main(int argc, char **argv) {
	int T = 1;
	int n = 6;
	if (argc > 1) n = atoi(argv[1]);
	if (argc > 2) T = atoi(argv[2]);

	srand(time(0));
	for (int t=0; t<T; t++) {
		int count = 0;
		int *degree = (int*)malloc(sizeof(int)*n);
		memset(degree, 0, sizeof(int)*n);
		Node *d = generate_data(n, degree, &count);
		count *= 2;
#ifdef DEBUG
		for (int i=0; i<n; i++) {
			printf("%d: ", i);
			Node *p = d[i].next;
			while (p) {
				printf("%d ", p->x);
				p = p->next;
			}
			printf("\n");
		}
		printf("Degree: ");
		for (int i=0; i<n; i++) printf("%d ", degree[i]);
		printf("\n");
		printf("Count of edges: %d\n", count);
#endif

		int *path = (int*)malloc(sizeof(int)*(count+2));
		int p = 0;
		find(0, d, degree, path, &p);
#ifdef DEBUG
		printf("Result: count=%d\n", p);
		for (int i=p-1; i>=0; i--) printf("%d ", path[i]);
		printf("\n");
#endif
		if (count + 1 != p) printf("ERROR\n");

		free(degree);
		free(path);
		free(d);
	}
	return 0;
}
