#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>

#include "myarray2.hpp"
#include "mylist2.hpp"
#include "hashtable.hpp"

using namespace std;
using namespace chrono;

string findBest(HashTable table, int size)
{
    int elements = 0;
    pair min(0, -1);
    for(int i = 0; i < size; i++){
        Node* temp = table[i].getHead();
        while (temp != nullptr){
            elements++;
            temp = temp->next;
        }
        
        if((elements < min.second && elements != 0) || min.second < 1){
            min.first = i;
            min.second = elements;
        }
        elements = 0;
    }
    
    // cout << endl << "Najlepsza komorka : " << min.first << endl;
    // cout << "Liczba elementow: " << min.second << endl;

    Node* best = table[min.first].getHead();
    return best->data;
}

string findWorst(HashTable table, int size)
{
    int elements = 0;
    pair max(0, -1);
    for(int i = 0; i < size; i++){
        Node* temp = table[i].getHead();
        while (temp != nullptr){
            elements++;
            temp = temp->next;
        }
        
        if(elements > max.second && elements != 0){
            max.first = i;
            max.second = elements;
        }
        elements = 0;
    }
    
    // cout << endl << "Najgorsza komorka : " << max.first << endl;
    // cout << "Liczba elementow: " << max.second << endl;

    Node* temp = table[max.first].getHead();
    Node* worst = table[max.first].getHead();
    while (temp != nullptr){
            worst = temp;
            temp = temp->next;
    }
    return worst->data;
}

int* operations(HashFunction hashFunc, int size, int elements){
    int* times = new int[6];
    int tests = 1000;
    srand(0);
    HashTable* functions = new HashTable[tests];

    for(int i=0; i < tests; i++){
        functions[i] = HashTable(size, hashFunc);
    }

    cout << "Rozmiar: " << elements << endl;  

    // Uzupełnianie

    for(int i=0; i < tests; i++){
        for(int j=0; j<elements; j++){
            functions[i].insert(to_string(j));
        }
    }

    // Optymistyczny

    // functions[0].print();

    string best = findBest(functions[0], size);
    cout << "=======================================" << endl;

        // Usuwanie

    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < tests; i++){
        functions[i].remove(best);
    } 
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    times[3] = duration.count()/tests;
    cout << "Usuwanie optymistycznie: " << times[3] << "ns" << endl;

    // functions[0].print(); 

        // Dodawanie

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < tests; i++){
        functions[i].insert(best);
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    times[0] = duration.count()/tests;
    cout << "Dodawanie optymistycznie: " << times[0] << "ns" << endl;
    
    // functions[0].print(); 

    // Pesymistyczny
    string worst = findWorst(functions[0], size);
    cout << "=======================================" << endl;
    // cout << "Najgorszy: " << worst << endl;

        // Usuwanie

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < tests; i++){
        functions[i].remove(worst);
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    times[5] = duration.count()/tests;
    cout << "Usuwanie pesymistyczne: " << times[5] << "ns" << endl;
    // functions[0].print(); 

        // Dodawanie

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < tests; i++){
        functions[i].insert(worst);
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    times[2] = duration.count()/tests;
    cout << "Dodawanie pesymistyczne: " << times[2] << "ns" << endl;
    // functions[0].print();  

    // Sredni
        // Dodawanie

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < tests; i++){
        functions[i].insert(to_string(rand() % elements + elements));
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    times[1] = duration.count()/tests;
    cout << "Dodawanie srednie: " << times[1] << "ns" << endl;
    // functions[0].print(); 

        // Usuwanie

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < tests; i++){
        functions[i].remove(to_string(rand() % elements));
    } 
    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    times[4] = duration.count()/tests;
    cout << "Usuwanie srednie: " << times[4] << "ns" << endl;
    // functions[0].print(); 

    cout << "########################################################" << endl;

    return times;
}

int main() {
    int*** full_times = new int**[3];
    int** timesSum = new int*[5];
    int** timesDJB2 = new int*[5];
    int** timesSDBM = new int*[5];

    int size = 32;

    int elements[5] = {250, 500, 750, 1000, 1250};
    string functions[3] = {"SumHash", "DJB2Hash", "SDMBHash"};

    cout << "Tablica dla SumHash: " << endl;
    for(int i = 0; i < 5; i++) {
        timesSum[i] = operations(hashSum, size, elements[i]);
    }
    full_times[0] = timesSum;
    cout << endl << endl;


    cout << "Tablica dla DJB2Hash: " << endl;
    for(int i = 0; i < 5; i++) {
        timesDJB2[i] = operations(hashDJB2, size, elements[i]);
    }
    full_times[1] = timesDJB2;
    cout << endl << endl;


    cout << "Tablica dla SDMBHash: " << endl;
    for(int i = 0; i < 5; i++) {
        timesSDBM[i] = operations(hashSDBM, size, elements[i]);
    }
    full_times[2] = timesSDBM;
    cout << endl << endl;

    
    for(int i = 0; i < 3; i++){
        cout << functions[i] << ": " << endl;
        cout << "Liczba elementow;Dodawanie opt.;Dodawanie sr;Dodawanie pes.;Usuwanie opt.;Usuwanie sr.;Usuwanie pes." << endl;
        for(int j = 0; j < 5; j++){
            cout << elements[j];
            for(int k = 0; k < 6; k++){
                cout << ";" << full_times[i][j][k];
            }
            cout << endl;
        }
        cout << endl << endl;
    }

    return 0;
}
