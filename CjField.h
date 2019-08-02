#pragma once
#include "cjar.h"
#include "SerialWriter.h"

namespace cjar
{

class CjField
{
private:
    static const unsigned char CONTAINER_TYPE = ContainerType::FIELD;
    int                 m_size = sizeof(char) + sizeof(int) + sizeof(short) + sizeof(char);
    short               m_name_length;
    const char*         m_name = nullptr;
    unsigned char       m_data_type;
    unsigned char*      m_data;
    inline CjField(){};
public:
    inline auto getdata(){ return m_data; }
    inline ~CjField(){ delete[] m_data; }
    
    inline static CjField* Char(const char* name, unsigned char value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::CHAR;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static CjField* Short(const char* name, unsigned short value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::SHORT;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static CjField* Int(const char* name, unsigned int value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::INTEGER;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static CjField* Long(const char* name, unsigned long value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::LONG;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static CjField* Bool(const char* name, bool value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::BOOLEAN;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static CjField* Float(const char* name, float value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::FLOAT;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }
    inline static CjField* Double(const char* name, double value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::DOUBLE;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        return field;
    }

    inline void setName(const char* name){
        if (m_name != nullptr) m_size -= m_name_length;
        m_name = name;
        m_name_length = getStrlen(name);
        m_size += m_name_length;
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_data_type);
        SerialWriter::writeBytes(stream, pointer, m_data, getTypeSize((Type)m_data_type));
    }

    inline int getSize()
    {
        return m_size;
    }
    


};

}