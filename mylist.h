#pragma once

#include <iostream>

using namespace std;

class Node {
    public:
        int key;
        string data; 
        Node* next;
    
        Node(int p, const string& d) {
            key = p;
            data = d;
            next = nullptr;
        }
    };
    
class SinglyLinkedList {
    private:
        Node* head;
    
    public:
        SinglyLinkedList() {
            head = nullptr;
        }
    
        ~SinglyLinkedList() {
            clear();
        }
        
        SinglyLinkedList(const SinglyLinkedList& other) {
            if (other.head == nullptr) {
                head = nullptr;
                return;
            }

            head = new Node(other.head->key, other.head->data);
            Node* current = head;
            Node* otherCurrent = other.head->next;

            while (otherCurrent != nullptr) {
                current->next = new Node(otherCurrent->key, otherCurrent->data);
                current = current->next;
                otherCurrent = otherCurrent->next;
            }
        }


        SinglyLinkedList& operator=(const SinglyLinkedList& other) {
            if (this == &other) return *this; 
        
            clear();
        
            if (other.head == nullptr) {
                head = nullptr;
                return *this;
            }
        
            head = new Node(other.head->key, other.head->data);
            Node* current = head;
            Node* otherCurrent = other.head->next;
        
            while (otherCurrent != nullptr) {
                current->next = new Node(otherCurrent->key, otherCurrent->data);
                current = current->next;
                otherCurrent = otherCurrent->next;
            }
        
            return *this;
        }        

        void insertAtBeginning(int key, string data) {
            if(key < 0){
                return;
            }
            
            Node* newNode = new Node(key, data);
            newNode->next = head;
            head = newNode;
        }
    
        void insertAtEnd(int key, string data) {
            if(key < 0){
                return;
            }
            
            Node* newNode = new Node(key, data);
            if (head == nullptr) {
                head = newNode;
                return;
            }
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    
        void insertAtIndex(int key, string data, int index) {
            if(key < 0){
                return;
            }
            
            Node* newNode = new Node(key, data);
            if (head == nullptr) {
                if (index == 0) {
                    head = newNode;
                } else {
                    delete newNode;
                }
                return;
            }
            Node* temp = head;
            int currentIndex = 0;
    
            while (temp != nullptr && currentIndex < index) {
                temp = temp->next;
                currentIndex++;
            }
    
            if (temp == nullptr) {
                std::cerr << "Indeks poza zakresem." << std::endl;
                delete newNode;
                return;
            }
    
            newNode->next = temp->next;
            temp->next = newNode;
        }
    
        void deleteFromBeginning() {
            if (head == nullptr) {
                cout << "Lista jest pusta." << endl;
                return;
            }
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    
        void deleteFromEnd() {
            if (head == nullptr) {
                cout << "Lista jest pusta." << endl;
                return;
            }
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
                return;
            }
    
            Node* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    
        void deleteIndex(int index) {
            if (head == nullptr) {
                cout << "Lista jest pusta." << endl;
                return;
            }
        
            if (index == 0) {
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }
        
            Node* temp = head;
            int currentIndex = 0;
        
            while (temp != nullptr && currentIndex < index - 1) {
                temp = temp->next;
                currentIndex++;
            }
        
            if (temp == nullptr || temp->next == nullptr) {
                cout << "Indeks poza zakresem." << endl;
                return;
            }
        
            Node* nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            delete nodeToDelete;
        }
        
        int search(string data) {
            Node* temp = head;
            int i = 0;
            while (temp != nullptr) {
                if (temp->data == data) return i;
                temp = temp->next;
                i++;
            }
            return -1;
        }
    
        void display() {
            if (head == nullptr) {
                cout << "Lista jest pusta." << endl;
                return;
            }
    
            Node* temp = head;
            while (temp != nullptr) {
                cout << temp->key << ":" << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    
        void clear() {
            while (head != nullptr) {
                deleteFromBeginning();
            }
        }

        int getKey(const string& data) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data == data)
                    return temp->key;
                temp = temp->next;
            }
            cout << "Element \"" << data << "\" nie został znaleziony." << endl;
            return -1;
        }

        Node* getHead() {
            return head;
        }
        
    };
    