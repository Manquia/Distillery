#pragma once


/*       WIP still need to make rehash and maybe subscript operator (to add kvpairs to table)      */


#include <vector> // @TODO: remove this and then use my vector class

#include <utility>     //std::forward<T>(T&&)
//#include <iostream>    //std::cout
#include <functional>  //std::hash<KeyType>

#include "SinglyLinkedList.h" //the linked list I made, is used here for the chaining
#include "Vec4.h"             //sample class for tests (just in a header for convenience)

//templated class for a hashtable
//this one use seperate chaining to
//resolve key hasing collisions
//(no iterator in this example)
template <class KeyType, class ValType>
class SCHashTable //seperate chaining hash table
{
private:

    //I used my own struct instead of std::pair because I like writing things myself.
    //also because the member variable names of std::pair are generically named
    //first and second and not (the more descriptive for this case) key and value
    struct KVpair //key value pair
    {
        KeyType key;
        ValType value;

        //construct a key value pair node from two existing lvalues
        KVpair(const KeyType& key, const ValType& val) : key(key), value(val){}

        //constructor for for forwarding rvalues to the keytype and valtype ctors
        KVpair(KeyType&& key, ValType&& val) 
            : key(std::forward<KeyType>(key)), value(std::forward<ValType>(val)){}

        //ctor for constructing keys and values in place inside table
        template<typename... Types>
        KVpair(KeyType&& key, Types&&... args) 
            : key(std::forward<KeyType>(key)), value(std::forward<Types>(args)...){}
    };

    std::vector<LinkedList<KVpair>> chains; //the dyanmic array of linked lists    
    size_t size;                            //number of elements in the hash table
    float loadFactor;                       //the number of elements / number of lists
    float maxLoadFactor;                    //if load factor exceeds this, a rehash happens

    //takes an index of which list to traverse, 
    //and a key. if key is in that list, return
    //the memory address of that key value pair
    KVpair* isKeyInList(const KeyType& key, const size_t index)
    {
        //start the iterator (pointer) at the begining 
        //of the list[index] and travel until key is found
        //or nullptr is found (end of list)
        auto* iter = chains[index].head;
        for( ; iter; iter=iter->next)
        {
            //if the key already exists then
            //replace the value at that location
            if(iter->data.key == key) 
                return &(iter->data);
        }

        //if the end of the list was reached
        //then the key isnt in the list
        return nullptr;
    }

    //rehash will grow array of lists
    //and re hash location of elements
    void rehash()
    {

    }

    //hash the key and map it to an 
    //index in the dynamic array of lists
    size_t hashAndMapKeyToIndex(KeyType key)
    {
        std::hash<KeyType> hash;
        return hash.operator()(key) % chains.size();
    }

public:

    //for the sake of this tutorial / example code
    //im not going to write these here again. Although if
    //you want to see them explicitly written out,
    //I did write them for DynamicArray.h, and 
    //LinkedList.h both used here for this hash table
    SCHashTable(const SCHashTable&)       = delete;//copy constructor
    SCHashTable(SCHashTable&&)            = delete;//move constructor
    SCHashTable& operator=(SCHashTable&)  = delete;//copy assignment operator
    SCHashTable& operator=(SCHashTable&&) = delete;//move assignment operator

    SCHashTable() : size(0u), loadFactor(0.0f), maxLoadFactor(3.0f)
    {
        chains.resize(10);
    }

    //constructs a linked list node in place
    template<typename... Types>
    void emplace(KeyType&& key, Types&&... args) 
    {
        size_t index = hashAndMapKeyToIndex(key);
        KVpair* kvpair = isKeyInList(key, index);

        //if the key given already exists in the table
        //use ValType's ctor to construct a ValType in place
        if(kvpair)
        {
            //since kvpair->value will get written over
            //free any resources it might control first
            kvpair->value.~ValType();
            new(&kvpair->value) ValType(std::forward<Types>(args)...);
        }
        else //if kpvair is nullptr (key wasnt already in list)
        {
            chains[index].emplaceFront(std::forward<KeyType>(key), 
                                       std::forward<Types>(args)...);
        }
    }

    //insert() overload to accept two rvalues and tries to move into table
    void insert(KeyType&& key, ValType&& value)    
    {
        size_t index = hashAndMapKeyToIndex(key);
        KVpair* kvpair = isKeyInList(key, index);
       
        if(kvpair) //if the key already exists, write over the value there
        {
            //since kvpair->value will get written over
            //free any resources it might control first
            kvpair->value.~ValType();
            new(&kvpair->value) ValType();
        }
        else //if kvpair is nullptr (key wasnt already in list)
        {
            chains[index].pushFront(KVpair(std::forward<KeyType>(key),
                                           std::forward<ValType>(value)));
        }
    }

    //inserts two already existing lvalues into the hash table
    void insert(const KeyType& key, const ValType& value)
    {
        //figure out which list to iterate over
        size_t index = hashAndMapKeyToIndex(key);
        KVpair* kvpair = isKeyInList(key, index);

        //if the key already exists, write over the value there
        if(kvpair)
        {
            //since kvpair->value will get written over
            //free any resources it might control first
            kvpair->value.~ValType();
            new(&kvpair->value) ValType(value);
        }        
        else //if kvpair is nullptr (key wasnt already in list)
        {
            chains[index].pushFront(KVpair(key,value));
        }
    }

    //return the location of the kvpair if key is in the table
    KVpair* search(const KeyType& key)
    {
        //get the index of which list to search
        size_t index = hashAndMapKeyToIndex(key);

        //start the iterator (pointer) at the beginning
        //of the list[index] and travel until key is found
        //or nullptr is found (end of list)
        auto* iter = chains[index].head;
        for( ; iter; iter=iter->next)
        {
            //if the key is found in a node
            //return the address of where it is
            if(iter->data.key == key)
                return &iter->data;
        }
        //if key not found in table return null
        return nullptr;
    }

    //returns wether or not it found and 
    //deleted the node with the key in it
    bool erase(const KeyType& key)
    {
        size_t index = hashAndMapKeyToIndex(key);
        
        //if the list is empty return
        if(!chains[index].head) 
            return false;

        //if the first node holds the key just popFront()
        if(chains[index].head->data.key == key)
        {
            chains[index].popFront();
            return true;
        }

        //else traverse the list looking for the key
        auto* iter = chains[index].head;       
        for( ; iter->next; iter=iter->next)
        {
            if(iter->next->data.key == key)   
            {
                chains[index].eraseAtLocation(iter);
                return true;
            }           
        }
        return false;
    }

};//class SChashtable<keytype, valtype>