using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class ShortCircuit
{
    // Is Loud returns true when the strig contains a '!' and false if it does not.
    static bool IsLoud(string name)
    {
        bool isLoud = name.Contains("!");

        if (isLoud)
            Console.WriteLine(name + " is Loud!");
        else
            Console.WriteLine(name + " is quiet...");

        return isLoud;
    }


    static void Main(string[] args)
    {
        bool result;

        // Brian and Bobby! do not get checked because the result cannot become false.
        //                           [--Not run---------------------------]
        result = IsLoud("Mandalor!") || IsLoud("Brian") || IsLoud("Bobby!");
        Console.WriteLine("Result: " + result + "\n\n");

        // Papa! and Mam! do not get checked because the result cannot become false.
        //                                                            [--Not run--------------------------]
        result = IsLoud("Pam") || IsLoud("Bill") || IsLoud("Trevor!") || IsLoud("Papa!") || IsLoud("Mama!");
        Console.WriteLine("Result: " + result + "\n\n");

        // Cameron! is not checked because the result cannot become true
        //                          [--Not run----------]
        result = IsLoud("Samantha") && IsLoud("Cameron!");
        Console.WriteLine("Result: " + result + "\n\n");

        // Chris! and Peter! do not get checked because the result cannot become true.
        //                                        [--Not run---------------------------]
        result = IsLoud("Kate!") && IsLoud("Kim") && IsLoud("Chris!") && IsLoud("Peter!");
        Console.WriteLine("Result: " + result + "\n\n");

        // Kim and Mat do not get checked because the result cannot become false.
        //                                                                [--Not run------------------------]
        result = ( IsLoud("Pete!") && IsLoud("Bob") ) || ( IsLoud("Sam!") || IsLoud("Kim") ) || IsLoud("Mat");
        
        // Wait for user input before closing the program
        Console.Read();
    }
}

