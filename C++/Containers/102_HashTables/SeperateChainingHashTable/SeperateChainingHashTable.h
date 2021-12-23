#pragma once

#include <exception>   //std::invalid_argument
#include <utility>     //std::forward<T>(), std::move()
#include <iostream>    //std::cout
#include <functional>  //std::hash<KeyType>

#include "dynamicArray.h"     //the dynamic array I made is used here for the array of singly linked lists
#include "SinglyLinkedList.h" //the linked list I made is used here for the chaining
#include "Vec4.h"             //sample class for tests (just in a header for convenience)

//templated class for a hashtable
//this one uses seperate chaining to
//resolve key hasing collisions
//(no iterator in this example)

template <class KeyType, class ValType>
class SCHashTable //seperate chaining hash table
{
public:

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

        //move constructor used for rehashing
        KVpair(KVpair&& oldPair) 
            : key(std::move(oldPair.key)), value(std::move(oldPair.value)){}
    };

    //pair to be returned from emplace/insert
    struct insertReturn
    {
        bool flag;
        KVpair& kvpair;
    };

    DynamicArray<LinkedList<KVpair>> chains; //the dyanmic array of linked lists 
    size_t       size;                       //number of elements in the hash table
    float        loadFactor;                 //the number of elements / number of lists
    float        maxLoadFactor;              //if load factor exceeds this, a rehash happens
    const size_t defaultNumOfLists;          //number of lists at initialization
    size_t       numOfLists;                 //number of lists at a given time
    
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

    bool isMaxLoadFactorReached()
    {
        loadFactor = size / (float)numOfLists;
        return loadFactor >= maxLoadFactor ? true : false;
    }

    //hash the key. Up to caller to mod value
    size_t hash(const KeyType& key)
    {
        std::hash<KeyType> hash;
        return hash.operator()(key);
    }

    //rehash will grow array of lists
    //and re hash location of elements
    void rehash()
    {
        uint32_t newNumOfLists = uint32_t(numOfLists * 1.5);
        
        //I found this end up being more 
        //readable/easier than resizing the old vector
        DynamicArray<LinkedList<KVpair>> temp;
        temp.resize(newNumOfLists);
    
        //for every list in old vector
        for(uint32_t i{}; i<numOfLists; i++) 
        {
            //for every node in old lists
            for(auto* it=chains[i].head; it; it=it->next)
            {
                //rehash key to a new index
                size_t newIndex = hash(it->data.key) % newNumOfLists;
    
                //now that we know which list to put the kvpair into,
                //move the data from the old list in the new one
                temp[newIndex].pushFront(std::move(it->data));
            }
        }
    
        chains = std::move(temp);   //copy assignment
        numOfLists = newNumOfLists; //update numOfLists
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

    SCHashTable()
        : size(0u), loadFactor(0.0f), 
          maxLoadFactor(2.0f), 
          defaultNumOfLists(10u),
          numOfLists(defaultNumOfLists)
    {
        chains.resize(10);
    }

    //destructor for the dynamic array is called automatically
    //and every node in all the linked lists are freed
    ~SCHashTable(){}

    const size_t getSize() const {return size;}
    const float  getLoadFactor() const {return loadFactor;}
    const float  getMaxLoadFactor() const {return maxLoadFactor;}

    //removes all linked list nodes
    void clearAll(bool shouldShrink = true)
    {
        for(uint32_t i = 0; i < chains.getSize(); i++)
            chains[i].~LinkedList();
        
        //shrink dynamic array to the default size
        if(numOfLists > defaultNumOfLists && shouldShrink)
            chains.shrink(defaultNumOfLists);

        loadFactor = 0.0f;
        size = 0;
        numOfLists = defaultNumOfLists;
    }

    ValType& operator[](KeyType&& key)
    {
        return tryEmplace(std::move(key)).kvpair.value;
    }

    void printTable()
    {
        //for every list
        for(uint32_t i{}; i<numOfLists; i++)
        {
            std::cout << "["<<i<<"]-->";
            //for every node in every list
            for(auto* it = chains[i].head; it; it=it->next)
            {
                std::cout << "{key: " << it->data.key << ", value:" << it->data.value<<"}";
                std::cout << "->";
            }
            std::cout << "NULL\n";
        }
    }

    //constructs a kvpair in place if the key doesnt exist yet
    template<typename... Types>
    insertReturn tryEmplace(KeyType&& key, Types&&... args)
    {
        size_t index = hash(key) % numOfLists;
        KVpair* kvpair = isKeyInList(key, index);

        //if the key isnt in the table
        if(!kvpair)
        {
            chains[index].emplaceFront(std::forward<KeyType>(key), 
                                       std::forward<Types>(args)...);
            size++;
            if(isMaxLoadFactorReached())
                rehash();

            //it emplaced the value at the front of list
            //so ret true (denoting a new node was emplaced)
            //and the head pointer's data's location 
            //(the location of the new kvpair)
            return {true, chains[index].head->data};
        }
        
        //else return false indicating tryEmplace
        //did not insert new kvpair (because key already existed)
        //and the location of where the 
        //kvpair is that blocked tryEmplace
        return {false, *kvpair};
    }

    //constructs a kvpair element in place
    //returns KVpair ref and a bool (false if it over wrote an element)
    template<typename... Types>
    insertReturn emplace(KeyType&& key, Types&&... args) 
    {
        size_t index = hash(key) % numOfLists;
        KVpair* kvpair = isKeyInList(key, index);

        //if the key given already exists in the table
        //use ValType's ctor to construct a ValType in place
        if(kvpair)
        {
            //since kvpair->value will get written over
            //free any resources it might control first
            kvpair->value.~ValType();
            new(&kvpair->value) ValType(std::forward<Types>(args)...);
            return {false, *kvpair};
        }
        {//if kpvair is nullptr (key wasnt already in list)
            chains[index].emplaceFront(std::forward<KeyType>(key), 
                                       std::forward<Types>(args)...);
            size++;
            if(isMaxLoadFactorReached())
                rehash();
            return {true, chains[index].head->data};
        }
    }

    //insert overload to accept two rvalues and tries to move into table
    //returns KVpair ref and a bool (false if it over wrote an element)
    insertReturn insert(KeyType&& key, ValType&& value)    
    {
        size_t index = hash(key) % numOfLists;
        KVpair* kvpair = isKeyInList(key, index);
        
        if(kvpair) //if the key already exists, write over the value there
        {
            //since kvpair->value will get written over
            //free any resources it might control first
            kvpair->value.~ValType();
            new(&kvpair->value) ValType(std::forward<ValType>(value));
            return {false, *kvpair};
        }      
        {//if kvpair is nullptr (key wasnt already in list)
            chains[index].pushFront(KVpair(std::forward<KeyType>(key),
                                           std::forward<ValType>(value)));
            size++;
            if(isMaxLoadFactorReached())
                rehash();
            return {true, chains[index].head->data};
        }
    }

    //inserts two already existing lvalues into the hash table
    //returns KVpair ref and a bool (false if it over wrote an element)
    insertReturn insert(const KeyType& key, const ValType& value)
    {
        //figure out which list to iterate over
        size_t index = hash(key) % numOfLists;
        KVpair* kvpair = isKeyInList(key, index);

        //if the key already exists, write over the value there
        if(kvpair)
        {
            //since kvpair->value will get written over
            //free any resources it might control first
            kvpair->value.~ValType();
            new(&kvpair->value) ValType(value);
            return {false, kvpair->data};
        }         
        {//if kvpair is nullptr (key wasnt already in list)
            chains[index].pushFront(KVpair(key,value));

            size++;
            if(isMaxLoadFactorReached())
                rehash(); 
            return {true, chains[index].head->data};
        }
    }

    //return the location of the kvpair if key is in the table.
    //Up to the user to check if the return isnt null before 
    //attempting to dereference the returned pointer
    KVpair* search(const KeyType& key)
    {
        //get the index of which list to search
        size_t index = hash(key) % numOfLists;

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

    //searches for key and deletes it
    //returns wether or not it found and 
    //deleted the node with the key in it
    bool erase(const KeyType& key)
    {
        size_t index = hash(key) % numOfLists;
        
        //if the list is empty return
        if(!chains[index].head)
            return false;

        //if the first node holds the key just popFront()
        if(chains[index].head->data.key == key)
        {
            chains[index].popFront();
            size--;
            return true;
        }

        //else traverse the list looking for the key
        auto* iter = chains[index].head;       
        for( ; iter->next; iter=iter->next)
        {
            if(iter->next->data.key == key)   
            {
                chains[index].eraseAtLocation(iter);
                size--;
                return true;
            }           
        }

        return false;
    }

};//class SChashtable<keytype, valtype>