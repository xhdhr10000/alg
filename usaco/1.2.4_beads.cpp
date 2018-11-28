/*
ID: xhdhr203
LANG: C++
TASK: beads
*/
#include <stdio.h>
#include <stdlib.h>

int prev(int x, int N) {
    return (x - 1 + N) % N;
}

int next(int x, int N) {
    return (x + 1) % N;
}

int main(int argc, char const *argv[])
{
    FILE *fin = fopen("beads.in", "r");
    FILE *fout = fopen("beads.out", "w");
    int N;
    char beads[352];
    int max = 0;

    fscanf(fin, "%d %s", &N, beads);
    for (int i=0; i<N; i++) {
        int count = 0;
        int s = prev(i, N);
        while (s != i && beads[s] == 'w') {
            s = prev(s, N);
            count++;
        }
        int t = i;
        if (beads[t] == 'w') {
            do {
                t = next(t, N);
                count++;
            } while (t != i && beads[t] == 'w');
        }
        if (s == t || next(t, N) == s) {
            max = N;
            break;
        }
        count += 2;
        int a = prev(s, N);
        int b = next(t, N);
        while (a != b && (beads[a] == 'w' || beads[a] == beads[s])) {
            a = prev(a, N);
            count++;
        }
        while (a != b && (beads[b] == 'w' || beads[b] == beads[t])) {
            b = next(b, N);
            count++;
        }
        if (a == b && (beads[a] == 'w' || beads[a] == beads[s] || beads[a] == beads[t])) count++;
        if (count > max) max = count;
    }
    fprintf(fout, "%d\n", max);
    fclose(fin);
    fclose(fout);

    return 0;
}