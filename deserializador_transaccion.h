//
// Created by ivhy on 21/10/19.
//

#ifndef PROJECT2_DESERIALIZADOR_TRANSACCION_H
#define PROJECT2_DESERIALIZADOR_TRANSACCION_H

#include "deserializador.h"
#include "transaccion.h"
#include <sstream>

class DeserializadorTransaccion :public Deserializador<Transaccion>{
public:
    DeserializadorTransaccion();
    ~DeserializadorTransaccion();
    Transaccion* deserializar(const string&, char) override;
};

DeserializadorTransaccion::DeserializadorTransaccion() : Deserializador(){}
DeserializadorTransaccion::~DeserializadorTransaccion() {}

Transaccion* DeserializadorTransaccion::deserializar(const string& informacion , char delim) {
    string campo;
    vector<string> campos;
    stringstream stream(informacion);

    while (getline(stream, campo, delim)){
        campos.push_back(campo);
    }

    if (campos.size() == 10){
        string countryArea = campos[0];
        int year = stoi(campos[1]);
        int code = stoi(campos[2]);
        string commodity = campos[3];
        string flow = campos[4];
        long long int trade_usd = stoll(campos[5]);
        string weight = campos[6];
        string quantity_name = campos[7];
        string quantity = campos[8];
        string category = campos[9];

        return new Transaccion(countryArea,year,code,commodity,flow,trade_usd,weight,quantity_name,quantity,category);
    }
    throw logic_error("No se puede crear transacción");
}


#endif //PROJECT2_DESERIALIZADOR_TRANSACCION_H
