#pragma once
#include "CjField.h"
#include "CjArray.h"

namespace cjar
{

class CjObject
{
private:
    static const unsigned char CONTAINER_TYPE = ContainerType::OBJECT;
    short                m_name_length;
    const char*          m_name = nullptr;
    std::vector<CjField> m_fields;
    std::vector<CjArray> m_arrays;
    int m_size = sizeof(char) + sizeof(short) + sizeof(int);

public:
    inline CjObject(const char* name){
        setName(name);
    }

    inline void setName(const char* name){
        if(m_name != nullptr) m_size -= m_name_length;
        m_name = name;
        m_name_length = getStrlen(name);
        m_size += m_name_length;
    }

    inline int getSize(){
        return m_size;
    }

    inline void addField(CjField& field){
        m_fields.push_back(field);
        m_size += field.getSize();
    }
    inline void addArray(CjArray& array){
        m_arrays.push_back(array);
        m_size += array.getSize();
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        for (CjField field : m_fields){
            field.writeBytes(stream, pointer);
        }
        for (CjArray array : m_arrays) {
            array.writeBytes(stream, pointer);
        }
    }


};

}