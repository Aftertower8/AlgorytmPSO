#include "pso.h"
#include <stdlib.h>
#include <time.h>
#define ITERACJE 500 //roboczo
coordinates PSO(int **matrix, int X, int Y, int ilosc){
    particle *dron = (particle*)malloc(ilosc * sizeof(particle));
    swarm roj;
    srand(time(NULL));
    init_particles(dron,&roj,ilosc,X,Y,matrix);
}

void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, int **matrix){
    for(int i=0;i<ilosc;i++){
        dron[i].current_position.x = rand() % zakres_x;
        dron[i].current_position.y = rand() % zakres_y;
        dron[i].best_position.x=dron[i].current_position.x;
        dron[i].best_position.y=dron[i].current_position.y;
        max_signal(matrix,&dron[i],roj);
        dron[i].velocity.x = -1 + rand()/(R)
    }
}

void max_signal(int **matrix, particle *dron, swarm *roj){
    if(matrix[(int)dron->current_position.x][(int)dron->current_position.y]>matrix[(int)dron->best_position.x][(int)dron->best_position.y]){
        dron->best_position.x=dron->current_position.x;
        dron->best_position.y=dron->current_position.y;
    }
    if(matrix[dron->best_position.x][dron->best_position.y]>matrix[roj->best_position.x][roj->best_position.y]){
        roj->best_position.x=dron->best_position.x;
        roj->best_position.x=dron->best_position.y;
    }
}