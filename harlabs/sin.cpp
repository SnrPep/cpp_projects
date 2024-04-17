#include <stdio.h>
#include "math.h"

double s(int n, double x, double prev){
    double next;
    next = prev * ((-1) * pow(x, 2)) / ((2 * n) * (2 * n + 1));
    return next;
}

int main(){
    double a[500];
    double x = 1.9;
    double res = 1, res1=1,res2=0;
    a[0]=1;
    a[1]=0;
    int i;
    for (i = 1; i < 500; i++){
        res1 = s(i, x,res1);
        a[i]=res1;
        res += res1;
        if ((s(i,x,res1) + res == res)) {
            break;
        }
        //printf("%.50f  %d\n", res, i);
    }
    for (int k=i; k>=0; k--){
        //printf("%g\r\n",a[k]);
        res2 +=a[k];
    }
    printf("my %g\n", res2);
    printf("real %g\n", sin(x));
    printf("diff %g\n", res2-sin(x));
}