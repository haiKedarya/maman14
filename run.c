#include "main.h"
#include "firstPass.h"
void printData(){
   SignNode *temp;
   if (shead == NULL) {
      printf("List is empty.\n");
      return;
   }
      printf("========================= \n");
   printf("elements of list are : \n");
         printf("========================= \n");
   temp = shead;
   while (temp != NULL) {
      
      printf("label name: %s\n", temp->sign.label);
      printf("value: %d \n", temp->sign.value);
      printf("type: %s \n", temp->sign.car);
               printf("========================= \n");
      
      temp = temp->next;
   }
   printf("\n");
}
void runProg(char * fileName[]){
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
