#pragma once
#include "myarray.h"

namespace arr{
    class PriorityQueue {
    private:
        DynamicElementArray arr;

    public:
        void enqueue(int key, const string& data) {
            if (key < 0) {
                cout << "Priorytet musi byc >= 0\n";
                return;
            }
            arr.insertSorted({key, data});
        }

        string dequeue() {
            if (arr.isEmpty()) {
                cout << "Kolejka jest pusta\n";
                return;
            }
            string data;
            if (arr.isEmpty())
                throw runtime_error("Kolejka jest pusta");
            Element e = arr.at(0);
            data = e.data + " (priorytet: " + to_string(e.key) + ")";
            arr.removeAt(0);
            return data;
        }

        string peek() {
            if (arr.isEmpty())
                throw runtime_error("Kolejka jest pusta");
            Element e = arr.at(0);
            return e.data + " (priorytet: " + to_string(e.key) + ")";
        }

        void updateKey(const string& data, int newkey) {
            if (newkey < 0) {
                cout << "Nowy priorytet musi byc >= 0\n";
                return;
            }
            
            int index = arr.search(data);
            if (index == -1) {
                cout << "Element \"" << data << "\" nie istnieje.\n";
                return;
            }
            arr.removeAt(index);
            enqueue(newkey, data);
        }

        int size() {
            return arr.getSize();
        }

        bool isEmpty() {
            return arr.isEmpty();
        }

        void display() {
            arr.print();
        }

        void clear() {
            arr.clear();
        }
    };
}
