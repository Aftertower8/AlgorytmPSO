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
} particle; //bedzie zrobiona tablica czasteczek(particle) - rozmiar podany przez uzytkownika
//wektor kierunku to suma 3 wektorow: aktualnego kierunku, najlepszej pozycji czasteczki, najlepszej pozycji roju

typedef struct {
    coordinates best_position;
} swarm;

coordinates PSO(int **matrix, int X, int Y, int ilosc);
#endif