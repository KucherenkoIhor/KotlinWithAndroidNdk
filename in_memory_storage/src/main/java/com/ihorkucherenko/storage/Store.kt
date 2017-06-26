package com.ihorkucherenko.storage

/**
 * Created by ihor_kucherenko on 6/22/17.
 * https://github.com/KucherenkoIhor
 */

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
