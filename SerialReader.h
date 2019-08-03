#pragma once 
#include "cjar.h"

namespace cjar
{

class SerialReader
{
private:
  union FloatUnion{
      float f; unsigned char c[0];
  };
  union DoubleUnion{
      double d; unsigned char c[0];
  };
public:
  inline static unsigned char readChar(unsigned char* stream, int* pointer){
      unsigned char result = 0;
      for (int i=sizeof(result)-1; i>=0; i--){
        result |= (long)stream[(*pointer)++] << 8*i;
      }
      return result;
  }

  inline static unsigned short readShort(unsigned char* stream, int* pointer){
      unsigned short result = 0;
      for (int i=sizeof(result)-1; i>=0; i--){
        result |= (long)stream[(*pointer)++] << 8*i;
      }
      return result;
  }

  inline static unsigned int readInt(unsigned char* stream, int* pointer){
      unsigned int result = 0;
      for (int i=sizeof(result)-1; i>=0; i--){
        result |= (long)stream[(*pointer)++] << 8*i;
      }
      return result;
  }

  inline static unsigned long readLong(unsigned char* stream, int* pointer){
      unsigned long result = 0;
      for (int i=sizeof(result)-1; i>=0; i--){
        result |= (long)stream[(*pointer)++] << 8*i;
      }
      return result;
  }

  inline static bool readBool(unsigned char* stream, int* pointer){
      return stream[(*pointer)++]!=0;
  }

  inline static float readFloat(unsigned char* stream, int* pointer){
      FloatUnion float_u;
      for (int i=sizeof(float)-1; i>=0; i--){
          float_u.c[i] = stream[(*pointer)++];
      }
      return float_u.f;
  }

  inline static double readDouble(unsigned char* stream, int* pointer){
      DoubleUnion double_u;
      for (int i=sizeof(double)-1; i>=0; i-- ){
          double_u.c[i] = stream[(*pointer)++];
      }
      return double_u.d;
  }

  //reading string
  inline static void readString(char* dest, short len, unsigned char* stream, int* pointer){
    readString( (unsigned char*) dest, len, stream, pointer);
  }
  inline static void readString(unsigned char* dest, short len, unsigned char* stream, int* pointer){
      for (int i=0; i<len; i++){
          dest[i] = stream[((*pointer)++)];
      }
      dest[len] = (unsigned char) 0x00;
  }

  // arrays
  inline static void readBytes(unsigned char* dest, short len, unsigned char* stream, int* pointer){
      for (int i=0; i<len; i++){
          dest[i] = stream[(*pointer)++];
      }
  }


};

}
