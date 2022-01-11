#pragma once
#include <utility>   //std::move(), std::forward<T>()
#include <iostream>  //std::cout
#include <exception> //std::out_of_range std::invalid_argument
#include "vec4.h"    //sample class for tests

//the same LinkedList class from 200_LinkedList 
//this one has an iterator for 204_iterators 

template<class T>
class LinkedList;

template <class List>
class ListIterator
{   
private:
    //ValTy is now = the type of data in the list
    using ValTy = typename List::ValType; 

    //NodePointer is now a Node*
    using NodePointer = typename List::Node*;

    NodePointer prevNode; //location of previous node
    NodePointer currNode; //location of current node

public:
    friend class LinkedList<ValTy>;

    ListIterator() = delete; //default not used

    //constructor that is used
    ListIterator(NodePointer currPtr, NodePointer backPtr) 
        : prevNode(backPtr), currNode(currPtr){}
    
    //deref the current node pointer to get the pointer to the data
    ValTy* operator->() {return &currNode->data;}

    //deref the current node pointer to get the data in the list
    ValTy& operator*() {return currNode->data;}

    //check if iterators are equal
    bool operator==(const ListIterator& rhs)
    {
        return(currNode == rhs.currNode);
    }

    //chech if iterators are not equal
    bool operator!=(const ListIterator& rhs)
    {
        return !(currNode == rhs.currNode);
    }

    //increment the iterator (prefix).
    ListIterator& operator++()
    {
        prevNode = currNode;
        currNode = currNode->next;
        return *this;
    }

    //increment the iterator (postfix).
    //increments *this with the operator defined above.
    //then returns a copy of the pointers 
    //before the increment occures
    ListIterator operator++(int)
    {        
        auto tmp = *this; //save current pointers  
        ++*this;        //increment *this with the above operator
        return tmp;    //return the un-incremented pointers
    }

    //advance n nodes forward in the list 
    ListIterator& operator+(const uint32_t n)
    {
        for(uint32_t i{}; i<n; i++)
        {
            prevNode = currNode;
            currNode = currNode->next; 
        }
        return *this;
    }

};//class ListIterator


//templated class for a singly linked list
//iterator for this class above
template<class T>
class LinkedList
{
private:
    struct Node
    {
        Node* next;
        T data;

        //construct a node from an existing lvalue
        Node(const T& data, Node* ptr) 
            : next(ptr), data(data){}

        //construct a node from an rvalue
        Node(T&& data, Node* ptr) 
            : next(ptr), data(std::move(data)){}

        //node constructor for emplacing inside node
        template<typename... Types>
        Node(Node* ptr, Types&&... args) 
            : next(ptr), data(std::forward<Types>(args)...){}
    };
    
    size_t size; //number of elements in the list
    Node* head; //the location of the first node in the list

public: 
    using ValType = T;
    using Iterator = ListIterator<LinkedList<T>>;//typename for an iterator
    friend class Iterator;//the list iterator class can now access the private stuff

    //begin iterator the previous node with just also be the head
    Iterator begin() {return Iterator(head, head);}

    //end iterator the current node will be null
    //and the previous will be the tail node or null
    Iterator end() {return Iterator(nullptr, nullptr);}

    size_t getSize() const {return size;}//get a copy of the size member
    bool isEmpty() const {return !head;}//if empty head is null. so return true

    //default constructor
    LinkedList(): head(nullptr), size(0){}

    //copy constructor
    LinkedList(LinkedList& oldObj) : size(0), head(nullptr)
    {     
        //keep track of where the last
        //node is in the new list as we push elements into it
        //start the new list by making the first node
        //with the data from the first node in old list
        Node* tail = new Node(oldObj.head->data, nullptr);
        head = tail;
        size = 1;

        //for every node in old list starting from the 
        //second node. copy the data over into the new nodes
        for(auto it = oldObj.begin()+1; it!=oldObj.end(); ++it)
        {
            //make a new node at the end of new list
            tail->next = new Node(*it, nullptr);

            //update where the tail points to
            tail = tail->next;
            ++size;
        }
    }

    //move constructor
    LinkedList(LinkedList&& oldObj) noexcept
    {
        //just make the head of the new list
        //point to the first node of the old list
        head = oldObj.head;
        size = oldObj.size;

        //then make sure the old list head pointer
        //points to nothing effectivly empting the old 
        //list out (and so there arent two pointers to the same memory)
        oldObj.head = nullptr;
        oldObj.size = 0;
    }

    //copy assignment operator
    LinkedList& operator=(LinkedList& rhs) 
    {
        //if the operands are the same lvalue
        if(this == &rhs) 
            return *this;

        //empty out the left hand size list before it becomes 
        //a copy of the right hand side list
        //(clearAll will also set head=null and size=0)
        clearAll();

        //keep track of where the lastnode is in the left 
        //hand side list as we push new nodes into it
        //start the new list by making the first node
        //with the data from the first node in old list
        Node* tail = new Node(rhs.head->data, nullptr);   
        head = tail;
        size = 1;

        for(auto it=rhs.begin()+1; it!=rhs.end(); ++it)
        {
            tail->next = new Node(*it, nullptr);
            tail = tail->next;
            ++size;
        }  
        return *this;
    }

    //move assignment operator
    LinkedList& operator=(LinkedList&& right) noexcept
    {
        //clear left hand side list before it becomes the right hand size
        clearAll();

        //just make the head of the new list
        //point to the first node of the old list
        head = right.head;
        size = right.size;   

        //then make sure the old list head pointer
        //points to nothing effectivly empting the old 
        //list out (and so there arent two pointers to the same memory)
        right.head = nullptr;
        right.size = 0;

        return *this;
    }

    //destructor
    ~LinkedList()
    {
        clearAll();
    }  

    void printList()
    {
        //if list is empty dont do anything
        if(!head)
        {
            std::cout << "EMPTY\n\n";
            return;
        }

        for(const auto& it : *this)
        {
            std::cout << it;
            std::cout << "->";    
        }
        std::cout << "NULL\n";
    }

    //erased a node at the given location
    void eraseAtLocation(Iterator& location)
    {
        if(!location.currNode)
            throw std::out_of_range("passed out of range iterator to eraseAtLocation()\n\n");

        //previous node points to node after current node
        location.prevNode->next = location.currNode->next; 

        //update the head pointer if the first element is removed
        if(location.currNode == head)
            head = location.currNode->next;

        //remove current node
        delete location.currNode;
        --size;
    }

    //deletes all the elements
    void clearAll()
    {
        //start the journey at the first node
        Node* traveler = head;
        
        //while the traveling pointer hasnt 
        //reached the end of the list
        while(traveler)
        {
            //save location of what current node points to
            Node* temp = traveler->next;

            //free current node
            delete traveler;

            //traveler now points to what current node points to. If current
            //node points to null, then this is the end of the while loop.
            //If it points to a valid node, then continue deleting
            //until traveler points to null (which means it reached the end of the list)
            traveler = temp;
        }
        //make sure head isnt a dangling pointer
        head = nullptr;
        size = 0;
    }

    //will construct the object in place 
    //in the list after a specified location
    template<typename... Types>
    void emplaceAfter(Iterator& location, Types&&... args)
    {
        //make a new node constructed with args... 
        //make that new node point to the node after the node at location
        //then make the node at location point to the new node
        location.currNode->next = new Node(location.currNode->next, std::forward<Types>(args)...);
        ++size;
    }

    //will construct the object in place
    //after at the front of the list
    template<typename... Types>
    void emplaceFront(Types&&... args)
    {
        //the new node's next ptr is set to head before head is 
        //then assigned to point at the new node
        head = new Node(head, std::forward<Types>(args)...);
        ++size;
    }

    //creates a new zero index node
    //version of pushFront to move an 
    //rvalue instead of copy into list
    void pushFront(T&& val)
    {
        //creates a new node that points to what
        //head USED to point to before head gets
        //reassigned to point at the new node
        head = new Node(std::move(val), head);
        size++;
    }

    //creates a new zero index node
    void pushFront(const T& val)
    {
        //creates a new node that points to what
        //head USED to point to before head gets
        //reassigned to point at the new node
        head = new Node(val, head);
        size++;
    }

    //delete node at the front of list
    void popFront()
    {
        if(!head)
            throw std::out_of_range("tried to popFront() on an empty list");

        //save location of node number two
        //if ther isnt a node number two then temp is null
        Node* temp = head->next;

        //free first node
        delete head;

        //head now points to second node or null
        head = temp;
    }

    //inserts new node after given index
    //if given index is greater than the max
    //index in list, then just insert after max index anyway
    void insertAfter(const T& val, Iterator& location)
    {
        //construct a new node with a copy of val inside
        //make the new node point to where the node at locatino points
        //then make the node at location point to the new node
        location.currNode->next = new Node(val, location.currNode->next);
        size++;
    }

    //verstion of above function to take 
    //and rvalue and move instead of copy into list
    void insertAfter(T&& val, Iterator& location)
    {
        //construct a new node and move val into it
        //make the new node point to where the node at locatino points
        //then make the node at location point to the new node
        location.currNode->next = new Node(std::move(val), location.currNode->next);
        size++;
    }

    //returns an iterator to the node with the 
    //specified value. if that value isnt in the list
    //then it returns the end iterator which is nullptr
    //so if you wanted to check if it was in the list
    //you could do...
    // auto it = myList.findValue(value);
    //if(it != myList.end())
    //to see if its in the list or not
    Iterator findValue(const T& value)
    {
        //use the iterator class to iterate over the list
        //if the value is found return the iterator where it is
        //if the value is not found return
        for(auto it = begin(); it != end(); it++)
        {
            if(*it == value)
                return it;
        }
        return Iterator(nullptr,nullptr);
    }

};//class LinkedList<T>