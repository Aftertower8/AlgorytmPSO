#include "pso.h"
#include <stdlib.h>
#include <time.h>
//gdzies tu trzeba bedzie wczytac logger
const int ITERACJE = 500; //wstepnie, pozniej mozna sprawic aby uzytkownik podawal ilosc iteracji
const double k=0.1; //procent przestrzeni, czyli czasteczka moze przejsc max 10% planszy w ciagu jednej iteracji (w jednej osi)
static double vmax_x=1;
static double vmax_y=1;

void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, int **matrix);
position new_particle_velocity(particle dron, swarm roj);
position new_particle_position(particle dron);
coordinates max_particle_signal(int **matrix, particle dron);
coordinates max_swarm_signal(int **matrix, particle dron, swarm roj);
double max_val_particle(int **matrix, particle dron);
double max_val_swarm(int **matrix, swarm roj);
double stochastic_elem();

coordinates PSO(int **matrix, int X, int Y, int ilosc){
    particle *dron = (particle*)malloc(ilosc * sizeof(particle));
    swarm roj;
    srand(time(NULL));
    init_particles(dron,&roj,ilosc,X,Y,matrix);
    for(int i=0;i<ITERACJE;i++){
        for(int j=0;j<ilosc;j++){
            dron[j].velocity = new_particle_velocity(dron[j],roj);
            dron[j].current_position = new_particle_position(dron[j]);
            dron[j].best_position = max_particle_signal(matrix,dron[j]);
            roj.best_position = max_swarm_signal(matrix,dron[j],roj);
            dron[j].best_val=max_val_particle(matrix,dron[j]);
            roj.best_val = max_val_swarm(matrix,roj);\
            /*
            Gdzies tutaj dodamy funkcje z loggera zeby wypisywal cale to info do osobnego pliku tekstowego
            */
        }
    }
    free(dron);
    return roj.best_position;
}

void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, int **matrix){
    vmax_x = k*zakres_x;
    vmax_y = k*zakres_y;
    roj->trust = 1.0;
    roj->best_position.x=0;  //zainicjowanie roj.best_position
    roj->best_position.y=0;
    for(int i=0;i<ilosc;i++){
        dron[i].current_position.x = rand() % zakres_x;
        dron[i].current_position.y = rand() % zakres_y;
        dron[i].best_position.x=dron[i].current_position.x;
        dron[i].best_position.y=dron[i].current_position.y;
        roj->best_position = max_swarm_signal(matrix,dron[i],*roj);
        dron[i].velocity.x = -vmax_x + (2.0 * vmax_x * rand() / (double)RAND_MAX);
        dron[i].velocity.y = -vmax_y + (2.0 * vmax_y * rand() / (double)RAND_MAX);
        dron[i].trust = 0.9;
        dron[i].weight = 0.5;
    }
    
}

coordinates max_particle_signal(int **matrix, particle dron){
    coordinates new_particle_best;
    if(matrix[(int)dron.current_position.x][(int)dron.current_position.y]>=matrix[(int)dron.best_position.x][(int)dron.best_position.y]){
        new_particle_best.x=(int)dron.current_position.x;
        new_particle_best.y=(int)dron.current_position.y;
        return new_particle_best;
    }
    else
        return dron.best_position;
}

double max_val_particle(int **matrix, particle dron){
    return matrix[dron.best_position.x][dron.best_position.y];
}

coordinates max_swarm_signal(int **matrix, particle dron, swarm roj){
    coordinates new_swarm_best;
    if(matrix[dron.best_position.x][dron.best_position.y]>=matrix[roj.best_position.x][roj.best_position.y]){
        new_swarm_best.x=(int)dron.best_position.x;
        new_swarm_best.y=(int)dron.best_position.y;
        return new_swarm_best;
    }
    else
        return roj.best_position;
}

double max_val_swarm(int **matrix, swarm roj){
    return matrix[roj.best_position.x][roj.best_position.y];
}

position new_particle_velocity(particle dron, swarm roj){
    position new_velocity;
    double r1=stochastic_elem();
    double r2=stochastic_elem();
    new_velocity.x = dron.weight*dron.velocity.x + dron.trust*r1 * (dron.best_position.x - dron.current_position.x) + roj.trust*r2 * (roj.best_position.x - dron.current_position.x);
    new_velocity.y = dron.weight*dron.velocity.y + dron.trust*r1 * (dron.best_position.y - dron.current_position.y) + roj.trust*r2 * (roj.best_position.y - dron.current_position.y);
    if(new_velocity.x>vmax_x)
        new_velocity.x=vmax_x;
    if(new_velocity.x<-vmax_x)
        new_velocity.x=-vmax_x;
    if(new_velocity.y>vmax_y)
        new_velocity.y=vmax_y;
    if(new_velocity.y<-vmax_y)
        new_velocity.y=-vmax_y;
    return new_velocity;
}

position new_particle_position(particle dron){
    position new_position;
    new_position.x = dron.current_position.x + dron.velocity.x;
    new_position.y = dron.current_position.y + dron.velocity.y;
    return new_position;
}

double stochastic_elem(){
    return rand() / (double)RAND_MAX;
}