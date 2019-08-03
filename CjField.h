#pragma once
#include "cjar.h"
#include "SerialWriter.h"
#include "SerialReader.h"

namespace cjar
{

class CjField
{
public:
    union Value{
        char* ptr;
        unsigned char   c;
        unsigned short  s;
        unsigned int    i;
        unsigned long   l;
                 bool   b;
                 float  f;
                 double d;
    };
private:
    static const unsigned char CONTAINER_TYPE = ContainerType::FIELD;
    int                 m_size = sizeof(char) + sizeof(int) + sizeof(short) + sizeof(char);
    short               m_name_length;
    const char*         m_name = nullptr;
    unsigned char       m_data_type;
    unsigned char*      m_data;
    Value               m_value;
    inline CjField(){};
public:
    inline auto getdata(){ return m_data; }
    inline ~CjField(){ delete[] m_data; delete[] m_name;}
    

    inline static CjField* Char(const char* name, unsigned char value){
        CjField* field = new CjField();
        field->setName(name);
        field->m_data_type = Type::CHAR;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        field->m_value.c = value;
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
        field->m_value.s = value;
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
        field->m_value.i = value;
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
        field->m_value.l = value;
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
        field->m_value.b = value;
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
        field->m_value.f = value;
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
        field->m_value.d = value;
        return field;
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
    inline Value getValue(){
        return m_value;
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_data_type);
        SerialWriter::writeBytes(stream, pointer, m_data, getTypeSize((Type)m_data_type));
    }

    inline static CjField* Deserialize(unsigned char* stream, int* pointer){
        unsigned char container_type = SerialReader::readChar(stream, pointer);
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
        return field;
    }

    
 


};

}