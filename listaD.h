#pragma once
#include <iostream>
#include "nodo.h"
using namespace std;


class listaD
{
private:
    nodo* primero;
    nodo* ultimo;


public:
    listaD();
    void insertarPrimero(char c);
    void eliminarUltimo();
    void buscar(string s);
    void imprimir();
};
