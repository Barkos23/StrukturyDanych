#include <iostream>
#include <chrono>
#include <cstdio>
#include "mylist.h"
#include "myarray.h"
#include "prioritylist.h"
#include "priorityarray.h"

using namespace std;

template <typename T>
int* operations(T& queue, int elements, int* keys){
    int key = 0;
    string data;
    for(int i = 0; i < elements; i++){
        queue.enqueue(keys[i], to_string(i));
    }

    T queues[100];
    int* times = new int[5];

    for(int i=0; i < 100; i++){
        queues[i] = queue;
    }

    cout << "Liczba elementow:" << elements << endl;

    // Dodawanie
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        queues[i].enqueue(500, "nowy");
    } 
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    times[0] = duration.count()/100;
    cout << "Dodawanie do kolejki (srodkowy priorytet): " << times[0] << "ns" << endl;
    
    // queues[0].display();
    // cout << endl;

    // Usuwanie
    string removed;
    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        removed = queues[i].dequeue();
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    times[1] = duration.count()/100;
    cout << "Usuwanie z kolejki (ostatnio dodany): " << times[1] << "ns" << endl;

    // queues[0].display();
    // cout << endl;

    // Zwracanie rozmiaru
    int size;
    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        size = queues[i].size();
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    times[2] = duration.count()/100;
    cout << "Zwracanie rozmiaru: " << times[2] << "ns";
    cout << "   Rozmiar: " << size << endl;

    // queues[0].display();
    // cout << endl;

    // Zwracanie peek
    string peek;
    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        peek = queues[i].peek();
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    times[3] = duration.count()/100;
    cout << "Sprawdzanie peek: " << times[3] << "ns";
    cout << "   Peek: " << peek << endl;

    // queues[0].display();
    // cout << endl;

    // Zwracanie peek
    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        queues[i].updateKey("nowy", 501);
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    times[4] = duration.count()/100;
    cout << "Zmienianie priorytetu: " << times[4] << "ns" << endl;

    // queues[0].display();
    cout << endl << endl;

    return times;
};

int main() {
    srand(0);

    int elements[9] {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000};
    int** times_list = new int*[5];
    int** times_array = new int*[5];

    int* keys = new int[elements[8]];
    for(int i = 0; i < elements[8]; i++){
        keys[i] = rand() % 1000;
    }

    list::PriorityQueue queue_list;
    arr::PriorityQueue queue_array;

    cout << "Lista: " << endl;
    for(int i = 0; i < 9; i++){
        times_list[i] = operations(queue_list, elements[i], keys);
    }

    cout << endl << "Tablica: " << endl;
    for(int i = 0; i < 9; i++){
        times_array[i] = operations(queue_array, elements[i], keys);
    }

    cout << "Listy: " << endl;
    cout << "Liczba elementow;Dodawanie;Usuwanie;Rozmiar;Peek;Zmiana priorytetu" << endl;
    for(int i = 0; i < 9; i++){
        cout << elements[i];
        for(int j = 0; j < 5; j++){
            cout << ";" << times_list[i][j];
        }
        cout << endl;
    }
    
    cout << "Tablice: " << endl;
    cout << "Liczba elementow;Dodawanie;Usuwanie;Rozmiar;Peek;Zmiana priorytetu" << endl;
    for(int i = 0; i < 9; i++){
        cout << elements[i];
        for(int j = 0; j < 5; j++){
            cout << ";" << times_array[i][j];
        }
        cout << endl;
    }

    return 0;
}