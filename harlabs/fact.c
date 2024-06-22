//
// Created by zubar on 22.05.2024.
//
#include <stdio.h>
long long int Pow(int n, int v)
{
    int i; long long  r;
    r=1;
    for(i=0; i<n; i++)
        r*=v;
    return r;
}
int main( int ac, char *av[])
{
    long long int d[20][40]; int i,j,k;
    int Nv=12;
    int Nt=9, Power=8;
    sscanf(av[1],"%d",&Power);
    Nt=Power+1;
    for (k=0; k<20; k++)
        for (j=0; j<40; j++) d[k][j]=0L;

    for (j=0; j<40; j++)
        d[0][j]=Pow(Power,j);

    for (k=1; k<Nt; k++)
        for (j=0; j<40-k; j++)
            d[k][j]=d[k-1][j+1]-d[k-1][j];

    for(k=0; k<Nt; k++)
    {
        for (j=0; j<Nv; j++)
            printf("%9Ld ",d[k][j]);
        printf("\n");
    }
    return 0;
}
