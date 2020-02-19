#include "listaCircular.h"

listaCircular::listaCircular() {
	primero = new nodoLC();
	ultimo = new nodoLC();
	primero->siguiente = ultimo;
	ultimo->siguiente = primero;
}

void listaCircular::insertarPrimero(nodoLC* n) {
	nodoLC* aux = new nodoLC();
	aux = primero;
	
	n->siguiente = aux->siguiente;
	aux->siguiente = n;
	
}
nodoLC* listaCircular::getPrimero() {
	return primero;
}
nodoLC* listaCircular::getUltimo() {
	return ultimo;
}
nodoLC* listaCircular::buscar(int id) {
	nodoLC* aux = new nodoLC();
	aux = primero;

	while (aux->siguiente != primero) {
		aux = aux->siguiente;
		if (aux->id == id) {
			
			break;
		}
		
	}
	return aux;
}