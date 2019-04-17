using System;

class ControlStatements
{
    static void Main(string[] args)
    {
        bool cond = true;
        int n = 10;

        // Curly brackets for scope are not needed so long as you 
        // only want 1 statement to be run by the if stetament.
        if (cond) Console.WriteLine("Start!");


        if(cond)
        {
            Console.WriteLine("Micky Mouse");
        }
            
        if(!cond)
        {
            Console.WriteLine("Peter Parker");
        }
        else
        {
            Console.WriteLine("Lara Croft");
        }

        // Chaining if/else
        if (!cond)
            Console.WriteLine("Pipe0");
        else if (n == 10)
            Console.WriteLine("Pipe1");
        else if (n > 10)
            Console.WriteLine("Pipe2");
        else
            Console.WriteLine("Pipe2");
            
        // Switch statement
        switch(n)
        {
            case 10:
                Console.WriteLine("Case 10");
                break;
            case 11:
                Console.WriteLine("Case 11");
                break;
            default: // every other case besides 10 or 11. Optional.
                Console.WriteLine("default");
                break;
        }

        //  Wait for user input before closing the program.
        Console.Read();
    }
}

