char array [] = {"sdsad"};


typedef struct int24{
    unsigned int data : 24;
}int24;

int24 * first;

static int24 * arr24 [100]; 




void makeBinary(int toPrint){

unsigned i; 

    for (i = 1 << 24; i > 0; i = i / 2) 
        (toPrint & i)? printf("1"): printf("0"); 
  
  
}
