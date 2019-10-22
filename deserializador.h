//
// Created by ivhy on 19/10/19.
//

#ifndef PROJECT2_DESERIALIZADOR_H
#define PROJECT2_DESERIALIZADOR_H

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Deserializador {
protected:
    vector<T*>* elementos;
public:
    Deserializador();
    ~Deserializador();
    vector<T*>* getElementos();
    virtual T* deserializar(const string&, char) = 0;
};
template <class T>
Deserializador<T>::Deserializador() {
    elementos = new vector<T*>();
}

template <class T>
Deserializador<T>::~Deserializador() {
    for (auto elemento : *elementos)
        delete elemento;
    delete elementos;
}

template <class T>
vector<T*>* Deserializador<T>::getElementos() {
    return elementos;
}

#endif //PROJECT2_DESERIALIZADOR_H