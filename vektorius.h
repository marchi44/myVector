#include <iostream>
#include <stdexcept>

template <typename T>
class myVector {
    private:
    T* data;
    size_t _size;
    size_t _capacity;

    void resize(size_t newCapacity){
        T* newData = new T[newCapacity];
        for(size_t i = 0; i < _size; i++)
            newData[i] = std::move(data[i]);
        delete[] data;
        data = newData;
        _capacity = newCapacity;
    }

    public:
    //default konstruktorius
    myVector() :
        data(nullptr), _size(0), _capacity(0) {}
    
    //destruktorius
    ~myVector() {
        delete[] data;
        _size = 0;
        _capacity = 0;
    }
    
};