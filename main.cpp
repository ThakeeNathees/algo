#include <stdio.h>
#include "Cookie-Jar.h"


void f(unsigned char c){}


int main()
{
  
  //cjar::SerialWriter::writeBytes(data, &pointer, "cookie-jar" );

  //short c[] = { 0xc0ff, 0xeec0, 0xffee };
  unsigned char* x = new unsigned char[3];
  x[0] = 1;x[1] = 2;x[2] = 3;
  cjar::CjArray* arr = cjar::CjArray::Char("array123", x, 3);
  cjar::CjField* fint = cjar::CjField::Int("fint32",32);

  cjar::CjObject cjo = cjar::CjObject("object0");
  cjo.addField(*fint); cjo.addArray(*arr);

  cjar::CjDataBase dbase = cjar::CjDataBase("dbase");
  dbase.addObject(cjo);

  unsigned char buffer[ dbase.getSize() ];
  int pointer = 0;
  int count = sizeof(buffer)/sizeof(*buffer);

  dbase.writeBytes(buffer, &pointer);


  cjar::writeToFile(buffer, count, "./serialdata");
  cjar::printBytes(count,buffer);

  //printf("%i \n", sizeof(char) + sizeof(short) );
  return 0;
}
