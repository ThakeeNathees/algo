#pragma once

#include <stdio.h>

/*
   using big-endian for reading and writing bytes.
   support variant size of permitive types.
 */

#include "SerialWriter.h"
#include "SerialReader.h"
#include "CjField.h"
#include "CjArray.h"
#include "CjObject.h"

namespace cjar
{
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


inline void writeToFile(unsigned char* buffer, int count, const char* path){
   FILE* file_p;
   file_p = fopen(path, "wb");
   fwrite(buffer, sizeof(char), count, file_p );
   fclose(file_p);
}

}