using System;

class BitwiseConditionals
{
    static void Main(string[] args)
    {
        byte flags0 = 0; // 00000000
        byte flags1 = 1; // 00000001
        byte flags2 = 2; // 00000010
        byte flags3 = 3; // 00000011

        bool result;

        // ----------------------------------------
        // bit-wise AND
        // ----------------------------------------
        //               e0   
        //             |0|1|  
        // 0&0=0      -+-+-+  
        // 0&1=0      0|0|1|  
        // 1&0=0    e1-+-+-+  
        // 1&1=1      1|1|1|  
        //            -+-+-+   

        // 00000000 & 00000001 == 00000000
        result = (flags0 & flags1) == 0;
        Console.WriteLine("(00000000 & 00000001) == 00000000\nResults: " + result);

        // 00000001 & 00000001 == 00000001
        result = (flags1 & flags1) == 1;
        Console.WriteLine("(00000001 & 00000001) == 00000001\nResults: " + result);

        // 00000001 & 00000010 == 00000001
        result = (flags1 & flags2) == 0;
        Console.WriteLine("(00000001 & 00000010) == 00000000\nResults: " + result);

        // 00000011 & 00000011 == 00000011
        result = (flags3 & flags3) == 3;
        Console.WriteLine("(00000011 & 00000011) == 00000011\nResults: " + result);


        Console.WriteLine();
        // ----------------------------------------
        // bit-wise OR
        // ----------------------------------------
        //              e0 
        //            |0|1|
        // 0|0=0     -+-+-+
        // 0|1=1     0|0|1|
        // 1|0=1   e1-+-+-+
        // 1|1=1     1|1|1|
        //           -+-+-+ 

        // 00000000 | 00000001 == 00000001
        result = (flags0 | flags1) == 1;
        Console.WriteLine("(00000000 | 00000001) == 00000001\nResults: " + result);

        // 00000001 | 00000001 == 00000001
        result = (flags1 | flags1) == 1;
        Console.WriteLine("(00000001 | 00000001) == 00000001\nResults: " + result);

        // 00000001 & 00000010 == 00000010
        result = (flags1 | flags2) == 3;
        Console.WriteLine("(00000001 | 00000010) == 00000011\nResults: " + result);

        // 00000011 & 00000011 == 00000011
        result = (flags3 | flags3) == 3;
        Console.WriteLine("(00000011 | 00000011) == 00000011\nResults: " + result);


        // Wait for input before closing the program
        Console.ReadLine();
    }
}
