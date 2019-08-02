#include <stdio.h>
#define print(x) printf("%x\n",x)
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
  inline static unsigned char readChar(unsigned char* stream, int pointer){
      return stream[pointer];
  }

  inline static unsigned short readShort(unsigned char* stream, int pointer){
      return ( stream[pointer] << 8 ) | ( stream[pointer+1] << 0 );
  }

  inline static unsigned int readInt(unsigned char* stream, int pointer){
      return (stream[pointer] << 24) | (stream[pointer+1] << 16) | 
             (stream[pointer+2] << 8) | (stream[pointer+3] << 0);
  }

  inline static unsigned long readLong(unsigned char* stream, int pointer){
      return ((long)stream[pointer]   << 56 ) | ((long)stream[pointer+1] << 48 ) | ((long)stream[pointer+2] << 40 ) | 
             ((long)stream[pointer+3] << 32 ) | ((long)stream[pointer+4] << 24 ) | ((long)stream[pointer+5] << 16 ) | 
             ((long)stream[pointer+6] <<  8 ) | ((long)stream[pointer+7] <<  0 );
  }

  inline static bool readBool(unsigned char* stream, int pointer){
      return stream[pointer]!=0;
  }

  inline static float readFloat(unsigned char* stream, int pointer){
      FloatUnion float_u;
      float_u.c[3] = stream[pointer++];
      float_u.c[2] = stream[pointer++];
      float_u.c[1] = stream[pointer++];
      float_u.c[0] = stream[pointer++];
      return float_u.f;
  }

  inline static double readDouble(unsigned char* stream, int pointer){
      DoubleUnion double_u;
      double_u.c[7] = stream[pointer++];
      double_u.c[6] = stream[pointer++];
      double_u.c[5] = stream[pointer++];
      double_u.c[4] = stream[pointer++];
      double_u.c[3] = stream[pointer++];
      double_u.c[2] = stream[pointer++];
      double_u.c[1] = stream[pointer++];
      double_u.c[0] = stream[pointer++];
      return double_u.d;
  }

  inline static void readBytes(char* dest, unsigned char* stream, int pointer){
    readBytes( (unsigned char*) dest, stream, pointer);
  }
  inline static void readBytes(unsigned char* dest, unsigned char* stream, int pointer){
      unsigned short len = readShort(stream, pointer);
      for (int i=0; i<len; i++){
          dest[i] = stream[pointer+2+i];
      }
      dest[len] = (unsigned char) 0x00;
  }


};

}
