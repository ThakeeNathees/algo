#include <stdio.h>
#include "Cookie-Jar.h"


void f(unsigned char c){}


int main()
{
  
  //cjar::SerialWriter::writeBytes(data, &pointer, "cookie-jar" );

  //short c[] = { 0xc0ff, 0xeec0, 0xffee };
  int c = 100;
  char* x = new char[c];
  for (int i=0; i<c; i++){
    x[i] = i;
  }
  cjar::CjArray* arr = cjar::CjArray::Char("arrayc", x, c);

  unsigned char buffer[ arr->getSize() ];
  int pointer = 0;
  int count = sizeof(buffer)/sizeof(*buffer);

  arr->writeBytes(buffer, &pointer);

  cjar::writeToFile(buffer, count, "./serialdata");

  cjar::printBytes(count,buffer);

  //printf("%f \n",floatx);
  return 0;
}
