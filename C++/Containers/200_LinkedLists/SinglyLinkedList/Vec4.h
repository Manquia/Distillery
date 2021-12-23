#pragma once
#include <iostream>

//sample class just for tests
//just in a .h for convienence
class Vec4
{
public:

	int x, y, z, w;
	int* memoryBlock;

	Vec4(int x, int y, int z, int w)
		:x(x), y(y), z(z), w(w)
	{
		std::cout << "Vec4 param construct\n";
		memoryBlock = new int[10];
	}

	Vec4() : x(0), y(0), z(0), w(0) 
	{
		std::cout << "Vec4 default construct\n";
		memoryBlock = new int[10];
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec4& obj)
	{
		std::cout << obj.x << obj.y << obj.z << obj.w;
		return os;
	}

	~Vec4()
	{
		std::cout << "Vec4 destroyed:" << *this << "and memory block at location:" << memoryBlock <<"\n";
		delete[] memoryBlock;
	}
			
	//copy constructor
	Vec4(const Vec4& oldObj) 
		: x(oldObj.x), y(oldObj.y), z(oldObj.z), w(oldObj.w)
	{
		std::cout << "Vec4 copy construct\n";
		memoryBlock = new int[10];
		memcpy(memoryBlock, oldObj.memoryBlock, (10*sizeof(int)));
	}

	//move constructor
	Vec4(Vec4&& oldObj) noexcept
		: x(oldObj.x), y(oldObj.y), z(oldObj.z), w(oldObj.w)
	{
		std::cout << "Vec4 move construct\n";
		memoryBlock = oldObj.memoryBlock;
		oldObj.memoryBlock = nullptr;

		oldObj.x = 0;
		oldObj.y = 0;
		oldObj.z = 0;
		oldObj.w = 0;
	}

	//move assignment operator
	Vec4& operator=(Vec4&& right) noexcept
	{
		if(this == &right)
			return *this;

		std::cout << "Vec4 move asign\n";
		delete[] memoryBlock;
		memoryBlock = right.memoryBlock;
		right.memoryBlock = nullptr;

		x = right.x;
		y = right.y;
		z = right.z;
		w = right.w;

		right.x = 0;
		right.y = 0;
		right.z = 0;
		right.w = 0;
		
		return *this;
	}

	//asignment operator
	Vec4& operator=(const Vec4& right)
	{
		if(this == &right)
			return *this;

		std::cout << "Vec4 copy asign\n";
		memoryBlock = new int[10];
		memcpy(memoryBlock, right.memoryBlock, sizeof(int)*10);

		x = right.x;
		y = right.y;
		z = right.z;
		w = right.w;

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