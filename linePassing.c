#include <stdio.h>
#include <stdlib.h>

int firstPart(char lineToBreak[]);
char p=0;
char x;
int i;
int j;
char userInput1[80];
char userInput2[80];
int err =0;
int numOfComas=0;
int numOfWords=0;

typedef struct lines{
char label[31];
char opName[4];
char param1[100];
char param2[100];
}line;

line line1;

int main(){
char test[80] = "mov r1,";
firstPart(test);
return 0;
}

int firstPart(char lineToBreak[]){	

/*analising the FIRST word only- locating in userInput*/
 	for(i = 0; p != ':'; i++){
            p = lineToBreak[i];
            /*if its a label*/
            if (p == ':'){
            	if(lineToBreak[i-1]==' '){
            	printf("illegel label name,: must be sticked to label");
            	break;
            	}
            }
            if( p== '.' || p=='\n'|| p== ' '){ 
            numOfWords++;
            break;
            }
            x = p;
            userInput1[i] = x;
            } 
            
if(p==':' && lineToBreak[i-1]!=' '){
printf("its a label\n");
/*DO SOMETHING*/
}

if(p=='.'){
printf("its a instruction");
/*DO SOMETHING*/
}
if(p=='\n'|| p== ' '){
printf("its a op");
/*DO SOMETHING*/
}


/*seconed word*/
for(i; p != ','; i++){
            p = lineToBreak[i];
            while(p==' '){/*remove white spaces from text for seconed word*/
            p = lineToBreak[++i];
            }
            if( p== ',') {
            numOfWords++;
            numOfComas++;
            break;
            }
            x = p;
            userInput2[i] = x;
            } 
            
            while(lineToBreak[i]==','){/*remove white spaces from text for seconed word*/
            ++i;
            }




            printf("\nuserInput1:\n");
for(i = 0; i < 80; i++){
            
            printf("%c",userInput1[i]);

            }
                        printf("\nuserInput2:\n");
            for(i = 0; i < 80; i++){
            
            printf("%c",userInput2[i]);

            }
            /**
                          printf("\nuserInput3:\n");
            for(i = 0; i < 80; i++){
            
            printf("%c",userInput3[i]);

            }
**/
            

return 0;
}

