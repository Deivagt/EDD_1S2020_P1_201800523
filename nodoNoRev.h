#pragma once
#include <iostream>
#include "listaD.h"
using namespace std;

class nodoNoRev
{
public:
	string palabraBuscada;
	string palabraReemplazada;
	bool revertido;
	string palabra;
	int posicion;
	int tipo;
	int cR;
	listaD* temp;
	listaD* temp1;
	
	nodoNoRev* siguiente;
	
	friend class pila;
	friend class listaSimple;

	

};

