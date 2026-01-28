CFLAGS = -Wall -Wextra -pedantic

pso: main.c map.c pso.c logger.c
	cc $(FLAGS) $^ -o pso
clean:
	rm -f *.o pso
