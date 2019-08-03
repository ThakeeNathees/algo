#include <stdio.h>
#include "Cookie-Jar.h"
#include <string.h>


int main()
{
  
  char* carray = new char[10]; char c = 0x61;
  for (int i=0; i<10; i++){
    carray[i] = c++;
  }

  //fields
  cjar::Field* int32 = cjar::Field::Int("int32",32);
  cjar::Array* arr = cjar::Array::Char("char_arr",carray, 10);
  cjar::Array* str = cjar::Array::String("str_name", "hello world!");
  //object
  cjar::Object* obj = cjar::Object::create("anobject");
  obj->addField(int32);
  obj->addArray(arr);
  obj->addArray(str);  
  // database
  cjar::DataBase* dbase = cjar::DataBase::create("dbase");
  dbase->addObject(obj);


  cjar::Jar jar("jar_test");
  jar.readFromFile("jar_test.cjar");
  //jar.setDataBase(dbase);
  //jar.convertBinary();
  jar.print();
  jar.writeToFile();

  const char* hello = jar.getDataBase()->getObjects()[0]->getArrays()[1]->getString();
  printf("%s\n",hello);

  return 0;
}
