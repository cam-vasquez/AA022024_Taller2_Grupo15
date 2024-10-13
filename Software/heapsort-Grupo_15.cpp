#include <iostream>
#include <fstream>
using namespace std;

class MaxHeap {
    int* heap;   
    int size;    
    int capacity; 

public:
    MaxHeap(int cap) : size(0), capacity(cap) {
        heap = new int[cap];
    }

    ~MaxHeap() {
        delete[] heap;
    }

    void insertar(int value) {
        if (size == capacity) {
            cout << "El Heap está lleno" << endl;
            return;
        }
        int i = size;
        heap[size++] = value;

        while (i != 0 && heap[padre(i)] < heap[i]) {
            int temp = heap[i];
            heap[i] = heap[padre(i)];
            heap[padre(i)] = temp;
            i = padre(i); 
        }
    }

    int eliminarMax() {
        if (size <= 0) return -1;
        int maxElemento = heap[0];
        heap[0] = heap[--size];
        reajustarHeap(0);
        return maxElemento;
    }

    void reajustarHeap(int i) {
        int mayor = i;
        int izquierdo = hijoIzquierdo(i);
        int derecho = hijoDerecho(i);

        if (izquierdo < size && heap[izquierdo] > heap[mayor]) mayor = izquierdo;
        if (derecho < size && heap[derecho] > heap[mayor]) mayor = derecho;

        if (mayor != i) {
            int temp = heap[i];
            heap[i] = heap[mayor];
            heap[mayor] = temp;
            reajustarHeap(mayor);
        }
    }

    void ordenarDescendente() {
        while (size > 0) {
            cout << eliminarMax() << " ";
        }
        cout << endl;
    }

    int padre(int i) { return (i - 1) / 2; }
    int hijoIzquierdo(int i) { return (2 * i) + 1; }
    int hijoDerecho(int i) { return (2 * i) + 2; }
};

int main() {
    MaxHeap heap(1000);

    ifstream archivo("../Software/salarios.txt");
    int salario;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de salarios." << endl;
        return 1;
    }

    while (archivo >> salario) {
        heap.insertar(salario);
    }
    archivo.close();

    int opcion;
    do {
        cout << "\n--------- Menu  ---------" << endl;
        cout << "1. Ordenar y mostrar salarios en orden descendente" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Salarios en orden descendente:" << endl;
                heap.ordenarDescendente();
                break;
            case 2:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, intente de nuevo." << endl;
                break;
        }
    } while (opcion != 2);

    return 0;
}
