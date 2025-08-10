#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(T data) : data(data), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void adauga( T data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        size++;
    }

    void sterge(int index) {
        if (index < 0 || index >= size) {
            throw "Index în afara intervalului";
        }

        if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else if (index == 0) {
            Node* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        else if (index == size - 1) {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }

        size--;
    }

    const T& obtine(int index) const {
        if (index < 0 || index >= size) {
            throw "Index în afara intervalului";
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    int getDimensiune() const {
        return size;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

class Task {
private:
    string descriere;
    double buget;
    string termen;
    bool areTermenLimita;
    bool areBugetLimitat;

public:
    Task(string descriere);
    Task(string descriere, string termen, double buget);
    Task(const Task& other);

    string getDescriere() const;
    void setDescriere(string descriere);
    double getBuget() const;
    void setBuget(double buget);
    string getTermen() const;
    void setTermen(string termen);
    bool getAreTermenLimita() const;
    bool getAreBugetLimitat() const;

    friend ostream& operator<<(ostream& out, const Task& t);
    friend istream& operator>>(istream& in, Task& t);
};


class Angajat {
protected:
    string nume;
    double salariu;
    string functie;
    string departament;
    DoublyLinkedList<Angajat*> subordonati;
    DoublyLinkedList<Task> taskuri;

public:
    Angajat(string nume, double salariu, string functie, string departament);
    Angajat(const  Angajat& other);
    virtual ~Angajat();

    string getNume() const;
    void setNume(string nume);
    double getSalariu() const;
    void setSalariu(double salariu);
    string getFunctie() const;
    string getDepartament() const;

    void adaugaSubordonat(Angajat* subordonat);
    void stergeSubordonat(int index);
    void adaugaTask(const Task& task);
    void stergeTask(int index);

    DoublyLinkedList<Angajat*>& getSubordonati();
    DoublyLinkedList<Task>& getTaskuri();

    virtual void afiseazaInfo() = 0; 

    friend ostream& operator<<(ostream& out, const Angajat& a);
};


class Muncitor : public Angajat {
public:
    Muncitor(string nume, double salariu, string departament);
    Muncitor(const Muncitor& other);

    void afiseazaInfo() override;

    friend ostream& operator<<(ostream& out, const Muncitor& m);
};


class Manager : public Angajat {
public:
    Manager(string nume, double salariu, string functie, string departament);
    Manager(const Manager& other);

    void afiseazaInfo() override;

    friend ostream& operator<<(ostream& out, const Manager& m);
};


class CEO : public Manager {
public:
    CEO(string nume, double salariu);
    CEO(const CEO& other);

    friend ostream& operator<<(ostream& out, const CEO& c);
};


class SefDepartament : public Manager {
public:
    SefDepartament(string nume, double salariu, string departament);
    SefDepartament(const SefDepartament& other);

    friend ostream& operator<<(ostream& out, const SefDepartament& sd);
};


class TeamLeader : public Manager {
public:
    TeamLeader(string nume, double salariu, string departament);
    TeamLeader(const TeamLeader& other);

    friend ostream& operator<<(ostream& out, const TeamLeader& tl);
};

class FileManager {
public:
    static void exportAngajati(const string& filename, DoublyLinkedList<Angajat*>& angajati);
    static DoublyLinkedList<Angajat*> importAngajati(const string& filename);
    static void verificaErori(const string& filename);
};