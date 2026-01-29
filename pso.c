#include "pso.h"
#include <stdlib.h>
#include <time.h>

const double k=0.1; 
static double vmax_x=1;
static double vmax_y=1;
double r1,r2;
int r_set=0;

// Prototypy z poprawionym typem double **
void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, double **matrix);
void free_particles(particle *dron);
position new_particle_velocity(particle dron, swarm roj);
position new_particle_position(particle dron);
coordinates max_particle_signal(double **matrix, particle dron);
coordinates max_swarm_signal(double **matrix, particle dron, swarm roj);
double max_val_particle(double **matrix, particle dron);
double max_val_swarm(double **matrix, swarm roj);
int is_inside_map(position p, int X, int Y);
double stochastic_elem();

void get_attrib(double *attrib, particle *dron, swarm *roj, int particle_count){
    for(int i=0;i<particle_count;i++){
        dron[i].weight = attrib[0];
        dron[i].trust = attrib[1];
    }
    roj->trust = attrib[3];
    r1 = attrib[2];
    r2 = attrib[4];
    r_set=1;    
}

coordinates PSO(double **matrix, particle *dron, swarm *roj, int X, int Y, int ilosc){
    for(int j=0; j<ilosc; j++){
        dron[j].velocity = new_particle_velocity(dron[j], *roj); 
        dron[j].current_position = new_particle_position(dron[j]); 
        
        if(is_inside_map(dron[j].current_position, X, Y)){ 
            dron[j].best_position = max_particle_signal(matrix, dron[j]); 
            // Aktualizacja pBest_val dla czastki
            dron[j].best_val = max_val_particle(matrix, dron[j]); 
            
            // Sprawdzenie i aktualizacja gBest dla calego roju
            if(dron[j].best_val > roj->best_val) { 
                roj->best_val = dron[j].best_val;
                roj->best_position = dron[j].best_position;
            }
        }
    }
    return roj->best_position; 
}

void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, double **matrix){
    vmax_x = k * zakres_x;
    vmax_y = k * zakres_y;
    
    roj->trust = 1.0; 
    roj->best_position.x = 0;
    roj->best_position.y = 0;
    roj->best_val = -1e9; // Startowa bardzo mala wartosc sygnallu

    for(int i=0; i<ilosc; i++){
        dron[i].current_position.x = rand() % zakres_x; 
        dron[i].current_position.y = rand() % zakres_y;
        dron[i].best_position.x = (int)dron[i].current_position.x;
        dron[i].best_position.y = (int)dron[i].current_position.y;
        
        // Pobranie wartosci startowej pBest_val
        dron[i].best_val = matrix[(int)dron[i].best_position.y][(int)dron[i].best_position.x];

        dron[i].velocity.x = -vmax_x + (2.0 * vmax_x * rand() / (double)RAND_MAX); 
        dron[i].velocity.y = -vmax_y + (2.0 * vmax_y * rand() / (double)RAND_MAX);
        
        dron[i].trust = 0.9; 
        dron[i].weight = 0.5; 

        // Wstepna aktualizacja gBest roju
        if(dron[i].best_val > roj->best_val) {
            roj->best_val = dron[i].best_val;
            roj->best_position = dron[i].best_position;
        }
    }
}

int is_inside_map(position p, int X, int Y){
    return (p.x >= 0 && p.x < X && p.y >= 0 && p.y < Y); 
}

coordinates max_particle_signal(double **matrix, particle dron){
    coordinates new_particle_best;
    // Zamiana [x][y] na [y][x]
    if(matrix[(int)dron.current_position.y][(int)dron.current_position.x] >= matrix[dron.best_position.y][dron.best_position.x]){ 
        new_particle_best.x = (int)dron.current_position.x;
        new_particle_best.y = (int)dron.current_position.y;
        return new_particle_best;
    }
    else
        return dron.best_position;
}

double max_val_particle(double **matrix, particle dron){
    // Zamiana [x][y] na [y][x]
    return matrix[dron.best_position.y][dron.best_position.x]; 
}

coordinates max_swarm_signal(double **matrix, particle dron, swarm roj){
    coordinates new_swarm_best;
    // Zamiana [x][y] na [y][x]
    if(matrix[dron.best_position.y][dron.best_position.x] >= matrix[roj.best_position.y][roj.best_position.x]){ 
        new_swarm_best.x = (int)dron.best_position.x;
        new_swarm_best.y = (int)dron.best_position.y;
        return new_swarm_best;
    }
    else
        return roj.best_position;
}

double max_val_swarm(double **matrix, swarm roj){
    // Zamiana [x][y] na [y][x]
    return matrix[roj.best_position.y][roj.best_position.x]; 
}

position new_particle_velocity(particle dron, swarm roj){
    position new_velocity;
    if(r_set!=0){
        r1 = stochastic_elem(); 
        r2 = stochastic_elem();
    }
    new_velocity.x = dron.weight*dron.velocity.x + dron.trust*r1 * (dron.best_position.x - dron.current_position.x) + roj.trust*r2 * (roj.best_position.x - dron.current_position.x); 
    new_velocity.y = dron.weight*dron.velocity.y + dron.trust*r1 * (dron.best_position.y - dron.current_position.y) + roj.trust*r2 * (roj.best_position.y - dron.current_position.y);
    
    if(new_velocity.x > vmax_x) new_velocity.x = vmax_x;
    if(new_velocity.x < -vmax_x) new_velocity.x = -vmax_x;
    if(new_velocity.y > vmax_y) new_velocity.y = vmax_y;
    if(new_velocity.y < -vmax_y) new_velocity.y = -vmax_y;
    
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
