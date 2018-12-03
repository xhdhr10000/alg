#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>

#define DEBUG

using namespace std;

int* generate_data(int n) {
	int *h = (int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++) h[i] = rand() % (n * 100);
	sort(&h[0], &h[n]);
	return h;
}

int main(int argc, char **argv) {
	srand(time(0));
	int n = 20;
	int c = rand() % (n * 100);
	int *h = generate_data(n);
	int *ans = (int*)malloc(sizeof(int)*n);
	int p = 0;

#ifdef DEBUG
	printf("Input: ");
	for (int i=0; i<n; i++) printf("%d ", h[i]);
	printf("\n");
	printf("c=%d\n", c);
#endif

	ans[p] = h[0] + c;
	for (int i=1; i<n; i++) {
		if (h[i] - ans[p] > c)
			ans[++p] = h[i] + c;
	}

	printf("Result: ");
	for (int i=0; i<=p; i++) printf("%d ", ans[i]);
	printf("\n");

	free(ans);
	free(h);
	return 0;
}
