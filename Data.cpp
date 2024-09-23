#include "Data.h"

// Constructor: Inicializa el objeto Data con un valor
Data::Data(std::string val, std::vector<float> coor) : valor(std::move(val)), coordenadas(std::move(coor))  {}
 
// Obtiene el valor almacenado
std::string Data::obtenerValor() const {
    return valor;
}

std::vector<float> Data::obtenerCoordenadas() const {
    return coordenadas;
}


// Establece un nuevo valor
void Data::establecerValor(const std::string& val) {
    valor = val;
}

// Compara dos objetos Data
bool Data::operator==(const Data& other) const {
    return valor == other.valor;
}