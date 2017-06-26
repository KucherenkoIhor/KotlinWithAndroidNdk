//
// Created by Ihor Kucherenko on 6/22/17.
//
#include "StoreUtil.h"
#include "Store.h"
#include <cstdlib>
#include <cstring>
#include <android/log.h>

bool isEntryValid(JNIEnv* pEnv, StoreEntry* pEntry, StoreType pType)
{
    if(pEntry == NULL)
    {
        throwNoKeyException(pEnv);
    }

    return ((pEntry != NULL) && (pEntry->mType == pType));
}

StoreEntry* findEntry(JNIEnv* pEnv, Store* pStore, jstring pKey)
{
    StoreEntry* entry = pStore->mEntries;
    StoreEntry* endEntry = entry + pStore->mLength;
    const char* tmpKey = pEnv->GetStringUTFChars(pKey, NULL);
    while ((entry < endEntry) && (strcmp(entry->mKey, tmpKey) != 0)) {
        ++entry;
    }
    pEnv->ReleaseStringUTFChars(pKey, tmpKey);
    return (entry == endEntry) ? NULL : entry;
}

StoreEntry* allocateEntry(JNIEnv* pEnv, Store* pStore, jstring pKey)
{
    StoreEntry* entry = findEntry(pEnv, pStore, pKey);
    if( entry !=  NULL) {
        releaseEntryValue(pEnv, entry);
    } else {
        entry = pStore->mEntries + pStore->mLength;

        const char* tmpKey = pEnv->GetStringUTFChars(pKey, NULL);
        entry->mKey = new char[strlen(tmpKey) + 1];
        strcpy(entry->mKey, tmpKey);
        pEnv->ReleaseStringUTFChars(pKey, tmpKey);

        ++pStore->mLength;
    }
    return entry;
}

void releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry)
{
    switch (pEntry->mType) {
        case StoreType_String:
            delete pEntry->mValue.mString;
            break;
        case StoreType_Object:
            pEnv->DeleteGlobalRef(pEntry->mValue.mObject);
            break;
    }
}

void throwNoKeyException(JNIEnv* pEnv) {
    jclass clazz = pEnv->FindClass("java/lang/IllegalArgumentException");
    if (clazz != NULL) {
        pEnv->ThrowNew(clazz, "Key does not exist.");
    }
    pEnv->DeleteLocalRef(clazz);
}