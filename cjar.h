#pragma once
#include <stdio.h>
#include <vector>

/* TODO: array copying 2 times 
     1. when m_data initialize by copying
     2. when writeByte() called
     may be m_data should be pointing to data[] -> need to deal with memory leak and distruction of data[]
*/

namespace cjar
{
    enum ContainerType
    {
        UNKNOWN = 0, 
        FIELD, 
        ARRAY, 
        OBJECT,
    };

    enum Type
    {
        //UNKNOWN = 0,
        CHAR    = 1,
        BOOLEAN = 2,
        SHORT   = 3,
        INTEGER = 4,
        LONG    = 5,
        FLOAT   = 6,
        DOUBLE  = 7,
    };

    int getTypeSize(Type type){
        switch(type){
            case CHAR    : return sizeof(char);
            case BOOLEAN : return sizeof(bool);
            case SHORT   : return sizeof(short);
            case INTEGER : return sizeof(int);
            case LONG    : return sizeof(long);
            case FLOAT   : return sizeof(float);
            case DOUBLE  : return sizeof(double);
            case UNKNOWN :
            default      : return 0;
        }
    }

}