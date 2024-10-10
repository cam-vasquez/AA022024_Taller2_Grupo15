#include <iostream>
#include <fstream>
using namespace std;

/* MaxHeap define el heap máximo y aseguramos que sigan la propiedad de 
los heaps de que cada nodo padre es mayor o igual a los hijos*/

// Uhh, para la parte que hagamos el ordenamiento estaba leyendo el lobro y en la pagina 163 del libro, 185 del pdf

class MaxHeap {
    int* heap;   
    int size;    
    int capacity; 


// un constructor para darle al heap el tamaño incial de 0 y el destructor para liberar memoria 
/*https://www.geeksforgeeks.org/destructors-c/ */

public:
    MaxHeap(int cap) : size(0), capacity(cap) {
        heap = new int[cap];
    }

    ~MaxHeap() {
        delete[] heap;
    }

// Insertamos un elemento nuevo en el heap aprecido a lo del libro de BUILD-MAX-HEAP 
// voy a poner las paginas del libro para qu e verifiquen que eesta bien el codigo
//pag 167 del libro y 189 del pdf 
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

// en base a lo del MAX-HEAP-INCREASE-KEY del libro
    // Funcion para modificar un valor existente en el heap
    void modificarValor(int i, int nuevoValor) {
        if (nuevoValor < heap[i]) {
            cerr << "El nuevo valor es menor que el valor actual" << endl;
            return;
        }
        heap[i] = nuevoValor;
        
        // mover hacia arriba para restaurar la propiedad del max-heap 
        while (i != 0 && heap[padre(i)] < heap[i]) {
        int temp = heap[i];
        heap[i] = heap[padre(i)];
        heap[padre(i)] = temp;
         i = padre(i); 
}
    }

    // funcion para eliminar un elemento específico del heap
    bool eliminar(int value) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (heap[i] == value) {
                index = i;
                break;
            }
        }
        if (index == -1) return false; // Si no se encuentra el valor, retorna false

        heap[index] = heap[--size];
        reajustarHeap(index); // Ajuste hacia abajo para mantener el max-heap
        return true;
    }

    // funcion para buscar un índice específico en el heap
    int buscarIndice(int value) {
        for (int i = 0; i < size; ++i) {
            if (heap[i] == value) return i;
        }
        return -1;
    }

    // Método para buscar un valor específico en el heap
    bool buscar(int value) {
        return buscarIndice(value) != -1;
    }

// usamos la fuuncion MAX-HEAPIFY restaurar la propiedad del max-heap empezando desde el índice dado, pagina 167 del libro, 187 delpdf
// funcion para reajustar el Heap
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

        reajustarHeap(mayor); // recursividad para analizarla con el teorema maestro
    }
}

// aqui usamos lo del MAX-HEAP-MAXIMUM del libro
// obterner el maximo salario
    int obtenerMax() {
        return size > 0 ? heap[0] : -1;
    }

// obterner el minimo salario
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


// Funcion para mostrar el heap
void imprimirHeap() {
        for (int i = 0; i < size; ++i) {
            cout << heap[i] << " " ;
        }
        cout << endl;
    }
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
        cout << "1. Agregar un nuevo salario" << endl;
        cout << "2. Buscar un salario" << endl;
        cout << "3. Eliminar un salario" << endl;
        cout << "4. Mostrar el contenido del heap" << endl;
        cout << "5. Mostrar el salario maximo" << endl;
        cout << "6. Mostrar el salario minimo" << endl;
        cout << "7. Modificar un salario existente" << endl;
        cout << "8. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int nuevoSalario;
                cout << "\nIngrese el salario a agregar: ";
                cin >> nuevoSalario;
                heap.insertar(nuevoSalario);
                cout << endl;
                cout << "El salario ha sido ingresado exitosamente.\n";
                break;
            }
            case 2: {
                int buscarSalario;
                cout << "\nIIngrese el salario a buscar: ";
                cin >> buscarSalario;
                if (heap.buscar(buscarSalario)) {
                    cout << endl;
                    cout << "El salario " << buscarSalario << " existe en el heap." << endl;
                } else {
                    cout << endl;
                    cout << "El salario " << buscarSalario << " no existe en el heap." << endl;
                }
                break;
            }
            case 3: {
                int eliminarSalario;
                cout << "\nIIngrese el salario a eliminar: ";
                cin >> eliminarSalario;
                if (heap.eliminar(eliminarSalario)) {
                    cout << endl;
                    cout << "El salario " << eliminarSalario << " ha sido eliminado del heap." << endl;
                } else {
                    cout << "El salario " << eliminarSalario << " no ha sido encontrado del heap." << endl;
                }
                break;
            }
            case 4:
                cout << "\nIContenido del heap:" << endl;
                heap.imprimirHeap();
                break;
            case 5: {
                int maxSalario = heap.obtenerMax();
                if (maxSalario != -1) {
                    cout << "\nISalario maximo: " << maxSalario << endl;
                } else {
                    cout << "\nIEl heap está vacío." << endl;
                }
                break;
            }
            case 6: {
                int minSalario = heap.obtenerMin();
                if (minSalario != -1) {
                    cout << "\nISalario minimo: " << minSalario << endl;
                } else {
                    cout << "\nIEl heap esta vacio." << endl;
                }
                break;
            }
            case 7: {
                int salarioActual, nuevoSalario;
                cout << "\nIIngrese el salario actual a modificar: ";
                cin >> salarioActual;
                int index = heap.buscarIndice(salarioActual);

                if (index == -1) {
                    cout << "\nIEl salario no ha sido encontrado en el heap." << endl;
                } else {
                    cout << "\nIIngrese el nuevo salario mayor: ";
                    cin >> nuevoSalario;
                    heap.modificarValor(index, nuevoSalario);
                    cout << "\nIalario modificado y ajustado en el heap." << endl;
                }
                break;
            }
            case 8:
                cout << "\nISaliendo del programa." << endl;
                break;
            default:
                cout << "\nIOpcion no valida. Por favor, intente de nuevo." << endl;
                break;
        }
    } while (opcion != 8);

    return 0;
}
