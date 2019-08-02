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


int main()
{
  unsigned char data[32] = {0};
  int pointer = 0;
  int size = sizeof(data)/sizeof(*data);
  
  cjar::SerialWriter::writeBytes(data, &pointer, "cookie-jar" );
  cjar::SerialWriter::writeBytes(data, &pointer, (char) 0xff);

  printBytes(size,data);
  //printf("%ld %ld\n",sizeof(float), sizeof(double));

  return 0;
}
