#include "pila.h"

pila::pila() {
	cabeza = new nodoNoRev();

}
void pila::push(nodoNoRev* n) {

		n->siguiente = cabeza;
		cabeza->siguiente = n;

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