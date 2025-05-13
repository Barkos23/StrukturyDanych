#pragma once
#include <iostream>
using namespace std;

class Element {
    public:
    int key;
    string data;
};

class DynamicElementArray {
private:
    Element* data;
    int size;
    int capacity;

    void resize(int newCapacity) {
        if (newCapacity == capacity) return;
        Element* newData = new Element[newCapacity];
        for (int i = 0; i < size && i < newCapacity; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
        if (size > newCapacity) size = newCapacity;
    }

public:
    DynamicElementArray() : size(0), capacity(50) {
        data = new Element[capacity];
    }

    ~DynamicElementArray() {
        delete[] data;
    }

    DynamicElementArray(const DynamicElementArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new Element[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    DynamicElementArray& operator=(const DynamicElementArray& other) {
        if (this == &other)
            return *this;

        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new Element[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];

        return *this;
    }

    void insertSorted(const Element& el) {
        if (size >= capacity)
            resize(capacity * 2);
        int i = 0;
        while (i < size && data[i].key <= el.key)
            ++i;
        for (int j = size; j > i; --j)
            data[j] = data[j - 1];
        data[i] = el;
        size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index + 1; i < size; ++i)
            data[i - 1] = data[i];
        size--;
    }

    int search(const string& val) const {
        for (int i = 0; i < size; ++i)
            if (data[i].data == val)
                return i;
        return -1;
    }

    Element& at(int index) {
        return data[index];
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        size = 0;
    }

    void print() const {
        for (int i = 0; i < size; ++i)
            cout << data[i].key << ":" << data[i].data << " -> ";
        cout << "NULL" << endl;
    }
};
