//
// Created by ivhy on 21/10/19.
//

#ifndef PROJECT2_SERIALIZADOR_TRANSACCION_H
#define PROJECT2_SERIALIZADOR_TRANSACCION_H

#include "serializador.h"
#include "transaccion.h"
#include <sstream>

template <class T>
class SerializadorTransaccion : public Serializador<Transaccion> {
public:
    SerializadorTransaccion();
    ~SerializadorTransaccion();
    string Serializar(T*, string) override;
};

template <class T>
SerializadorTransaccion<T>::SerializadorTransaccion() : Serializador() {}

template <class T>
SerializadorTransaccion<T>::~SerializadorTransaccion() {}

template <class T>
string SerializadorTransaccion<T>::Serializar(T* transaccion, string delim) {
    return transaccion->getCountryArea() + delim+
            to_string(transaccion->getYear()) + delim +
            to_string(transaccion->getCode()) + delim +
           transaccion->getCommodity() + delim +
           transaccion->getFlow() + delim +
            to_string(transaccion->getTradeUsd()) + delim +
           transaccion->getWeight() + delim +
           transaccion->getQuantityName() + delim +
           transaccion->getQuantity() + delim +
           transaccion->getCategory();
}
#endif //PROJECT2_SERIALIZADOR_TRANSACCION_H
