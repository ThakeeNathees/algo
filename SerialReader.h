

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
      unsigned char result = 0;
      for (int i=sizeof(result)-1, j=0; i>=0; i--, j++){
        result |= (long)stream[pointer+j] << 8*i;
      }
      return result;
  }

  inline static unsigned short readShort(unsigned char* stream, int pointer){
      unsigned short result = 0;
      for (int i=sizeof(result)-1, j=0; i>=0; i--, j++){
        result |= (long)stream[pointer+j] << 8*i;
      }
      return result;
  }

  inline static unsigned int readInt(unsigned char* stream, int pointer){
      unsigned int result = 0;
      for (int i=sizeof(result)-1, j=0; i>=0; i--, j++){
        result |= (long)stream[pointer+j] << 8*i;
      }
      return result;
  }

  inline static unsigned long readLong(unsigned char* stream, int pointer){
      unsigned long result = 0;
      for (int i=sizeof(result)-1, j=0; i>=0; i--, j++){
        result |= (long)stream[pointer+j] << 8*i;
      }
      return result;
  }

  inline static bool readBool(unsigned char* stream, int pointer){
      return stream[pointer]!=0;
  }

  inline static float readFloat(unsigned char* stream, int pointer){
      FloatUnion float_u;
      for (int i=sizeof(float)-1; i>=0; i--){
          float_u.c[i] = stream[pointer++];
      }
      return float_u.f;
  }

  inline static double readDouble(unsigned char* stream, int pointer){
      DoubleUnion double_u;
      for (int i=sizeof(double)-1; i>=0; i-- ){
          double_u.c[i] = stream[pointer++];
      }
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
