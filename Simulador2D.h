#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

#include <iostream>
using namespace std;


template <typename T>
class Simulador2D
{
private:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

public:
    // MÉTODOS PÚBLICOS OBLIGATORIOS:

    // Constructor
    Simulador2D(int f, int c)
    { 
        _filas = f;
        _columnas = c;

        // Creamos la matriz dinámica
        _grid = new T *[_filas];
        for (int i = 0; i < _filas; i++)
        {
            _grid[i] = new T[_columnas]{0}; // Inicializamos a 0
        }

        cout << "Creando Grid (FLOAT) de " << _filas << "x" << _columnas << "..." << endl;


        // Inicializamos el vector de fuentes
        _capacidadFuentes = 2; // Capacidad inicial
        _numFuentes = 0;
        _fuentes = new T[_capacidadFuentes];

        // Inicializamos las constantes de simulación
        _constantes[0] = 0.25f; // Coeficiente de Difusión
        _constantes[1] = 1.0f;  // DeltaX
        _constantes[2] = 0.1f;  // DeltaT

        
    }

    // Destructor 
    ~Simulador2D()
    { 
        // Liberamos la memoria de la matriz dinámica
        for (int i = 0; i < _filas; i++)
        {
            delete[] _grid[i];
        }
        delete[] _grid;

        // Liberamos la memoria del vector de fuentes
        delete[] _fuentes;

        cout << "Liberando memoria del Grid y Fuentes... Sistema cerrado." << endl;
    }

    void redimensionarGrid(int nuevaF, int nuevaC)
    {
        // Creamos una nueva matriz con las nuevas dimensiones
        T **nuevoGrid = new T *[nuevaF];
        for (int i = 0; i < nuevaF; i++)
        {
            nuevoGrid[i] = new T[nuevaC]{0}; // Inicializamos a 0
        }

        // Copiamos los valores de la matriz antigua a la nueva
        int filasMin = (nuevaF < _filas) ? nuevaF : _filas;
        int columnasMin = (nuevaC < _columnas) ? nuevaC : _columnas;

        for (int i = 0; i < filasMin; i++)
        {
            for (int j = 0; j < columnasMin; j++)
            {
                nuevoGrid[i][j] = _grid[i][j];
            }
        }

        // Liberamos la memoria de la matriz antigua
        for (int i = 0; i < _filas; i++)
        {
            delete[] _grid[i];
        }
        delete[] _grid;

        // Actualizamos los punteros y dimensiones
        _grid = nuevoGrid;
        _filas = nuevaF;
        _columnas = nuevaC;

        cout << "Redimensionando Grid a " << nuevaF << "x" << nuevaC << ". Datos copiados." << endl;
    }

     // Expansión manual del vector dinámico si es necesario
    void agregarFuente(T valor)
    {
        // Verificar si el vector esta lleno, y expandir si es necesario
        if (_numFuentes >= _capacidadFuentes)
        {
            _capacidadFuentes *= 2; // Duplicamos la capacidad
            T *nuevoVector = new T[_capacidadFuentes];
            for (int i = 0; i < _numFuentes; i++)
            {
                nuevoVector[i] = _fuentes[i]; // Copiamos los valores antiguos
            }
            delete[] _fuentes;      // Liberamos la memoria antigua
            _fuentes = nuevoVector; // Actualizamos el puntero
        }

        // Agregamos la nueva fuente
        _fuentes[_numFuentes] = valor;
        _numFuentes++;
        cout << "Agregar Fuente " << _numFuentes << "(Valor " << valor << "): Éxito." << endl;
    }

    // Implementación del algoritmo 
    void simularPaso()
    { 
        cout << "Simulando Propagación..." << endl;

        // Creamos una matriz temporal
        T **nuevo = new T *[_filas];
        for (int i = 0; i < _filas; i++)
        {
            nuevo[i] = new T[_columnas]{0};
        }

        float D = _constantes[0]; // Coeficiente de Difusión

        // Recorremos cada celda y distibuit parte de su valor a vecinos
        for (int i = 0; i < _filas; i++)
        {
            for (int j = 0; j < _columnas; j++)
            {
                T valorActual = _grid[i][j];
                if (valorActual > 0)
                {
                    T parte = valorActual * D;
                    if (i > 0)
                    {
                        nuevo[i - 1][j] += parte; // Arriba
                    }
                    if (i < _filas - 1)
                    {
                        nuevo[i + 1][j] += parte; // Abajo
                    }
                    if (j > 0)
                    {
                        nuevo[i][j - 1] += parte; // Izquierda
                    }
                    if (j < _columnas - 1)
                    {
                        nuevo[i][j + 1] += parte; // Derecha
                    }
                    nuevo[i][j] += valorActual - 4 * parte; // El restante se queda en la celda actual
                }
            }
        }

        // Actualizamos la matriz original
        for (int i = 0; i < _filas; i++)
        {
            for (int j = 0; j < _columnas; j++)
            {
                _grid[i][j] = nuevo[i][j];
            }
        }

        // Liberamos la memoria de la matriz temporal
        for (int i = 0; i < _filas; i++)
        {
            delete[] nuevo[i];
        }
        delete[] nuevo;
    }

    // Establece el valor en una posición específica
    void setValor(int fila, int columna, T valor)
    {
        if (fila >= 0 && fila < _filas && columna >= 0 && columna < _columnas)
        {
            _grid[fila][columna] = valor;
        }
    }

    // Imprime el estado actual de la cuadrícula
    void imprimirGrid()
    { 
        for (int i = 0; i < _filas; i++)
        {
            cout << "|  ";
            for (int j = 0; j < _columnas; j++)
            {
                // Ajustamos los espacios para mejor visualización
                if (_grid[i][j] < 10)
                    cout << "  ";
                cout << _grid[i][j] << "  | ";
            }
            cout << endl;
        }
    }
};

#endif // SIMULADOR2D_H