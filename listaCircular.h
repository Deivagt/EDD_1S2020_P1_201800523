

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
    void insertarPrimero(nodoLC* n) ;
    void imprimir();
    nodoLC* getPrimero();
    nodoLC* getUltimo();
    nodoLC* buscar(int id);
};

