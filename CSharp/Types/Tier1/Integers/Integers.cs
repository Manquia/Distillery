using System;

class Integers
{
    static void Main(string[] args)
    {
        // ------------------------------------
        // 8 bit integer types
        // ------------------------------------

        // "character" range: 0 to 255
        char myCharMinValue = (char)0;
        char myCharMaxValue = (char)255;
        // "byte" range: 0 to 255
        byte myByteMinValue = 0;
        byte myByteMaxValue = 255;
        // "signed byte" range: -128 to 127
        sbyte mySbyteMinValue = -128;
        sbyte mySbyteMaxValue =  127;

        // ------------------------------------
        // 16 bit integer types
        // ------------------------------------

        // "short" range: -32,768 to 32,767
        short myShortMinValue = -32768;
        short myShortMaxValue =  32767;
        // "unsigned short" range: 	0 to 65,535
        ushort myUshortMinValue = 0;
        ushort myUshortMaxValue = 65535;

        // ------------------------------------
        // 32 bit integer types
        // ------------------------------------

        // "integer" range: -2,147,483,648 to 2,147,483,647
        int myIntMinValue = -2147483648;
        int myIntMaxValue =  2147483647;
        // "unsigned integer" range: 0 to 4,294,967,295
        uint myUintMinValue = 0;
        uint myUintMaxValue = 4294967295;

        // ------------------------------------
        // 64 bit integer types
        // ------------------------------------

        // "long" range: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
        long myLongMinValue = -9223372036854775808;
        long myLongMaxValue =  9223372036854775807;
        // "unsigned long" range: 0 to 18,446,744,073,709,551,615
        ulong myUlongMinValue = 0;
        ulong myUlongMaxValue = 18446744073709551615;

        // wait for user-input before closing the program
        Console.Read();
    }
}
