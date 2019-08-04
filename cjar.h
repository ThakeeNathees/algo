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

    char* strConCat(const char* str1, const char* str2){
        int len1 = getStrlen(str1);
        int len2 = getStrlen(str2);
        char* _ret = new char[ len1 + len2 + 1 ];
        for (int i=0; i < len1; i++  ){
            _ret[i] = str1[i];
        }
        for (int i=len1, j=0; i < (len1+len2); i++, j++ ){
            _ret[i] = str2[j];
        }
        _ret[len1+len2] = 0;
        return _ret;
    }

    bool isStrEquals(const char* str1, const char* str2){
        int i=0;
        while( str1[i] ){
            if( !str2[i] ) return false;
            if( str1[i] != str2[i++] ) return false;
        }
        return ( str2[i] == 0 );
    }

}