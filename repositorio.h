//
// Created by ivhy on 19/10/19.
//

#ifndef PROJECT2_REPOSITORIO_H
#define PROJECT2_REPOSITORIO_H

#include "deserializador_transaccion.h"
#include "serializador_transaccion.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

template <class T>
class Repositorio {
private:
    Deserializador<T>* deserializador;
    Serializador<T>* serializador;
public:
    Repositorio(const std::string&);
    ~Repositorio();
    void mostrarElementos();
};

template <class T>
Repositorio<T>::Repositorio(const string& nombreArchivo) {
    deserializador = new DeserializadorTransaccion();
    serializador = new SerializadorTransaccion<T>();

    fstream* archivo = new std::fstream(nombreArchivo, std::ios_base::in);
    string linea;
    getline(*archivo,linea);

    if (archivo) {
        while (getline(*archivo, linea)) {
            Transaccion* transaccion = deserializador->deserializar(linea, ',');
            deserializador->getElementos()->push_back(transaccion);
        }
        archivo->close();
    }
    delete archivo;
}

template <class T>
Repositorio<T>::~Repositorio() {
    delete deserializador;
    delete serializador;
}

template <class T>
void Repositorio<T>::mostrarElementos() {
    for (auto transaccion : *deserializador->getElementos()) {
        cout << transaccion->getCountryArea() << " ";
        cout << transaccion->getCode() << " ";
        cout << transaccion->getCommodity() << " ";
        cout << transaccion->getFlow() << " ";
        cout << transaccion->getTradeUsd() << " ";
        cout << transaccion->getWeight() << " ";
        cout << transaccion->getQuantityName() << " ";
        cout << transaccion->getQuantity() << " ";
        cout << transaccion->getCategory() << endl;
    }
}

#endif //PROJECT2_REPOSITORIO_H
