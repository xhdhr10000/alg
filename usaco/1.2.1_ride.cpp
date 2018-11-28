/*
ID: xhdhr203
LANG: C++
TASK: ride
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");
    char s1[8], s2[8];
    int n1 = 1, n2 = 1;
    fscanf(fin, "%s%s", s1, s2);
    for (int i=0; i<strlen(s1); i++) n1 = n1 * (s1[i] - 'A' + 1) % 47;
    for (int i=0; i<strlen(s2); i++) n2 = n2 * (s2[i] - 'A' + 1) % 47;
    if (n1 == n2) fprintf(fout, "GO\n");
    else fprintf(fout, "STAY\n");
    fclose(fin);
    fclose(fout);
    return 0;
}