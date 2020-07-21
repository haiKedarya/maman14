#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define DOT 46
#define MAX_LINE 80
#define makeCalloc(name, type, size){
type name = (type*) calloc(size, sizeof(type));/
if(!name){exit(0);}} /*add here someething to eror file*/

typedef struct FilesObj{ 
	File source;/*creation of file reading*/
	File obj;/*creation of 3 pointers to file printing*/
	File ext;
	File entry;	
    };
typedef struct mila{ 
	char opCode[6];
	char sourceMiun[2];
	char sourceRegister[3];
	char destinationMiun[2];
	char destinationRegister[3];
	char funct[5];
	char Are[3];
    };
typedef struct lines{
char label[31];
char opName[4];
char param1[100];
char param2[100];
int lineAdrress;
};


int main(int argc, char *argv[]){
    printf("\nmain");
    FilesObj files ;
    char *fileName;
    if( argc == 1  || argc == 0) {/*we dont have any file names*/
      printf("at least one argument expected.\n");
      return 0;
    }else if(argc == 2){/*we have only 1 file name*/
	fileName = checkCommandLineInput(2, *argv[]);
        assignAddressOfFiles(files, fileName);
    }else{/*we have more then 1 file name*/
    	for(int i = 2; i < argc; i++){
	    fileName = checkCommandLineInput(i, *argv[]);/*here the loop will run on each file*/
	    assignAddressOfFiles(files, fileName);
	}
    }    
}

/* 
 * @description this method assigninig values to the files in FilesObj
 * @param files of type FilesObj contain the files
 * @param fileName contain the file name that we need to open and create
 */
void assignAddressOfFiles(FilesObj files, char[] fileName){
    if(!(files.source = fopen(fileName + ".as","r"))){
	fprintf(stderr, "cant open the file:" %s "\n", fileName);
        exit(0);
    }
    file.obj = fopen(fileName + ".obj", "w"); 
}
/* 
 * @description this method check the command line argument if the argument is legal the method will return the location of '.' in argv so we can extract the file name if the argument is not legal the method will return 0 
 *param location locates us to the string that contains the file name(in case we have several files)
 *param *argv[] contain the command line arguments from main
*/
char *checkCommandLineInput(int location, char *argv[]){
    printf("check input");
    int i = 0;
    
    while(i < strlen(argv[location])){
	if(*argv[location][i] == DOT){
	    break;/*so we save the location of '.'  in i*/
	}
	i++;
    }
    char *str = (char*) malloc(10*sizeof(char)); 
    memcpy(str, argv[location], i);
    return str;/*str == file name*/
}
/* 
 * @description this method run on the entire file.as and sends every time a whole line(maximum of 80 chars) to some check methods
 *param file is an indicator to file.as
*/ 
int startRunOnFile(File file){
    int LineAddress = 100;
    char *arrTextOfLine = (char*) calloc(MAX_LINE,sizeof(char));  
    lines line;
    while(1){
	if( feof(fp) ) { 
         break ;
         }
	 
         fgets(input,MAX_LINE,file);
         if(*arr == ';'){/*its a comment line*/
	    continue;
	 }
	 /*call here to the other functions*/
	 line.lineAdrress = LineAddress;
	 firstPart(arrTextOfLine, &line);
	 LineAddress = /*other function that returns it after constructing a MILA*/;
    }
}
int makeMila(lines line, int LineAddress){
    mila myMila;
    if(makepOpCode){return 111;}/* 111 is eror code that says illegal opCode */
    if()

}
/* 
 * @description this method assigning values to the registers if there is any "r0-7" in line.param1-2
 *param myMila is a pointer to the given mila that we want to change
 *param (struct) line we take from him the  
*/ 
int assignRegistersValues(lines line,mila *myMila){
   int count = 0;
   char check[100];
   strcpy(check, line.param1);/*assign check array the value of param1 */
   while(count <= 1){
   switch(check){
	case("r0"):0
	if(count){
	    myMila->destinationRegister = "000";
	}else{
	    myMila->sourceRegister = "000";
	}
	break:
	case("r1"):1
	if(count){
	    myMila->destinationRegister = "001";
	}else{
	    myMila->sourceRegister = "001";
	}
	break:
	case("r2"):1
	if(count){
	    myMila->destinationRegister = "010";
	}else{
	    myMila->sourceRegister = "010";
	}
	break:
	case("r3"):1
	if(count){
	    myMila->destinationRegister = "011";
	}else{
	    myMila->sourceRegister = "011";
	}
	break:
	case("r4"):0
	if(count){
	    myMila->destinationRegister = "100";
	}else{
	    myMila->sourceRegister = "100";
	}
	break:
	case("r5"):1
	if(count){
	    myMila->destinationRegister = "101";
	}else{
	    myMila->sourceRegister = "101";
	}
	break:
	case("r6"):1
	if(count){
	    myMila->destinationRegister = "110";
	}else{
	    myMila->sourceRegister = "110";
	}
	break:
	case("r7"):1
	if(count){
	    myMila->destinationRegister = "111";
	}else{
	    myMila->sourceRegister = "111";
	}
	break:
	default:
	if(count){
	    myMila->destinationRegister = "000";
	}else{
	    myMila->sourceRegister = "000";
	}
	break;
	}
	count ++;	
        strcpy(check, line.param2);/*assign check array the value of param2 */
    }
    return 0;
}
/* 
 * @description this method assigning value to miun variables in the structure mila (each call for the fucntion declare the targeted miun)
 *param myMila is a pointer to the given mila that we want to change
 *param value is the value we want to assign to the mila
 *param first indicate with of the miun variables we want to change (if 1 or any value that is not 0 then its the source, else its destinationMiun)
*/ 
int assignMiunValues(mila *myMila, int value, char first){    
    switch(value){
	case(0):0
	if(fisrt){
	    myMila->sourceMiun = "00";
	}else{
	    myMila->destinationMiun = "00";
	}
	break:
	case(1):1
	if(fisrt){
	    myMila->sourceMiun = "01";
	}else{
	    myMila->destinationMiun = "01";
	}
	break:
	case(2):1
	if(fisrt){
	    myMila->sourceMiun = "10";
	}else{
	    myMila->destinationMiun = "10";
	}
	break:
	case(3):1
	if(fisrt){
	    myMila->sourceMiun = "11";
	}else{
	    myMila->destinationMiun = "11";
	}
	break:
	default:
	return 1;/*so i can know that there is no miun */
	break;
    return 0;
}

/* 
 * @description this method assign the opcode amd funct values of the given pointed mila
 *param line is the line struct that we extract from that opcode
 *param myMila is a pointer to the given mila that we want to change
*/ 
int makepOpCodeAndFunct(lines line,mila *myMila){    
    switch(line.opNode){
	case("mov"):
	myMila->funct = "00000";
	myMila->opCode = "000000";
	break:
	case("cmp"):
	myMila->funct = "00000";
	myMila->opCode = "000001";
	break:

	case("add"):
	myMila->funct = "00001";
	myMila->opCode = "000010";
	break:

	case("sub"):
	myMila->funct = "00010";
	myMila->opCode = "000010";
	break:

	case("lea"):
	myMila->funct = "00000";
	myMila->opCode = "000100";
	break:

	case("clr"):
	myMila->funct = "00001";
	myMila->opCode = "000101";
	break:

	case("not"):
	myMila->funct = "00010";
	myMila->opCode = "000101";
	break:

	case("inc"):
	myMila->funct = "00011";
	myMila->opCode = "000101";
	break:

	case("dec"):
	myMila->funct = "00100";
	myMila->opCode = "000101";
	break:

	case("jmp"):
	myMila->funct = "00001";
	myMila->opCode = "001001";
	break:

	case("bne"):
	myMila->funct = "00010";
	myMila->opCode = "001001";
	break:

	case("jsr"):
	myMila->funct = "00011";
	myMila->opCode = "001001";
	break:

	case("red"):
	myMila->funct = "00000";
	myMila->opCode = "001100";
	break:

	case("prn"):
	myMila->funct = "00000";
	myMila->opCode = "001101";
	break:	

        case("rts"):
	myMila->funct = "00000";
	myMila->opCode = "001110";
	break:       
 
	case("stop"):
	myMila->funct = "00000";
	myMila->opCode = "001111";
	break:
        default:
	return 1;/*eror code 1 = no operation code!!*/
	break;
	return 0;/*everything is ok*/
    }
}    


}

