#ifndef GLES_BASIC_TYPE_H
#define GLES_BASIC_TYPE_H

#include <cstdio>

#define YUN_LOG(format, ...) printf("[YunMap]%s %d:"#format"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define element_of(A) (sizeof(A) / sizeof(A[0]))

#include <time.h>
#include <sys/time.h>


inline timeval getTime() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
}



#endif