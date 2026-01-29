#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate(FILE *out, int w, int h, double min, double max){
    fprintf(out,"%d %d\n",w,h);
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            fprintf(out,"%lf ", min + (double)rand()/RAND_MAX*(max-min));
        }
        fprintf(out,"\n");
    }
}

void blad_arg(char* name){
	printf("Uzycie: %s -f <plik_wyjsciowy> -w <szerokosc> -h <wysokosc> -min <min_val> -max <max_val>\n",name);
}

int main(int argc, char **argv){
    srand(time(NULL));
    char *flags[5]={"-f","-w","-h","-min", "-max"};
    char *default_file = "random_matrix_generated.txt";
    FILE *out=NULL;
    int w=50, h=50;
    double min=-100, max=100;
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i],flags[0])==0 && i+1<argc){
            i++;
            out = fopen(argv[i],"w");
            if(out==NULL)
                return EXIT_FAILURE;
	    printf("Utworzono plik %s\n", argv[i]);
        }
        else if(strcmp(argv[i],flags[1])==0 && i+1<argc){
            i++;
            w=atoi(argv[i]);
        }
        else if(strcmp(argv[i],flags[2])==0 && i+1<argc){
            i++;
            h=atoi(argv[i]);
        }
        else if(strcmp(argv[i],flags[3])==0 && i+1<argc){
            i++;
            min=atof(argv[i]);
        }
        else if(strcmp(argv[i],flags[4])==0 && i+1<argc){
            i++;
            max=atof(argv[i]);
        }
        else{
	    blad_arg(argv[0]);
            return EXIT_FAILURE;
        }
    }
    if(out==NULL){
	    out=fopen(default_file,"w");
    	    printf("Utworzono plik %s\n",default_file);
    }
    if(w<1 || h<1){
	    fprintf(stderr, "Blad! wysokosc lub szerokosc ujemne\n");
	    return EXIT_FAILURE;
    }
    if(max<min){
	    fprintf(stderr, "Blad! max mniejsze od min\n");
	    return EXIT_FAILURE;
    }
    generate(out,w,h,min,max);
    fclose(out);
    return EXIT_SUCCESS;
}
