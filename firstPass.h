#include "main.h"


#define MAX_LENGTH 200
char label[80];
char guide[80];
char externy[80];
char string[80];

char regs [8][3] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"}; 

char ops [16][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}; 
 
 int IC = 100;
 int DC = 0;
 
 int flagForError = 0;
 

typedef struct{
    char label[50];
    int value;
    char car[50];
}Sign;

typedef struct SNode {
    Sign sign;
    struct SNode * next;
}SNode;

SNode * shead ;
SNode * curSNode;


typedef union Data{
    int num;
    char ch;
}Data;



typedef struct DNode {
    Data data;
    struct DNode* next;
}DNode;

DNode* dhead;
SNode* curDNode;


void printData(){
   struct SNode *temp;
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



bool checkForLabel(char* line[]);
int checkForGuide(char * line[],int place);
void handleExtern(char * line[],int place);
void addSign(char label[50], char character[50], int value);


