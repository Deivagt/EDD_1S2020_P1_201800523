#pragma once
#include "nodoNoRev.h"
class pila
{
private:
	

public:
	nodoNoRev* cabeza;
	pila();
	void push(string palabraBuscada = NULL, string palabraReemplazada = NULL, bool revertido = false, string palabra = NULL, int posicion = NULL);
	void rePush(nodoNoRev* n);
	nodoNoRev* pop();
	nodoNoRev* peek();
	void imprimir();
};

