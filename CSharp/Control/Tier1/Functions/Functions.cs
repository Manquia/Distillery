using System;


// Modifier legend:
// public - May be viewed from outside namespaces/scopes
// private - may be viewed from only the current namespace/scope
// protected - may be viewed from only the current namespace/scope AND any object which inheret the object.

// static - Makes a variable or function "global" in that it does not need a referece to access it.

// In C# all functions reside with a class or struct object. In turn the class or object may also be inside a namespace.
namespace CrazyPoprocks
{
    // MyClass 123 is inside the CrazyPoprocks namespace
    // every class and struct is private by default unless we specify otherwise.
    public class MyClass123
    {
        // Static functions may be called without an instance of the object
        // Every function is private by default unless we specify otherwise.
        public static void PrintMyClass()
        {
            Console.WriteLine("MyClass123");
        }
    }
}

class BongoDrums
{
    // Member functions take an implicit "this" reference which grants access to the variables that the object encapsulate.
    public void PrintBongoDrums()
    {
        // both of these statements are the same thing
        Console.WriteLine("Print BongoDrums" + classValue + " by implicit this reference");
        Console.WriteLine("Print BongoDrums" + this.classValue + " by explicity this reference");
    }

    // A member function is simular to calling a static function with a hidden "this" reference input parameter
    public static void PrintBongoDrumsExplicit(BongoDrums outThisReference)
    {
        Console.WriteLine("Print BongoDrums" + outThisReference.classValue + " by outThisReference");
    }

    // example variable integer we access by the "this" reference
    int classValue = 456;
}

class Functions
{
    // The "Main" function is the entry point into the program and is the first (and last) bit of user-code that is executed in the program.
    static void Main(string[] args)
    {
        Console.WriteLine("Hello World!");

        // Call the static function PrintMyClass
        CrazyPoprocks.MyClass123.PrintMyClass();

        // Create an instance of MyClass123
        BongoDrums drums = new BongoDrums();
        drums.PrintBongoDrums();

        BongoDrums.PrintBongoDrumsExplicit(drums);

        // Wait for user input before we exit the program.
        Console.ReadLine();
    }
}
