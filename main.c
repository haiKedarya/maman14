
#include "main.h"

    int main(int argc, char* argv[]){

        int i;

        if(argc<2){
            fprintf(stderr, "No file found");
            exit(1);
        }

        for (i = 1; i < argc; i++)
        {
            runProg(argv[i]);
        }
        exit(1);
    }



