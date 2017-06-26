package com.ihorkucherenko.inmemorystorage

import android.content.Context
import android.graphics.Color
import android.support.test.InstrumentationRegistry
import android.support.test.runner.AndroidJUnit4

import com.ihorkucherenko.storage.Store

import org.junit.Test
import org.junit.runner.RunWith

import org.junit.Assert.*
import java.util.*

/**
 * Instrumentation test, which will execute on an Android device.

 * @see [Testing documentation](http://d.android.com/tools/testing)
 */
@RunWith(AndroidJUnit4::class)
class ExampleInstrumentedTest {

    val store = Store()

    @Test
    fun storeObject() {
        val calendar = Calendar.getInstance()
        val key = "object"
        store.setObject(key, calendar)
        assertSame(calendar, store.getObject(key))
    }

    @Test
    fun storeFloatEquals() {
        val float = 3f
        val key = "float"
        store.setFloat(key, float)
        assertEquals(float, store.getFloat(key))
    }

    @Test
    fun storeIntegerEquals() {
        val int = 3
        val key = "int"
        store.setInteger(key, int)
        assertEquals(int, store.getInteger(key))
    }

    @Test
    fun storeFloatNotTheSame() {
        val float = 3f
        val key = "float"
        store.setFloat(key, float)
        assertNotSame(float, store.getFloat(key))
    }

    @Test
    fun storeIntegerTheSame() {
        val int = 3
        val key = "int"
        store.setInteger(key, int)
        assertSame(int, store.getInteger(key))
    }

    @Test
    fun storeIntegerNotTheSame() {
        val int = 128
        val key = "int"
        store.setInteger(key, int)
        assertNotSame(int, store.getInteger(key))
    }

    @Test
    fun storeStringNotTheSame() {
        val string = "string"
        val key = "string"
        store.setString(key, string)
        assertNotSame(string, store.getString(key))
    }

    @Test
    fun storeStringEquals() {
        val string = "string"
        val key = "string"
        store.setString(key, string)
        assertEquals(string, store.getString(key))
    }

    @Test
    fun storeBooleanTheSame() {
        val boolean = true
        val key = "boolean"
        store.setBoolean(key, boolean)
        assertSame(boolean, store.getBoolean(key))
    }

    @Test
    fun storeShortNotTheSame() {
        val short: Short = 128
        val key = "short"
        store.setShort(key, short)
        assertNotSame(short, store.getShort(key))
    }

    @Test
    fun storeShortEquals() {
        val short: Short = 128
        val key = "short"
        store.setShort(key, short)
        assertEquals(short, store.getShort(key))
    }

    @Test
    fun storeShortTheSame() {
        val short: Short = 3
        val key = "short"
        store.setShort(key, short)
        assertSame(short, store.getShort(key))
    }

    @Test
    fun storeByteEquals() {
        val byte: Byte = 3
        val key = "byte"
        store.setByte(key, byte)
        assertEquals(byte, store.getByte(key))
    }

    @Test
    fun storeByteTheSame() {
        val byte: Byte = 3
        val key = "byte"
        store.setByte(key, byte)
        assertSame(byte, store.getByte(key))
    }

    @Test
    fun storeDoubleNotTheSame() {
        val double: Double = 8.0
        val key = "double"
        store.setDouble(key, double)
        assertNotSame(double, store.getDouble(key))
    }

    @Test
    fun storeDoubleEquals() {
        val double: Double = 128.0
        val key = "double"
        store.setDouble(key, double)
        assertEquals(double, store.getDouble(key), 0.0)
    }

    @Test
    fun storeLongNotTheSame() {
        val long: Long = 128
        val key = "long"
        store.setLong(key, long)
        assertNotSame(long, store.getLong(key))
    }

    @Test
    fun storeLongEquals() {
        val long: Long = 128
        val key = "long"
        store.setLong(key, long)
        assertEquals(long, store.getLong(key))
    }

    @Test
    fun storeLongTheSame() {
        val long: Long = 3
        val key = "long"
        store.setLong(key, long)
        assertSame(long, store.getLong(key))
    }


}
