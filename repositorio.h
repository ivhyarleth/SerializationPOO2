//
// Created by ivhy on 19/10/19.
//

#ifndef PROJECT2_REPOSITORIO_H
#define PROJECT2_REPOSITORIO_H

#include "deserializador_transaccion.h"
#include "serializador_transaccion.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <cstring>
using namespace std;

template <class T>
class Repositorio {
private:
    Deserializador<T>* deserializador;
    Serializador<T>* serializador;
    void listar(const string&);
    void listarTradeUsd(const string&);
    void listarColumnas(const string&);
    int partition(int inicio, int final);
    int partition2(int inicio, int final);
    vector<T*>* elementos;
public:
    Repositorio(const std::string&);
    int size();
    ~Repositorio();
    void mostrarElementos();
    void listarTransacciones();
    void listarCriterio1();
    void listarCriterio2();
    void ordenarConQuicksort(int inicio, int final);
    void ordenarConQuicksort2(int inicio, int final);
};

template <class T>
int Repositorio<T>::size() {
    return deserializador->getElementos()->size();
}

template <class T>
int Repositorio<T>::partition2(int inicio, int final ) {
    Transaccion* x = elementos->at(final);
    int i  = inicio - 1;
    for(int j = inicio; j < final; j++) {
        if(elementos->at(j)->getCountryArea() < x->getCountryArea()) {
            i++;
            iter_swap(elementos->operator[](i), elementos->operator[](j));
        } else if ( elementos->at(j)->getCountryArea() == x->getCountryArea()) {
            if(elementos->at(j)->getYear() < x->getYear()) {
                i++;
                iter_swap(elementos->operator[](i), elementos->operator[](j));
            } else if ( elementos->at(j)->getYear() == x->getYear() ){
                if(elementos->at(j)->getTradeUsd() < x->getTradeUsd()) {
                    i++;
                    iter_swap(elementos->operator[](i), elementos->operator[](j));
                }
            }
        }
    }
    iter_swap(elementos->operator[](i+1), elementos->operator[](final));
    return i+1;
}
template<class T>
void Repositorio<T>::ordenarConQuicksort2(int inicio, int final) {
    if(inicio<final) {
        int p = partition2(inicio, final);
        ordenarConQuicksort2(inicio, p-1);
        ordenarConQuicksort2(p+1,final);
    }
}
template <class T>
int Repositorio<T>::partition(int inicio, int final) {
    int x = elementos->at(final)->getTradeUsd();
    int i = inicio-1;
    for(int j = inicio; j < final; j++) {
        if(elementos->at(j)->getTradeUsd() < x) {
            i++;
            iter_swap(elementos->operator[](i), elementos->operator[](j));
        }
    }
    iter_swap(elementos->operator[](i+1), elementos->operator[](final));
    return i+1;
}

template<class T>
void Repositorio<T>::ordenarConQuicksort(int inicio, int final) {
    if(inicio<final) {
        int p = partition(inicio, final);
        ordenarConQuicksort(inicio, p-1);
        ordenarConQuicksort(p+1,final);
    }
}

template <class T>
Repositorio<T>::Repositorio(const string& nombreArchivo) {
    deserializador = new DeserializadorTransaccion();
    serializador = new SerializadorTransaccion<T>();

    fstream* archivo = new fstream(nombreArchivo,ios_base::in);
    string linea;
    getline(*archivo,linea);

    if (archivo) {
        while (getline(*archivo, linea)) {
            Transaccion* transaccion = deserializador->deserializar(linea, ',');
            deserializador->getElementos()->push_back(transaccion);
        }
        archivo->close();
    }
    elementos = deserializador->getElementos();
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
        cout << transaccion->getYear() << " ";
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
template <class T>
void Repositorio<T>::listar(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
                *archivo << serializador->Serializar(transaccion,",") << endl;
                cout << transaccion->getCountryArea() <<" ";
                cout << transaccion->getYear()<<" ";
                cout << transaccion->getCode()<<" ";
                cout << transaccion->getCommodity()<<" ";
                cout << transaccion->getFlow()<<" ";
                cout << transaccion->getTradeUsd()<<" ";
                cout << transaccion->getWeight()<<" ";
                cout << transaccion->getQuantityName()<<" ";
                cout << transaccion->getQuantity()<<" ";
                cout << transaccion->getCategory()<<" "<<endl;
        }
        archivo->close();
    }
    delete archivo;
}

template <class T>
void Repositorio<T>::listarTransacciones() {
    listar("transacciones.csv");
}

template <class T>
void Repositorio<T>::listarTradeUsd(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    double duration;
    start = clock();

    ordenarConQuicksort(0, size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Quicksort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
}
template <class T>
void Repositorio<T>::listarCriterio1() {
    listarTradeUsd("quicksortcriterio1.csv");
}

template <class T>
void Repositorio<T>::listarColumnas(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    double duration;
    start = clock();

    ordenarConQuicksort2(0, size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Quicksort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
}
template <class T>
void Repositorio<T>::listarCriterio2() {
    listarColumnas("quicksortcriterio2.csv");
}


#endif //PROJECT2_REPOSITORIO_H
