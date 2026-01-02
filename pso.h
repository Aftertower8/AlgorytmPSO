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
    double random_val; //zakres <0;1>, element stochastyczny
} particle; //bedzie zrobiona tablica czasteczek(particle) - rozmiar podany przez uzytkownika

typedef struct {
    coordinates best_position;
    double best_val;
    double trust;
    double random_val;
} swarm;

coordinates PSO(int **matrix, int X, int Y, int ilosc);
#endif