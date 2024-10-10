#include <iostream>
#include <fstream>

using namespace std;

class MaxHeap {
    int* heap;
    int size;
    int capacity;

public:
// Consytuctor
    MaxHeap(int cap) : size(0), capacity(cap) {
        heap = new int[cap];
    }

//Destructor
    ~MaxHeap() {
        delete[] heap;
    }

    void insertar(int value) {
        if (size == capacity) {
            cerr << "Heap está lleno" << endl;
            return;
        }
        int i = size;
        heap[size++] = value;

        while (i != 0 && heap[padre(i)] < heap[i]) {
            swap(heap[i], heap[padre(i)]);
            i = padre(i);
        }
    }

    bool eliminar(int value) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (heap[i] == value) {
                index = i;
                break;
            }
        }
        if (index == -1) return false;

        heap[index] = heap[--size];
        reajustarHeap(index);
        return true;
    }

    bool buscar(int value) {
        for (int i = 0; i < size; ++i) {
            if (heap[i] == value) return true;
        }
        return false;
    }

    void reajustarHeap(int i) {
        int mayor = i;
        int izquierdo = hijoIzquierdo(i);
        int derecho = hijoDerecho(i);

        if (izquierdo < size && heap[izquierdo] > heap[mayor]) mayor = izquierdo;
        if (derecho < size && heap[derecho] > heap[mayor]) mayor = derecho;

        if (mayor != i) {
            swap(heap[i], heap[mayor]);
            reajustarHeap(mayor);
        }
    }

    int obtenerMax() {
        return size > 0 ? heap[0] : -1;
    }

    int obtenerMin() {
        int minIndex = 0;
        for (int i = 1; i < size; ++i) {
            if (heap[i] < heap[minIndex]) {
                minIndex = i;
            }
        }
        return size > 0 ? heap[minIndex] : -1;
    }

    int padre(int i) { return (i - 1) / 2; }
    int hijoIzquierdo(int i) { return (2 * i) + 1; }
    int hijoDerecho(int i) { return (2 * i) + 2; }

    void imprimirHeap() {
        for (int i = 0; i < size; ++i) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap heap(1000);

    ifstream archivo("../Software/salarios.txt");
    int salario;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de salarios." << endl;
        return 1;
    }

    while (archivo >> salario) {
        heap.insertar(salario);
    }
    archivo.close();

    int opcion;
    do {
        cout << "\n--- Menú Principal ---" << endl;
        cout << "1. Insertar nuevo salario" << endl;
        cout << "2. Buscar un salario" << endl;
        cout << "3. Eliminar un salario" << endl;
        cout << "4. Mostrar el contenido del heap" << endl;
        cout << "5. Mostrar el salario maximo" << endl;
        cout << "6. Mostrar el salario minimo" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int nuevoSalario;
                cout << "Ingrese el salario a insertar: ";
                cin >> nuevoSalario;
                heap.insertar(nuevoSalario);
                break;
            }
            case 2: {
                int buscarSalario;
                cout << "Ingrese el salario a buscar: ";
                cin >> buscarSalario;
                if (heap.buscar(buscarSalario)) {
                    cout << "Salario encontrado en el heap." << endl;
                } else {
                    cout << "Salario no encontrado en el heap." << endl;
                }
                break;
            }
            case 3: {
                int eliminarSalario;
                cout << "Ingrese el salario a eliminar: ";
                cin >> eliminarSalario;
                if (heap.eliminar(eliminarSalario)) {
                    cout << "Salario eliminado del heap." << endl;
                } else {
                    cout << "Salario no encontrado en el heap." << endl;
                }
                break;
            }
            case 4:
                cout << "Contenido del heap:" << endl;
                heap.imprimirHeap();
                break;
            case 5: {
                int maxSalario = heap.obtenerMax();
                if (maxSalario != -1) {
                    cout << "Salario máximo: " << maxSalario << endl;
                } else {
                    cout << "El heap está vacío." << endl;
                }
                break;
            }
            case 6: {
                int minSalario = heap.obtenerMin();
                if (minSalario != -1) {
                    cout << "Salario mínimo: " << minSalario << endl;
                } else {
                    cout << "El heap está vacío." << endl;
                }
                break;
            }
            case 7:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, intente de nuevo." << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}
 