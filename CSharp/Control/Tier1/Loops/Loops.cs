using System;
using System.Collections.Generic;

class Loops
{
    static void Main(string[] args)
    {
        // Loops untill the condtion becomes false
        int counter = 5;
        while(counter > 0)
        {
            Console.WriteLine("While loop: " + counter);
            counter -= 1;
        }

        // do while loop will always executes atleast once and then untill the condition becomes false 
        counter = 2;
        do
        {
            Console.WriteLine("do while loop: " + counter);
            counter += 1;
        } while (counter < 2);


        // Loops until the condition become false
        for(int i = 0; i < 3; ++i)
        {
            Console.WriteLine("For loop i value");
        }


        List<int> list = new List<int>();
        list.Add(1);
        list.Add(3);
        list.Add(5);
        list.Add(7);

        // iterator over every item in the list container.
        foreach(var v in list)
        {
            Console.WriteLine("foreach list value: " + v);
        }


        // wait for user-input before the program ends.
        Console.Read();
    }
}
