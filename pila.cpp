#include "pila.h"

pila::pila() {
	cabeza = new nodoNoRev();

}
void pila::push(string palabraBuscada , string palabraReemplazada , bool revertido , string palabra , int posicion) {
	nodoNoRev* n = new nodoNoRev();

	n->palabraBuscada = palabraBuscada;
	n->palabraReemplazada = palabraReemplazada;
	n->revertido = revertido;
	n->palabra = palabra;
	n->posicion = posicion;


	n->siguiente = cabeza;
		cabeza= n;



}

void pila::rePush(nodoNoRev* n) {
	n->siguiente = cabeza;
	cabeza = n;
}

nodoNoRev* pila::pop() {
	if (cabeza->siguiente != NULL) {
		nodoNoRev* aux = new nodoNoRev();
		aux = cabeza;
		cabeza = cabeza->siguiente;
		aux->siguiente = NULL;

		return aux;
	}
	else {
		cout << "la pila esta vacia"<< endl;
	}
	
}

nodoNoRev* pila::peek() {
	if (cabeza->siguiente != NULL) {
		return cabeza;
	}
	else {
		cout << "la pila esta vacia" << endl;
	}
}

void pila::imprimir() {
	nodoNoRev* aux = new nodoNoRev();
	aux = cabeza;

	if (cabeza->siguiente != NULL) {
		while (aux->siguiente != NULL) {
			cout << aux->palabraBuscada << aux->palabraReemplazada << "\n";
			aux = aux->siguiente;
		}
	}
	else {
		cout << "la pila esta vacia" << endl;
	}
	
}