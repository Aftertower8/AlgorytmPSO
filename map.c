#include <stdlib.h>
#include "map.h"
double** ReadFromFile(FILE *in, int *W, int *H){
    
    if(fscanf(in,"%d%d",&W,&H) !=2) return NULL;
    int rzedy = *H;
    int kolumny = *W;

    double **matrix = malloc(rzedy*sizeof(double));
    for(int i=0;i<rzedy;i++){
        matrix[i] = malloc(kolumny*sizeof(double));
        for(int j=0;j<kolumny;j++){
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