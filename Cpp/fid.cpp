#include <iostream>
#include "ctime"
#define N 1000
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
/// N=100   t=0.002 t=0.003
/// N=200   t=0.013 t=0.017
/// N=400   t=0.128 t=0.153
/// N=800   t=0.838 t=1.253
/// N=1000  t=1.595 t=3.878
/// N=2000  t=12.705 t=49.605
/// N=5000  t=199.127 t=1178.319


int main(){
    srand(time(NULL));
    int i, j;

    double** a = create_matrix(N);
    double** b = create_matrix(N);
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            a[i][j] = rand()%10;
            b[i][j] = rand()%10;
        }
    }

    double** c = create_matrix(N);
    double start=clock();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int r = A(i,j);
            for (int k = 0; k < N; k++) {
                c[i][k] += r * b[j][k];
            }
        }
    }
    double end=clock();
    printf("time %lf",((end-start)/(double)CLOCKS_PER_SEC));

    return 0;
}
