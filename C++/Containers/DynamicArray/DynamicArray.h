#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <cassert>
#ifndef _DEBUG
#define NDEBUG
#endif

namespace MYC //(my containers)
{
template<class T> 
class DynamicArray
{
private:
	const static size_t defaultCapacity = 8;
	size_t numOfElements;
	size_t capacity;
	T* typePtr;
public:
	size_t getSize() const {return numOfElements;}

	T& operator[](size_t index)
	{
		//(if in debug mode only) check that index insnt out of bounds
		//and if it is, then print err msg and terminate program
		assert(("subscript operator used to access an invalid array index",
			    index >=0 && index < numOfElements));
	
		return typePtr[index];
	}

	DynamicArray()
	: numOfElements(0), capacity(0), typePtr(nullptr){}

	~DynamicArray()
	{
		clear();//call destructor on all elements first
		::operator delete(typePtr, sizeof(T)*capacity);
	}

	DynamicArray(DynamicArray&&) = delete;
	DynamicArray& operator=(DynamicArray&& right) = delete;
	
	//copy constructor
	DynamicArray(const DynamicArray& oldObj) 
	{
		typePtr = nullptr;//gets set on first realloc
		numOfElements = 0;//needs to be zero on first realloc

		//if the old obj has had memory allocated already
		//then allocate new memory for new array
		if(oldObj.typePtr)
			reAllocate(oldObj.capacity);

		//if the oldobj has a size then realloc just happend
		//and that means there is an array to put things into
		//otherwise the loop wont run
		for(int i = 0; i < oldObj.getSize(); ++i)			
			new(typePtr + i) T(oldObj.typePtr[i]);

		numOfElements = oldObj.numOfElements;
	}

	//assignment operator
	DynamicArray& operator=(const DynamicArray& right)
	{
		//if the user assigned the same obj to itself
		if(this == &right) 
			return *this;
	
		//deconstruct everything
		for(int i = 0; i < numOfElements; i++)
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
		
		for(int i = 0; i < right.numOfElements; ++i)
			new(typePtr + i) T(right.typePtr[i]);

		numOfElements = right.numOfElements;
		return *this;
	}

	void pushBack(const T& val)
	{
		//if first push/emplace allocate the first array
		if(!typePtr)
			reAllocate(DynamicArray::defaultCapacity);
	
		//if the array runs out of room make more room (1.5x as much)
		if(numOfElements >= capacity)
			reAllocate(capacity + capacity / 2);
		
		new(typePtr + numOfElements) T(val);
		numOfElements++;
	}

	void pushBack(T&& val)
	{
		//if first push/emplace allocate the first array
		if(!typePtr)
			reAllocate(DynamicArray::defaultCapacity);

		//if the array runs out of room make more room (1.5x as much)
		if(numOfElements >= capacity)
			reAllocate(capacity + capacity / 2);

		new(typePtr + numOfElements) T(std::move(val));
		numOfElements++;
	}

	template<typename... Types>
	T& emplaceBack(Types&&... args)
	{
		//if first push/emplace allocate the first array
		if(!typePtr)
			reAllocate(DynamicArray::defaultCapacity);

		//if the array runs out of room make more room (1.5x as much)
		if(numOfElements >= capacity)	
			reAllocate(capacity + capacity / 2);

		//placement new to construct item in array
		new(typePtr + numOfElements) T(std::forward<Types>(args)...);
		return typePtr[numOfElements++];	
	}

	void erase(size_t index)
	{	
		if(index >= 0 && index < numOfElements)
		{
			//destroy element at specified index
			typePtr[index].~T();
			
			//by default user expects array to be in the order they made it in.
			//So instead of taking the last element and putting it at typePtr[index]
			//I'm going to shift the entire vector over from the "right" by 1 spot
			for(uint32_t i=index,j=index+1; j<numOfElements; ++i, ++j)				
				typePtr[i] = std::move(typePtr[j]);		
			
			--numOfElements;
		}
	}

	void popBack()
	{
		//manually call destructor. If you were to pop an element
		//then push a new one in its place, then the resources the
		//old one may have owned never got destroyed/freed;	
		//same thing goes for erase() and clear()
		if(numOfElements > 0)			
			typePtr[--numOfElements].~T();		
	}

	void shrinkToFit()
	{
		if(typePtr)
		{
			if(!numOfElements)
			{
				::operator delete(typePtr, sizeof(T)*capacity);
				typePtr = nullptr;
			}
			else 			
				reAllocate(numOfElements);			
		}
	}

	void clear()
	{
		//if the type has its own resources to clean up, then destroy them
		for(uint32_t i = 0; i < numOfElements; i++)
			typePtr[i].~T();
		
		numOfElements = 0;
	}

	void reserve(size_t size)
	{
		if(size > capacity);
			reAllocate(size);
	}		
private:	
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
			for(uint32_t i = 0; i < numOfElements; i++)
				new(tempPtr + i) T(std::move(typePtr[i]));
		}
		
		//if the type has its own resources to clean up, then destroy them
		//(if first alloc then numOfElements is = 0 and loop wont run)
		for(int i = 0; i < numOfElements; i++)
			typePtr[i].~T();				 
		
		//delete old array
		//(deleting nullptr on first alloc is okay)
		::operator delete(typePtr, sizeof(T)*capacity);
		typePtr = tempPtr;
	}

};//class DynamicArray
}//namespace MYC (my containers)
#endif //ifdef DYNAMIC_ARRAY