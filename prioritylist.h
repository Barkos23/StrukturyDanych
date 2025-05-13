#pragma once
#include "mylist.h"


namespace list{
    class PriorityQueue {
    private:
        SinglyLinkedList list;

    public:
        // Dodawanie elementu z zachowaniem kolejności (malejąco po priorytecie)
        void enqueue(int key, const string& data) {
            if (key < 0) {
                cout << "Priorytet musi byc >= 0\n";
                return;
            }
        
            // Lista pusta lub nowy element ma mniejszy priorytet niż pierwszy
            if (list.getHead() == nullptr || key < list.getHead()->key) {
                list.insertAtBeginning(key, data);
                return;
            }
        
            // Znalezienie odpowiedniego miejsca (pierwszego większego)
            Node* temp = list.getHead();
            int index = 0;
            while (temp->next != nullptr && temp->next->key <= key) {
                temp = temp->next;
                index++;
            }
            list.insertAtIndex(key, data, index);
        }        

        // Usuwanie elementu o najwyższym priorytecie (z początku listy)
        void dequeue() {
            list.deleteFromBeginning();
        }

        // Zwracanie elementu z najwyższym priorytetem (bez usuwania)
        string peek() {
            Node* head = list.getHead();
            if (head == nullptr) {
                throw runtime_error("Kolejka jest pusta");
            }
            return head->data + " (priorytet: " + to_string(head->key) + ")";
        }

        // Zmiana priorytetu istniejącego elementu
        void updateKey(const string& data, int newkey) {
            if (newkey < 0) {
                cout << "Nowy priorytet musi byc >= 0\n";
                return;
            }

            int index = list.search(data);
            if (index == -1) {
                cout << "Element \"" << data << "\" nie istnieje.\n";
                return;
            }

            list.deleteIndex(index);
            enqueue(newkey, data);
        }

        // Zwracanie liczby elementów
        int size() {
            int count = 0;
            Node* temp = list.getHead();
            while (temp != nullptr) {
                count++;
                temp = temp->next;
            }
            return count;
        }

        // Czy kolejka jest pusta
        bool isEmpty() {
            return list.getHead() == nullptr;
        }

        // Wyświetlanie zawartości kolejki
        void display() {
            list.display();
        }

        // Czyszczenie kolejki
        void clear() {
            list.clear();
        }
    };
}