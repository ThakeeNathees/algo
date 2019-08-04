#pragma once
#include "CjField.h"
#include "CjArray.h"

namespace cjar
{

class Object
{
private:
    static const unsigned char CONTAINER_TYPE = ContainerType::OBJECT;
    short                 m_name_length;
    const char*           m_name = nullptr;
    unsigned int          m_field_count = 0;
    std::vector<Field*>   m_fields;
    unsigned int          m_array_count = 0;
    std::vector<Array*>   m_arrays;
    unsigned int          m_object_count;
    std::vector<Object*>  m_objects;
    int m_size = sizeof(char) + sizeof(short) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int);
    
    inline Object(){}
    inline Object(const char* name){
        setName(name);
    }

public:
    inline static Object* create(const char* name){
        return new Object(name);
    }

    inline ~Object(){
        for (Field* field_p: m_fields)
            delete field_p;
        for (Array* array_p: m_arrays)
            delete array_p;
        delete[] m_name;
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
    inline std::vector<Field*>& getFields(){
        return m_fields;
    }
    inline std::vector<Array*>& getArrays(){
        return m_arrays;
    }
    inline std::vector<Object*>& getObject(){
        return m_objects;
    }

    inline Object* addField(Field* field){
        m_fields.push_back(field);
        m_field_count++;
        m_size += field->getSize();
        return this;
    }
    inline Object* addArray(Array* array){
        m_arrays.push_back(array);
        m_array_count++;
        m_size += array->getSize();
        return this;
    }
    inline Object* addObject(Object* object){
        m_objects.push_back(object);
        m_object_count++;
        m_size += object->getSize();
        return this;
    }

    inline Field* findField(const char* name){
        for (auto field : m_fields){
            if( isStrEquals(field->getName(), name) ) { return field; }
        }
        return nullptr;
    }
    inline Array* findArray(const char* name){
        for (auto array : m_arrays){
            if( isStrEquals(array->getName(), name) ){ return array; }
        }
        return nullptr;
    }
    inline Object* findObject(const char* name){
        for (auto object : m_objects){
            if( isStrEquals(object->getName(), name) ){ return object; }
        }
        return nullptr;
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_field_count);
        for (Field* field : m_fields){
            field->writeBytes(stream, pointer);
        }
        SerialWriter::writeBytes(stream, pointer, m_array_count);
        for (Array* array : m_arrays) {
            array->writeBytes(stream, pointer);
        }
        SerialWriter::writeBytes(stream, pointer, m_object_count);
        for (Object* object : m_objects) {
            object->writeBytes(stream, pointer);
        }
    }

    inline static Object* Deserialize(unsigned char* stream, int* pointer){
        unsigned char container_type = SerialReader::readChar(stream, pointer);
        assert( container_type == ContainerType::OBJECT );
        Object* object = new Object();
        object->m_size = SerialReader::readInt(stream, pointer);
        object->m_name_length = SerialReader::readShort(stream, pointer);
        char* _name_p = new char[object->m_name_length+1];
        SerialReader::readString(_name_p, object->m_name_length, stream, pointer);
        object->m_name = _name_p;
        object->m_field_count = SerialReader::readInt(stream, pointer);
        for (int i=0; i<object->m_field_count; i++){
            Field* field = Field::Deserialize(stream, pointer);
            object->m_fields.push_back(field);
        }
        object->m_array_count = SerialReader::readInt(stream, pointer);
        for (int i=0; i<object->m_array_count; i++){
            Array* array = Array::Deserialize(stream, pointer);
            object->m_arrays.push_back(array);
        }
        object->m_object_count = SerialReader::readInt(stream, pointer);
        for (int i=0; i<object->m_object_count; i++){
            Object* obj = Object::Deserialize(stream, pointer);
            object->m_objects.push_back(obj);
        }
        return object;
    }

};

}