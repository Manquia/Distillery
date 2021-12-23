#pragma once
#include <utility>//std::move, std::forward<T>

//templated class for an array that is resizeable at runtime (std::vector<T>)
//iterator not necessary
template<class T> 
class DynamicArray
{
private:
	const static size_t defaultCapacity = 8;
	size_t numOfElems;
	size_t capacity;
	T* typePtr;
	
	void reAllocate(size_t newCapacity)
	{
		//allocate new block of memory in free store/heap
		T* tempPtr = (T*)::operator new(sizeof(T)*newCapacity);
		capacity = newCapacity;
		
		//if first allocate then skip the copy/move
		//if realloc was called due to assignment then skip
		if(typePtr)
		{
			//copy/move elements over to new array
			for(uint32_t i = 0; i < numOfElems; i++)
			{
				new(tempPtr + i) T(std::move(typePtr[i]));
				typePtr[i].~T();	
			}
		}
	
		//delete old array
		::operator delete(typePtr, sizeof(T)*capacity);
		typePtr = tempPtr;
	}

public:
	size_t getSize() const {return numOfElems;}

	T& operator[](size_t index) {return typePtr[index];}

	DynamicArray()
	: numOfElems(0), capacity(0), typePtr(nullptr){}

	~DynamicArray()
	{
		clear();//call destructor on all elements first
		::operator delete(typePtr, sizeof(T)*capacity);
	}

	DynamicArray(DynamicArray&&) = delete;

	//copy constructor
	DynamicArray(const DynamicArray& oldObj) 
	{
		typePtr = nullptr;//gets set on first realloc
		numOfElems = 0;//needs to be zero on first realloc

		//if the old obj has had memory allocated already
		//then allocate new memory for new array
		if(oldObj.typePtr)
			reAllocate(oldObj.capacity);
	
		//if the oldobj has a size then realloc just happend
		//and that means there is an array to put things into
		//otherwise the loop wont run
		for(int i = 0; i < oldObj.getSize(); ++i)	
			::new(typePtr + i) T(oldObj.typePtr[i]);
		
		numOfElems = oldObj.numOfElems;
	}

	//assignment operator
	DynamicArray& operator=(const DynamicArray& right)
	{
		//if the operands are the same lvalue
		if(this == &right) return *this;
	
		//deconstruct everything
		for(int i = 0; i < numOfElems; i++)
			typePtr[i].~T();
		
		//if the capacity of the arrays arent already the same size
		//then reallocate so the left side capacity is the same as right
		if(capacity != right.capacity)
		{
			//free left side memory
			::operator delete(typePtr, sizeof(T)*capacity);

			//make arrays the same size
			typePtr = (T*)::operator new(sizeof(T)*right.capacity);

			capacity = right.capacity;
		}
		
		//copy items over
		for(int i = 0; i < right.numOfElems; ++i)	
			new(typePtr + i) T(right.typePtr[i]);
		
		numOfElems = right.numOfElems;
		return *this;
	}

	//move assignment operator
	DynamicArray& operator=(DynamicArray&& right) noexcept
	{
		if(this == &right)
			return *this;

		//free left sides resources	and
		//copy the pointer from the old vector
		clear(); 
		::operator delete(typePtr, sizeof(T)*capacity);
		typePtr = right.typePtr; 

		numOfElems = right.numOfElems;
		capacity = right.capacity;

		//old vector now points to null so that the
		//destructor doesnt free the same memory twice
		right.typePtr = nullptr;
		right.numOfElems = 0;
		right.capacity = 0;

		return *this;
	}

	void pushBack(const T& val)
	{
		//if first push/emplace allocate the first array
		if(!typePtr)
			reAllocate(DynamicArray::defaultCapacity);
	
		//if the array runs out of room make more room (1.5x as much)
		if(numOfElems >= capacity)
			reAllocate(capacity + capacity / 2);
	
		::new(typePtr + numOfElems) T(val);
		numOfElems++;
	}

	void pushBack(T&& val)
	{
		//if first push/emplace allocate the first array
		if(!typePtr)
			reAllocate(DynamicArray::defaultCapacity);

		//if the array runs out of room make more room (1.5x as much)
		if(numOfElems >= capacity)
			reAllocate(capacity + capacity / 2);
	
		//new(typePtr + numOfElements) T(std::move(val));
		typePtr[numOfElems] = std::move(val);
		numOfElems++;
	}

	//constructs the elements in place in the array.
	//Takes a varying number of arguments to give the constructor
	//and also might need a varying number of types
	template<typename... Types>
	void emplaceBack(Types&&... args)
	{
		//if first push/emplace allocate the first array
		if(!typePtr)
			reAllocate(DynamicArray::defaultCapacity);
	
		//if the array runs out of room make more room (1.5x as much)
		if(numOfElems >= capacity)
			reAllocate(capacity + capacity / 2);
		
		//placement new to construct item in array
		::new(typePtr + numOfElems) T(std::forward<Types>(args)...);
		numOfElems++;
	}

	void eraseAt(size_t index)
	{	
		//if its a valid index
		if(index >= 0 && index < numOfElems)
		{
			//destroy element at specified index
			typePtr[index].~T();
			
			//by default user expects array to be in the order they made it in.
			//So instead of taking the last element and putting it at typePtr[index]
			//I'm going to shift the entire vector over from the "right" by 1 spot
			for(uint32_t i=index,j=index+1; j<numOfElems; ++i, ++j)	
			    typePtr[i] = std::move(typePtr[j]);		
		
			--numOfElems;
		}
	}

	void popBack()
	{
		//manually call destructor. If you were to pop an element
		//then push a new one in its place, then the resources the
		//old one may have owned never got destroyed/freed;	
		//same thing goes for erase() and clear()
		if(numOfElems)		
			typePtr[--numOfElems].~T();	
	}

	//shrink the capacity to the specified size
	void shrink(size_t newCapacity)
	{
		if(newCapacity >= capacity)
			return;

		if(newCapacity < numOfElems)
		{
			while(numOfElems != newCapacity)
				popBack();

			shrinkToFit();
		}
		else//if size >= numOfElems
			reAllocate(newCapacity);		
	}

	//makes capacity = numofelements
	void shrinkToFit()
	{
		if(numOfElems == capacity)
			return;

		if(typePtr)
		{
			//case: 0 elements just delete array
			if(!numOfElems)
			{
			   	::operator delete(typePtr, sizeof(T)*capacity);
			   	typePtr = nullptr;	
			}
			else//else if numofelements > 0 shrink capacity to numofelements
			{
				reAllocate(numOfElems);
			}
		}
	}

	//deletes everything while not chaning capacity
	//it is up to the user to call shrinkToFit()
	void clear()
	{
		//if the type has its own resources to clean up, then free them
		for(uint32_t i = 0; i < numOfElems; i++)
			typePtr[i].~T();
	
		numOfElems = 0;
	}

	//makes capacity = the size param
	void reserve(size_t size)
	{
		if(size > capacity)
			reAllocate(size);
	}

	//resize overload for calling placement new
	//to default construct T's in place in the array
	//instead of having default T's on the stack
	//and copying it into the array one by one
	void resize(size_t newNumOfElems)
	{
		if(newNumOfElems == numOfElems)
			return;

		if(newNumOfElems < numOfElems)
		{
			while(numOfElems != newNumOfElems)
				popBack();
		}
		else//if newSize > numOfElems
		{
			//if numOfNewElems > capacity then reserve will
			//allocate a new array. else if numOfNewElems <= capacity
			//then no reAllocation will happen
			reserve(newNumOfElems);
		
			while(numOfElems != newNumOfElems)
				emplaceBack();
		}
	}

	//does not change capacity unless newNumOfElems > capacity.
	//so it is up to the user to call shrinkToFit to downsize
	//the capacity (if they want to) after calling 
	//resize where newNumOfElems < numOfElems
	void resize(size_t newNumOfElems, const T& val)
	{
		if(newNumOfElems == numOfElems)
			return;

		if(newNumOfElems < numOfElems)
		{
			while(numOfElems != newNumOfElems)
				popBack();
		}
		else//if newSize > numOfElems
		{
			//if numOfNewElems > capacity then reserve will
			//allocate a new array. else if numOfNewElems <= capacity
			//then no reAllocation will happen
			reserve(newNumOfElems);

			while(numOfElems != newNumOfElems)
				pushBack(val);		
		}
	}

};//class DynamicArray<T>