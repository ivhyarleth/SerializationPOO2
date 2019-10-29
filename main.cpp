#include <iostream>
#include <algorithm>
#include "repositorio.h"
using namespace std;

int main(){

    auto* repositorio = new Repositorio<Transaccion>("sample_data.csv");
    repositorio->mostrarElementos();
    //repositorio->listarTransacciones();
    repositorio->ordenarConQuicksort(0, repositorio->size()-1);

    return 0;
}
