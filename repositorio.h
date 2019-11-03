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
#include <vector>
#include <map>
using namespace std;

template <class T>
class Repositorio {
private:
    Deserializador<T>* deserializador;
    Serializador<T>* serializador;

    void listarTradeUsdQ(const string&);
    void listarTradeUsdM(const string&);
    void listarTradeUsdS(const string&);
    void listarTradeUsdH(const string&);

    void listarColumnas(const string&);
    void listarColumnas2(const string&);
    void listarColumnas3(const string&);
    void listarColumnas4(const string&);

    int partition(vector<Transaccion*> &transacciones, int inicio, int final);
    int partition2(vector<Transaccion*> &transacciones, int inicio, int final);
    vector<T*>* elementos;

public:
    Repositorio(const std::string&);
    int size();
    ~Repositorio();


    void listarCriterio1();
    void listarCriterio2();


    void ordenarConQuicksort(vector<T*> &transacciones, int inicio, int final);
    void ordenarConQuicksort2(vector<Transaccion*> &transacciones, int inicio, int final);

    void merge(vector<T*> &transacciones, int left, int middle, int right);
    void ordenarConMergesort(vector<T*> &transacciones, int left, int right);
    void merge2(vector<Transaccion*> &transacciones, int left, int middle, int right);
    void ordenarConMergesort2(vector<Transaccion*> &transacciones, int left, int right);

    void ordenarConShellsort(int size);
    void ordenarConShellsort2(int size);

    void heap(int size, int node);
    void ordenarConHeapsort(int size);
    void heap2(int size, int node);
    void ordenarConHeapsort2(int size);

};

// Constructor

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

// Destructor

template <class T>
Repositorio<T>::~Repositorio() {
    delete deserializador;
    delete serializador;
}


//                                             ALGORITMOS DE ORDENAMIENTO

//                                                     QUICKSORT

// Quicksort criterio 1:

template <class T>
int Repositorio<T>::size() {
    return deserializador->getElementos()->size();
}

template <class T>
int Repositorio<T>::partition(vector<Transaccion*> &transacciones, int inicio, int final) {
    long long int x = transacciones[final]->getTradeUsd();
    int i = inicio-1;
    for(int j = inicio; j < final; j++) {
        if(transacciones[j]->getTradeUsd() > x) {
            i++;
            swap(transacciones[i], transacciones[j]);
        }
    }
    swap(transacciones[i+1], transacciones[final]);
    return i+1;
}

template<class T>
void Repositorio<T>::ordenarConQuicksort(vector<T*> &transacciones,int inicio, int final) {
    if(inicio<final) {
        int p = partition(transacciones,inicio, final);
        ordenarConQuicksort(transacciones, inicio, p-1);
        ordenarConQuicksort(transacciones, p+1,final);
    }
}


// Quicksort criterio 2:


template <class T>
int Repositorio<T>::partition2(vector<Transaccion*> &transacciones, int inicio, int final ) {
    Transaccion* x = transacciones[final];
    int i  = inicio - 1;
    for(int j = inicio; j < final; j++) {
        if(transacciones[j]->getCountryArea() > x->getCountryArea()) {
            i++;
            swap(transacciones[i], transacciones[j]);
        } else if ( transacciones[j]->getCountryArea() == x->getCountryArea()) {
            if(transacciones[j]->getYear() > x->getYear()) {
                i++;
                swap(transacciones[i], transacciones[j]);
            } else if ( transacciones[j]->getYear() == x->getYear() ){
                if(transacciones[j]->getTradeUsd() > x->getTradeUsd()) {
                    i++;
                    swap(transacciones[i], transacciones[j]);
                }
            }
        }
    }
    swap(transacciones[i+1], transacciones[final]);
    return i+1;
}
template<class T>
void Repositorio<T>::ordenarConQuicksort2(vector<Transaccion*> &transacciones, int inicio, int final) {
    if(inicio<final) {
        int p = partition2(transacciones, inicio, final);
        ordenarConQuicksort2(transacciones , inicio , p-1);
        ordenarConQuicksort2(transacciones, p+1, final);
    }
}
//                                                MERGESORT

//Mergesort criterio 1:

template <class T>
void Repositorio<T>::merge(vector<T*> &transacciones , int left, int middle, int right){
        int i,j,k;
        int n1 = middle - left + 1;
        int n2 = right - middle;
        vector<Transaccion*> L(n1);
        vector<Transaccion*> R(n2);
        for (i = 0; i < n1; ++i)
            L[i] = transacciones[left + i];
        for (j = 0; j < n2; ++j)
            R[j] = transacciones[middle + 1 + j];
        i = 0;
        j = 0;
        k = left;
        while (i < n1 && j < n2) {
            if (L[i]->getTradeUsd() >= R[j]->getTradeUsd()) {
                transacciones[k] = L[i];
                i++;
            }
            else {
                transacciones[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            transacciones[k]= L[i];
            i++;
            k++;
        }
        while (j < n2) {
            transacciones[k]= R[j];
            j++;
            k++;
        }
}

template <class T>
void Repositorio<T>::ordenarConMergesort(vector<T*> &transacciones , int left, int right){

        if (left < right) {
            int middle = left + (right - left) / 2;
            ordenarConMergesort(transacciones, left, middle);
            ordenarConMergesort(transacciones, middle + 1, right);
            merge( transacciones, left, middle, right);
        }
}

// Mergesort criterio 2:

template <class T>
void Repositorio<T>::merge2(vector<Transaccion*> &transacciones, int left, int middle, int right){
    int i,j,k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<Transaccion*> L(n1);
    vector<Transaccion*> R(n2);
    for (i = 0; i < n1; ++i)
        L[i] = transacciones[left + i];
    for (j = 0; j < n2; ++j)
        R[j] = transacciones[middle + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i]->getCountryArea() > R[j]->getCountryArea()
            || (L[i]->getCountryArea() == R[j]->getCountryArea() && L[i]->getYear() > R[j]->getYear())
            || (L[i]->getCountryArea() == R[j]->getCountryArea() && L[i]->getYear() == R[j]->getYear() && L[i]->getTradeUsd() >= R[j]->getTradeUsd())) {
            transacciones[k] = L[i];
            i++;
        }
        else {
            transacciones[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        transacciones[k]= L[i];
        i++;
        k++;
    }
    while (j < n2) {
        transacciones[k]= R[j];
        j++;
        k++;
    }
}

template <class T>
void Repositorio<T>::ordenarConMergesort2(vector<Transaccion*> &transacciones, int left, int right){

    if (left < right) {
        int middle = left + (right - left) / 2;
        ordenarConMergesort2(transacciones,left, middle);
        ordenarConMergesort2(transacciones, middle + 1, right);

        merge2(transacciones, left, middle, right);
    }
}




//                                                 SHELLSORT

// Shellsort criterio 1:

template <class T>
void Repositorio<T>::ordenarConShellsort(int size){

    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            auto temp = elementos->at(i);
            int j;
            for (j = i; j >= gap && elementos->at(j-gap)->getTradeUsd() < temp->getTradeUsd(); j -= gap)
                swap(elementos->at(j), elementos->at(j-gap));
        }
    }
}
//Shellsort criterio 2:
template <class T>
void Repositorio<T>::ordenarConShellsort2(int size){

    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            auto temp = elementos->at(i);
            int j;
            for (j = i; (j >= gap) && (elementos->at(j-gap)->getCountryArea() < temp->getCountryArea()
                                       || (elementos->at(j-gap)->getCountryArea() == temp->getCountryArea() && elementos->at(j-gap)->getYear() < temp->getYear())
                                       || (elementos->at(j-gap)->getCountryArea() == temp->getCountryArea() && elementos->at(j-gap)->getYear() == temp->getYear() && elementos->at(j-gap)->getTradeUsd() < temp->getTradeUsd())); j -= gap)
                swap(elementos->at(j), elementos->at(j-gap));
        }
    }
}



//                                       HEAPSORT

// Heapsort criterio 1:

template <class T>
void Repositorio<T>::heap(int size, int node){

        int smallest = node;
        int l = 2*node + 1;
        int r = 2*node + 2;
        if (l < size && elementos->at(l)->getTradeUsd() < elementos->at(smallest)->getTradeUsd())
            smallest = l;
        if (r < size && elementos->at(r)->getTradeUsd() < elementos->at(smallest)->getTradeUsd())
            smallest = r;

        if (smallest != node) {
            swap(elementos->at(node), elementos->at(smallest));
            heap(size, smallest);
        }
}

template <class T>
void Repositorio<T>::ordenarConHeapsort(int size){
    for (int i = size / 2 - 1; i >= 0; --i)
        heap(size, i);
    for (int i = size-1; i >= 0; --i)
    {
        swap(elementos->at(0), elementos->at(i));
        heap( i, 0);
    }
}

// Heapsort criterio 2:

template <class T>
void Repositorio<T>::heap2(int size, int node){

    int smallest = node;
    int l = 2*node + 1;
    int r = 2*node + 2;
    if (l < size && (elementos->at(l)->getCountryArea() < elementos->at(smallest)->getCountryArea()
    || (elementos->at(l)->getCountryArea() == elementos->at(smallest)->getCountryArea() && elementos->at(l)->getYear() < elementos->at(smallest)->getYear())
    || (elementos->at(l)->getCountryArea() == elementos->at(smallest)->getCountryArea() && elementos->at(l)->getYear() == elementos->at(smallest)->getYear() && elementos->at(l)->getTradeUsd() < elementos->at(smallest)->getTradeUsd())))
        smallest = l;
    if (r < size && (elementos->at(r)->getCountryArea() < elementos->at(smallest)->getCountryArea()
        || (elementos->at(r)->getCountryArea() == elementos->at(smallest)->getCountryArea() && elementos->at(r)->getYear() < elementos->at(smallest)->getYear())
        || (elementos->at(r)->getCountryArea() == elementos->at(smallest)->getCountryArea() && elementos->at(r)->getYear() == elementos->at(smallest)->getYear() && elementos->at(l)->getTradeUsd() < elementos->at(smallest)->getTradeUsd())))
        smallest = r;

    if (smallest != node) {
        swap(elementos->at(node), elementos->at(smallest));
        heap(size, smallest);
    }
}

template <class T>
void Repositorio<T>::ordenarConHeapsort2(int size){
    for (int i = size / 2 - 1; i >= 0; --i)
        heap2(size, i);
    for (int i = size-1; i >= 0; --i)
    {
        swap(elementos->at(0), elementos->at(i));
        heap2( i, 0);
    }
}



//                                                    Funciones de listar:

// Listar primer criterio:

template <class T>
void Repositorio<T>::listarTradeUsdQ(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    double duration;
    vector<T*>* desordenado = new vector<T*>();
    *desordenado = *elementos;
    start = clock();

    ordenarConQuicksort(*desordenado,0, size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Quicksort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *desordenado) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}

template <class T>
void Repositorio<T>::listarTradeUsdM(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    vector<T*>* desordenado = new vector<T*>();
    *desordenado = *elementos;
    double duration;
    start = clock();

    ordenarConMergesort(*desordenado,0, elementos->size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Mergesort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *desordenado) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}

template <class T>
void Repositorio<T>::listarTradeUsdS(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    double duration;
    vector<T*>* desordenado = new vector<T*>();
    *desordenado = elementos;
    start = clock();

    ordenarConShellsort(elementos->size());

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Shellsort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}

template <class T>
void Repositorio<T>::listarTradeUsdH(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    vector<T*>* desordenado = new vector<T*>();
    desordenado = elementos;
    double duration;
    start = clock();

    ordenarConHeapsort(elementos->size());

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Heapsort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}

template <class T>
void Repositorio<T>::listarCriterio1() {

    listarTradeUsdM("mergesortcriterio1.csv");
    listarTradeUsdQ("quicksortcriterio1.csv");
    //listarTradeUsdS("shellsortcriterio1.csv");
    //listarTradeUsdH("heapsortcriterio1.csv");
}

// Listar segundo criterio:

template <class T>
void Repositorio<T>::listarColumnas(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    vector<T*>* desordenado = new vector<T*>();
    *desordenado = *elementos;
    double duration;
    start = clock();

    ordenarConQuicksort2(*desordenado,0, size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Quicksort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *desordenado) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}

template <class T>
void Repositorio<T>::listarColumnas2(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    vector<T*>* desordenado = new vector<T*>();
    *desordenado = *elementos;
    double duration;
    start = clock();

    ordenarConMergesort2( *desordenado,0, size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Mergesort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *desordenado) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}

template <class T>
void Repositorio<T>::listarColumnas3(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    vector<T*>* desordenado = new vector<T*>*();
    desordenado = elementos;
    double duration;
    start = clock();

    ordenarConShellsort2(elementos->size());

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Shellsort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}


template <class T>
void Repositorio<T>::listarColumnas4(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    vector<T*>* desordenado = new vector<T*>*();
    *desordenado = elementos;
    double duration;
    start = clock();
    ordenarConHeapsort2(elementos->size());

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Heapsort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
    delete desordenado;
}
template <class T>
void Repositorio<T>::listarCriterio2() {
    listarColumnas2("mergesortcriterio2.csv");
    listarColumnas("quicksortcriterio2.csv");
//    listarColumnas3("shellsortcriterio2.csv");
//    listarColumnas4("heapsortcriterio2.csv");
}


#endif //PROJECT2_REPOSITORIO_H
