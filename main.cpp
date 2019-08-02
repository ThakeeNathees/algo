#include <stdio.h>
#include "Cookie-Jar.h"




int main()
{
  unsigned char data[64] = {0};
  int pointer = 0;
  int size = sizeof(data)/sizeof(*data);
  
  unsigned char str[20];

  cjar::SerialWriter::writeBytes(data, &pointer, "cookie-jar" );
  cjar::SerialReader::readBytes(str, data, 0);
  cjar::SerialWriter::writeBytes(data, &pointer, str );
  cjar::SerialWriter::writeBytes(data, &pointer, 0xff );

  printBytes(size,data);
  
  printf("%s \n",str);

  return 0;
}
