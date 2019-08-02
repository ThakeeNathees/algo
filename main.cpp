#include <stdio.h>
#include "Cookie-Jar.h"

#include <memory>

void f(unsigned char c){}


int main()
{
  
  cjar::CjArray* arr = cjar::CjArray::Char("string_arr","some string");
  cjar::CjField* fint = cjar::CjField::Int("fint32",32);

  cjar::CjObject cjo = cjar::CjObject("object0");
  cjo.addField(*fint); cjo.addArray(*arr);

  cjar::CjDataBase dbase = cjar::CjDataBase("dbase");
  dbase.addObject(cjo);

  unsigned char buffer[ dbase.getSize() ];
  int pointer = 0;
  int count = sizeof(buffer)/sizeof(*buffer);

  dbase.writeBytes(buffer, &pointer);


  cjar::writeToFile(buffer, count, "./serialdata.cjar");
  cjar::printBytes(count,buffer);

  return 0;
}
