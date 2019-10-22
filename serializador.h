//
// Created by ivhy on 19/10/19.
//

#ifndef PROJECT2_SERIALIZADOR_H
#define PROJECT2_SERIALIZADOR_H

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Serializador {
protected:
    vector<T*>* elementos;
public:
    Serializador();
    ~Serializador();
    vector<T*>* getElementos();
    virtual string Serializar(T*, char) = 0;
};

template <class T>
Serializador<T>::Serializador() {
    elementos = new vector<T*>();
}

template <class T>
Serializador<T>::~Serializador() {
    for (auto elemento : *elementos)
        delete elemento;
    delete elementos;
}

template <class T>
std::vector<T*>* Serializador<T>::getElementos() {
    return elementos;
}
#endif //PROJECT2_SERIALIZADOR_H
