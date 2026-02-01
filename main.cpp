#include <iostream>
using namespace std;

// Estructura del nodo
struct Nodo {
    int id;
    string nombre;
    float peso;
    Nodo* sig;
    Nodo* ant;
};

// Punteros globales
Nodo* head = NULL;
Nodo* tail = NULL;

// Buscar por ID para validar repetidos
Nodo* buscarPorId(int id) {
    Nodo* aux = head;
    while (aux) {
        if (aux->id == id)
            return aux;
        aux = aux->sig;
    }
    return NULL;
}

void insertarInicio(int id, string nombre, float peso) {
    if (buscarPorId(id)) return;

    Nodo* nuevo = new Nodo{id, nombre, peso, NULL, NULL};

    if (!head) {
        head = tail = nuevo;
    } else {
        nuevo->sig = head;
        head->ant = nuevo;
        head = nuevo;
    }
}

void insertarFinal(int id, string nombre, float peso) {
    if (buscarPorId(id)) return;

    Nodo* nuevo = new Nodo{id, nombre, peso, NULL, NULL};

    if (!tail) {
        head = tail = nuevo;
    } else {
        tail->sig = nuevo;
        nuevo->ant = tail;
        tail = nuevo;
    }
}

int main() {
    return 0;
}
