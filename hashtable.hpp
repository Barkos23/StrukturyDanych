#include <iostream>
#include "myarray2.hpp"
#include "mylist2.hpp"


size_t hashSum(const string& key, size_t size) {
    size_t hash = 0;
    for (char c : key) hash += c;
    return hash % size;
}

size_t hashDJB2(const string& key, size_t size) {
    size_t hash = 5381;
    for (char c : key) hash = ((hash << 5) + hash) + c;
    return hash % size;
}

size_t hashSDBM(const string& key, size_t tableSize) {
    size_t hash = 0;
    for (char c : key) {
        hash = static_cast<size_t>(c) + (hash << 6) + (hash << 16) - hash;
    }
    return hash % tableSize;
}


typedef size_t(*HashFunction)(const string&, size_t);

class HashTable {
private:
    DynamicArray<SinglyLinkedList> table;
    HashFunction hashFunction;
    size_t tableSize;

public:
    HashTable(size_t size, HashFunction func)
        : table(size), hashFunction(func), tableSize(size) {}

    HashTable(const HashTable& other)
        : table(other.table), hashFunction(other.hashFunction), tableSize(other.tableSize) {}

    HashTable()
    : table(1), hashFunction([](const std::string&, size_t) -> unsigned long long { return 0; }), tableSize(1) {}

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            table = other.table;
            hashFunction = other.hashFunction;
            tableSize = other.tableSize;
        }
        return *this;
    }

    SinglyLinkedList& operator[](size_t index) {
        return table[index];
    }

    ~HashTable() = default;

    void insert(const string& key) {
        size_t index = hashFunction(key, tableSize);
        if (table[index].search(key) == -1) { 
            table[index].insertAtEnd(key);
        }
    }

    void remove(const string& key) {
        size_t index = hashFunction(key, tableSize);
        int pos = table[index].search(key);
        if (pos != -1) {
            table[index].deleteIndex(pos);
        }
    }

    bool contains(const string& key) const {
        size_t index = hashFunction(key, tableSize);
        return table[index].search(key) != -1;
    }

    void print() const {
        for (size_t i = 0; i < tableSize; ++i) {
            cout << "[" << i << "]: ";
            table[i].display();
        }
        cout << endl;
    }
};
