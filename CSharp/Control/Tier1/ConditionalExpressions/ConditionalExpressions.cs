using System;


class Program
{
    static void Main(string[] args)
    {
        // boolean expressions
        if (true == true) { }   // true
        if (false == true) { }  // false
        if (true != true) { }   // false
        if (false != true) { }  // true

        // interger comparisions
        if (1 == 1) { }         // true
        if (1 == 0) { }         // false
        if (-1 != -1) { }       // false
        if (-10 != 99) { }      // true

        if (0 > 0) { }          // false
        if (0 >= 0) { }         // true
        if (-1 > 0) { }         // false
        if (0 < 10) { }         // true


        // float comparisons
        if (10.0f == 10.0f) { }      // true
        if (1.4f + 0.3f != 1.7f) { } // false: float operations have rounding errors and may have hardware dependent behavior.
        
        // double compariosons
        if (10.0 == 10.0) { }       // true
        if (4.0 < 10.0) { }         // true
    }
}
