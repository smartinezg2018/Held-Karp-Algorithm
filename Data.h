#ifndef DATA_H
#define DATA_H
#include <vector>
#include <string>

// Clase Data: Almacena y maneja la información asociada a cada nodo del grafo
class Data {
private:
    std::string valor;  // Almacena el valor (por ejemplo, nombre de una ciudad)
    std::vector<float> coordenadas;

public:
    // Constructor: Inicializa el objeto Data con un valor
    explicit Data(std::string val,std::vector<float> coor);

    // Obtiene el valor almacenado
    // Retorna: El valor almacenado como string
    std::string obtenerValor() const;
      // Obtiene el coordenadas almacenadas
    // Retorna: coordenadas almacenadas como vector
    std::vector<float> obtenerCoordenadas() const;

    // Establece un nuevo valor
    // Parámetro val: El nuevo valor a establecer
    void establecerValor(const std::string& val);

    // Compara dos objetos Data
    // Parámetro other: Objeto Data a comparar
    // Retorna: true si los valores son iguales, false en caso contrario
    bool operator==(const Data& other) const;
};

#endif // DATA_H