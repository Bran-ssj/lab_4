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
Nodo* head = nullptr;
Nodo* tail = nullptr;

// Buscar por ID para validar repetidos
Nodo* buscarPorId(int id) {
    Nodo* aux = head;
    while (aux) {
        if (aux->id == id)
            return aux;
        aux = aux->sig;
    }
    return nullptr;
}

void insertarInicio(int id, string nombre, float peso) {
    if (buscarPorId(id)) return;

    Nodo* nuevo = new Nodo{id, nombre, peso, nullptr, nullptr};

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

    Nodo* nuevo = new Nodo{id, nombre, peso, nullptr, nullptr};

    if (!tail) {
        head = tail = nuevo;
    } else {
        tail->sig = nuevo;
        nuevo->ant = tail;
        tail = nuevo;
    }
}

void mostrarAdelante() {
    if (!head) {
        cout << "Lista vacia\n";
        return;
    }
    Nodo* aux = head;
    while (aux) {
        cout << aux->id << " " << aux->nombre << " " << aux->peso << "kg\n";
        aux = aux->sig;
    }
}

void mostrarAtras() {
    if (!tail) {
        cout << "Lista vacia\n";
        return;
    }
    Nodo* aux = tail;
    while (aux) {
        cout << aux->id << " " << aux->nombre << " " << aux->peso << "kg\n";
        aux = aux->ant;
    }
}
void mostrarPaquetePorId(int id) {
    Nodo* p = buscarPorId(id);
    if (!p) {
        cout << "Paquete no encontrado\n";
        return;
    }
    cout << p->id << " " << p->nombre << " " << p->peso << "kg\n";
}

bool eliminarPorId(int id) {
    Nodo* p = buscarPorId(id);
    if (!p) return false;

    if (p == head && p == tail) {
        head = tail = nullptr;
    } else if (p == head) {
        head = head->sig;
        head->ant = nullptr;
    } else if (p == tail) {
        tail = tail->ant;
        tail->sig = nullptr;
    } else {
        p->ant->sig = p->sig;
        p->sig->ant = p->ant;
    }

    delete p;
    return true;
}

int contarPaquetes() {
    int c = 0;
    Nodo* aux = head;
    while (aux) {
        c++;
        aux = aux->sig;
    }
    return c;
}

void liberarLista() {
    while (head) {
        Nodo* aux = head;
        head = head->sig;
        delete aux;
    }
    tail = nullptr;
}

void insertarOrdenado(int id, string nombre, float peso) {
    if (buscarPorId(id)) return;

    Nodo* nuevo = new Nodo{id, nombre, peso, nullptr, nullptr};

    if (!head) {
        head = tail = nuevo;
        return;
    }

    if (id < head->id) {
        nuevo->sig = head;
        head->ant = nuevo;
        head = nuevo;
        return;
    }

    Nodo* aux = head;
    while (aux->sig && aux->sig->id < id)
        aux = aux->sig;

    nuevo->sig = aux->sig;
    nuevo->ant = aux;

    if (aux->sig)
        aux->sig->ant = nuevo;
    else
        tail = nuevo;

    aux->sig = nuevo;
}


int main() {
    return 0;
}
