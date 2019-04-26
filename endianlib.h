#ifndef RSO_ENDIANLIB_H
#define RSO_ENDIANLIB_H

#include <netinet/in.h>

using namespace std;

template <typename T>
T swap_endian(const T& value){
    if(htons(10) == 10){ //if u have bigendian format then it return true, in other way htons(10) return 40960
        return value;
    }else{
        T result;
        char* old_v = (char*) &value;
        char* new_v = (char*) &result;
        for(size_t i=0; i<sizeof(value); i++){
            new_v[i] = old_v[sizeof(value) - i - 1];
        }
        return result;
    }
}

#endif