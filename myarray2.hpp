#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Element {
    public:
    int key;
    T data;

    Element(int k = 0, const T& d = T()) : key(k), data(d) {}
};

template <typename T>
class DynamicArray {
private:
    int size;
    int capacity;
    T* data;

    void resize(int newCapacity) {
        if (newCapacity == capacity) return;

        T* newData = new T[newCapacity];
        int elementsToCopy = (size < newCapacity) ? size : newCapacity;
    
        for (int i = 0; i < elementsToCopy; i++)
            newData[i] = data[i];
    
        delete[] data;
        data = newData;
        capacity = newCapacity;
    
        if (newCapacity < size)
            size = newCapacity;
    }

public:
    DynamicArray() : size(0), capacity(50) {
        data = new T[capacity];
    }

    DynamicArray(int n) : size(n), capacity(n) {
        data = new T[capacity];
        for (int i = 0; i < size; i++)
            data[i] = T();
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    DynamicArray& operator=(DynamicArray other) {
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        std::swap(data, other.data);
        return *this;
    }
    

    void push_back(T value) {
        if (size >= capacity)
            resize(capacity == 0 ? 1 : capacity * 2);
        data[size++] = value;
    }

    void push_front(T value) {
        if (size >= capacity)
            resize(capacity == 0 ? 1 : capacity * 2);
        for (int i = size; i > 0; i--)
            data[i] = data[i - 1];
        data[0] = value;
        size++;
    }

    void insert_at(T value, int index) {
        if (index < 0 || index > size) {
            cout << "Niepoprawy indeks" << endl;
            return;
        } 
        if (size >= capacity)
            resize(capacity == 0 ? 1 : capacity * 2);
        for (int i = size; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        size++;
    }

    void pop_back() {
        if (size > 0) size--;
    }

    void pop_front() {
        if (size == 0) return;
        for (int i = 1; i < size; i++)
            data[i - 1] = data[i];
        size--;
    }

    void remove_at(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index + 1; i < size; i++)
            data[i - 1] = data[i];
        size--;
    }

    int search(T value) const {
        for (int i = 0; i < size; i++)
            if (data[i] == value)
                return i;
        return -1;
    }

    void print() const {
        for (int i = 0; i < size; ++i)
            cout << i << "-" << data[i] << ' ';
        cout << endl;
    }

    T& operator[](int index) {
    return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    T* getData() const {
        return data;
    }
};
