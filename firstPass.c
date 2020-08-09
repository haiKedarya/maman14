#include "main.h"
#include "firstPass.h"
#include "words.h"

void firstParse(FILE * fp)
{

shead = (SNode *) malloc(sizeof(SNode));
curSNode = shead;
dhead = (DNode *) malloc(sizeof(DNode));
curDNode = dhead;

char * line = NULL;
size_t len = 0;
ssize_t read;



while ((read = getline(&line, &len, fp)) != -1) {
puts(line);
int flagForError = 0;
int place=0;
char * ptr = line;
int labelFlag=0;          

while(*ptr == ' ')/*clear spaces before line*/
{
	ptr++;
	place++;
}


while(1){ /*THE SCAN LOOP*/
   
   /*if the input end*/        
	if(*ptr == NULL){ break; }




if(*ptr == ':')
{ 
	labelFlag = checkForLabel(line);/*equal 1 if there is label, 0 if not*/	
	if(checkForLabel(line))
	{
	printf("labelFlag IS ON\n");
	}else{/*if we got : and we get false from funtion their is a problem and break*/
		break; 
	}
	
}
	
if(*ptr == '.')
{ 
switch(checkForGuide(line,place)){

	case 1: {
	if(labelFlag){
	        addSign(label, "data", IC);
	        }
		}
	break;
	
	
	case 2: {
		addString(line,place);
			if(labelFlag){
			addSign(label, "data", IC);
			}
		}
	break;
	
	
	case 3: {
		printf("ITS .ENTRY");
		}
	break;
	
	case 4: {
		printf("THE EXTERN: ");
		handleExtern(line,place);
		}
	break;
	
	
	default: {

		 }
	break;
}
}

/*moving ptr to next char in line*/
place++;
ptr++;

}	

printf("%d\n",IC);
IC++;
/*moving to next line IC grow by 1*/

}
}
/*=================================================*/
bool checkForLabel(char * line[]){
/*funtion for cheking if label have no errors*/
char * ptr1 = line;
int i=0;
int error=0;

while(*ptr1 == ' ')
{
	ptr1++;
	
}

if(!isalpha(*ptr1) && !isdigit(*ptr1))
{
printf("MUST BE START WITH LETTER\n");
}

while(*ptr1 != ':'){
	label[i] = *ptr1;
	ptr1++;
	i++;
}

if(*ptr1 == ':' && (*(ptr1-1))==' ')
{
	error=1;
	printf("CANT BE SPACE BEFORE SEMICOLON");
	return 0;
}

for(i=0; i < 8; i++){
    if (!strcmp(label, regs[i]))
    {
    	printf("CANT BE REGISTER NAME");
    	return 0;
    }
}

if(*ptr1 == ':')
{
	label[i] = '\0';
}

return 1;
}

/*=================================================*/
int checkForGuide(char * line[],int place){
   /*function check if it .string/.data/.external/.entry,and if it is illigel input, return 0*/
char * ptr1 = line;
ptr1 = ptr1 + place + 1 ;
int i=0;
int error=0;

while(*ptr1 == ' ')
{
	ptr1++;
	
}

while(*ptr1 != ' ')
{
	guide[i] = *ptr1;
	ptr1++;
	i++;

}

if(*ptr1 == ' ')
{
	guide[i] = '\0';
}

    if (!strcmp(guide, "data"))
        return 1;
    else if (!strcmp(guide, "string"))
        return 2;
    else if (!strcmp(guide, "entry"))
        return 3;
    else if (!strcmp(guide, "extern"))
        return 4;

    return 0;
}
/*=================================================*/
void handleExtern(char * line[],int place){

char * ptr2 = line;
ptr2 = ptr2 + place + 1 ;
int i;

while(*ptr2 != ' ')
{
	ptr2++;
	
}

while(*ptr2 == ' ')
{
	ptr2++;
	
}


while(*ptr2!=NULL){
externy[i] = *ptr2;
	ptr2++;
	i++;
}


externy[i-1] = '\0';

addSign(externy, "external", 0);


}

/*=================================================*/
void addString(line,place){
static int i=0;
char * p;
int len = 0;
char * ptr3 = line;
int numOfP=0;
/*check if the is two "X" if not, error and return */
for(p=line;*p!=NULL;p++){
	if(*p == '"'){
	numOfP++;
	}
}

if(numOfP!=2){
printf("ERROR: must be 2 quotation marks. you insert: %d quotation marks.\n",numOfP); 
return;
}

while(*ptr3 != '.')
{
	ptr3++;
	
}
while(*ptr3 != '"')
{
	ptr3++;
	
}
	
	
ptr3++;

while(*ptr3!='"'){
/*first is type of int24. can found in words.h file */
first = *ptr3;
arr24[i] = first;
makeBinary(arr24[i]);
printf("\n");
ptr3++;
i++;
len++;

}

i++;
arr24[i] = '\0';
i++;

DC+=len+2;
printf("dc:%d\n",DC);
return;

}

/*=================================================*/
void addSign(char label[50], char character[50], int value) {
/*send values for symbol table*/
    strcpy(curSNode->sign.label, label);
    curSNode->sign.value = (value);
    strcpy(curSNode->sign.car, character);

    SNode *newSNode = (SNode *) malloc(sizeof(SNode));
    curSNode->next = newSNode;
    curSNode = newSNode;

}
