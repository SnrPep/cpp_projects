#include <iostream>
#include "ctime"
#define N 100
#define A(r,c) a[r][c]

double** create_matrix(int n){
    int i;
    double** res = new double *[n];
    for (i = 0; i < n; i++){
        res[i] = new double [n];
    }
    return res;
}
///
/// N=100  t=0.009
/// N=200  t=0.063
/// N=400  t=0.25
/// N=800  t=1.812
/// N=1000  t=3.878
/// N=2000  t=49.605
/// N=5000  t=0.005


int main(){
    srand(time(NULL));
    int n, i, j, k;
    n=N;
    double** a = create_matrix(n);
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            a[i][j] = rand()%10;
        }
    }
    /*printf("Введенная матрица:\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%lf\t", a[i][j]);
        }
        printf("\n");
    }*/
    double** b = create_matrix(n);
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            b[i][j] = rand()%10;
        }
    }
    /*printf("Введенная матрица:\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%lf\t", b[i][j]);
        }
        printf("\n");
    }*/
    double** c = create_matrix(n);
    double start=clock();
    double r;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            r = a[i][j];
            for (k = 0; k < n; k++){
                c[i][k] += r* b[j][k];
            }
        }
    }
    double end=clock();
    printf("time %lf",((end-start)/1000000));
    /*printf("Результат перемножения матриц:\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%lf\t", c[i][j]);
        }
        printf("\n");
    }*/
    return 0;
}