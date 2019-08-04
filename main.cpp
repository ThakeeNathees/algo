#include <stdio.h>
#include "Cookie-Jar.h"
#include <string.h>


int main()
{
  int size = 20;
  int* iarray = new int[size]; int c = 0;
  for (int i=0; i<size; i++){
    iarray[i] = c++;
  }

  //fields
  cjar::Field* int32 = cjar::Field::Int("int32",32);
  cjar::Array* arr = cjar::Array::Int("arr",iarray, size);
  delete[] iarray;
  cjar::Array* str = cjar::Array::String("str", "hello world!");
  //object
  cjar::Object* obj = cjar::Object::create("AnObject");
  obj->addField(int32);
  obj->addArray(arr);
  obj->addArray(str);  
  cjar::Object* obj1 = cjar::Object::create("Obj2");
  obj1->addField( cjar::Field::Bool("boolval", true) );
  // database
  cjar::DataBase* dbase = cjar::DataBase::create("dbase");
  dbase->addObject(obj);
  dbase->addObject(obj1);


  cjar::Jar jar("jar_test");
  //jar.readFromFile("jar_test.cjar");
  jar.setDataBase(dbase);
  jar.convertBinary();
  jar.printBytes();
  jar.printString();
  //jar.writeToFile();

  const char* hello = jar.getDataBase()->getObjects()[0]->getArrays()[1]->getString();
  //printf("%s\n",hello);

  return 0;
}
