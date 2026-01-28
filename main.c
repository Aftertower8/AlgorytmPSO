#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "pso.h"
#include "logger.h"

void read_config(FILE* config, particle *drones, swarm *roj, int particle_count){
    double attrib[5];   //w,c1,r1,c2,r2
    int i=0;
    while(fscanf(config,"%lf",&attrib[i++])==1);
    get_attrib(attrib,drones,roj,particle_count);
}

int main(int argc, char *argv[]) {
    char *map_file = NULL;
    char *config_file = NULL; 
    int particle_count = 30;
    int iterations = 100;
    int log_interval = 0;

    if (argc < 2) {
        fprintf(stderr, "Uzycie: %s <plik_mapy> -p <liczba> -i <iteracje> -c <config> -n <log>\n", argv[0]);
        return 1;
    }
    map_file = argv[1];

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            particle_count = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            iterations = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            config_file = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            log_interval = atoi(argv[++i]);
        }
    }

    // Wczytanie mapy
    FILE *f_map = fopen(map_file, "r");
    if (!f_map) {
        perror("Blad otwarcia pliku mapy\n");
        return 1;
    }

    // Wczytanie pliku config
    FILE *config = fopen(config_file, "r");
    if(!config){
        perror("Blad otwarcia pliku konfiguracyjnego\n");
        return 2;
    }

    int W, H;
    // Wczytaniex mapy oraz jej wymiary (W, H) przez wskaźniki
    double **map = ReadFromFile(f_map, &W, &H);
    fclose(f_map);

    if (map == NULL) {
        perror("Blad wczytywania mapy.\n");
        return 1;
    }

    // Alokacja pamięci dla roju w main (nie w funkcji init)
    particle *drones = (particle*)malloc(particle_count * sizeof(particle));
    swarm roj;

    // Inicjalizacja stanu początkowego roju
    init_particles(drones, &roj, particle_count, W, H, map);
    
    read_config(config,drones,&roj,particle_count);

    if (log_interval > 0) {
        logger_init("pso_log.csv");
    }

    printf("Start symulacji: %d czastek, %d iteracji, mapa %dx%d\n", particle_count, iterations, W, H);

    for (int t = 0; t < iterations; t++) {
        // Wykonanie ruchu roju
        PSO(map, drones, &roj, W, H, particle_count);

        // Log co n iteracji
        if (log_interval > 0 && (t % log_interval == 0)) {
            for (int p = 0; p < particle_count; p++) {
                log_swarm("pso_log.csv", t, p, &drones[p]);
            }
        }
    }

    printf("Znaleziony cel (gBest): X=%d, Y=%d\n", roj.best_position.x, roj.best_position.y);
    printf("Wartosc sygnalu: %.4f\n", roj.best_val);

    free_particles(drones);
    free_matrix(map, H);

    return 0;
}