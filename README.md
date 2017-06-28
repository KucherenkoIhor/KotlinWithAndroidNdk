# Android NDK. Interaction Kotlin with C/C++
![](https://cdn-images-1.medium.com/max/1600/1*3x1QE3VzG5MWi5Qk6C-HLQ.gif)


## Read article [here](https://proandroiddev.com/android-ndk-interraction-kotlin-with-c-c-5e19e35bac74)
It’s a simple in-memory storage that can be used to pass some value from one Activity to another. IBinder works in the similar way: just created the Global Reference to Java’s object.

![](https://cdn-images-1.medium.com/max/1600/1*4T2zOyp6wTcM6exNCtwfsA.gif)

Please notice, that jobject is just pointer to Java’s object but not the direct reference. Java objects do not have a  xed loca on in memory on the opposite to C++ objects. They may be moved during their life me. Regardless, it would be a bad idea to mess with a Java object representation in the memory. The same is true for instances of IBinder.

```Kotlin
class Store {

    external fun getCount(): Int

    @Throws(IllegalArgumentException::class)
    external fun getString(pKey: String): String

    @Throws(IllegalArgumentException::class)
    external fun getInteger(pKey: String): Int

    @Throws(IllegalArgumentException::class)
    external fun getFloat(pKey: String): Float

    @Throws(IllegalArgumentException::class)
    external fun getBoolean(pKey: String): Boolean

    @Throws(IllegalArgumentException::class)
    external fun getShort(pKey: String): Short

    @Throws(IllegalArgumentException::class)
    external fun getObject(pKey: String): Any

    @Throws(IllegalArgumentException::class)
    external fun getLong(pKey: String): Long

    @Throws(IllegalArgumentException::class)
    external fun getDouble(pKey: String): Double

    @Throws(IllegalArgumentException::class)
    external fun getByte(pKey: String): Byte

    external fun setString(pKey: String, pString: String)

    external fun setInteger(pKey: String, pInt: Int)

    external fun setFloat(pKey: String, pFloat: Float)

    external fun setBoolean(pKey: String, pBoolean: Boolean)

    external fun setShort(pKey: String, pShort: Short)

    external fun setObject(pKey: String, pObject: Any)

    external fun setByte(pKey: String, pByte: Byte)

    external fun setLong(pKey: String, pLong: Long)

    external fun setDouble(pKey: String, pDouble: Double)

    external fun hasEntry(pKey: String): Boolean

    companion object {
        init {
            System.loadLibrary("Store")
        }
    }
}
```

All this methods have appropriate native functions in [Store.cpp](https://github.com/KucherenkoIhor/KotlinWithAndroidNdk/blob/master/in_memory_storage/src/main/cpp/Store.cpp) file.

```C
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
```
## Exception
As you have probably noticed, native methods can throw Java’s Exceptions. If you try to get some non-existent value from Store, it will throw an appropriate Exception. StoreUtil.cpp file contains throwNoKeyException function for this:

```C
void throwNoKeyException(JNIEnv* pEnv) {
    jclass clazz = pEnv->FindClass("java/lang/IllegalArgumentException");
    if (clazz != NULL) {
        pEnv->ThrowNew(clazz, "Key does not exist.");
    }
    pEnv->DeleteLocalRef(clazz);
}
```

## Logging
[CMakeLists.txt](https://github.com/KucherenkoIhor/KotlinWithAndroidNdk/blob/master/in_memory_storage/CMakeLists.txt) file also contains calling of ```target_link_libraries``` to add the library for logging to the project. We can include this library ```#include <android/log.h>``` to *.cpp file and to log some event ```__android_log_print(ANDROID_LOG_INFO, __FUNCTION__, “onLoad”);```.

## Conclusions

Kotlin can call C/C++ code with any type of data or object.
We found out a lot of theoretical material and based on it created the sample project. We converted Java Strings inside native code, passed Kotlin objects to native code, called functions and threw Exceptions of Java.
Kotlin is a new official tool for Android Development and this article demonstrates that this programming language works with Android NDK without any problems.
