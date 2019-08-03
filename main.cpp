#include <stdio.h>
#include "Cookie-Jar.h"
#include <string.h>


int main()
{
  
  cjar::CjArray* arr = cjar::CjArray::Char("string_arr","some string");

  cjar::CjObject* cjo = cjar::CjObject::create("object0");
  
  cjo->addField( cjar::CjField::Int("fint32",32) );   
  cjo->addArray(arr);
  

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
