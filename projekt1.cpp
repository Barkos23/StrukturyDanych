#include <iostream>
#include <chrono>

using namespace std;

// Pojedynczy węzeł listy
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Lista jednokierunkowa
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

    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
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

    void insertAtIndex(int value, int index) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            if (index == -1) {
                head = newNode;
            } else {
                cout << "Indeks poza zakresem (lista pusta)." << endl;
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
    
    int search(int value) {
        Node* temp = head;
        int i = 0;
        while (temp != nullptr) {
            if (temp->data == value) return i;
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
        cout << "Head: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void clear() {
        while (head != nullptr) {
            deleteFromBeginning();
        }
    }
};

// Tablica dynamiczna
class DynamicArray {
private:
    int* data;
    int size;
    int capacity;

    void resize(int newCapacity) {
        if (newCapacity == capacity) return;

        int* newData = new int[newCapacity];
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
        data = new int[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
        return *this;
    }

    void push_back(int value) {
        if (size >= capacity)
            resize(capacity == 0 ? 1 : capacity * 2);
        data[size++] = value;
    }

    void push_front(int value) {
        if (size >= capacity)
            resize(capacity == 0 ? 1 : capacity * 2);
        for (int i = size; i > 0; i--)
            data[i] = data[i - 1];
        data[0] = value;
        size++;
    }

    void insert_at(int value, int index) {
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

    int search(int value) const {
        for (int i = 0; i <= size; i++)
            if (data[i] == value)
                return i;
        return -1;
    }

    void print() const {
        for (int i = 0; i < size; ++i)
            cout << i << "-" << data[i] << ' ';
        cout << endl;
    }
};

//Tworzenie i operacje na listach
int* list(int liczbaList, int rozmiarList) {
    cout << "Liczba elementow: " << rozmiarList << endl;
    
    SinglyLinkedList* list = new SinglyLinkedList[liczbaList]; //tablica z obiektami list do zwiększenia dokładności pomiarów

    int* times = new int[7];

    for (int i = 0; i < liczbaList; i++) {
        for (int j = rozmiarList-1; j >= 0; j--) {
            list[i].insertAtBeginning(j);
        }
    }

    // for(int i = 0; i < liczbaList; i++) {
    //     cout << endl << "Lista nr" << i << ":" << endl;
    //     list[i].display();
    // }

    // list[0].display();

    cout << "=======================================" << endl;

    cout << "Szukanie wartosci w liscie" << endl << endl;

    //Wyszukiwanie wartości
    auto start_search = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaList; i++) {
        list[i].search(rozmiarList/2);
    }
    auto end_search = chrono::high_resolution_clock::now();
    auto duration_search = chrono::duration_cast<std::chrono::nanoseconds>(end_search - start_search);

    times[6] = duration_search.count()/liczbaList;
    cout << "Czas szukania: " << times[6] << " ns" << endl;
    cout << "Indeks wezla z wartoscia 1: " << list[0].search(1) << endl;
    cout << "Indeks wezla z wartoscia 4999: " << list[0].search(4999) << endl;
    cout << "Indeks wezla z wartoscia 14999: " << list[0].search(14999) << endl;

    cout << "-----------------------------------" << endl;

    cout << "Usuwanie z listy" << endl << endl;

    //Usuwanie z początku
    auto start_delB = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaList; i++) {
        list[i].deleteFromBeginning();
    }
    auto end_delB = chrono::high_resolution_clock::now();
    auto duration_delB = chrono::duration_cast<std::chrono::nanoseconds>(end_delB - start_delB);

    times[0] = duration_delB.count()/liczbaList;
    cout << "Czas usuwania z poczatku: " << times[0] << " ns" << endl;

    //Usuwanie z końca
    auto start_delE = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaList; i++) {
        list[i].deleteFromEnd();
    }
    auto end_delE = chrono::high_resolution_clock::now();
    auto duration_delE = chrono::duration_cast<std::chrono::nanoseconds>(end_delE - start_delE);

    times[1] = duration_delE.count()/liczbaList;
    cout << "Czas usuwania z konca: " << times[1] << " ns" << endl;

    //Usuwanie po indeksie
    auto start_delI = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaList; i++) {
        list[i].deleteIndex(rozmiarList/2);
    }
    auto end_delI = chrono::high_resolution_clock::now();
    auto duration_delI = chrono::duration_cast<std::chrono::nanoseconds>(end_delI - start_delI);

    times[2] = duration_delI.count()/liczbaList;
    cout << "Czas usuwania indeksu: " << times[2] << " ns" << endl;
    cout << "-----------------------------------";

    
    cout << endl << "Dodawanie do listy" << endl << endl;

    //Dodawanie na początek
    auto start_insB = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaList; i++) {
        list[i].insertAtBeginning(200);
    }
    auto end_insB = chrono::high_resolution_clock::now();
    auto duration_insB = chrono::duration_cast<std::chrono::nanoseconds>(end_insB - start_insB);

    times[3] = duration_insB.count()/liczbaList;
    cout << "Czas dodawania na poczatek: " << times[3] << " ns" << endl;

    //Dodawanie na koniec
    auto start_insE = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaList; i++) {
        list[i].insertAtEnd(100);
    }
    auto end_insE = chrono::high_resolution_clock::now();
    auto duration_insE = chrono::duration_cast<std::chrono::nanoseconds>(end_insE - start_insE);

    times[4] = duration_insE.count()/liczbaList;
    cout << "Czas dodawania na koniec: " << times[4] << " ns" << endl;

    //Dodawanie po indeksie
    auto start_insI = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaList; i++) {
        list[i].insertAtIndex(500,rozmiarList/2);
    }
    auto end_insI = chrono::high_resolution_clock::now();
    auto duration_insI = chrono::duration_cast<std::chrono::nanoseconds>(end_insI - start_insI);

    times[5] = duration_insI.count()/liczbaList;
    cout << "Czas dodawania po indeksie: " << times[5] << " ns" << endl;

    cout << "=======================================" << endl;
    cout << endl << endl;

    for(int i = 0; i < liczbaList; i++) {
        list[i].clear();
    }

    delete[] list;
    return times;
}

//Tworzenie i operacje na tablicach
int* table(int liczbaTablic, int rozmiarTablic) {
    cout << "Liczba elementow: " << rozmiarTablic << endl;

    DynamicArray* table = new DynamicArray[liczbaTablic]; //tablica z obiektami tablic do zwiększenia dokładności pomiarów

    int* times = new int[7];

    for (int i = 0; i < liczbaTablic; i++) {
        for (int j = 0; j < rozmiarTablic; j++) {
            table[i].push_back(j);
        }
    }

    // for (int i = 0; i < liczbaTablic; i++) {
    //     cout << "Tablica " << i << ": ";
    //     table[i].print();
    // }

    // table[0].print();

    cout << "=======================================" << endl;
    
    cout << endl << "Szukanie wartosci w tablicy" << endl << endl;

    //Szukanie wartości
    auto start_search = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaTablic; i++) {
        table[i].search(rozmiarTablic/2);
    }
    auto end_search = chrono::high_resolution_clock::now();
    auto duration_search = chrono::duration_cast<std::chrono::nanoseconds>(end_search - start_search);

    times[6] = duration_search.count()/liczbaTablic;
    cout << "Czas szukania: " << times[6] << " ns" << endl;
    cout << "Indeks komorki z wartoscia 1: " << table[0].search(1) << endl;
    cout << "Indeks komorki z wartoscia 4999: " << table[0].search(4999) << endl;
    cout << "Indeks komorki z wartoscia 14999: " << table[0].search(14999) << endl;

    cout << "-----------------------------------" << endl;
    cout << "Usuwanie z tablicy" << endl << endl;

    //Usuwanie z początku
    auto start_delB = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaTablic; i++) {
        table[i].pop_front();
    }
    auto end_delB = chrono::high_resolution_clock::now();
    auto duration_delB = chrono::duration_cast<std::chrono::nanoseconds>(end_delB - start_delB);

    times[0] = duration_delB.count()/liczbaTablic;
    cout << "Czas usuwania z poczatku: " << times[0] << " ns" << endl;

    //Usuwanie z końca
    auto start_delE = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaTablic; i++) {
        table[i].pop_back();
    }
    auto end_delE = chrono::high_resolution_clock::now();
    auto duration_delE = chrono::duration_cast<std::chrono::nanoseconds>(end_delE - start_delE);

    times[1] = duration_delE.count()/liczbaTablic;
    cout << "Czas usuwania z konca: " << times[1] << " ns" << endl;

    //Usuwanie z indeksu
    auto start_delI = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaTablic; i++) {
        table[i].remove_at(rozmiarTablic/2);
    }
    auto end_delI = chrono::high_resolution_clock::now();
    auto duration_delI = chrono::duration_cast<std::chrono::nanoseconds>(end_delI - start_delI);

    times[2] = duration_delI.count()/liczbaTablic;
    cout << "Czas usuwania indeksu: " << times[2] << " ns" << endl;
    cout << "-----------------------------------" << endl;



    cout << "Dodawanie do tablicy" << endl << endl;

    //Dodawanie na początek
    auto start_insB = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaTablic; i++) {
        table[i].push_front(200);
    }
    auto end_insB = chrono::high_resolution_clock::now();
    auto duration_insB = chrono::duration_cast<std::chrono::nanoseconds>(end_insB - start_insB);

    times[3] = duration_insB.count()/liczbaTablic;
    cout << "Czas dodawania na poczatek: " << times[3] << " ns" << endl;

    //Dodawanie na koniec
    auto start_insE = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaTablic; i++) {
        table[i].push_back(100);
    }
    auto end_insE = chrono::high_resolution_clock::now();
    auto duration_insE = chrono::duration_cast<std::chrono::nanoseconds>(end_insE - start_insE);

    times[4] = duration_insE.count()/liczbaTablic;
    cout << "Czas dodawania na koniec: " << times[4] << " ns" << endl;

    //Dodawanie po indeksie
    auto start_insI = chrono::high_resolution_clock::now(); 
    for(int i = 0; i < liczbaTablic; i++) {
        table[i].insert_at(500, rozmiarTablic/2);
    }
    auto end_insI = chrono::high_resolution_clock::now();
    auto duration_insI = chrono::duration_cast<std::chrono::nanoseconds>(end_insI - start_insI);

    times[5] = duration_insI.count()/liczbaTablic;
    cout << "Czas dodawania po indeksie: " << times[5] << " ns" << endl;

    cout << "=======================================" << endl;
    cout << endl << endl;

    delete[] table;
    return times;
}

int main() {
    int struct_number = 500; //liczba list lub tablic do badań - dla większej dokładności pomiaru
    cout << "---------------------------------------------------------------------------------------" << endl;

    int* elements_number = new int[16]; //tablica z liczbą elementów tablic/list - do porównywania czasów
    elements_number[0] = 100;
    elements_number[1] = 2500;
    elements_number[2] = 5000;
    elements_number[3] = 7500;
    elements_number[4] = 10000;
    elements_number[5] = 12500;
    elements_number[6] = 15000;
    elements_number[7] = 17500;
    elements_number[8] = 20000;
    elements_number[9] = 22500;
    elements_number[10] = 25000;
    elements_number[11] = 27500;
    elements_number[12] = 30000;
    elements_number[13] = 32500;
    elements_number[14] = 35000;
    elements_number[15] = 37500;

    int tests_num = 16; //zmienna odpowiedzialna za liczbę testów dla różnej liczby elementów

    //Czasy dla list
    int** tests_lists = new int*[tests_num]; //tablica z czasami z list

    cout << "Listy: " << endl << endl;
    for(int i=0;i<tests_num;i++) {
        tests_lists[i] = list(struct_number, elements_number[i]);
    }

    cout << "-------------------------------------------------------------" << endl;

    //Czasy dla tablic
    int** tests_tables = new int*[tests_num]; //tablica z czasami z tablic

    cout << "Tablice: " << endl << endl;
    for(int i=0;i<tests_num;i++) {
        tests_tables[i] = table(struct_number, elements_number[i]);
    }

    //Tabela z wynikami list
    cout << "Listy: " << endl;

    cout << "Liczba elementow;Usuwanie poczatek;Usuwanie koniec;Usuwanie indeks;Dodawanie poczatek;Dodawanie koniec;Dodawanie indeks;Szukanie" << endl;
    for(int i = 0;i<tests_num;i++) {
        cout << elements_number[i];
        for(int j = 0;j<7;j++) {
            cout << ";" << tests_lists[i][j];
        }
        cout << endl;
    }

    //Tabela z wynikami tablic
    cout << endl << "Tablice: " << endl;
    
    cout << "Liczba elementow;Usuwanie poczatek;Usuwanie koniec;Usuwanie indeks;Dodawanie poczatek;Dodawanie koniec;Dodawanie indeks;Szukanie" << endl;
    for(int i = 0;i<tests_num;i++) {
        cout << elements_number[i];
        for(int j = 0;j<7;j++) {
            cout << ";" << tests_tables[i][j];
        }
        cout << endl;
    }

    return 0;
}