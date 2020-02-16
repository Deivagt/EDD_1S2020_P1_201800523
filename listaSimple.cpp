#include "listaSimple.h"
#include "nodoNoRev.h"

listaSimple::listaSimple() {
    primero = new nodoNoRev();
    ultimo = new nodoNoRev();
    primero->siguiente = ultimo;
  
    ultimo->siguiente = NULL;

}

void listaSimple::insertarPrimero(nodoNoRev* n) {
    
    n->siguiente = primero->siguiente;
    primero->siguiente = n;
    
}
void listaSimple::ordenar() {

}
void listaSimple::imprimir() {
    nodoNoRev* aux = new nodoNoRev();
    aux = primero->siguiente;
    if (aux->siguiente == NULL) {
        cout << "La lista esta vacia" << endl;
    }
    else {

        while (aux != ultimo) {
            cout << aux->palabraBuscada<<endl;
            aux = aux->siguiente;
        }
    }
}