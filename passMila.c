#include "firstPass.h"

char regs [8][3] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"}; 

char ops [16][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}; 

void printMila(mila *myMila){
printf("this is the mila\n");
printf("%s",myMila->opCode);
printf("%s",myMila->sourceMiun);
printf("%s",myMila->sourceRegister);
printf("%s",myMila->destinationMiun);
printf("%s",myMila->destinationRegister);
printf("%s\n",myMila->funct);
/*printf("%s",myMila->a_r_e);*/
}
/* 
 * @description this method assigning values to the registers if there is any "r0-7" in line.param1-2
 *param myMila is a pointer to the given mila that we want to change
 *param (struct) line we take from him the  
*/ 
void assignRegistersValues(preMila pre_mila,mila *myMila){
printf("welcome to assignRegistersValues");
   int count = 0;
   char check[100];
   strcpy(check, pre_mila.param1);/*assign check array the value of param1 */
   int i;  
puts(pre_mila.param1);
   while(count <= 1){
    	for(i = 0; i < 8;i++){/*this loop will run until it will find r0-r7*/
	if(!strcmp(regs[i],check)){
	break;
	}
	
   	}
   	printf("\nvalue is:%s", check);
printf("\nregister is:%d", i);
if(i!=8){
   switch(i){
	case(0):
	if(count){
	    strcpy(myMila->destinationRegister,"000");
	    strcpy(myMila->destinationMiun,"00");
	    /*myMila->destinationRegister = ;
	    myMila->destinationMiun = "00";*/
	}else{
	    /*myMila->sourceRegister = "000";
	    myMila->sourceMiun = "00";*/
	    strcpy(myMila->sourceRegister,"000");
	    strcpy(myMila->sourceMiun,"00");	    
	}
	break;
	case(1):
	if(count){
	    strcpy(myMila->destinationRegister,"001");
	    strcpy(myMila->destinationMiun,"00");
	    /*myMila->destinationRegister = "001";
            myMila->destinationMiun = "00";*/
	}else{
	    strcpy(myMila->sourceRegister,"001");
	    strcpy(myMila->sourceMiun,"00");	    
	   /* myMila->sourceRegister = "001";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(2):
	if(count){
	    strcpy(myMila->destinationRegister,"010");
	    strcpy(myMila->destinationMiun,"00");
	    /*myMila->destinationRegister = "010";
            myMila->destinationMiun = "00";*/
	}else{
	    strcpy(myMila->sourceRegister,"010");
	    strcpy(myMila->sourceMiun,"00");	    
	   /* myMila->sourceRegister = "010";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case (3):
	if(count){
	    strcpy(myMila->destinationRegister,"011");
	    strcpy(myMila->destinationMiun,"00");
/*	    myMila->destinationRegister = "011";
            myMila->destinationMiun = "00";*/
	}else{
	
	    strcpy(myMila->sourceRegister,"011");
	    strcpy(myMila->sourceMiun,"00");
	    /*myMila->sourceRegister = "011";
	    *myMila->sourceMiun = "00";*/
	}
	break;
	case(4):
	if(count){
	    strcpy(myMila->destinationRegister,"100");
	    strcpy(myMila->destinationMiun,"00");
/*	    myMila->destinationRegister = "100";
            myMila->destinationMiun = "00";*/
	}else{
	    strcpy(myMila->sourceRegister,"100");
	    strcpy(myMila->sourceMiun,"00");	    
	   /*myMila->sourceRegister = "100";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(5):
	if(count){
	    strcpy(myMila->destinationRegister,"101");
	    strcpy(myMila->destinationMiun,"00");
/*	    myMila->destinationRegister = "101";
            myMila->destinationMiun = "00";*/
	}else{
	    strcpy(myMila->sourceRegister,"101");
	    strcpy(myMila->sourceMiun,"00");	    
/*	    myMila->sourceRegister = "101";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(6):
	if(count){
	    strcpy(myMila->destinationRegister,"110");
	    strcpy(myMila->destinationMiun,"00");
/*	    myMila->destinationRegister = "110";
            myMila->destinationMiun = "00";*/
	}else{
	    strcpy(myMila->sourceRegister,"110");
	    strcpy(myMila->sourceMiun,"00");	    
	   /* myMila->sourceRegister = "110";
	    myMila->sourceMiun = "00";*/
	}
	break;
	case(7):
	if(count){
   	    strcpy(myMila->destinationRegister,"111");
	    strcpy(myMila->destinationMiun,"00");
/* 	    myMila->destinationRegister = "111";
            myMila->destinationMiun = "00";*/
	}else{
	    strcpy(myMila->sourceRegister,"111");
	    strcpy(myMila->sourceMiun,"00");	    
/*	    myMila->sourceRegister = "111";
	    myMila->sourceMiun = "00";*/
	}
	break;
	default:
	break;
	break;
	}
	}
	count ++;
        strcpy(check, pre_mila.param2);/*assign check array the value of param2 */
    }
}
/* 
 * @description this method assign values to the preMila values
 *param line is pointer to the line after getting the function name
 *param preMila is a pointer to the given preMila that we want to change
 *return will return 2 if we got 2 parameters with values. 1 if got one parameter, -2 if we got comma with no parameters, -1 if we got no parameters
*/ 

int getParameters(char * line,preMila *myPreMila, mila *myMila){
printf(" pre start get param\n");
char *ptr = line;
char * ifpars = line;
int pars=0;
		if(*ifpars == '#')
		{
		ifpars = strtok(line,"#");
		ptr = ifpars;
		}

char *ptr2;
char gotParameter = 0;/*act as a boolean that idicates us to assign value to the next parameter in the mila*/
char *temp = (char*) calloc(100,sizeof(char));  
int i =0;
int i2;
puts(line);

printf("start get param");
while(*ptr != '\0'){

	while(*ptr == " "){
	ptr++;
	}

	if(*ptr == COMMA){
	gotParameter = 1;
	ptr++;
		if(*temp == 0){/*eror got comma without parameter*/
		return -1;
		}
		for(i2 = 0;i2<=i;i2++){
		*(myPreMila->param1+i2) = *(temp +i2);
		}
	i=0;
	}
	
	if(!isspace(*ptr)){
		if(*ptr == '#' || ){/*this parameter has miun 0 value*/
		i2=0;
		ptr2 = ptr+1;
			while(*ptr2 != COMMA || *ptr2 !='\0'){/*run a loop to check if its a whole number*/
				if(*ptr == '.' && *(ptr+1) == '0'){/*its a whole number (not legal look for page 23)*/
				printf("illegal parameter value");
				break;
				}
			}
			if(!gotParameter){
			myPreMila->param1_miun = 0;
			}else{
			myPreMila->param1_miun = 0;
			}
		}
		if(*ptr == '&'){
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
	
ptr++;

}
if(gotParameter){/*eror got comma without second parameter*/
	if(*temp == 0){
	return -2;
	}
}else{/*no comma*/
	if(*temp == 0){/*no parameters*/
	return -1;
	}
	return 1;
}
for(i2 = 0;i2<i;i2++){
*(myPreMila->param2+i2) = *(temp +i2);
}

*(myPreMila->param2+i2) = '\0';
return 2;
}



/* 
 * @description this method assign the opcode amd funct values of the given pointed mila
 *param line is the line struct that we extract from that opcode
 *param myMila is a pointer to the given mila that we want to change
*/ 
int makepOpCodeAndFunct(int funct,mila *myMila){  
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
