#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate(FILE *out, int w, int h, int min, int max){
    fprintf(out,"%d %d\n",w,h);
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            fprintf(out,"%d ", min + rand()%(max-min+1));
        }
        fprintf(out,"\n");
    }
}

int main(int argc, char **argv){
    srand(time(NULL));
    char *flags[5]={"-f","-w","-h","-min", "-max"};
    FILE *out=stdout;
    int w=50, h=50, min=-100, max=100;
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i],flags[0])==0 && i+1<argc){
            i++;
            out = fopen(argv[i],"w");
            if(out==NULL)
                return EXIT_FAILURE;
            i++;
        }
        else if(strcmp(argv[i],flags[1])==0 && i+1<argc){
            i++;
            w=atoi(argv[i]);
            i++;
        }
        else if(strcmp(argv[i],flags[2])==0 && i+1<argc){
            i++;
            h=atoi(argv[i]);
            i++;
        }
        else if(strcmp(argv[i],flags[3])==0 && i+1<argc){
            i++;
            min=atoi(argv[i]);
            i++;
        }
        else if(strcmp(argv[i],flags[4])==0 && i+1<argc){
            i++;
            max=atoi(argv[i]);
            i++;
        }
        else{
            return EXIT_FAILURE;
        }
    }
    generate(out,w,h,min,max);
    return EXIT_SUCCESS;
}