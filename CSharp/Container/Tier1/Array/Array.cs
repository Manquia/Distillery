using System;

class Array
{
    // sample will create an array and do some operations with the data
    static void Main(string[] args)
    {
        // create an array of 26 char(s).
        char[] integerArray = new char[26];

        // initialize the array to values 'a-z'
        for (int i = 0; i < integerArray.Length; ++i)
        {
            // increment character 'a' by i values and assign it to the 'i'th element in the array.
            // See ASCII tables for more information.
            integerArray[i] = (char)('a' + i);
            Console.WriteLine("Initialized index " + i + " to character value: " + (char)('a' + i));
        }
        PrintArray(integerArray);

        // find index and print the result
        int index = FindFirst('b', integerArray);
        if(index == -1) // not found
        {
            Console.WriteLine("We did not find b.");
        }
        else // success, found value
        {
            Console.WriteLine("We found 'b' at index: " + index);
        }

        // wait for user input before closing the program
        Console.ReadLine();
    }

    // Returns the index of the first value wihch matches 'find'.
    // If value is not found then -1 is returned
    static public int FindFirst(char find, char[] array)
    {
        for (int i = 0; i < array.Length; ++i)
        {
            if(array[i] == find)
            {
                return i;
            }
        }
        return -1;
    }

    static public void PrintArray(int[] array)
    {
        for (int i = 0; i < array.Length; ++i)
        {
            Console.Write(array[i] + ' ');
        }
        Console.Write('\n');
    }
    
    // @Excercise impliment function: static public int FindLast(char find, char[] array)
    // @Excercise impliment function: static public int[] GrowArray(char[] oldArray, int newSize)
    // @Excercise impliment function: static public bool RemoveFirst(char toRemove, char[] array)
    // @Excercise impliment function: static public bool RemoveLast(char find, char[] array)
}
