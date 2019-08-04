#include "Cookie-Jar.h"


int main()
{
/*int size = 10;
  int* int_array = new int[size];
  for (int i=0; i<size; i++) int_array[i] = i;

  int int_val = 32;
  const char* str = "hello world!";

  //fields & arrays
  cjar::Field* i_val = cjar::Field::Int("int_val",int_val);
  cjar::Array* i_arr = cjar::Array::Int("int_array",int_array, size);
  delete[] int_array;
  cjar::Array* str_arr = cjar::Array::String("str", str);
  
  //objects
  cjar::Object* obj0 = cjar::Object::create("Obj0");
  obj0->addField(i_val)->addArray(i_arr)->addArray(str_arr);

  cjar::Object* obj1 = cjar::Object::create("Obj2");
  obj1->addField( cjar::Field::Bool("bool_val", true) );

  // database
  cjar::DataBase* dbase = cjar::DataBase::create("dbase");
  dbase->addObject(obj0)->addObject(obj1);*/


  cjar::Jar jar("MyJar");
  jar.readFromFile("MyJar.cjar");
  jar.printString();

  cjar::DataBase* dbase = jar.getDataBase();
  int int_val     = dbase->getObjects()[0]->getFields()[0]->getValue().i;
  int* int_array  = dbase->getObjects()[0]->getArrays()[0]->getValues<int>();
  const char* str = dbase->getObjects()[0]->getArrays()[1]->getString();
  bool bool_val   = dbase->getObjects()[1]->getFields()[0]->getValue().b;

  return 0;
}
