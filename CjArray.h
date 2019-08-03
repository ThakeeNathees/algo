#pragma once
#include "cjar.h"
#include "SerialWriter.h"
#include "SerialReader.h"

namespace cjar
{
class Array
{
private:
    inline Array(){}
    static const unsigned char CONTAINER_TYPE = ContainerType::ARRAY;
    int                 m_size = sizeof(char) + sizeof(int) + sizeof(short) + sizeof(char) + sizeof(int);
    short               m_name_length;
    const char*         m_name = nullptr;
    unsigned char       m_data_type;
    unsigned int        m_count;
    unsigned char*      m_data;

public:
    inline ~Array(){ delete[] m_data; delete[] m_name; }

    inline static Array* Char(const char* name, char* data, unsigned int count ){
        return Char(name, (unsigned char*)data, count);
    }
    inline static Array* Char(const char* name, unsigned char* data, unsigned int count ){
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::CHAR;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, count);
        return array;
    }
    // for string
    inline static Array* String(const char* name, const char* data){
        int count = getStrlen(data);
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::CHAR;
        array->m_count = count+1;  // for null \0 character
        array->m_size += getTypeSize((Type)array->m_data_type) * array->m_count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes( array->m_data, &pointer, data, count);
        SerialWriter::writeBytes( array->m_data, &pointer, (char)0 );
        return array;
    }

    inline static Array* Short(const char* name, short* data, unsigned int count ){
        return Short(name, (unsigned short*)data, count);
    }
    inline static Array* Short(const char* name, unsigned short* data, unsigned int count ){
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::SHORT;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static Array* Int(const char* name, int* data, unsigned int count ){
        return Int(name, (unsigned int*)data, count);
    }
    inline static Array* Int(const char* name, unsigned int* data, unsigned int count ){
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::INTEGER;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static Array* Long(const char* name, long* data, unsigned int count ){
        return Long(name, (unsigned long*)data, count);
    }
    inline static Array* Long(const char* name, unsigned long* data, unsigned int count ){
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::LONG;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static Array* Bool(const char* name, bool* data, unsigned int count ){
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::BOOLEAN;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static Array* Float(const char* name, float* data, unsigned int count ){
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::FLOAT;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static Array* Double(const char* name, double* data, unsigned int count ){
        Array* array = new Array();
        array->setName(name);
        array->m_data_type = Type::DOUBLE;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }
    
    inline void setName(const char* name){
        if (m_name != nullptr) m_size -= m_name_length;
        m_name_length = getStrlen(name);
        char* _name_p = new char[m_name_length];
        setStr(_name_p, name);
        m_name = _name_p;
        m_size += m_name_length;
        
    }

    inline int getSize(){
        return m_size;
    }
    inline const char* getName(){
        return m_name;
    }
    inline int getCount(){
        return m_count;
    }


    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_data_type);
        SerialWriter::writeBytes(stream, pointer, m_count);
        SerialWriter::writeBytes(stream, pointer, m_data, getTypeSize((Type)m_data_type) * m_count );
    }

    template <typename T>
    T* getValues(){
        T* values = new T[ m_count ];
        int pointer =0;
        for (int i=0; i<m_count; i++){
            switch ((Type)m_data_type){
                case CHAR    : values[i] = SerialReader::readChar(m_data, &pointer);   break;
                case SHORT   : values[i] = SerialReader::readShort(m_data, &pointer);  break;
                case INTEGER : values[i] = SerialReader::readInt(m_data, &pointer);    break;
                case LONG    : values[i] = SerialReader::readLong(m_data, &pointer);   break;
                case BOOLEAN : values[i] = SerialReader::readBool(m_data, &pointer);   break;
                case FLOAT   : values[i] = SerialReader::readFloat(m_data, &pointer);  break;
                case DOUBLE  : values[i] = SerialReader::readDouble(m_data, &pointer); break;
            }
        }
        return values;
    }

    const char* getString(){ // array value is a string
        int len = m_count * sizeof(char);
        int pointer = 0;
        char* _str = new char[ len + 1];
        SerialReader::readString(_str, len, m_data, &pointer);
        return _str;
    }


    inline static Array* Deserialize(unsigned char* stream, int* pointer){
        unsigned char container_type = SerialReader::readChar(stream, pointer);
        assert( container_type == ContainerType::ARRAY );
        Array* array = new Array();
        array->m_size = SerialReader::readInt(stream, pointer);
        array->m_name_length = SerialReader::readShort(stream, pointer);
        char* _name_p = new char[array->m_name_length+1];
        SerialReader::readString(_name_p, array->m_name_length, stream, pointer);
        array->m_name = _name_p;
        array->m_data_type = SerialReader::readChar(stream, pointer);
        array->m_count = SerialReader::readInt(stream, pointer);
        int len = getTypeSize((Type)array->m_data_type) * array->m_count;
        array->m_data = new unsigned char[ len ];
        SerialReader::readBytes(array->m_data, len, stream, pointer);
        return array;
    }

};

}