#include <stdlib.h>
#include "map.h"
double** ReadFromFile(FILE *in){
    int W=0,H=0;
    fscanf(in,"%d%d",&W,&H);
    double **matrix = malloc(H*sizeof(double));
    for(int i=0;i<H;i++){
        matrix[i] = malloc(W*sizeof(double));
        for(int j=0;j<W;j++){
            fscanf(in,"%lf",&matrix[i][j]);
        }
    }
    return matrix;
}

void free_matrix(int **matrix, int H){
    for(int i=0;i<H;i++){
        free(matrix[i]);
    }
    free(matrix);
}