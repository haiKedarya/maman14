#include "main.h"
void runProg(char * fileName){
    {

        
        
        fp = fopen(fileName, "r");
        if (fp == NULL){
            exit(1);
        }

	firstParse(fp);
	printData();
/*
        fclose(fp);
        if (line){
            free(line);
        }
*/

        exit(1);

    }}
