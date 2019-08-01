
// using big-endian for writing bytes

class SerialWriter
{
public:
           const char* HEADER  = "Cookie-Jar";
  unsigned const short VERSION = 0x0100;

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
      writeBytes(stream, pointer, value);
  }
  inline static void writeBytes(unsigned char* stream, int* pointer, unsigned int value){
      stream[(*pointer)++] = (unsigned char) (value >> 24) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >> 16) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >>  8) & 0x00ff;
      stream[(*pointer)++] = (unsigned char) (value >>  0) & 0x00ff;
  }



};