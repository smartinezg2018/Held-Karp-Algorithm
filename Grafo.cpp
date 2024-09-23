#include "Grafo.h"
#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>
#include <limits>


// Constructor: Inicializa la tabla hash con tamaño 100
Grafo::Grafo() : tablaHash(100) {}

// Destructor: Libera la memoria de todos los nodos
Grafo::~Grafo() {
    for (auto nodo : nodos) {
        delete nodo;
    }
}

// Agrega un nuevo nodo al grafo
void Grafo::agregarNodo(const Data& dato) {
    Nodo* nuevoNodo = new Nodo(dato);
    nodos.push_back(nuevoNodo);
    tablaHash.insertar(nuevoNodo);
}



float calcularDistancia(std::vector<float> origen,std::vector<float> destino){
    // float x1 = locales[origen][0];
    // float y1 = locales[origen][1];
    // float x2 = locales[destino][0];
    // float y2 = locales[destino][1];

    // float distancia = std::sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    
    // return distancia;


    double lat1_rad = origen[0] * M_PI / 180.0;
    double lon1_rad = origen[1] * M_PI / 180.0;
    double lat2_rad = destino[0] * M_PI / 180.0;
    double lon2_rad = destino[1]* M_PI / 180.0;

    double dlat = lat2_rad - lat1_rad;
    double dlon = lon2_rad - lon1_rad;


    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1_rad) * std::cos(lat2_rad) *
               std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));


    double distance = 6371.0 * c;

    return distance;
}




// Agrega una arista entre dos nodos
void Grafo::agregarArista(const std::string& origen, const std::string& destino) {
    Nodo* nodoOrigen = tablaHash.buscar(origen);
    Nodo* nodoDestino = tablaHash.buscar(destino);

    float distancia = calcularDistancia(nodoOrigen->obtenerDato().obtenerCoordenadas(),nodoDestino->obtenerDato().obtenerCoordenadas());

    if (nodoOrigen && nodoDestino) {
        nodoOrigen->agregarArista(nodoDestino, distancia);
    } else {
        std::cout << "Error: Nodo no encontrado" << std::endl;
    }
}



// Imprime la estructura del grafo
void Grafo::imprimirGrafo() const {
    for (const auto& nodo : nodos) {
        std::cout << "Nodo " << nodo->obtenerDato().obtenerValor() << " conectado a: ";
        for (const auto& arista : nodo->obtenerAristas()) {
            std::cout << arista.first->obtenerDato().obtenerValor() << " (peso: " << arista.second << ") ";
        }
        std::cout << std::endl;
    }
}




// Implementa el algoritmo de Búsqueda en Anchura (BFS)
void Grafo::bfs(const std::string& inicio) const {
    // Pseudocódigo:
    // 1. Inicializar una cola y un mapa de visitados
    // 2. Marcar el nodo inicial como visitado y encolarlo
    // 3. Mientras la cola no esté vacía:
    //    a. Sacar un nodo de la cola
    //    b. Procesar el nodo (imprimirlo)
    //    c. Para cada vecino no visitado del nodo:
    //       - Marcarlo como visitado
    //       - Encolarlo

    Nodo* nodoInicio = tablaHash.buscar(inicio);
    if (!nodoInicio) {
        std::cout << "Nodo de inicio no encontrado" << std::endl;
        return;
    }

    std::unordered_map<Nodo*, bool> visitado;
    std::queue<Nodo*> cola;

    visitado[nodoInicio] = true;
    cola.push(nodoInicio);

    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();

        std::cout << actual->obtenerDato().obtenerValor() << " ";

        for (const auto& arista : actual->obtenerAristas()) {
            if (!visitado[arista.first]) {
                visitado[arista.first] = true;
                cola.push(arista.first);
            }
        }
    }
    std::cout << std::endl;
}

// Implementa el algoritmo de Dijkstra para encontrar la ruta más corta
void Grafo::dijkstra(const std::string& inicio, const std::string& fin) const {
    // Pseudocódigo:
    // 1. Inicializar distancias, nodos previos y cola de prioridad
    // 2. Establecer distancia del nodo inicial a 0 y añadirlo a la cola
    // 3. Mientras la cola no esté vacía:
    //    a. Sacar el nodo con menor distancia
    //    b. Si es el nodo final, terminar
    //    c. Para cada vecino del nodo actual:
    //       - Calcular nueva distancia
    //       - Si es menor que la distancia actual, actualizar y añadir a la cola
    // 4. Reconstruir y mostrar la ruta

    Nodo* nodoInicio = tablaHash.buscar(inicio);
    Nodo* nodoFin = tablaHash.buscar(fin);

    if (!nodoInicio || !nodoFin) {
        std::cout << "Nodo de inicio o fin no encontrado" << std::endl;
        return;
    }

    std::unordered_map<Nodo*, int> distancia;
    std::unordered_map<Nodo*, Nodo*> previo;
    std::priority_queue<std::pair<int, Nodo*>, std::vector<std::pair<int, Nodo*>>, std::greater<std::pair<int, Nodo*>>> pq;

    for (auto nodo : nodos) {
        distancia[nodo] = std::numeric_limits<int>::max();
        previo[nodo] = nullptr;
    }

    distancia[nodoInicio] = 0;
    pq.push({0, nodoInicio});

    while (!pq.empty()) {
        Nodo* actual = pq.top().second;
        pq.pop();

        if (actual == nodoFin) break;

        for (const auto& arista : actual->obtenerAristas()) {
            Nodo* vecino = arista.first;
            int peso = arista.second;
            int nuevaDistancia = distancia[actual] + peso;

            if (nuevaDistancia < distancia[vecino]) {
                distancia[vecino] = nuevaDistancia;
                previo[vecino] = actual;
                pq.push({nuevaDistancia, vecino});
            }
        }
    }

    // Reconstrucción de la ruta
    std::vector<std::string> ruta;
    for (Nodo* actual = nodoFin; actual != nullptr; actual = previo[actual]) {
        ruta.push_back(actual->obtenerDato().obtenerValor());
    }
    std::reverse(ruta.begin(), ruta.end());

    // Impresión de la ruta y la distancia total
    std::cout << "Ruta más corta: ";
    for (const auto& dato : ruta) {
        std::cout << dato << " ";
    }
    std::cout << "\nDistancia total: " << distancia[nodoFin] << std::endl;
}


