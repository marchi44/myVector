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

    T& operator[] (size_t index) {
        return data[index];
    }

    const T& operator[] (size_t index) const {
        return data[index];
    }

    void push_back(const T& value){
        if(_size == _capacity){
            size_t newCapacity = (_capacity == 0) ? 1 : _capacity * 2;
            resize(newCapacity);
        }
        data[_size++] = value;
    }

    void pop_back(){
        if(_size > 0)
            --_size;
    }

    size_t size() const {return _size};

    size_t capacity() const {return _capacity};

    bool empty() const {return _size == 0};

    void clear() {
        _size = 0;
    }
};