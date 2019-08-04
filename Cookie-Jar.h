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
void _printString(DataBase* dbase);
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

  inline void convertToBinary(){
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

  // TODO: create toString() method
  inline void printBytes(){
    assert(m_buffer != nullptr);
    _printBytes(m_buffer, m_buffer_size);
  }
  inline void printString(){
    assert(m_buffer != nullptr);
    _printString(m_dbase);
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

inline void _printString(DataBase* dbase){
  for (int i=0; i<80; i++) printf("=");printf("\n");
  printf("HEADER   : %s VERSION : %04x\nDataBase : %s\n", dbase->HEADER, dbase->VERSION, dbase->getName() );
  for (int i=0; i<80; i++) printf("=");printf("\n\n");

  for (auto o : dbase->getObjects()){
    printf("%s:\n", o->getName());
    for (auto f: o->getFields()){
      switch(f->getType()){
        case CHAR    : printf("\t%-15s = %c\n",f->getName(), f->getValue<char>() );   break;
        case SHORT   : printf("\t%-15s = %u\n",f->getName(), f->getValue<short>() );  break;
        case INTEGER : printf("\t%-15s = %u\n",f->getName(), f->getValue<int>() );    break;
        case LONG    : printf("\t%-15s = %lu\n",f->getName(), f->getValue<long>() );   break;
        case BOOLEAN : printf("\t%-15s = %s\n",f->getName(), (f->getValue<bool>())?"true":"false" );   break;
        case FLOAT   : printf("\t%-15s = %f\n",f->getName(), f->getValue<float>() );  break;
        case DOUBLE  : printf("\t%-15s = %f\n",f->getName(), f->getValue<double>() ); break;
      }
    }
    for (auto a : o->getArrays()){
      if (a->canBeString()) printf("\t%-15s = %s\n", a->getName(), a->getString() );
      else{
        printf("\t%-15s = { ", a->getName() );
        switch (a->getType()){
          case CHAR    :
          {
              char* arr = a->getValues<char>();
              for (int i=0; i<a->getCount(); i++){ printf("%u, %s",arr[i], ((i+1)%16)?"":"\n\t\t\t") ; } 
              delete[] arr;
              break;
          }
          case SHORT   :
          {
              short* arr = a->getValues<short>();
              for (int i=0; i<a->getCount(); i++){ printf("%u, %s",arr[i], ((i+1)%16)?"":"\n\t\t\t" ); } 
              delete[] arr;
              break;
          }
          case INTEGER :
          {
              int* arr = a->getValues<int>();
              for (int i=0; i<a->getCount(); i++){ printf("%u, %s",arr[i], ((i+1)%16)?"":"\n\t\t\t" ); } 
              delete[] arr;
              break;
          }
          case LONG    :
          {
              long* arr = a->getValues<long>();
              for (int i=0; i<a->getCount(); i++){ printf("%lu, %s",arr[i], ((i+1)%16)?"":"\n\t\t\t" ); } 
              delete[] arr;
              break;
          }
          case BOOLEAN :
          {
              bool* arr = a->getValues<bool>();
              for (int i=0; i<a->getCount(); i++){ printf("%s, %s",arr[i]?"true":"false", ((i+1)%16)?"":"\n\t\t\t" ); } 
              delete[] arr;
              break;
          }
          case FLOAT   :
          {
              float* arr = a->getValues<float>();
              for (int i=0; i<a->getCount(); i++){ printf("%f, %s",arr[i], ((i+1)%16)?"":"\n\t\t\t" ); } 
              delete[] arr;
              break;
          }
          case DOUBLE  :
          {
              double* arr = a->getValues<double>();
              for (int i=0; i<a->getCount(); i++){ printf("%f, %s",arr[i], ((i+1)%16)?"":"\n\t\t\t" ); } 
              delete[] arr;
              break;
          }
        } printf("}\n");
      }
    } 
    for (auto _o :o->getObject() ){
        printf("\t%-15s : %s\n","[object]",_o->getName());
    }
    printf("\n");
  }

  for (int i=0; i<80; i++) printf("=");printf("\n");

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