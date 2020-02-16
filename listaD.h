#pragma once
#include <iostream>
#include "nodo.h"
using namespace std;


class listaD
{
private:
    nodo* primero;
    nodo* ultimo;
    int indice = 0;

public:
    listaD();
    nodo* getPrimero();
    nodo* getUltimo();
 
    void insertarUltimo(char c);
    void eliminarUltimo();
    void eliminar(int id);
    void buscar(string s);
    int reemplazar(string b, string r);
    void reemplazar(string b, string r, int cantidad);
    void insertar(char c, nodo* temp);
    void imprimir();
    listaD* duplicar();
};
