#pragma once
#include "cjar.h"
#include "SerialWriter.h"
#include "SerialReader.h"

namespace cjar
{

class Field
{
public:
    union Value{
        char ptr[0];
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
    inline Field(){};
public:
    inline auto getdata(){ return m_data; }
    inline ~Field(){ delete[] m_data; delete[] m_name;}
    

    inline static Field* Char(const char* name, unsigned char value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::CHAR;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        field->m_value.c = value;
        return field;
    }
    inline static Field* Short(const char* name, unsigned short value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::SHORT;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        field->m_value.s = value;
        return field;
    }
    inline static Field* Int(const char* name, unsigned int value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::INTEGER;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        field->m_value.i = value;
        return field;
    }
    inline static Field* Long(const char* name, unsigned long value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::LONG;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[getTypeSize( (Type)field->m_data_type )];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        field->m_value.l = value;
        return field;
    }
    inline static Field* Bool(const char* name, bool value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::BOOLEAN;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        field->m_value.b = value;
        return field;
    }
    inline static Field* Float(const char* name, float value){
        Field* field = new Field();
        field->setName(name);
        field->m_data_type = Type::FLOAT;
        field->m_size += getTypeSize( (Type)field->m_data_type );
        field->m_data = new unsigned char[ getTypeSize( (Type)field->m_data_type ) ];
        int pointer = 0;
        SerialWriter::writeBytes(field->m_data, &pointer, value);
        field->m_value.f = value;
        return field;
    }
    inline static Field* Double(const char* name, double value){
        Field* field = new Field();
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
    inline const char* getName(){
        return m_name;
    }
    template <typename T>
    inline T getValue(){
        switch ((Type)m_data_type){
            case CHAR    : return m_value.c;
            case SHORT   : return m_value.s;
            case INTEGER : return m_value.i;
            case LONG    : return m_value.l;
            case BOOLEAN : return m_value.b;
            case FLOAT   : return m_value.f;
            case DOUBLE  : return m_value.d;
            default      : return 0;
        }
    }
    inline Type getType(){
        return (Type)m_data_type;
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_data_type);
        SerialWriter::writeBytes(stream, pointer, m_data, getTypeSize((Type)m_data_type));
    }

    inline static Field* Deserialize(unsigned char* stream, int* pointer){
        unsigned char container_type = SerialReader::readChar(stream, pointer);
        assert( container_type == ContainerType::FIELD );
        Field* field = new Field();
        field->m_size = SerialReader::readInt(stream, pointer);
        field->m_name_length = SerialReader::readShort(stream, pointer);
        char* _name_p = new char[field->m_name_length+1];
        SerialReader::readString(_name_p, field->m_name_length, stream, pointer);
        field->m_name = _name_p;
        field->m_data_type = SerialReader::readChar(stream, pointer);
        int len = getTypeSize((Type)field->m_data_type);
        field->m_data = new unsigned char[ len ];
        SerialReader::readBytes(field->m_data, len, stream, pointer);

        for (int i=0; i<len; i++){
            field->m_value.ptr[i] = field->m_data[len-1 -i];
        }
        return field;
    }    
 


};

}