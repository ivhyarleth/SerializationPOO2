#include <iostream>
#include <algorithm>
#include "repositorio.h"
using namespace std;

int main(){

    //auto* repositorio = new Repositorio<Transaccion>("sample_data.csv");
    auto* repositorio = new Repositorio<Transaccion>("commodity_trade_statistics_data.csv");
    //repositorio->mostrarElementos();
    //repositorio->listarTransacciones();

    //repositorio->printTotalTradeUsdByCountryOrArea_year();


    cout<<"Sort by Trade_Usd: "<<endl;
    //repositorio->listarCriterio1();

    cout<<"Sort by country_or_area, year, trade_usd: "<<endl;
    repositorio->listarCriterio2();

    //repositorio->sumatoria1();
    return 0;
}
