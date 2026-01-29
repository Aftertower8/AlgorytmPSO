FLAGS = -Wall -Wextra -pedantic

all: pso generate

pso: main.c map.c pso.c logger.c
	cc $(FLAGS) $^ -o pso

generate: random_matrix.c
	cc $(FLAGS) $^ -o generate
clean:
	rm -f *.o pso generate
