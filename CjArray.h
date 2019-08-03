#pragma once
#include "cjar.h"
#include "SerialWriter.h"
#include "SerialReader.h"

namespace cjar
{
class CjArray
{
private:
    inline CjArray(){}
    static const unsigned char CONTAINER_TYPE = ContainerType::ARRAY;
    int                 m_size = sizeof(char) + sizeof(int) + sizeof(short) + sizeof(char) + sizeof(int);
    short               m_name_length;
    const char*         m_name = nullptr;
    unsigned char       m_data_type;
    unsigned int        m_count;
    unsigned char*      m_data;

public:
    inline ~CjArray(){ delete[] m_data; delete[] m_name; }

    inline static CjArray* Char(const char* name, char* data, unsigned int count ){
        return Char(name, (unsigned char*)data, count);
    }
    inline static CjArray* Char(const char* name, unsigned char* data, unsigned int count ){
        CjArray* array = new CjArray();
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
    inline static CjArray* Char(const char* name, const char* data){
        int count = getStrlen(data);
        CjArray* array = new CjArray();
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

    inline static CjArray* Short(const char* name, short* data, unsigned int count ){
        return Short(name, (unsigned short*)data, count);
    }
    inline static CjArray* Short(const char* name, unsigned short* data, unsigned int count ){
        CjArray* array = new CjArray();
        array->setName(name);
        array->m_data_type = Type::SHORT;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static CjArray* Int(const char* name, int* data, unsigned int count ){
        return Int(name, (unsigned int*)data, count);
    }
    inline static CjArray* Int(const char* name, unsigned int* data, unsigned int count ){
        CjArray* array = new CjArray();
        array->setName(name);
        array->m_data_type = Type::INTEGER;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static CjArray* Long(const char* name, long* data, unsigned int count ){
        return Long(name, (unsigned long*)data, count);
    }
    inline static CjArray* Long(const char* name, unsigned long* data, unsigned int count ){
        CjArray* array = new CjArray();
        array->setName(name);
        array->m_data_type = Type::LONG;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static CjArray* Bool(const char* name, bool* data, unsigned int count ){
        CjArray* array = new CjArray();
        array->setName(name);
        array->m_data_type = Type::BOOLEAN;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static CjArray* Float(const char* name, float* data, unsigned int count ){
        CjArray* array = new CjArray();
        array->setName(name);
        array->m_data_type = Type::FLOAT;
        array->m_count = count;
        array->m_size += getTypeSize((Type)array->m_data_type) * count;
        array->m_data = new unsigned char[ getTypeSize((Type)array->m_data_type) * count ];
        int pointer = 0;
        SerialWriter::writeBytes(array->m_data, &pointer, data, array->m_count);
        return array;
    }

    inline static CjArray* Double(const char* name, double* data, unsigned int count ){
        CjArray* array = new CjArray();
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


    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_data_type);
        SerialWriter::writeBytes(stream, pointer, m_count);
        SerialWriter::writeBytes(stream, pointer, m_data, getTypeSize((Type)m_data_type) * m_count );
    }


    inline static CjField* Deserialize(unsigned char* stream, int* pointer){
        /* unsigned char container_type = SerialReader::readChar(stream, pointer);
        assert( container_type == ContainerType::FIELD );
        CjField* field = new CjField();
        field->m_size = SerialReader::readInt(stream, pointer);
        field->m_name_length = SerialReader::readShort(stream, pointer);
        char* _name_p = new char[field->m_name_length+1];
        SerialReader::readString(_name_p, field->m_name_length+1, stream, pointer);
        field->m_name = _name_p;
        field->m_data_type = SerialReader::readChar(stream, pointer);
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int len = getTypeSize((Type)field->m_data_type);
        SerialReader::readBytes(field->m_data, len, stream, pointer);
        for (int i=0; i<len; i++){
            field->m_value.ptr[i] = field->m_data[len-i];
        }
        return field;*/
        return nullptr;

};
}