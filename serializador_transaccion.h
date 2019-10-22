//
// Created by ivhy on 21/10/19.
//

#ifndef PROJECT2_SERIALIZADOR_TRANSACCION_H
#define PROJECT2_SERIALIZADOR_TRANSACCION_H

#include "serializador.h"
#include "transaccion.h"

template <class T>
class SerializadorTransaccion : public Serializador<Transaccion> {
public:
    SerializadorTransaccion();
    ~SerializadorTransaccion();
    string Serializar(T*, char) override;
};

template <class T>
SerializadorTransaccion<T>::SerializadorTransaccion() : Serializador() {}

template <class T>
SerializadorTransaccion<T>::~SerializadorTransaccion() {}

template <class T>
string SerializadorTransaccion<T>::Serializar(T* transaccion, char delim) {
    return transaccion->getCountryArea() + delim;
           /*transaccion->getYear() + delim +
           transaccion->getCode() + delim +
           transaccion->getCommodity() + delim +
           transaccion->getFlow() + delim +
           transaccion->getTradeUsd() + delim +
           transaccion->getWeight() + delim +
           transaccion->getQuantityName() + delim +
           transaccion->getQuantity() + delim +
           transaccion->getCategory() + delim ;*/
}
#endif //PROJECT2_SERIALIZADOR_TRANSACCION_H
