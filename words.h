
typedef struct int24{
    unsigned int data : 24;
}int24;

int24 * first;

static int24 * arr24 [100]; 

int24 arrNum[100];


int makeBinary(int toPrint,int sibit){

unsigned i; 

    for (i = 1 << sibit; i > 0; i = i / 2) 
        (toPrint & i)? printf("1"): printf("0"); 
  printf("\n");
  return 1;
  
}
