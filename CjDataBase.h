#include "CjObject.h"

namespace cjar
{

class DataBase
{
public:
    const char* HEADER  = "Cookie-Jar"; // can't make static & inline with c++11
    static unsigned const short VERSION = 0x0100;
private:
    static const unsigned char CONTAINER_TYPE = ContainerType::DATABASE;
    short                 m_name_length;
    const char*           m_name = nullptr;
    int m_object_count = 0;
    std::vector<Object*> m_objects;
    int m_size = (getStrlen(HEADER)+sizeof(short)) + sizeof(short) + sizeof(char) +
                  sizeof(short) + sizeof(int) + sizeof(int);
    inline DataBase(){}
    inline DataBase(const char* name){
        setName(name);
    }
    
public:
    inline ~DataBase(){
        for (Object* object_p : m_objects){
            delete object_p;
        }
        delete[] m_name;
    }
    inline static DataBase* create(const char* name){
        return new DataBase(name);
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
    inline std::vector<Object*>& getObjects(){
        return m_objects;
    }

    inline DataBase* addObject(Object* object){
        m_objects.push_back(object);
        m_object_count++;
        m_size += object->getSize();
        return this;
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, HEADER);
        SerialWriter::writeBytes(stream, pointer, VERSION);
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        SerialWriter::writeBytes(stream, pointer, m_object_count);
        for (Object* object : m_objects){
            object->writeBytes(stream, pointer);
        }
    }

    inline static DataBase* Deserialize(unsigned char* stream, int* pointer){
        
        unsigned short _header_length = SerialReader::readShort(stream, pointer);
        (*pointer) += _header_length;
        unsigned short version = SerialReader::readShort(stream, pointer);
        assert(version==VERSION);
        unsigned char container_type = SerialReader::readChar(stream, pointer);
        assert( container_type == ContainerType::DATABASE );
        DataBase* dbase = new DataBase();

        dbase->m_size = SerialReader::readInt(stream, pointer);
        dbase->m_name_length = SerialReader::readShort(stream, pointer);
        char* _name_p = new char[dbase->m_name_length+1];
        SerialReader::readString(_name_p, dbase->m_name_length, stream, pointer);
        dbase->m_name = _name_p;
        dbase->m_object_count = SerialReader::readInt(stream, pointer);
        for (int i=0; i<dbase->m_object_count; i++){
            Object* object = Object::Deserialize(stream, pointer);
            dbase->m_objects.push_back(object);
        }
        return dbase;
    }
};

}