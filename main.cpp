#include <stdio.h>
#include "Cookie-Jar.h"




int main()
{
  unsigned char data[64] = {0};
  int pointer = 0;
  int size = sizeof(data)/sizeof(*data);
  
  unsigned char str[20];

  cjar::SerialWriter::writeBytes(data, &pointer, "cookie-jar" );
  
  cjar::Field* f = cjar::Field::Float("floatx", 1.5);
  f->writeBytes(data, &pointer);
  float floatx = cjar::SerialReader::readFloat(data, pointer-sizeof(float));
  
  
  cjar::SerialWriter::writeBytes(data, &pointer, (char)65 );


  printBytes(size,data);
  printf("%f \n",floatx);
  return 0;
}
