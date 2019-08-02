#pragma once
#include "cjar.h"
#include "SerialWriter.h"

namespace cjar
{

class Field
{
private:
    inline Field(){};
public:
    inline ~Field(){ delete[] m_data; }
    
    inline static Field* Char(const char* name, unsigned char value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::CHAR;
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static Field* Short(const char* name, unsigned short value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::SHORT;
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static Field* Int(const char* name, unsigned int value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::INTEGER;
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static Field* Long(const char* name, unsigned long value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::LONG;
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static Field* Bool(const char* name, bool value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::BOOLEAN;
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static Field* Float(const char* name, float value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::FLOAT;
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static Field* Double(const char* name, double value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::DOUBLE;
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }

public:
    static const unsigned char CONTAINER_TYPE = ContainerType::FIELD;
    short               m_name_length;
    const char*         m_name;
    unsigned char       m_data_type;
    unsigned char*      m_data;

    inline void setName(const char* name){
        m_name = name;
        m_name_length = 0; while( *(name++) ) m_name_length++ ;
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        //SerialWriter::writeBytes(stream, pointer, m_name_length);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_data_type);
        SerialWriter::writeBytes(stream, pointer, m_data, getTypeSize((Type)m_data_type));
    }

    inline int getSize()
    {
        return sizeof(char) + sizeof(short) + m_name_length + sizeof(char) + getTypeSize((Type)m_data_type) ;
    }
    


};

}