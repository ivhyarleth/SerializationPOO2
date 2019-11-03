//
// Created by ivhy on 19/10/19.
//

#ifndef PROJECT2_TRANSACCION_H
#define PROJECT2_TRANSACCION_H

#include <iostream>
#include <string>
using namespace std;

class Transaccion{
protected:
    string countryArea;
    string year;
    int code;
    string commodity;
    string flow;
    long long int trade_usd;
    string weight;
    string quantity_name;
    string quantity;
    string category;
public:
    Transaccion(const string &, const string &, int, const string &c, const string &, long long int,  const string & , const string &,  const string &, const string &);

    virtual ~Transaccion();
    const string &getCountryArea() const;
    const string & getYear() const;
    int getCode() const;
    const string &getCommodity() const;
    const string &getFlow() const;
    long long int getTradeUsd() const;
    const string &getWeight() const;
    const string &getQuantityName() const;
    const string &getQuantity() const;
    const string &getCategory() const;


};


Transaccion::Transaccion(const string &countryArea, const string & year, int code, const string &commodity, const string &flow,
                         long long int tradeUsd, const string &weight, const string &quantityName, const string &quantity,
                         const string &category) : countryArea(countryArea), year(year), code(code),
                                                   commodity(commodity), flow(flow), trade_usd(tradeUsd),
                                                   weight(weight), quantity_name(quantityName), quantity(quantity),
                                                   category(category) {}
Transaccion::~Transaccion() {}

const string& Transaccion::getCountryArea() const {
    return countryArea;
}

const string & Transaccion::getYear() const {
    return year;
}

int Transaccion::getCode() const {
    return code;
}

const string& Transaccion::getCommodity() const {
    return commodity;
}

const string& Transaccion::getFlow() const {
    return flow;
}

long long int Transaccion::getTradeUsd() const {
    return trade_usd;
}

const string & Transaccion::getWeight()  const {
    return weight;
}

const string& Transaccion::getQuantityName() const {
    return quantity_name;
}

const string & Transaccion::getQuantity() const {
    return quantity;
}

const string& Transaccion::getCategory() const {
    return category;
}

#endif //PROJECT2_TRANSACCION_H
