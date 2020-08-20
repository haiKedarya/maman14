#include "words.h"
#include "firstPass.h"

int flagForError = 0;
myRegister registers[8];

void firstParse(FILE * fp)
{
ehead = (EntryNode *) malloc(sizeof(EntryNode));
curENode = ehead;
shead = (SignNode *) malloc(sizeof(SignNode));
curSNode = shead;
dhead = (DataNode *) malloc(sizeof(DataNode));
curDNode = dhead;

IC=100;
DC=0;

int parametersCheck;
char * line = NULL;
size_t len = 0;
ssize_t read;
int insertCode=0;
int flagForError = 0;
int place=0;
char * ptr;
int labelFlag;
char functLabel;  /*for each line indicates the function number(if no function name appeard the value will be zero)*/        
preMila pre_Mila;
mila lineMila;

while ((read = getline(&line, &len, fp)) != -1) {/*get lines*/

	resetValues(&pre_Mila, &lineMila);/*resets the the mila values*/
	ptr = line;
	puts(line);
	labelFlag = 0;
	functLabel = 0;

while(*ptr == ' ')/*clear spaces before line*/
{
	ptr++;
	place++;
}


while(1){ /*THE SCAN LOOP*/
   /*if the input end*/        
if(*ptr == '\0'){ 	
	break; 
}

if(*ptr == ':')
{ 
	labelFlag = checkForLabel(line);/*equal 1 if there is label, 0 if not*/	
	if(labelFlag)
	{
	pre_Mila.has_label = 1;
	/*printf("labelFlag IS ON\n");*/
	}else{/*if we got : and we get false from funtion their is a problem and break*/
		break; 
	}
}

if(*ptr == '.')
{ 

switch(checkForGuide(line,place)){

	case 1: {
		pre_Mila.hasGuide = 1;
		addData(line,place);
		if(labelFlag){
	        addSign(label, "data", IC);
		
	        }
		}
	break;
	
	case 2: {
		pre_Mila.hasGuide = 2;
		ptr += addString(line,place);
			if(labelFlag){
			addSign(label, "data", IC);
			}
		}
	break;
	
	case 3: {
		/*printf("ITS .ENTRY");*/
		handleEntry(line,place);
		pre_Mila.hasGuide = 3;
		}
	break;
	
	case 4: {
		pre_Mila.hasGuide = 4;
		/*printf("THE EXTERN: ");*/
		handleExtern(line,place);
		}
	break;

}
}


if(!functLabel){
	if(isalpha(*ptr)){

		functLabel = checkFunct(ptr,&pre_Mila);/*will return the funct number 1-16 if found any*/	
		/*printf("\nthis is functLabel: %d\n", functLabel);*/
		if(functLabel > 0){
		ptr+=3;
		makepOpCodeAndFunct(functLabel-1, &lineMila);
		}
	}
}

if(functLabel > 0 && labelFlag && insertCode == 0)
{
insertCode=1;
addSign(label, "code", IC);
}

if(functLabel == 16){/*stop the program*/

}
if(functLabel == 15){/*no parameters*/

printf("%d\n",IC);
place = 0;
IC++;
/*moving to next line IC grow by 1*/
}
if(functLabel > 0){/*start look for parameters*/
printf("functLabel : %d\n",functLabel);
	if(!isspace(*ptr)){/*if its not blank space */	
		parametersCheck = getParameters(ptr, &pre_Mila, &lineMila);
		/*printf("this is parametersCheck: %d",parametersCheck);*/		
			if(parametersCheck > 0){
				printf("parametersCheck : %d\n",parametersCheck);
				assignRegistersValues(&pre_Mila, &lineMila, &registers);
				checkIfParamIsLabel(&pre_Mila, &lineMila);
			}
			break;		
	
	}

}

/*moving ptr to next char in line*/
place++;
ptr++;

}	

printMila(&pre_Mila,&lineMila);

printf("ic: %d\n",IC);
place = 0;
IC++;
/*moving to next line IC grow by 1*/

}
}
/*=================================================*/
int handleEntry(char * line,int place){
char *ptr;
char *ptr2;
int i=0;
ptr = strtok(line," ");
ptr2 = strtok(NULL,"");

while(isalpha(*ptr2))
{
ptr2++;
i++;
}

while(*ptr2 != '\0')
{
if(isalpha(*ptr2)||isdigit(*ptr2)||(!isspace(*ptr2)))
{
printf("ERROR-cant be more than 1 parmeter in ENTRY statement!");
return 1; /*return 1 for error*/
}
ptr2++;
i++;
}

ptr2=ptr2-i;

strcpy(curENode->entry.label, &ptr2[0]); /*put the entry label in list*/    
    EntryNode *newENode = (EntryNode *) malloc(sizeof(EntryNode));
    curENode->next = newENode;
    curENode = newENode;

}

/*=================================================*/
bool checkForLabel(char * line){
char regs [8][3] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"}; 
/*funtion for cheking if label have no errors*/
char * ptr1 = line;
int i=0, i2 ;
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

for(i2=0; i2 < 8; i2++){
    if (!strcmp(label, regs[i2]))
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
int checkForGuide(char * line,int place){
/*printf("start of checkForGuide\n");
puts(line);*/
   /*function check if it .string/.data/.external/.entry,and if it is illigel input, return 0*/
char *ptr1 = line;
char guide[80];
int i = 0;

while(*ptr1 != '.')
{
	ptr1++;
	
}
ptr1++;

while(*ptr1 != ' ')
{
	guide[i] = *ptr1;
	ptr1++;
	i++;
}
guide[i] = '\0';
puts(guide);
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
void handleExtern(char * line,int place){

char * ptr2 = line;
ptr2 = ptr2 + place + 1 ;
int i = 0;

while(*ptr2 != ' ')
{
	ptr2++;
	
}

while(*ptr2 == ' ')
{
	ptr2++;
	
}


while(*ptr2 != NULL ){
externy[i] = *ptr2;
	ptr2++;
	i++;
}


externy[i-1] = '\0';

addSign(externy, "external", 0);


}

/*=================================================*/
int addString(char * line,int place){
static int i=0;
int i2 = 0;
char *p;
int len = 0;
char *ptr3 = line+1;
int numOfP = 0;
/*check if there is two "X" if not, error and return */
for(p = line;*p != '\0';p++){
printf("%c",*p);
	if(*p == 34){/*34 is ascii value of ( " ) */
	if(numOfP == 1){
	i2++;
	}
	numOfP++;
	}
}

if(numOfP != 2){
printf("ERROR: must be 2 quotation marks. you insert: %d quotation marks.\n",numOfP); 
return 0;
}

while(*ptr3 != '.' && *ptr3 != '\0')
{
	ptr3++;	
}
while(*ptr3 != 34 && *ptr3 != '\0')
{
	ptr3++;
}
	
	
ptr3++;

while(*ptr3 !='"' && *ptr3 != '\0'){
/*first is type of int24. can found in words.h file */
first = *ptr3;
arr24[i] = first;
makeBinary(arr24[i], 24);
printf("\n");
ptr3++;
i++;
len++;

}

i++;
arr24[i] = '\0';
i++;

DC += len + 1;
printf("dc:%d\n",DC);
return i2;;

}

/*=================================================*/
/* 
 * @description this method extrcat the parameters from "data" Guide type lines
 * @param line is pointer to the location in the line that the program read right now
 * @return the funct number 1-16 or 0 if not found
 */
int addData(char * line,int place){
int i=0;
int i2=0;
char *p;
int len = 0;
int send = 0;
char arrNumer[100];
p = line;
int itsNeg=0;


while(*p<48 || *p>57 )
{
if(*p=='-'){itsNeg=1;break;}
p++;
}
printf("the line:\n");
puts(p);


while(*p != '\0'){
/*first is type of int24. can found in words.h file */

arrNumer[i] = *p;
p++;
i++;
if(*p==',')
{

arrNumer[i] = '\0';
if(itsNeg)
	arrNumer[i-len] = '-';
	
sscanf(arrNumer, "%d", &send);
len+=makeBinary(send, 24);
p++;
i=0;
}

}

arrNumer[i] = '\0';
if(itsNeg)
	arrNumer[i-len] = '-';
	
sscanf(arrNumer, "%d", &send);
len+=makeBinary(send, 24);


printf("len:%d\n",len);
DC += len;
printf("dc:%d\n",DC);
return i2;

}


/* 
 * @description this method check if there is any funct name
 * @param line is pointer to the location in the line that the program read right now
 * @return the funct number 1-16 or 0 if not fount, in case we searched to whole line and did not found any funct name will return -1;
 */
int checkFunct(char * line, preMila *pre_mila){
char ops [16][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}; 
char s[3];
int i;
if(*(line +1)== '\0'){
return -1;}
if(*(line +2) == '\0'){  
return -1;}
s[0] = *line;
s[1] = *(line +1);
s[2] = *(line +2);
for(i = 0;i<16;i++){
	if(strcmp(s, ops[i]) == 0){
	pre_mila->operation = i;
	return i+1;
	}
}
return 0;
}
/*======================================================*/
void addSign(char label[50], char character[50], int value) {
/*send values for symbol table*/
	
    strcpy(curSNode->sign.label, label);
    curSNode->sign.value = (value);
    strcpy(curSNode->sign.car, character);

    SignNode *newSNode = (SignNode *) malloc(sizeof(SignNode));
    curSNode->next = newSNode;
    curSNode = newSNode;

}
