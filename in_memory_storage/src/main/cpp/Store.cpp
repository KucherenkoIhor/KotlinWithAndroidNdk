//
// Created by Ihor Kucherenko on 6/22/17.
//
#include <jni.h>
#include <string>

#include "Store.h"
#include "StoreUtil.h"

#include <android/log.h>

static Store gStore;

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    __android_log_print(ANDROID_LOG_INFO,  __FUNCTION__, "onLoad");
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    // Get jclass with env->FindClass.
    // Register methods with env->RegisterNatives.
    gStore.mLength = 0;
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ihorkucherenko_storage_Store_getCount(
        JNIEnv* env,
        jobject /* this */) {
    return gStore.mLength;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ihorkucherenko_storage_Store_getString(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_String)) {
        // Converts a C string into a Java String.
        return pEnv->NewStringUTF(entry->mValue.mString);
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ihorkucherenko_storage_Store_getInteger(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Integer)) {
        return entry->mValue.mInteger;
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_ihorkucherenko_storage_Store_getFloat(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Float)) {
        return entry->mValue.mFloat;
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_ihorkucherenko_storage_Store_getBoolean(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Boolean)) {
        return entry->mValue.mBoolean;
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT jshort JNICALL
Java_com_ihorkucherenko_storage_Store_getShort(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Short)) {
        return entry->mValue.mShort;
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_ihorkucherenko_storage_Store_getDouble(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Double)) {
        return entry->mValue.mDouble;
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_ihorkucherenko_storage_Store_getLong(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Long)) {
        return entry->mValue.mLong;
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_com_ihorkucherenko_storage_Store_getByte(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Byte)) {
        return entry->mValue.mByte;
    } else {
        return NULL;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setString(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jstring pString) {
    // Turns the Java string into a temporary C string.
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_String;
        // Copy the temporary C string into its dynamically allocated
        // final location. Then releases the temporary string.
        jsize stringLength = pEnv->GetStringUTFLength(pString);
        entry->mValue.mString = new char[stringLength + 1];
        // Directly copies the Java String into our new C buffer.
        pEnv->GetStringUTFRegion(pString, 0, stringLength, entry->mValue.mString);
        // Append the null character for string termination.
        entry->mValue.mString[stringLength] = '\0';
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setInteger(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jint pInteger) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Integer;
        entry->mValue.mInteger = pInteger;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setObject(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jobject pObject) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Object;
        entry->mValue.mObject = pEnv->NewGlobalRef(pObject);
        if(entry->mValue.mObject != NULL) {
            __android_log_print(ANDROID_LOG_INFO,  __FUNCTION__, "SUCCESS");
        }
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setFloat(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jfloat pFloat) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Float;
        entry->mValue.mFloat = pFloat;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setShort(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jshort pShort) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Short;
        entry->mValue.mShort = pShort;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setLong(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jlong pLong) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Long;
        entry->mValue.mLong = pLong;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setDouble(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jdouble pDouble) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Double;
        entry->mValue.mDouble = pDouble;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setByte(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jbyte pByte) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Byte;
        entry->mValue.mByte = pByte;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ihorkucherenko_storage_Store_setBoolean(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey,
        jboolean pBoolean) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Boolean;
        entry->mValue.mBoolean = pBoolean;
    }
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_ihorkucherenko_storage_Store_getObject(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Object)) {
        return entry->mValue.mObject;
    } else {
        return NULL;
    }
}



extern "C"
JNIEXPORT jboolean JNICALL
Java_com_ihorkucherenko_storage_Store_hasEntry(
        JNIEnv* pEnv,
        jobject pThis,
        jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    return entry != NULL;
}
