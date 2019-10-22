#include <iostream>
#include "repositorio.h"
using namespace std;

int main(){

    auto* repositorio = new Repositorio<Transaccion>("sample_data.csv");
    repositorio->mostrarElementos();

    return 0;
}
