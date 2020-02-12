#pragma once
#include <iostream>
using namespace std;

class nodoNoRev
{
private:
	string palabraBuscada;
	string palabraReemplazada;
	bool revertido;
	string palabra;
	int posicion;
	
	nodoNoRev* siguiente;

	friend class pila;

	

};

