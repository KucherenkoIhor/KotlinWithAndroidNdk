//
// Created by Ihor Kucherenko on 6/22/17.
//

#ifndef INMEMORYSTORAGE_STORE_H
#define INMEMORYSTORAGE_STORE_H

#include <cstdint>
#include "jni.h"

#define STORE_MAX_CAPACITY 16

typedef enum {
    StoreType_Float,
    StoreType_String,
    StoreType_Integer,
    StoreType_Object,
    StoreType_Boolean,
    StoreType_Short,
    StoreType_Long,
    StoreType_Double,
    StoreType_Byte,
} StoreType;

typedef union {
    float mFloat;
    int32_t mInteger;
    char* mString;
    jobject mObject;
    jboolean mBoolean;
    jshort mShort;
    jlong mLong;
    jdouble mDouble;
    jbyte mByte;
} StoreValue;

typedef struct {
    char* mKey;
    StoreType mType;
    StoreValue mValue;
} StoreEntry;

typedef struct {
    StoreEntry mEntries[STORE_MAX_CAPACITY];
    int32_t mLength;
} Store;

#endif //INMEMORYSTORAGE_STORE_H
