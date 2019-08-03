#pragma once

/*
   using big-endian for reading and writing bytes.
   support variant size of permitive types.

   TODO: file error handle!
 */

#include "CjDataBase.h"


namespace cjar
{
void _printBytes(unsigned char data[], int size);
int _writeToFile(unsigned char* buffer, int count, const char* path);
int _readFromFile(unsigned char* buffer, unsigned long len, const char* path);
unsigned long _fileSize(const char* path);
class Jar
{
private:
  DataBase*   m_dbase = nullptr;
  const char* m_name  = "serialdata";
  int m_write_pointer = 0;
  int m_read_pointer  = 0;
  unsigned char* m_buffer = nullptr;
  int m_buffer_size   = 0;
public:
  inline ~Jar(){
    delete m_dbase;
    delete[] m_buffer;
  }
  inline Jar(const char* name){
    m_name = name;
  }
  inline Jar(const char* name, DataBase* dbase){
    m_name  = name;
    m_dbase = dbase;
  }
  inline void setDataBase(DataBase* dbase){
    m_dbase = dbase;
  }
  inline DataBase* getDataBase(){
    return m_dbase;
  }

  inline void convertBinary(){
    assert(m_dbase != nullptr);
    m_buffer = new unsigned char[ m_dbase->getSize() ];
    m_buffer_size = m_dbase->getSize();
    m_dbase->writeBytes(m_buffer, &m_write_pointer);
  }

  inline int writeToFile(const char* path){
    assert(m_buffer != nullptr);
    int error = _writeToFile(m_buffer, m_buffer_size, path);
    if (error) fprintf(stderr, "[error] cant write to file : %s", path);
    return error;
  }
  inline int writeToFile(){
    assert(m_buffer != nullptr);
    char* file_name;
    file_name = strConCat( m_name, ".cjar");
    int error = _writeToFile(m_buffer, m_buffer_size, file_name );
    if (error) fprintf(stderr, "[error] cant write to file : %s", file_name);
    return error;
  }

  inline void print(){
    assert(m_buffer != nullptr);
    _printBytes(m_buffer, m_buffer_size);
  }

  inline void readFromBuffer(unsigned char* buffer){
    m_dbase = DataBase::Deserialize(buffer, &m_read_pointer);
  }
  inline int readFromFile(const char* path){
    unsigned long len = _fileSize(path);
    m_buffer = new unsigned char[len];
    m_buffer_size = len;
    int error = _readFromFile(m_buffer, len, path);
    if (error) {
      fprintf(stderr, "[error] cant write to file : %s", path);
      return -1;
    }
    m_dbase = DataBase::Deserialize(m_buffer, &m_read_pointer);
    return 0;
  }
  
}; // Jar ends
}

namespace cjar
{

inline void _printBytes(unsigned char data[], int size){
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

  int remain = size % 16;
  for (int i=0; i<16-remain; i++) printf("   ");
  for (int i=remain; i>0; i--){
    char c = data[size-i];
    c = ( c>=0x20 && c<=0x7e )?c:'.';
    printf(" %c", c);
  }

  printf("\n");
}


inline int _writeToFile(unsigned char* buffer, int count, const char* path){
   FILE* file_p;
   file_p = fopen(path, "wb");
   if (file_p == NULL) return -1;
   fwrite(buffer, sizeof(char), count, file_p );
   fclose(file_p);
   return 0;
}

inline int _readFromFile(unsigned char* buffer, unsigned long len, const char* path){
  FILE* file_p;
  file_p = fopen(path, "rb");
  if (file_p == NULL) return -1;
  fread(buffer, sizeof(char), len, file_p);
  fclose(file_p);
  return 0;
}

inline unsigned long _fileSize(const char* path){
  FILE* file_p;
  file_p = fopen(path, "rb");
   
  fseek(file_p, 0, SEEK_END);
  unsigned long length = ftell(file_p);  // returns the number of bytes
  fclose(file_p);
  return length;
}

}