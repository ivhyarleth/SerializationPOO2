#include <iostream>
#include <algorithm>
#include "repositorio.h"
using namespace std;

int main(){

    //auto* repositorio = new Repositorio<Transaccion>("sample_data.csv");
    auto* repositorio = new Repositorio<Transaccion>("commodity_trade_statistics_data.csv");


    cout<<"Sort by Trade_Usd: "<<endl;
    repositorio->listarCriterio1();

    cout<<"Sort by country_or_area, year, trade_usd: "<<endl;
    //repositorio->listarCriterio2();


    return 0;
}
