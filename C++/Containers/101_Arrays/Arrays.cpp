#include "DynamicArray.h"
#include "StaticArray.h"
#include <iostream>

//sample class for tests
class Vec4
{
public:

	int x, y, z, w;
	int* memoryBlock;

	Vec4(int x, int y, int z, int w)
		:x(x), y(y), z(z), w(w)
	{
		std::cout << "param construct\n";
		memoryBlock = new int[10];
	}

	Vec4() : x(0), y(0), z(0), w(0) 
	{
		std::cout << "default construct\n";
		memoryBlock = new int[10];
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec4& obj)
	{
		std::cout << obj.x << obj.y << obj.z << obj.w << '\n';
		return os;
	}

	~Vec4()
	{
		std::cout << "destroyed:" << *this << "and memory block at location:" << memoryBlock <<"\n";
		delete[] memoryBlock;
	}
			
	//copy constructor
	Vec4(const Vec4& oldObj) 
		: x(oldObj.x), y(oldObj.y), z(oldObj.z), w(oldObj.w)
	{
		std::cout << "copy construct\n";
		memoryBlock = new int[10];
		memcpy(memoryBlock, oldObj.memoryBlock, (10*sizeof(int)));
	}

	//move constructor
	Vec4(Vec4&& oldObj) noexcept
		: x(oldObj.x), y(oldObj.y), z(oldObj.z), w(oldObj.w)
	{
		std::cout << "move construct\n";
		memoryBlock = oldObj.memoryBlock;
		oldObj.memoryBlock = nullptr;

		oldObj.x = 0;
		oldObj.y = 0;
		oldObj.z = 0;
		oldObj.w = 0;
	}

	//move assignment operator
	Vec4& operator=(Vec4&& oldObj) noexcept
	{
		std::cout << "move asign\n";
		memoryBlock = oldObj.memoryBlock;
		oldObj.memoryBlock = nullptr;

		x = oldObj.x;
		y = oldObj.y;
		z = oldObj.z;
		w = oldObj.w;

		oldObj.x = 0;
		oldObj.y = 0;
		oldObj.z = 0;
		oldObj.w = 0;
		
		return *this;
	}

	//asignment operator
	Vec4& operator=(Vec4& oldObj)
	{
		std::cout << "copy asign\n";
		memoryBlock = new int[10];
		memcpy(memoryBlock, oldObj.memoryBlock, sizeof(int)*10);

		x = oldObj.x;
		y = oldObj.y;
		z = oldObj.z;
		w = oldObj.w;

		return *this;
	}

	//comparison operator
	bool operator==(const Vec4& right) const 
	{//this ignores comparing the heap allocations as they're just there for testing
		return (
				right.x == this->x &&
				right.y == this->y &&
				right.z == this->z &&
				right.w == this->w
			   );
	}
};

int main()
{
	DynamicArray<Vec4> dynamicArray;

	StaticArray<Vec4, 5> staticArray;

	DynamicArray<Vec4> dynamicArray2;

	dynamicArray2 = std::move(dynamicArray);

    return 0;
}