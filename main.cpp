#include <stdio.h>
#include "Cookie-Jar.h"


void f(unsigned char c){}


int main()
{
  
  //cjar::SerialWriter::writeBytes(data, &pointer, "cookie-jar" );

  //short c[] = { 0xc0ff, 0xeec0, 0xffee };
  int c = 3;
  char* x = new char[c];
  for (int i=0; i<c; i++){x[i] = i;}
  cjar::CjArray* arr = cjar::CjArray::Char("array123", x, c);
  cjar::CjField* fint = cjar::CjField::Int("fint32",32);

  cjar::CjObject cjo = cjar::CjObject("object0");
  cjo.addField(*fint); cjo.addArray(*arr);

  unsigned char buffer[ cjo.getSize() ];
  int pointer = 0;
  int count = sizeof(buffer)/sizeof(*buffer);

  cjo.writeBytes(buffer, &pointer);

  cjar::writeToFile(buffer, count, "./serialdata");

  cjar::printBytes(count,buffer);

  //printf("%i \n", sizeof(char) + sizeof(short) );
  return 0;
}
