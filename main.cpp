#include "Cookie-Jar.h"


int main()
{
/*
  int size = 10;
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

  cjar::Object* obj1 = cjar::Object::create("Obj1");
  cjar::Object* obj2 = cjar::Object::create("Obj2");

  obj1->addField( cjar::Field::Bool("bool_val", true) )->addObject(obj2);

  // database
  cjar::DataBase* dbase = cjar::DataBase::create("dbase");
  dbase->addObject(obj0)->addObject(obj1);
  //*/


  cjar::Jar jar("MyJar");
  jar.readFromFile("MyJar.cjar");
  //jar.setDataBase(dbase);
  //jar.convertToBinary();
  //jar.writeToFile();
  jar.printString();
  //jar.printBytes();

//*
  cjar::DataBase* dbase = jar.getDataBase();
  int int_val        = dbase->findObject("Obj0")->findField("int_val")->getValue<int>();  
  int* int_array     = dbase->findObject("Obj0")->findArray("int_array")->getValues<int>();
  const char* str    = dbase->findObject("Obj0")->findArray("str")->getString();
  bool bool_val      = dbase->findObject("Obj1")->findField("bool_val")->getValue<bool>();
  cjar::Object* obj2 = dbase->findObject("Obj1")->findObject("Obj2");

//*/

  return 0;
}
