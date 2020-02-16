#pragma once
#include <iostream>
#include "nodoNoRev.h"
using namespace std;

class listaSimple
{
private:
    nodoNoRev* primero;
    nodoNoRev* ultimo;


public:
    listaSimple();
    void insertarPrimero(nodoNoRev* n);
    void ordenar();
    void imprimir();
};

