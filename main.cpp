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

// Buscar por ID (validar repetidos y buscar)
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
    if (buscarPorId(id)) {
        cout << "ID repetido\n";
        return;
    }

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
    if (buscarPorId(id)) {
        cout << "ID repetido\n";
        return;
    }

    Nodo* nuevo = new Nodo{id, nombre, peso, nullptr, nullptr};

    if (!tail) {
        head = tail = nuevo;
    } else {
        tail->sig = nuevo;
        nuevo->ant = tail;
        tail = nuevo;
    }
}

// EXTRA – insertar ordenado por id
void insertarOrdenado(int id, string nombre, float peso) {
    if (buscarPorId(id)) {
        cout << "ID repetido\n";
        return;
    }

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

void mostrarAdelante() {
    if (!head) {
        cout << "Lista vacia\n";
        return;
    }

    Nodo* aux = head;
    while (aux) {
        cout << aux->id << " | " << aux->nombre << " | " << aux->peso << "kg\n";
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
        cout << aux->id << " | " << aux->nombre << " | " << aux->peso << "kg\n";
        aux = aux->ant;
    }
}

void mostrarPaquetePorId(int id) {
    Nodo* p = buscarPorId(id);
    if (!p) {
        cout << "Paquete no encontrado\n";
        return;
    }
    cout << p->id << " | " << p->nombre << " | " << p->peso << "kg\n";
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

int main() {
    int opcion;

    do {
        cout << "\n--- SISTEMA DE PAQUETES ---\n";
        cout << "1. Insertar paquete al final\n";
        cout << "2. Insertar paquete al inicio\n";
        cout << "3. Mostrar lista adelante\n";
        cout << "4. Mostrar lista atras\n";
        cout << "5. Buscar paquete por id\n";
        cout << "6. Eliminar paquete por id\n";
        cout << "7. Mostrar cantidad de paquetes\n";
        cout << "8. Insertar paquete ordenado por id (Extra)\n";
        cout << "9. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        int id;
        string nombre;
        float peso;

        switch (opcion) {
            case 1:
                cout << "ID: "; cin >> id;
                cout << "Nombre: "; cin >> nombre;
                cout << "Peso: "; cin >> peso;
                insertarFinal(id, nombre, peso);
                break;

            case 2:
                cout << "ID: "; cin >> id;
                cout << "Nombre: "; cin >> nombre;
                cout << "Peso: "; cin >> peso;
                insertarInicio(id, nombre, peso);
                break;

            case 3:
                mostrarAdelante();
                break;

            case 4:
                mostrarAtras();
                break;

            case 5:
                cout << "ID a buscar: ";
                cin >> id;
                mostrarPaquetePorId(id);
                break;

            case 6:
                cout << "ID a eliminar: ";
                cin >> id;
                if (eliminarPorId(id))
                    cout << "Paquete eliminado\n";
                else
                    cout << "Paquete no encontrado\n";
                break;

            case 7:
                cout << "Total de paquetes: " << contarPaquetes() << endl;
                break;

            case 8:
                cout << "ID: "; cin >> id;
                cout << "Nombre: "; cin >> nombre;
                cout << "Peso: "; cin >> peso;
                insertarOrdenado(id, nombre, peso);
                break;

            case 9:
                liberarLista();
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 9);

    return 0;
}
