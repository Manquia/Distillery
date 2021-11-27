#pragma once
//#include <stdexcept> //std::out_of_range()
#include <utility> //std::move(), std::forward<T>
#include <iostream>



//////////////////////////////////////////////////////////////
/*--------------------work in progress----------------------*/
/////////////////////////////////////////////////////////////



//templated class for a singly linked list (std::forward_list)
//with no iterators
template<class T>
class LinkedList
{
public:
    struct Node
    {
        Node* next;
        T data;

        //Node constructors for moving and copying into list
        Node(const T& data, Node* ptr): next(ptr), data(data){}
        Node(T&& data, Node* ptr): next(ptr), data(std::move(data)){}

        //node constructor for emplacing inside node
        template<typename... Types>
        Node(Types&&... args, Node* ptr): next(ptr), data(std::forward<Types>(args)...){}
    };

    size_t size;
    Node* head;

    //size_t getSize() const {return size;}

    LinkedList(): head(nullptr), size(0){}

    //LinkedList(const LinkedList& oldObj) {}
    //LinkedList& operator=(const LinkedList& right) {}

    ~LinkedList()
    {
        clearAll();
    }

    //erase at a specific index
    //if the index is > max index eraseAt() 
    //will erase the last element
    void eraseAt(size_t index)
    {
        //case index provided is the first element (index 0)
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

        //make previous node point to the node after the one deleted
        previousNodeLocation->next = nextNodeLocation;
    }

    //deletes all the elements
    void clearAll()
    {
        //start the journey at the first node
        Node* traveler = head;
        
        //traverse list and free every node
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
    }

    //will construct the object in place 
    //in the list after a specified index
    template<typename... Types>
    void emplaceAfter(Types&&... args, const size_t index)
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
        temp->next = new Node(std::forward<Types>(args)... , temp->next);
    }

    //will construct the object in place
    //after at the front of the list
    template<typename... Types>
    void emplaceFront(Types&&... args)
    {
        //the new node's next ptr is set to head before head is 
        //then assigned to point at the new node
        head = new Node(std::forward<Types>(args)... , head);
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
        //if the list is empty then dont do anything
        if(!head) return;

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
    }

    Node* iterateUntil(const size_t index)
    {   
        //start the journey at the first node
        Node* traveler = head;

        //traverse list until specified index.
        //if the index is > max index in the list
        //then return address of last node
        for(size_t i = 0; (i < index) && (traveler->next); i++)
        {
            traveler = traveler->next;
        }

        //return the address that the specified index is at
        return traveler;
    }

};//class LinkedList<T>
