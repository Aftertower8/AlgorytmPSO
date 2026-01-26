#ifndef PSO_H
#define PSO_H
typedef struct {
    int x;
    int y;
} coordinates;  //dyskretne koordynaty mapy

typedef struct {
    double x;
    double y;
} position;     //przestrzen ciagla czasteczki

typedef struct {
    position current_position;
    position velocity;
    coordinates best_position;
    double best_val;
    double trust;
    double weight;
} particle; //bedzie zrobiona tablica czasteczek(particle) - rozmiar podany przez uzytkownika

typedef struct {
    coordinates best_position;
    double best_val;
    double trust;
} swarm;
void init_particles(particle *dron, swarm *roj, int ilosc, int zakres_x, int zakres_y, double **matrix);
void free_particles(particle *dron);
coordinates PSO(double **matrix, particle *dron, swarm *roj, int X, int Y, int ilosc);

#endif