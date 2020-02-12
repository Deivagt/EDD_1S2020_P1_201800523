#pragma once
#include "nodoNoRev.h"
class pila
{
private:
	nodoNoRev* cabeza;
	int tamanio;
public:
	pila();
	void push(nodoNoRev* n);
	nodoNoRev* pop();
	nodoNoRev* peek();

};

