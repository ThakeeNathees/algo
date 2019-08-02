

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
      stream[(*pointer)++] = value;
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, short value){
      writeBytes(stream, pointer, (unsigned short)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned short value){
      stream[(*pointer)++] = (unsigned char) (value >> 8) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 0) & 0x00ff;
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, int value){
      writeBytes(stream, pointer, (unsigned int)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned int value){
      stream[(*pointer)++] = (unsigned char) (value >> 24) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 16) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >>  8) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >>  0) & 0x00ff;
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
      stream[(*pointer)++] = (unsigned char) (value >> 56) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 48) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 40) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 32) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 24) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 16) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >>  8) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >>  0) & 0x00ff;
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, float value){
      FloatUnion float_u;
      float_u.f = value;
      stream[(*pointer)++] = (unsigned char) (float_u.c[3]);
      stream[(*pointer)++] = (unsigned char) (float_u.c[2]);
      stream[(*pointer)++] = (unsigned char) (float_u.c[1]);
      stream[(*pointer)++] = (unsigned char) (float_u.c[0]);
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, double value){
      DoubleUnion double_u;
      double_u.d = value;
      stream[(*pointer)++] = (unsigned char) (double_u.c[7]);
      stream[(*pointer)++] = (unsigned char) (double_u.c[6]);
      stream[(*pointer)++] = (unsigned char) (double_u.c[5]);
      stream[(*pointer)++] = (unsigned char) (double_u.c[4]);
      stream[(*pointer)++] = (unsigned char) (double_u.c[3]);
      stream[(*pointer)++] = (unsigned char) (double_u.c[2]);
      stream[(*pointer)++] = (unsigned char) (double_u.c[1]);
      stream[(*pointer)++] = (unsigned char) (double_u.c[0]);
  }

  inline static void writeBytes(unsigned char* stream, int* pointer, bool value){
      stream[(*pointer)++] = (unsigned char) value; 
  }
  
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned char* value){
    writeBytes(stream, pointer, (const char*)value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, char* value){
    writeBytes(stream, pointer, (const char*)value);
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




};

}