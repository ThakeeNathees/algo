#include <stdio.h>
#include "Cookie-Jar.h"

void printBytes(int size, unsigned char data[]){
  int counter = 0;
  for (int i=0; i<size; i++){
    printf("%02x ",data[i]);
    if ( counter++ == 15 ) printf("\n");
  }
  printf("\n");
}

union F
{
  float f;
  unsigned char c[0];
};

int main()
{
  unsigned char data[32] = {0};
  int pointer = 0;
  int size = sizeof(data)/sizeof(*data);
  
  F f; f.f = 1.5;
  for (size_t i=0; i<sizeof(F); i++){
    printf("%02x\n",f.c[i]);
  }
  
  //printBytes(size,data);

  return 0;
}
