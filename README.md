# Cookie-Jar
A simple & fast C++ serialization header only library.

### Install
It's a header only library just copy the source folder to your include path and use a C++11 compiler or use as a pre-compiled library.

### Usage Samples
```c++
#include "Cookie-Jar.h"


int main()
{
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

  cjar::Object* obj1 = cjar::Object::create("Obj2");
  obj1->addField( cjar::Field::Bool("bool_val", true) );

  // database
  cjar::DataBase* dbase = cjar::DataBase::create("dbase");
  dbase->addObject(obj0)->addObject(obj1);


  cjar::Jar jar("MyJar");
  jar.setDataBase(dbase);
  jar.convertToBinary();
  jar.printBytes();
  jar.writeToFile(); // writes to MyJar.cjar

  return 0;
}
```
binary data
```
00 0a 43 6f 6f 6b 69 65 2d 4a 61 72 01 00 04 00  . . C o o k i e - J a r . . . .
00 00 c1 00 05 64 62 61 73 65 00 00 00 02 03 00  . . . . . d b a s e . . . . . .
00 00 7f 00 04 4f 62 6a 30 00 00 00 01 01 00 00  . . . . . O b j 0 . . . . . . .
00 13 00 07 69 6e 74 5f 76 61 6c 04 00 00 00 20  . . . . i n t _ v a l . . . .  
00 00 00 02 02 00 00 00 3d 00 09 69 6e 74 5f 61  . . . . . . . . = . . i n t _ a
72 72 61 79 04 00 00 00 0a 00 00 00 00 00 00 00  r r a y . . . . . . . . . . . .
01 00 00 00 02 00 00 00 03 00 00 00 04 00 00 00  . . . . . . . . . . . . . . . .
05 00 00 00 06 00 00 00 07 00 00 00 08 00 00 00  . . . . . . . . . . . . . . . .
09 02 00 00 00 1c 00 03 73 74 72 01 00 00 00 0d  . . . . . . . . s t r . . . . .
68 65 6c 6c 6f 20 77 6f 72 6c 64 21 00 03 00 00  h e l l o   w o r l d ! . . . .
00 24 00 04 4f 62 6a 32 00 00 00 01 01 00 00 00  . $ . . O b j 2 . . . . . . . .
11 00 08 62 6f 6f 6c 5f 76 61 6c 02 01 00 00 00  . . . b o o l _ v a l . . . . .
00                                               .
```
---
```c++

#include "Cookie-Jar.h"

int main()
{
  cjar::Jar jar("MyJar");
  jar.readFromFile("MyJar.cjar");
  jar.printString();

  cjar::DataBase* dbase = jar.getDataBase();
  int int_val     = dbase->getObjects()[0]->getFields()[0]->getValue<int>();
  int* int_array  = dbase->getObjects()[0]->getArrays()[0]->getValues<int>();
  const char* str = dbase->getObjects()[0]->getArrays()[1]->getString();
  bool bool_val   = dbase->getObjects()[1]->getFields()[0]->getValue<bool>();

  return 0;
}
```
console output
```
================================================================================
HEADER : Cookie-Jar VERSION = 0100
DataBase : dbase
================================================================================

Obj0:
        int_val         = 32
        int_array       = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, }
        str             = hello world!

Obj2:
        bool_val        = true

================================================================================
```
