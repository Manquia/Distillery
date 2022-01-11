#pragma once
#include <iostream>
struct Vec4;

std::ostream& operator<<(std::ostream&, const Vec4&);

//sample struct just for tests
struct Vec4
{
	int x, y, z, w;
	int* memoryBlock;

	Vec4(int, int, int, int);	        //param constructor
	Vec4();								//default constructor
	~Vec4();							//destructor
	Vec4(const Vec4&);					//copy constructor
	Vec4(Vec4&&) noexcept;				//move constructor
	Vec4& operator=(Vec4&&) noexcept;   //move assignment operator
	Vec4& operator=(const Vec4&);		//copy assignment operator
	bool operator==(const Vec4&) const;	//comparison operator
};