#include "pso.h"
#include <stdlib.h>
#include <time.h>
const double k=0.1; //procent przestrzeni, czyli czasteczka moze przejsc max 10% planszy w ciagu jednej iteracji (w jednej osi)
static double vmax_x=1;
static double vmax_y=1;
//zeby zainicjowac struktury wywolac init_particles(...)
//pozniej w petli w main dla kazdej iteracji wywolywac PSO(...) - przesuniecie czastek o jedna iteracje

void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, int **matrix);
void free_particles(particle *dron);
position new_particle_velocity(particle dron, swarm roj);
position new_particle_position(particle dron);
coordinates max_particle_signal(double **matrix, particle dron);
coordinates max_swarm_signal(double **matrix, particle dron, swarm roj);
double max_val_particle(double **matrix, particle dron);
double max_val_swarm(double **matrix, swarm roj);
int is_inside_map(position p, int X, int Y);
double stochastic_elem();

coordinates PSO(double **matrix, particle *dron, swarm *roj, int X, int Y, int ilosc){
        for(int j=0;j<ilosc;j++){
            dron[j].velocity = new_particle_velocity(dron[j],*roj);
            dron[j].current_position = new_particle_position(dron[j]);
            if(is_inside_map(dron[j].current_position,X,Y)){
                dron[j].best_position = max_particle_signal(matrix,dron[j]);
                roj->best_position = max_swarm_signal(matrix,dron[j],*roj);
                dron[j].best_val=max_val_particle(matrix,dron[j]);
                roj->best_val = max_val_swarm(matrix,*roj);
            }
        }
    return roj->best_position;
}

void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, int **matrix){
    srand(time(NULL));
    dron = (particle*)malloc(ilosc*sizeof(particle));
    swarm roj;
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

int is_inside_map(position p, int X, int Y){
    return (p.x >= 0 && p.x < X && p.y >= 0 && p.y < Y);
}


coordinates max_particle_signal(double **matrix, particle dron){
    coordinates new_particle_best;
    if(matrix[(int)dron.current_position.x][(int)dron.current_position.y]>=matrix[(int)dron.best_position.x][(int)dron.best_position.y]){
        new_particle_best.x=(int)dron.current_position.x;
        new_particle_best.y=(int)dron.current_position.y;
        return new_particle_best;
    }
    else
        return dron.best_position;
}

double max_val_particle(double **matrix, particle dron){
    return matrix[dron.best_position.x][dron.best_position.y];
}

coordinates max_swarm_signal(double **matrix, particle dron, swarm roj){
    coordinates new_swarm_best;
    if(matrix[dron.best_position.x][dron.best_position.y]>=matrix[roj.best_position.x][roj.best_position.y]){
        new_swarm_best.x=(int)dron.best_position.x;
        new_swarm_best.y=(int)dron.best_position.y;
        return new_swarm_best;
    }
    else
        return roj.best_position;
}

double max_val_swarm(double **matrix, swarm roj){
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

void free_particles(particle *dron){
    free(dron);
}