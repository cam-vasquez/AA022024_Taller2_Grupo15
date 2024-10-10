#include <iostream>
#include <fstream>
using namespace std;

/* MaxHeap define el heap máximo y aseguramos que sigan la propiedad de 
los heaps de que cada nodo padre es mayor o igual a los hijos */

class MaxHeap {
    int* heap;   
    int size;    
    int capacity; 

// un constructor para darle al heap el tamaño inicial de 0 y el destructor para liberar memoria 
/*https://www.geeksforgeeks.org/destructors-c/ */

public:
    MaxHeap(int cap) : size(0), capacity(cap) {
        heap = new int[cap];
    }

    ~MaxHeap() {
        delete[] heap;
    }

// Insertamos un elemento nuevo en el heap similar a lo del libro de BUILD-MAX-HEAP 
// pag 167 del libro y 189 del pdf 
    void insertar(int value) {
        if (size == capacity) {
            cout << "El Heap está lleno" << endl;
            return;
        }
        int i = size;
        heap[size++] = value;

        // Ajustar hacia arriba para mantener el max-heap
        while (i != 0 && heap[padre(i)] < heap[i]) {
            int temp = heap[i];
            heap[i] = heap[padre(i)];
            heap[padre(i)] = temp;
            i = padre(i); 
        }
    }

// Función para eliminar y retornar el máximo (raíz) del MaxHeap
// Siguiendo el proceso de eliminación del MAX-HEAP-MAXIMUM del libro
    int eliminarMax() {
        if (size <= 0) return -1;
        int maxElemento = heap[0];
        heap[0] = heap[--size];
        reajustarHeap(0); // Reajusta para mantener el MaxHeap después de eliminar el máximo
        return maxElemento;
    }

// usamos la función MAX-HEAPIFY para restaurar la propiedad del max-heap 
// empezando desde el índice dado, página 167 del libro, 187 del pdf
// función para reajustar el Heap
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

// Función para ordenar y mostrar salarios en orden descendente
// al eliminar los elementos del MaxHeap uno por uno
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

// Lee los salarios del archivo e inserta cada uno en el MaxHeap
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
