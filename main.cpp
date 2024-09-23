#include "Grafo.h"
#include <iostream>
#include <chrono> 

int main() {
    Grafo grafo;

    // Agregar nodos
grafo.agregarNodo(Data("Bodega Norte", {6.30000, -75.57000}));
grafo.agregarNodo(Data("D1 Laureles", {6.23457, -75.58132}));
grafo.agregarNodo(Data("D1 Estadio", {6.24931, -75.57014}));
grafo.agregarNodo(Data("D1 Belén", {6.26708, -75.56435}));
grafo.agregarNodo(Data("D1 Envigado", {6.17123, -75.58291}));
grafo.agregarNodo(Data("D1 Poblado", {6.20528, -75.56719}));
grafo.agregarNodo(Data("D1 Centro", {6.24611, -75.56889}));
grafo.agregarNodo(Data("D1 Castilla", {6.28512, -75.55987}));
grafo.agregarNodo(Data("D1 Robledo", {6.29876, -75.58743}));
grafo.agregarNodo(Data("D1 Buenos Aires", {6.24032, -75.57561}));
grafo.agregarNodo(Data("D1 Manrique", {6.27394, -75.55203}));
grafo.agregarNodo(Data("D1 Aranjuez", {6.25817, -75.56128}));
grafo.agregarNodo(Data("D1 Floresta", {6.23019, -75.57845}));
grafo.agregarNodo(Data("D1 Guayabal", {6.21854, -75.59320}));
grafo.agregarNodo(Data("D1 Itagüí", {6.16256, -75.60183}));
grafo.agregarNodo(Data("D1 Sabaneta", {6.14589, -75.61027}));
grafo.agregarNodo(Data("Bodega Sur", {6.20000, -75.57000}));


    // Agregar aristas
std::vector<std::string> nodos = {
    "Bodega Norte", "D1 Laureles", "D1 Estadio", "D1 Belén", 
    "D1 Envigado", "D1 Poblado", "D1 Centro", "D1 Castilla", 
    "D1 Robledo", "D1 Buenos Aires", "D1 Manrique", "D1 Aranjuez", 
    "D1 Floresta", "D1 Guayabal", "D1 Itagüí", "D1 Sabaneta", 
    "Bodega Sur"
};

for (size_t i = 0; i < nodos.size(); ++i) {
    for (size_t j = 0; j < nodos.size(); ++j) {
        if (i != j) { 
            grafo.agregarArista(nodos[i], nodos[j]);
        }
    }
}


    // std::cout << "Estructura del grafo:" << std::endl;
    // grafo.imprimirGrafo();




    auto inicio = std::chrono::high_resolution_clock::now();
    std::cout << "\nRecorrido BFS desde A: ";
    grafo.dijkstra("Bodega Norte","Bodega Sur");
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    std::cout << "Tiempo de BFS: " << duracion.count() << " segundos" << std::endl;





    // std::cout << "\nRecorrido BFS desde A: ";
    // std::cout << "\nRuta más corta de A a E:" << std::endl;
    // auto inicio1 = std::chrono::high_resolution_clock::now();
    // grafo.dijkstra("A", "E");
    // auto fin1 = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duracion1 = fin1 - inicio1;
    // std::cout << "Tiempo de dijkstra: " << duracion1.count() << " segundos" << std::endl;



    return 0;
}