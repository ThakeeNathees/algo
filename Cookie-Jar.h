#pragma once

#include <stdio.h>

/*
   using big-endian for reading and writing bytes.
   support variant size of permitive types.
 */

#include "SerialWriter.h"
#include "SerialReader.h"
#include "Field.h"

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