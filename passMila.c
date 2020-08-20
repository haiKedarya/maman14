#include "firstPass.h"

char regs [8][3] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"}; 

char ops [16][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}; 


/* 
 * @description this method check if there is any label in the parameters 
 *param myMila is a pointer to the given mila that we want to assign 
 *param pre_mila is a pointer to where we take from the parameters
 *return will return 0 if there is no label in the parameter,return 1 if label appeared in first param or 2 for second param
*/ 

int checkIfParamIsLabel(preMila *pre_mila, mila *myMila){
int s = 0;
s = checkInWitchParamLabel(pre_mila,myMila);
printf("s: %d \n", s);
if(s > 0){
	if(s == 1){
		if(!pre_mila->param1_miun){
			pre_mila->param1_miun = MIUN1;
			strcpy(myMila->sourceMiun,"01");
		}
	}
	if(s == 2){	
		if(!pre_mila->param2_miun){	
			pre_mila->param2_miun = MIUN1;
			strcpy(myMila->destinationMiun,"01");
		}
	}
}else{
	return 0;
}
/*SignNode *temp;
if (shead == NULL) {
	printf("List is empty.\n");
	return 0;
}
temp = shead;
while (temp != NULL) {
        if(!strcmp(temp->sign.label, pre_mila->param1)){
		pre_mila->has_label = 1;	
		pre_mila->param1_miun = 1;
		strcpy(myMila->sourceMiun,"01");
		return 1;
	}
	if(!strcmp(temp->sign.label, pre_mila->param2)){
		pre_mila->has_label = 2;
		printf("ani kan\n");
		pre_mila->param2_miun = 1;
		strcpy(myMila->destinationMiun,"01");
		return 2;
	}
        temp = temp->next;*/
	/*printf("type: %s \n", temp->sign.car);
   }
return 0;*/
}

/* 
 * @description this method indicates in witch parameter we have label

 *param myMila is a pointer to the given mila 
 *param pre_mila is a pointer to the given pre_mila 
 *return returns 1 if there is label in first param
or 2 if there is label in second param
*/ 
int checkInWitchParamLabel(preMila *pre_mila, mila *myMila){
char check[100]; 

int i = 0;
int count = 1;
if(pre_mila->first_register || pre_mila->operation > LEA){
	if(pre_mila->second_register){
		return 0;
	}
	count = 2; 
	strcpy(check, pre_mila->param2);
}else{
	strcpy(check, pre_mila->param1);
}

while(check[i] != '\0'){

if(i >= 100){
	if(count == 1){
		strcpy(check, pre_mila->param2);
		i = 0;
		continue;
	}else{
		return count;
	}	
}
if(check[i] == '#' || check[i] == '&'){
	if(check[i] == '&'){
		strcpy(myMila->a_r_e,"100");
		if(count == 1){
			pre_mila->param1_miun = MIUN2;
			strcpy(myMila->sourceMiun,"10");
		}else{
			pre_mila->param2_miun = MIUN2;
			strcpy(myMila->destinationMiun,"10");
		}
	}
	i++;
	if(!isalpha(check[i])){
		if(count == 1){
			strcpy(check, pre_mila->param2);
			i = 0;
			if(check[i] == '#' || check[i] == '&'){
				i++;
				if(!isalpha(check[i])){
					return 0;
				}
			}
		}else{
			return 0;
		}	
	}
}
if(isalpha(check[i]) || isdigit(check[i])){
		if(check[i+1] == '\0'){
			if(count == 1){
				return 1;
				
			}else if(count == 2){
				return count;
			}
		}
		i++;	
		continue;
}else{
	i = 0;
	strcpy(check, pre_mila->param2);
	count = 2;
	continue;
}
	i++;
}
return count;
}

/* 
 * @description this method print the mila!
 *param myMila is a pointer to the given mila 
 *param pre_mila is a pointer to the given pre_mila 
*/ 
void printMila(preMila *pre_mila, mila *myMila){
printf("this is the mila: ");
printf("%s.",myMila->opCode);
if(pre_mila->param1_miun > 0){
	printf("%s.",myMila->sourceMiun);
}else{
	printf("00.");
}
if(pre_mila->first_register){
	printf("%s.",myMila->sourceRegister);
}else{
	printf("000.");
}
if(pre_mila->param2_miun > 0){
	printf("%s.",myMila->destinationMiun);
}else{
	printf("00.");
}

if(pre_mila->second_register){
	printf("%s.",myMila->destinationRegister);
}else{
	printf("000.");
}
printf("%s.",myMila->funct);
printf("%s\n",myMila->a_r_e);
if(pre_mila->param2_miun == MIUN0 || pre_mila->param1_miun == MIUN0){
	makeBinary(myMila->number, 21);
	printf("001\n");
}
printf("\n================================================================================\n");
}
/* 
 * @description this method reset the values 
 *param myMila is a pointer to the given mila that we want to reset
 *param pre_mila is a pointer to the given pre_mila that we want to reset
*/ 
void resetValues(preMila *pre_mila,mila *myMila){
pre_mila->first_register=0;
pre_mila->second_register=0;
pre_mila->has_label=0;
pre_mila->operation=0;
int hasGuide = 0;
memset(pre_mila->param1, 0, 100);
memset(pre_mila->param2, 0, 100);
pre_mila->param1_miun=0;
pre_mila->param2_miun=0;

memset(myMila->opCode, 0, 6);
memset(myMila->sourceMiun, 0, 2);
memset(myMila->sourceRegister, 0, 3);
memset(myMila->destinationMiun, 0, 2);
memset(myMila->destinationRegister, 0, 3);
memset(myMila->funct, 0, 5);
memset(myMila->a_r_e, 0, 3);
myMila->number = 0;
}
/* 
 * @description this method assigning values to the registers if there is any "r0-7" in line.param1-2
 *param myMila is a pointer to the given mila that we want to change
 *param (struct) line we take from him the  
*/ 
void assignRegistersValues(preMila *pre_mila,mila *myMila, myRegister *regist){

   	
   int count = 0;
   int found=0;
   char check[100];
   char toCheckAddres[100];
   strcpy(check, pre_mila->param1);/*assign check array the value of param1 */
   int i; 
   int j=0; 
   printf("this is param1: .%s.\n", pre_mila->param1);
   printf("this is param2: .%s.\n", pre_mila->param2);
   if(pre_mila->operation >= 4){
	count = 1;
	strcpy(check, pre_mila->param2);
   }
   while(count <= 1){
	for(i = 0; i < 9;i++){/*this loop will run until it will find r0-r7 or not*/
		if(strcmp(regs[i],check) == 0){
			found=1;
			strcpy(myMila->a_r_e,"100");
			break;
		}
		
	}
	
	if(!found){ /*in line line "add r3,K" keep the K to check if exist in seconed pass*/
			IC+=1;
			strcpy (curDNode->data.word,check);	
			curDNode->data.ic=IC;	
			DataNode *newDNode = (DataNode *) malloc(sizeof(DataNode));
   			curDNode->next = newDNode;
   			curDNode = newDNode;
		}
		
   switch(i){
	case(0):
	if(count){
	    pre_mila->second_register = 1;
	    pre_mila->param2_miun = MIUN3;
	    strcpy(myMila->destinationRegister,"000");
	    strcpy(myMila->destinationMiun,"11");
	    /*myMila->destinationRegister = ;
	    myMila->destinationMiun = "00";*/
	}else{
	    /*myMila->sourceRegister = "000";
	    myMila->sourceMiun = "00";*/
	    pre_mila->param1_miun = MIUN3;
	    pre_mila->first_register = 1;
	    strcpy(myMila->sourceRegister,"000");
	    strcpy(myMila->sourceMiun,"11");	    
	}
	break;
	case(1):
	if(count){
	    pre_mila->second_register = 2;
	    pre_mila->param2_miun = MIUN3;
	    strcpy(myMila->destinationRegister,"001");
	    strcpy(myMila->destinationMiun,"11");
	    /*myMila->destinationRegister = "001";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 2;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"001");
	    strcpy(myMila->sourceMiun,"11");	    
	   /* myMila->sourceRegister = "001";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(2):
	if(count){
	    pre_mila->second_register = 3;
	    pre_mila->param2_miun = MIUN3;
	    strcpy(myMila->destinationRegister,"010");
	    strcpy(myMila->destinationMiun,"11");
	    /*myMila->destinationRegister = "010";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 3;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"010");
	    strcpy(myMila->sourceMiun,"11");	    
	   /* myMila->sourceRegister = "010";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case (3):
	if(count){
	    pre_mila->second_register = 4;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"011");
	    strcpy(myMila->destinationMiun,"11");
/*	    myMila->destinationRegister = "011";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 4;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"011");
	    strcpy(myMila->sourceMiun,"11");
	/*printf("this is shit:  %s", myMila->sourceRegister);	  */  
	    /* *myMila->sourceRegister = "011";
	    *myMila->sourceMiun = "00";*/
	}
	break;
	case(4):
	if(count){
	    pre_mila->second_register = 5;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"100");
	    strcpy(myMila->destinationMiun,"11");
/*	    myMila->destinationRegister = "100";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 5;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"100");
	    strcpy(myMila->sourceMiun,"11");	    
	   /*myMila->sourceRegister = "100";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(5):
	if(count){
	    pre_mila->second_register = 6;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"101");
	    strcpy(myMila->destinationMiun,"11");
/*	    myMila->destinationRegister = "101";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 6;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"101");
	    strcpy(myMila->sourceMiun,"11");	    
/*	    myMila->sourceRegister = "101";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(6):
	if(count){
	    pre_mila->second_register = 7;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"110");
	    strcpy(myMila->destinationMiun,"11");
/*	    myMila->destinationRegister = "110";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 7;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"110");
	    strcpy(myMila->sourceMiun,"11");	    
	   /* myMila->sourceRegister = "110";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(7):
	if(count){
	    pre_mila->second_register = 8;
	    pre_mila->param2_miun = MIUN3;
   	    strcpy(myMila->destinationRegister,"111");
	    strcpy(myMila->destinationMiun,"11");
/* 	    myMila->destinationRegister = "111";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 8;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"111");
	    strcpy(myMila->sourceMiun,"11");	    
/*	    myMila->sourceRegister = "111";
	    myMila->sourceMiun = "00";*/
	}
	break;
	default:
	if(count){/*check later if needed to cancel the MIUN assiment*/
	    pre_mila->second_register = 0;
   	    strcpy(myMila->destinationRegister,"000");
	    /*myMila->destinationRegister = "000";
            myMila->destinationMiun = "00";*/
	}else{
	    pre_mila->first_register = 0;
	    strcpy(myMila->sourceRegister,"000"); 
	   /* myMila->sourceRegister = "000";
	    myMila->sourceMiun = "00";*/
	}
	break;
	}
	found=0;
	count ++;	
        strcpy(check, pre_mila->param2);/*assign check array the value of param2 */
    }
}

/* 
 * @description this method assign the mila number value
 *param line is pointer to the line after getting the function name
 *return will return -1 if there is corrupted patameter, will return number of char that readen by this function
*/ 

int getNumber(char * line,mila *myMila){
printf("start getNum\n");
char *ptr = line;
bool check = 0;/*indicates that we got any data*/
bool negative = 0;/*indicates that we got negative data*/
int i =0;
int num = 0;
if(*ptr == '#'){
	i++;
	ptr++;		
}
while(*ptr != '\0'){
	if(isspace(*ptr)){
		if(check == 1){/*corrupted patameter (has a space between data)*/
			break;
		}
	i++;
	ptr++;
	continue;
	}
	if(*ptr == COMMA){
		break; 
	}
	
	if(*ptr == '-'){
		if(check == 0 && negative == 0){
			negative = 1;
			check == 1;
			ptr++;
			i++;
			continue;
		}else{/*5*/
			return -1;
		}
	}
	if(isdigit(*ptr)){
		if(check == 0){			
			num = *ptr - 48;
			check = 1;
		}else{		
		check = 1;
		num = num * 10;
		num += *ptr - 48;			
		}
	}else{/*corrupted patameter (has something diffrent from whole number;)*/
		return -1;
	}
++ptr;
++i;
}/*end of loop*/
	/*printf("end of getNumTo21Bits we got : %d", num);*/
	if(negative){
		num = num * -1;
	}
	strcpy(myMila->a_r_e, "100");
	myMila->number = num;
	return i;
}

/* 
 * @description this method assign values to the preMila values
 *param line is pointer to the line after getting the function name
 *param preMila is a pointer to the given preMila that we want to change
 *return will return 2 if we got 2 parameters with values. 1 if got one parameter, -2 if we got comma with no parameters, -1 if we got no parameters, 0 if there is illegal operand info, -3 if there is too much commas
*/ 

int getParameters(char * line,preMila *myPreMila, mila *myMila){
printf(" start get param\n");
bool typeOfOperation;
if(PRN >= myPreMila->operation && myPreMila->operation >= CLR){
	typeOfOperation = 2;	
	strcpy(myMila->sourceRegister,"000");
	strcpy(myMila->sourceMiun, "00");  
}
if(myPreMila->operation <= LEA){
	typeOfOperation = 1;
}
if(myPreMila->operation >= RTS){	
	strcpy(myMila->sourceRegister,"000");
	strcpy(myMila->sourceMiun, "00");
	strcpy(myMila->destinationRegister,"000");
	strcpy(myMila->destinationMiun, "00");
	typeOfOperation = 2;
	return 0;
}
char *ptr = line;
char *ptr2;
char gotParameter = 0;/*act as a boolean that idicates us to assign value to the next parameter in the mila*/
if(typeOfOperation == 2){
	gotParameter = 1;
}
char *temp = (char*) calloc(100,sizeof(char));  
int i =0;
int i2;
while(*ptr != '\0'){
printf("c: %c\n", *ptr);
	if(isspace(*ptr)){
	ptr++; 
	}
	if(*ptr == COMMA){
		if(gotParameter >= 1 || typeOfOperation != 1){
			return -3;/* there is too much commas */
		}	
		if(*temp == 0){/*eror got comma without parameter*/
			return -1;
		}
		for(i2 = 0;i2<=i;i2++){
			*(myPreMila->param1+i2) = *(temp +i2);
		}
	free(temp);
	temp = (char*) calloc(100,sizeof(char));  
	gotParameter = 1;
	ptr++;
	i=0;	
	}	
	if(!isspace(*ptr)){
		if(*ptr == '#'){/*this parameter has miun 0 value*/
			i2 = 0;
			i2 = getNumber(ptr, myMila);/*go get the number value*/
			if(i2 == -1){/*no number*/
				printf("\ngot a corrupted shit parameter skip to next mila\n");
			}else{
				ptr+i2;/*skip the chars that we read in getNumber fucntion*/
				if(gotParameter){
					strcpy(myMila->destinationMiun, "00");
					myPreMila->param2_miun = MIUN0;/*MIUN1*/
				}else{
					strcpy(myMila->sourceMiun, "00");
					myPreMila->param1_miun = MIUN0;
				}
				while(*ptr2 != COMMA && *ptr2 != '\0'){
					ptr++;
				}			
			}
		}
		if(*ptr == '&'){/*this parameter has miun 2 value*/
			strcpy(myMila->a_r_e, "100");
			if(!gotParameter){
			strcpy(myMila->sourceMiun, "10");
			/*myMila->sourceMiun = ;*/
			}else{
			strcpy(myMila->destinationMiun, "10");
			/*myMila->destinationMiun = "10";*/
			}
		}
	*(temp+i) = *ptr;
	i++;
	}
	if(*ptr == '\0'){
		break;
	}
	ptr++;
}

/*printf("\npo\n");*/
for(i2 = 0;i2<=i;i2++){
*(myPreMila->param2+i2) = *(temp +i2);
}
return 2;
}


/* 
 * @description this method assign the opcode amd funct values of the given pointed mila
 *param line is the line struct that we extract from that opcode
 *param myMila is a pointer to the given mila that we want to change
*/ 
int makepOpCodeAndFunct(int funct,mila *myMila){  
	/*printf("funct: %d\n", funct); */
    switch(funct){
	case(0):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "000000");
	/*myMila->funct = "00000";
	myMila->opCode = "000000";*/
	break;
	case(1):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "000001");
	/*myMila->funct = "00000";
	myMila->opCode = "000001";*/
	break;

	case(2):
	strcpy(myMila->funct, "00001");
	strcpy(myMila->opCode, "000010");
	/*myMila->funct = "00001";
	myMila->opCode = "000010";*/
	break;

	case(3):
	strcpy(myMila->funct, "00010");
	strcpy(myMila->opCode, "000010");
	/*myMila->funct = "00010";
	myMila->opCode = "000010";*/
	break;

	case(4):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "000100");
	/*myMila->funct = "00000";
	myMila->opCode = "000100";*/
	break;

	case(5):
	strcpy(myMila->funct, "00001");
	strcpy(myMila->opCode, "000101");
	/*myMila->funct = "00001";
	myMila->opCode = "000101";*/
	break;

	case(6):
	strcpy(myMila->funct, "00010");
	strcpy(myMila->opCode, "000101");
	/*myMila->funct = "00010";
	myMila->opCode = "000101";*/
	break;

	case(7):
	strcpy(myMila->funct, "00011");
	strcpy(myMila->opCode, "000101");
	/*myMila->funct = "00011";
	myMila->opCode = "000101";*/
	break;

	case(8):
	strcpy(myMila->funct, "00100");
	strcpy(myMila->opCode, "000101");
	/*myMila->funct = "00100";
	myMila->opCode = "000101";*/
	break;

	case(9):
	strcpy(myMila->funct, "00001");
	strcpy(myMila->opCode, "001001");
	/*myMila->funct = "00001";
	myMila->opCode = "001001";*/
	break;

	case(10):	
	strcpy(myMila->funct, "00010");
	strcpy(myMila->opCode, "001001");
	/*myMila->funct = "00010";
	myMila->opCode = "001001";*/
	break;

	case(11):
	strcpy(myMila->funct, "00011");
	strcpy(myMila->opCode, "001001");
/*	myMila->funct = "00011";
	myMila->opCode = "001001";*/
	break;

	case(12):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001100");
/*	myMila->funct = "00000";
	myMila->opCode = "001100";*/
	break;

	case(13):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001101");
	/*myMila->funct = "00000";
	myMila->opCode = "001101";*/
	break;	

        case(14):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001110");
/*	myMila->funct = "00000";
	myMila->opCode = "001110";*/
	break;       
 
	case(15):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001111");
	/*myMila->funct = "00000";
	myMila->opCode = "001111";*/
	break;
        default:
	return 1;/*eror code 1 = no operation code!!*/
	break;
	return 0;/*everything is ok*/
    }
}    
