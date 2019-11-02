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
    void listar(const string&);
    void listarTradeUsdQ(const string&);
    void listarTradeUsdM(const string&);
    void listarTradeUsdS(const string&);
    void listarTradeUsdH(const string&);

    void listarColumnas(const string&);
    void listarColumnas2(const string&);
    void listarColumnas3(const string&);
    void listarColumnas4(const string&);

    int partition(int inicio, int final);
    int partition2(int inicio, int final);
    vector<T*>* elementos;

    void listarMap(const string&, const map<string, long long int>&);
public:
    Repositorio(const std::string&);
    int size();
    ~Repositorio();

    void listarTransacciones();
    void listarCriterio1();
    void listarCriterio2();


    void ordenarConQuicksort(int inicio, int final);
    void ordenarConQuicksort2(int inicio, int final);

    void merge(int left, int middle, int right);
    void ordenarConMergesort(int left, int right);
    void merge2(int left, int middle, int right);
    void ordenarConMergesort2(int left, int right);

    void ordenarConShellsort(int size);
    void ordenarConShellsort2(int size);

    void heap(int size, int node);
    void ordenarConHeapsort(int size);
    void heap2(int size, int node);
    void ordenarConHeapsort2(int size);

    void sumatoria1();

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


// Quicksort criterio 2:


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
//                                                MERGESORT

//Mergesort criterio 1:

template <class T>
void Repositorio<T>::merge(int left, int middle, int right){
        int i,j,k;
        int n1 = middle - left + 1;
        int n2 = right - middle;
        vector<Transaccion*> L(n1);
        vector<Transaccion*> R(n2);
        for (i = 0; i < n1; ++i)
            L[i] = elementos->at(left + i);
        for (j = 0; j < n2; ++j)
            R[j] = elementos->at(middle + 1 + j);
        i = 0;
        j = 0;
        k = left;
        while (i < n1 && j < n2) {
            if (L[i]->getTradeUsd() >= R[j]->getTradeUsd()) {
                elementos->at(k) = L[i];
                i++;
            }
            else {
                elementos->at(k) = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            elementos->at(k)= L[i];
            i++;
            k++;
        }
        while (j < n2) {
            elementos->at(k)= R[j];
            j++;
            k++;
        }
}

template <class T>
void Repositorio<T>::ordenarConMergesort(int left, int right){

        if (left < right) {
            int middle = left + (right - left) / 2;
            ordenarConMergesort(left, middle);
            ordenarConMergesort(middle + 1, right);

            merge(left, middle, right);
        }
}

// Mergesort criterio 2:

template <class T>
void Repositorio<T>::merge2(int left, int middle, int right){
    int i,j,k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<Transaccion*> L(n1);
    vector<Transaccion*> R(n2);
    for (i = 0; i < n1; ++i)
        L[i] = elementos->at(left + i);
    for (j = 0; j < n2; ++j)
        R[j] = elementos->at(middle + 1 + j);
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i]->getCountryArea() > R[j]->getCountryArea()
            || (L[i]->getCountryArea() == R[j]->getCountryArea() && L[i]->getYear() > R[j]->getYear())
            || (L[i]->getCountryArea() == R[j]->getCountryArea() && L[i]->getYear() == R[j]->getYear() && L[i]->getTradeUsd() >= R[j]->getTradeUsd())) {
            elementos->at(k) = L[i];
            i++;
        }
        else {
            elementos->at(k) = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        elementos->at(k)= L[i];
        i++;
        k++;
    }
    while (j < n2) {
        elementos->at(k)= R[j];
        j++;
        k++;
    }
}

template <class T>
void Repositorio<T>::ordenarConMergesort2(int left, int right){

    if (left < right) {
        int middle = left + (right - left) / 2;
        ordenarConMergesort2(left, middle);
        ordenarConMergesort2(middle + 1, right);

        merge2(left, middle, right);
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
        heap(size, i);
    for (int i = size-1; i >= 0; --i)
    {
        swap(elementos->at(0), elementos->at(i));
        heap( i, 0);
    }
}



//                                                    Funciones de listar:

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

// Listar primer criterio:

template <class T>
void Repositorio<T>::listarTradeUsdQ(const string& nombreArchivo) {
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
void Repositorio<T>::listarTradeUsdM(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    double duration;
    start = clock();

    ordenarConMergesort(0, elementos->size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Mergesort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
}

template <class T>
void Repositorio<T>::listarTradeUsdS(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    double duration;
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
}

template <class T>
void Repositorio<T>::listarTradeUsdH(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
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
}

template <class T>
void Repositorio<T>::listarCriterio1() {
    listarTradeUsdQ("quicksortcriterio1.csv");
    listarTradeUsdM("mergesortcriterio1.csv");
    listarTradeUsdS("shellsortcriterio1.csv");
    listarTradeUsdH("heapsortcriterio1.csv");
}

// Listar segundo criterio:

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
void Repositorio<T>::listarColumnas2(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
    double duration;
    start = clock();

    ordenarConMergesort2(0, size()-1);

    duration = (clock() - start)/(double) CLOCKS_PER_SEC;

    cout<<"Mergesort: "<<duration<<" seconds"<<endl;

    if (archivo) {
        for (Transaccion* transaccion : *deserializador->getElementos()) {
            *archivo << serializador->Serializar(transaccion,",") << endl;
        }
        archivo->close();
    }
    delete archivo;
}

template <class T>
void Repositorio<T>::listarColumnas3(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
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
}


template <class T>
void Repositorio<T>::listarColumnas4(const string& nombreArchivo) {
    fstream* archivo = new fstream(nombreArchivo, ios_base::out);
    clock_t start;
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
}
template <class T>
void Repositorio<T>::listarCriterio2() {
    listarColumnas("quicksortcriterio2.csv");
    listarColumnas2("mergesortcriterio2.csv");
    listarColumnas3("shellsortcriterio2.csv");
    listarColumnas4("heapsortcriterio2.csv");
}


//                                              SUMATORIAS

template <class T>
void Repositorio<T>::listarMap(const string& fileName, const map<string, long long int>& map) {
    fstream* file = new fstream(fileName, ios_base::out); /* Crea el archivo donde se guardará el map*/
    if (file) {
        for (auto it = map.begin(); it != map.end(); it++) { /* Crea un iterador para recorrer el map e imprimir */
            *file << it->first << ", " << it->second << std::endl; /* first: double or triple key, second: value */
        }
        file->close();
    }
    delete file;
}
template <class T>
void Repositorio<T>::sumatoria1() {

    auto* map = new std::map<string, long long int>(); /* Se asigna memoria en heap para el map */

    /* Recorre el vector de records y sumariza el trade_usd por la respectiva doble llave */
    for (auto *elemento : *deserializador->getElementos()){
        (*map)[elementos->getCountryArea()+ ", " + to_string(elementos->getYear())] += elementos->getTradeUsd();
    }
    listarMap("total_trade_by_country_year.csv", *map); /* Llama al método printMap para guardar el map en un archivo */
    delete map;
}
#endif //PROJECT2_REPOSITORIO_H
