#pragma once

//templated class as a wrapper for a 
//default stack allocated, statically sized array (std::array<T, size_t>)
//iterator not necessary
template <class T, size_t size>
class StaticArray
{
private:
    T elems[size];
public:
    constexpr size_t getSize() const {return size;}

    T& operator[](size_t index) {return elems[index];}
    const T& operator[](size_t index) const {return elems[index];}

    //helper method to fill the array with a specific value
    void fill(const T& value) 
    {
        for(int i = 0; i < size; i++)
        {
            elems[i] = value;
        }
    }

    T* data() {return elems;}
    const T* data() const {return elems;}
};