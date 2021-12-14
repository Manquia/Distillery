#pragma once
#include <utility>   //std::move(), std::forward<T>()
#include <iostream>  //std::cout
#include <exception> //std::out_of_range std::invalid_argument

//the same LinkedList class from 200_LinkedList 
//included here for use in the seperate chaning hash table

//templated class for a singly linked list
//no iterator in this example
template<class T>
class LinkedList
{
public:
    struct Node
    {
        Node* next;
        T data;

        //construct a node from an existing lvalue
        Node(const T& data, Node* ptr) : next(ptr), data(data){}

        //construct a node from an rvalue
        Node(T&& data, Node* ptr) : next(ptr), data(std::move(data)){}

        //node constructor for emplacing inside node
        template<typename... Types>
        Node(Node* ptr, Types&&... args) : next(ptr), data(std::forward<Types>(args)...){}
    };

    size_t size; //number of elements in the list
    Node* head; //the location of the first node in the list

    //default constructor
    LinkedList(): head(nullptr), size(0){}

    //copy constructor
    LinkedList(const LinkedList& oldObj) 
    {
        //if theres nothing in the old list make an epmty list
        if(!oldObj.head)
        {
            head = nullptr;
            size = 0;
            return;
        }

        //start the journey through the old object at the first node
        Node* traveler = oldObj.head;
       
        //while the traveling pointer hasnt 
        //reached the end of the old object's list
        uint32_t index = 0;
        while(traveler)
        {
            //for each node in old list, push a 
            //new node to the back of the new list
            this->insertAfter(traveler->data, index);

            traveler = traveler->next;
            index++;
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
    LinkedList& operator=(const LinkedList& right) 
    {
        //if the operands are the same lvalue
        if(this == &right) 
            return *this;
        
        //if theres nothing in the old list make an epmty list
        if(!right.head)
        {
            head = nullptr;
            size = 0;
            return *this;
        }

        //start the journey through the old object at the first node
        Node* traveler = right.head;   

        //while the traveling pointer hasnt
        //reached the end of the old object's list
        uint32_t index = 0;
        while(traveler)
        {
            //for each node in old list, push a 
            //new node to the back of the new list
            this->insertAfter(traveler->data, index);
        
            traveler = traveler->next;
            index++;
        }
        return *this;
    }

    //move assignment operator
    LinkedList& operator=(LinkedList&& right) noexcept
    {
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

    void printList() const
    {
        //if list is empty dont do anything
        if(!head) 
        {
            std::cout << "EMPTY\n\n";
            return;
        }

        //start the journey at the first node
        Node* traveler = head;

        for(;;)
        {
            std::cout << traveler->data;
            std::cout << "->";
            traveler = traveler->next;

            //if the traveling pointer has reached
            //the end of the list then print its value (NULL)
            //and break out of the loop 
            if(!traveler)
            {
                std::cout << "NULL\n\n";
                break;
            }
        }
    }

    //if you already (traversed the list) know where the node is
    //that you want to delete, then use this function.
    //give it the node before the one that you want to delete
    void eraseAtLocation(Node* b4Target)
    {
        if(!b4Target)
            throw std::out_of_range("passed null to eraseAtLocation()\n\n");

        //node to delete
        Node* target = b4Target->next;

        //it is possible to delete nullptr, 
        //but I want to make sure target isnt null before I try
        //to dereference it to obtain what it points to
        if(!target)
            throw std::out_of_range("passed the end of list to eraseAtLocation()\n\n");

        //previous node now points to
        //where target used to point to
        b4Target->next = target->next;

        delete target;
        --size;
    }

    //if you dont know where nodes location is yet
    //use then function (it will traverse list index times then erase)
    void eraseAtIndex(size_t index)
    {
        //if index is out of range / too large
        if(index > size-1) 
            throw std::out_of_range("tried to erase at invalid index");

        //case: index provided is the first element (index 0)
        if(!index)
        {
            popFront();
            return;
        }

        //find the address of the location of the element
        //previous the one we want to delete
        Node* previousNodeLocation = iterateUntil(index-1);

        //get the address of the node after the node we want to delete
        //if we are deleting the last node the address will be null
        Node* nextNodeLocation = previousNodeLocation->next->next;

        //delete node at index
        delete previousNodeLocation->next;
        --size;

        //make previous node point to the node after the one deleted
        previousNodeLocation->next = nextNodeLocation;
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
    //in the list after a specified index
    template<typename... Types>
    void emplaceAfter(const size_t index, Types&&... args)
    {
        //if the first element hasnt been made 
        //emplace in the front first
        if(!head)
        {
            emplaceFront(std::forward<Types>(args)...);
            return;
        }
        //get adress of list[index] then make a new node
        //that points to where list[index] points to 
        //then change list[index] to point to the new node
        Node* temp = iterateUntil(index);
        temp->next = new Node(temp->next, std::forward<Types>(args)...);
        size++;
    }

    //will construct the object in place
    //after at the front of the list
    template<typename... Types>
    void emplaceFront(Types&&... args)
    {
        //the new node's next ptr is set to head before head is 
        //then assigned to point at the new node
        head = new Node(head, std::forward<Types>(args)...);
        size++;
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
    void insertAfter(const T& val, const size_t index)
    {
        //if the first node hasnt been
        //made then create one and return
        if(!head)
        {
            pushFront(val);
            return;
        }
        //get adress of list[index] then make a new node
        //that points to where list[index] points to
        //then change list[index] to point to the new node
        Node* temp = iterateUntil(index);
        temp->next = new Node(val, temp->next);
        size++;
    }

    //verstion of above function to take 
    //and rvalue and move instead of copy into list
    void insertAfter(T&& val, const size_t index)
    {
        //if the first node hasnt been
        //made then create one and return
        if(!head)
        {
            pushFront(std::move(val));
            return;
        }
        //get adress of list[index] then make a new node
        //that points to where list[index] points to
        //then change list[index] to point to the new node
        Node* temp = iterateUntil(index);
        temp->next = new Node(std::move(val), temp->next);
        size++;
    }

    //returns the location of the node at index
    //if you give it an index > max index then
    //it returns location of last node
    Node* iterateUntil(const size_t index) const
    {
        //start the journey at the first node
        Node* traveler = head;

        //traverse list until specified index.
        //if the index is > max index in the list
        //then return address of last node
        for(size_t i = 0; (i < index) && (traveler->next); i++)     
            traveler = traveler->next;
        
        //return the address that the specified index is at
        return traveler;
    }

    //returns the location of the node with the 
    //specified value. If there are mutiple of the
    //same value it will return the first one it finds
    Node* findValue(const T& value) const
    {
        //start the journey at the first node
        Node* traveler = head;

        for(;;)
        {
            //if the data where the traveler is 
            //matches the specified value return the 
            //memory address of where the traveler is
            if(traveler->data == value)          
                return traveler;
            
            traveler = traveler->next;

            //if the loop reached the end of the list 
            //without returning a value it wasnt in the list
            if(!traveler) 
                return nullptr;
        }
    }

};//class LinkedList<T>