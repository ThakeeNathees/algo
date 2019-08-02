#include <stdio.h>

/*
 using big-endian for reading and writing bytes with the following
 primitive sizes.

  char      1 byte
  bool      1 byte
  short     2 bytes
  int       4 bytes
  long      8 bytes
  long long 8 bytes
  float     4 bytes
  double    8 bytes
 */

#include "SerialWriter.h"
#include "SerialReader.h"

inline void printBytes(int size, unsigned char data[]){
  int counter = 0;
  for (int i=0; i<size; i++){
    printf("%02x ",data[i]);
    if ( !(++counter % 16) ){
        for ( int j=i-15; j<=i; j++ )
        {
          char c = data[j];
          c = ( c>=0x20 && c<=0x7e )?c:'.';
          printf(" %c", c);
        }
        printf("\n");
    }
  }
  printf("\n");
}