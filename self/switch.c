#include <stdio.h>

float calc(){
  int h =5;
  int m = 42;
  int code = 692;
  switch(code){
    case 44: return (h*60+m)*0.77;break; //Kiev
    case 62: return (h*60+m)*0.8;break; //Doneck
    case 32: return (h*60+m)*0.95;break; //Lviv
    case 697:	     
    case 692: return (h*60+m)*1.5;break;//Simp/Sevast
    default:
	   if(code>999 | code<10) puts("Error!");return -1;
	  puts("Invalid code"); return -2;
	 break; 
  }
}

int main(){
 float r; 
 if(r=calc()){
   printf("Spent %f", r);
 } 
}
