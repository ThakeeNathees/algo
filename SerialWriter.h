#pragma once

namespace cjar{

class SerialWriter
{
public:
           const char* HEADER  = "Cookie-Jar";
  unsigned const short VERSION = 0x0100;
private:
  union FloatUnion{
      float f; unsigned char c[0];
  };
  union DoubleUnion{
      double d; unsigned char c[0];
  };
public:
  inline static void writeBytes(unsigned char* stream, int* pointer, char value){
      writeBytes(stream, pointer, (unsigned char)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned char value){
      for (int i=sizeof(value)-1; i >= 0 ; i--){
          stream[(*pointer)++] = (unsigned char) (value >>  8*i) & 0x00ff;
      }
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, short value){
      writeBytes(stream, pointer, (unsigned short)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned short value){
      for (int i=sizeof(value)-1; i >= 0 ; i--){
          stream[(*pointer)++] = (unsigned char) (value >>  8*i) & 0x00ff;
      }
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, int value){
      writeBytes(stream, pointer, (unsigned int)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned int value){
      for (int i=sizeof(value)-1; i >= 0 ; i--){
          stream[(*pointer)++] = (unsigned char) (value >>  8*i) & 0x00ff;
      }
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned long long value){
      writeBytes(stream, pointer, (unsigned long)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, long long value){
      writeBytes(stream, pointer, (unsigned long)value);
  }inline static void writeBytes(unsigned char* stream, int* pointer, long value){
      writeBytes(stream, pointer, (unsigned long)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned long value){
      for (int i=sizeof(value)-1; i >= 0 ; i--){
          stream[(*pointer)++] = (unsigned char) (value >>  8*i) & 0x00ff;
      }
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, float value){
      FloatUnion float_u;
      float_u.f = value;
      for (int i=sizeof(value)-1; i >= 0 ; i--){
          stream[(*pointer)++] = (unsigned char) (float_u.c[i]);
      }
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, double value){
      DoubleUnion double_u;
      double_u.d = value;
      for (int i=sizeof(value)-1; i >= 0 ; i--){
          stream[(*pointer)++] = (unsigned char) (double_u.c[i]);
      }
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, bool value){
      stream[(*pointer)++] = (unsigned char) value; 
  }
  
  inline static void writeBytes(unsigned char* stream, int* pointer, char* value, int count){
    writeBytes(stream, pointer, (unsigned char*)value, count);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned char* value, int count){
      for( int i=0; i < count; i++  )
          writeBytes(stream, pointer, value[i] );
  }
  
  inline static void writeBytes(unsigned char* stream, int* pointer, const char* value){
      unsigned short len = 0;
      int len_p = *pointer;
      writeBytes(stream, pointer, len); // reserve memory for len
      while( value[len] ){
          writeBytes(stream, pointer, value[len++] );
      }
      writeBytes(stream, &len_p, len);
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, const char* value, int count){
      for(int i=0; i<count; i++){
          writeBytes(stream, pointer, value[i] );
      }
  }


};

}