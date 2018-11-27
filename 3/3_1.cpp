#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG

struct Edge {
	int from;
	int to;
	int length;
	Edge *next;
};

struct Edge* generate_data(int n) {
	Edge *d = (Edge*)malloc(sizeof(Edge)*n);
	srand(time(0));
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			if (rand() % 2) {
				int l = rand() % 2 + 1;
				Edge *e = (Edge*)malloc(sizeof(Edge));
				e->next = d[i].next;
				e->length = l;
				e->to = j;
				d[i].next = e;

				e = (Edge*)malloc(sizeof(Edge));
				e->next = d[j].next;
				e->length = l;
				e->to = i;
				d[j].next = e;
			}
		}
	}
	return d;
}

void outputMatrix(int n, Edge *g) {
	int **matrix = (int**)malloc(sizeof(int*)*n);
	for (int i=0; i<n; i++) {
		matrix[i] = (int*)malloc(sizeof(int)*n);
		for (int j=0; j<n; j++) matrix[i][j] = 0;
		Edge *p = g[i].next;
		while (p) {
			matrix[i][p->to] = p->length;
			p = p->next;
		}
	}
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) printf("%d ", matrix[i][j]);
		printf("\n");
	}
	for (int i=0; i<n; i++) free(matrix[i]);
	free(matrix);
}

void addEdges(int x, Edge *g, Edge **head, Edge **tail, int *hash) {
#ifdef DEBUG
	printf("Adding edges from %d\n", x);
	for (int i=0; i<10; i++) printf("%d ", hash[i]);
	printf("\n");
#endif
	Edge *p = g[x].next;
	while (p) {
#ifdef DEBUG
		printf("Edge %d->%d: %d\n", x, p->to, p->length);
#endif
		if (!hash[p->to]) {
			Edge *e = (Edge*)malloc(sizeof(Edge));
			e->from = x;
			e->to = p->to;
			e->length = p->length;
			e->next = NULL;
			if (!(*head)) {
				*head = e;
				*tail = e;
			} else if (e->length == 1) {
				e->next = *head;
				*head = e;
#ifdef DEBUG
				printf("Head %d->%d: %d\n", (*head)->from, (*head)->to, (*head)->length);
#endif
			} else if (e->length == 2) {
				(*tail)->next = e;
				*tail = e;
#ifdef DEBUG
				printf("Tail %d->%d: %d\n", (*tail)->from, (*tail)->to, (*tail)->length);
#endif
			}
		}
		p = p->next;
	}
#ifdef DEBUG
	p = *head;
	while (p) {
		printf("%d->%d: %d\n", p->from, p->to, p->length);
		p = p->next;
	}
#endif
}

int* MST(Edge *g, int n) {
	int *prev = (int*)malloc(sizeof(int)*n);
	int total = 0;
	int *hash = (int*)malloc(sizeof(int)*n);
	Edge *head = NULL, *tail = NULL;

	for (int i=0; i<n; i++) prev[i] = -1;
	memset(hash, 0, sizeof(int)*n);
	hash[0] = 1;
	addEdges(0, g, &head, &tail, hash);

	for (int i=1; i<n; i++) {
		while (head && hash[head->to]) {
			printf("Repeat %d->%d\n", head->from, head->to);
			Edge *e = head;
			head = head->next;
			free(e);
		}
		if (!head) {
			printf("Error in iteration %d\n", i);
			break;
		}
		Edge *e = head;
		head = head->next;
		hash[e->to] = 1;
		prev[e->to] = e->from;
		total += e->length;
		addEdges(e->to, g, &head, &tail, hash);
	}

	printf("Total length %d\n", total);
	free(hash);
	while (head) {
		Edge *e = head;
		head = head->next;
		free(e);
	}
	return prev;
}

int main(int argc, char **argv) {
	int n = 10;
	Edge *g = generate_data(n);
	outputMatrix(n, g);

	int *ret = MST(g, n);

	printf("Result: ");
	for (int i=0; i<n; i++) printf("%d ", ret[i]);
	printf("\n");
	outputMatrix(n, g);

	free(ret);
	for (int i=0; i<n; i++) {
		Edge *p = g[i].next;
		while (p) {
			Edge *l = p;
			p = p->next;
			free(l);
		}
	}
	free(g);
	return 0;
}
