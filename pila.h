#pragma once
#include "nodoNoRev.h"
class pila
{
private:
	nodoNoRev* cabeza;

public:
	pila();
	void push(string palabraBuscada = NULL, string palabraReemplazada = NULL, bool revertido = false, string palabra = NULL, int posicion = NULL);
	void rePush(nodoNoRev* n);
	nodoNoRev* pop();
	nodoNoRev* peek();
	void imprimir();
};

