#pragma once

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