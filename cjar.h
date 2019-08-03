#pragma once
#include <stdio.h>
#include <assert.h>
#include <vector>

/* TODO: array copying 2 times 
    1. when m_data initialize by copying
    2. when writeByte() called
    may be m_data should be pointing to data[] -> need to deal with memory leak and distruction of data[]

    memory management;
    CjDataBase free all other fields when it deleted
    don't manually delete any CjArray, CjField, or CjObject


  NOTE:
    strings are just CjArray of char but the last character is 0;
*/

namespace cjar
{
    enum ContainerType
    {
        UNKNOWN  = 0, 
        FIELD    = 1,
        ARRAY    = 2, 
        OBJECT   = 3,
        DATABASE = 4,
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

    int getStrlen(const char* str){
        int result = 0;
        while(str[++result]);
        return result;
    }

    void setStr(char* dest, const char* src){
        int pointer =0;
        while(*src){
            dest[pointer++] = *src++;
        }
        dest[pointer] = 0;
    }

}