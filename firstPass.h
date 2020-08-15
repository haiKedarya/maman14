#include "main.h"

#define COMMA 44
#define MAX_LENGTH 200
char label[80];
char externy[80];
char string[80];

/*char regs [8][3] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"}; 

char ops [16][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}; 
 
 int IC = 100;
 int DC = 0;
 
 int flagForError = 0;
*/
typedef struct {
bool has_register;
bool has_label;
char param1[100];
char param2[100];
int param1_miun;
int param2_miun;
}preMila;

typedef struct { 
	char opCode[7];
	char sourceMiun[3];
	char sourceRegister[4];
	char destinationMiun[3];
	char destinationRegister[4];
	char funct[6];
	char a_r_e[4];
    }mila;
    
   
typedef struct {
    char label[50];
    int value;
    char car[50];
}Sign;

typedef struct {
    Sign sign;
    struct SignNode * next;
}SignNode;

SignNode * shead ;
SignNode * curSNode;


typedef struct {
    int count;
    int num[38];/*38 maximum number of values that can be added in .data*/
}Data;

typedef struct DNode {
    Data data;
    struct DNode* next;
}DataNode;

DataNode* dhead;
DataNode* curDNode;


/*void printData(){
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
}*/

int addData(char * line,int place);
void printMila(mila *myMila);
int checkFunct(char *line);
void assignRegistersValues(preMila pre_mila,mila *myMila);
int getParameters(char * line,preMila *myPreMila, mila *myMila);
int makepOpCodeAndFunct(int funct,mila *myMila);
bool checkForLabel(char * line);
int checkForGuide(char * line,int place);
void handleExtern(char * line,int place);
void addSign(char label[50], char character[50], int value);


