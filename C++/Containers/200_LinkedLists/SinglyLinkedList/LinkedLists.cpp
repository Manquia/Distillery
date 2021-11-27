#include "SinglyLinkedList.h"
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
};

int main()
{
	LinkedList<Vec4> list;


	return 0;
}