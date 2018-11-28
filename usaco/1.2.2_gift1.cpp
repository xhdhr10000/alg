/*
ID: xhdhr203
LANG: C++
TASK: gift1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *fin = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");
    int n;
    char names[10][20];
    int money[10];

    fscanf(fin, "%d", &n);
    for (int i=0; i<n; i++) {
        fscanf(fin, "%s", names[i]);
        money[i] = 0;
    }
    for (int i=0; i<n; i++) {
        char name[20];
        fscanf(fin, "%s", name);
        int who;
        for (who=0; who<n; who++)
            if (!strcmp(names[who], name)) break;
        int total, number;
        fscanf(fin, "%d%d", &total, &number);
        if (number == 0) {
            money[who] += total;
        } else {
            money[who] += total % number - total;
            for (int j=0; j<number; j++) {
                fscanf(fin, "%s", name);
                int to;
                for (to=0; to<n; to++)
                    if (!strcmp(names[to], name)) break;
                money[to] += total / number;
            }
        }
    }
    for (int i=0; i<n; i++) {
        fprintf(fout, "%s %d\n", names[i], money[i]);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}