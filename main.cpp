#include "Simulador2D.h"
#include <iostream>
using namespace std;

int main() {

    cout << "--- Simulador Genérico de Fuidos (Difusión) ---\n" << endl;
    cout << "\n>> Inicializando Sistema (Tipo FLOAT) <<" << endl;

    // Creamos el simulador para el tipo float de 5x5
    Simulador2D<float> simuladorFloat(5, 5);

    cout << "\n>> Agregando Fuentes de Concentración <<" << endl;
    simuladorFloat.agregarFuente(100.0f);
    simuladorFloat.agregarFuente(50.0f);

    cout << "\n>> Aplicando Valores Iniciales <<" << endl;
    simuladorFloat.setValor(2, 2, 100.0f); // Centro
    cout << "Grid[2,2] = 100.0 (Fuente 1)" << endl;
    simuladorFloat.setValor(4, 0, 50.0f); // Esquina Inferior Izquierda
    cout << "Grid[4,0] = 50.0 (Fuente 2)" << endl;


    cout << "\n--- Grid Inicial (Paso 0) ---" << endl;
    simuladorFloat.imprimirGrid();

    cout << "\nOpción: Simular 1 Paso" << endl;
    simuladorFloat.simularPaso();

    cout << "\n--- Grid Después de 1 Paso ---" << endl;
    simuladorFloat.imprimirGrid();

    cout << "\nOpción: Redimensionar" << endl;
    simuladorFloat.redimensionarGrid(6, 6);
    cout << "\n--- Grid Después de Redimensionar a 6x6 ---" << endl;
    simuladorFloat.imprimirGrid();

    cout << "\nOpción: Salir" << endl;

    return 0;
}