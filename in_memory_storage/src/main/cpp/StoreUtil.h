//
// Created by Ihor Kucherenko on 6/22/17.
//

#ifndef INMEMORYSTORAGE_STOREUTIL_H
#define INMEMORYSTORAGE_STOREUTIL_H

#include <jni.h>
#include "Store.h"

bool isEntryValid(JNIEnv* pEnv, StoreEntry* pEntry, StoreType pType);

StoreEntry* allocateEntry(JNIEnv* pEnv, Store* pStore, jstring pKey);

StoreEntry* findEntry(JNIEnv* pEnv, Store* pStore, jstring pKey);

void releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry);

void throwNoKeyException(JNIEnv* pEnv);

#endif //INMEMORYSTORAGE_STOREUTIL_H
