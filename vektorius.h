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

    void swap(myVector& other) noexcept {
        std::swap(data, other.data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    public:
    //default konstruktorius
    myVector() :
        data(nullptr), _size(0), _capacity(0) {}
    
    // Konstruktorius su zinomu vektoriaus dydziu
    explicit myVector(size_t n) : _size(n), _capacity(n) {
        if (n > 0) {
            data = new T[n];
        } else {
            data = nullptr;
        }
    }

    // Konstruktorius jei zinomas vektoriaus dydis ir naudotojas nori ji uzpildyti kazkokia reiksme
    explicit myVector(size_t n, const T& initialValue) : _size(n), _capacity(n) {
        if (n > 0) {
            data = new T[n];
            for (size_t i = 0; i < n; i++) {
                data[i] = initialValue;
            }
        } else {
            data = nullptr;
        }
    }
    
    //destruktorius
    ~myVector() {
        delete[] data;
        _size = 0;
        _capacity = 0;
    }

    //copy konstruktoriai
    myVector(const myVector& other) : _size(other._size), _capacity(other._capacity) {
        if (other._capacity > 0) {
            data = new T[other._capacity];
            for (size_t i = 0; i < _size; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    //universalus copy/move priskyrimo operatorius
    myVector& operator=(myVector other) { 
        this->swap(other);
        return *this;
    }

    //move konstruktoriai
    myVector(myVector&& other) noexcept 
    : data(other.data), _size(other._size), _capacity(other._capacity) {
        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    T& at(size_t index) {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& at(const size_t index) const{
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
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

    T& front() {
        return data[0];
    }
    const T& front() const{
        return data[0];
    }

    T& back() {
        return data[_size - 1];
    }
    const T& back() const{
        return data[_size - 1];
    }

    T* begin() {
        return data;
    }
    const T* begin() const{
        return data;
    }

    T* end() {
        return data + _size;
    }
    const T* end() const{
        return data + _size;
    }

    void reserve(size_t newCapacity) {
        if(newCapacity > _capacity)
            resize(newCapacity);
    }
};