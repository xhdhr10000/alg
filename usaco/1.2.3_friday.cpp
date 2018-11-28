/*
ID: xhdhr203
LANG: C++
TASK: friday
*/
#include <stdio.h>
#include <stdlib.h>

int leapYear(int year) {
    return year % 100 == 0 ? !(year % 400) : !(year % 4);
}

int main(int argc, char const *argv[])
{
    FILE *fin = fopen("friday.in", "r");
    FILE *fout = fopen("friday.out", "w");
    const int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int N, current = 0;
    int ans[7];

    fscanf(fin, "%d", &N);
    for (int i=0; i<7; i++) ans[i] = 0;
    for (int i=1900; i<1900+N; i++) {
        for (int j=0; j<12; j++) {
            ans[current]++;
            if (j == 1 && leapYear(i))
                current = (current + 29) % 7;
            else
                current = (current + days[j]) % 7;
        }
    }
    for (int i=0; i<6; i++) fprintf(fout, "%d ", ans[i]);
    fprintf(fout, "%d\n", ans[6]);
    fclose(fin);
    fclose(fout);

    return 0;
}