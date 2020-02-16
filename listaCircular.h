

#include <iostream>
#include "nodoLC.h"
#include "curses.h"
using namespace std;


class listaCircular
{
private:
    nodoLC* primero;
    nodoLC* ultimo;


public:
    listaCircular();
    void insertarUltimo(nodoLC* n) ;
    void imprimir();
};

