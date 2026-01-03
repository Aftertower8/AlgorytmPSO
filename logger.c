#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> //mkdir
#include "logger.h"

void logger_init(const char *filename){

    FILE *in =fopen(filename, "w");
    if(in ==NULL){
        fprintf(stderr, "Blad: Nie mozna utworzyc pliku logow: %s\n", filename);
        return;
    }
    // Naglowek
    fprintf(in, "iteracja,id,x,y,best_val,vx,vy\n");
    fclose(in);
}

void log_swarm(const char *filename, int iteration, particle *drones, int count){
    // Otwieram w trybie "a" (append) - dopisze na koniec pliku
    // count - ile dronow
    FILE *in = fopen(filename, "a");
    if(in ==NULL){
        fprintf(stderr, "Blad: Nie mozna dopisac do logu %s\n", filename);
        return;
    }
    for(int i=0; i< count; i++){
        fprintf(in, "%d,%d,%.4f,%.4f,%.4f,%.4f,%.4f\n",
        iteration,
        i,
        drones[i].current_position.x,
        drones[i].current_position.y,
        drones[i].best_val,
        drones[i].velocity.x,
        drones[i].velocity.y
    );
     }
     fclose(in);
}