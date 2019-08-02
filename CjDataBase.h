#include "CjObject.h"

namespace cjar
{

class CjDataBase
{
private:
    const char* HEADER  = "Cookie-Jar";
    unsigned const short VERSION = 0x0100;
    static const unsigned char CONTAINER_TYPE = ContainerType::DATABASE;
    short                 m_name_length;
    const char*           m_name = nullptr;
    std::vector<CjObject> m_objects;
    int m_size = getStrlen(HEADER) + sizeof(short) + sizeof(char) + sizeof(short) + sizeof(int);

public:
        inline CjDataBase(const char* name){
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

    inline void addObject(CjObject& object){
        m_objects.push_back(object);
        m_size += object.getSize();
    }

    inline void writeBytes(unsigned char* stream, int* pointer){
        SerialWriter::writeBytes(stream, pointer, HEADER, getStrlen(HEADER));
        SerialWriter::writeBytes(stream, pointer, VERSION);
        SerialWriter::writeBytes(stream, pointer, CONTAINER_TYPE);
        SerialWriter::writeBytes(stream, pointer, m_size);
        SerialWriter::writeBytes(stream, pointer, m_name);
        for (CjObject object : m_objects){
            object.writeBytes(stream, pointer);            
        }

    }
};

}