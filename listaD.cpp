#include "listaD.h"


listaD::listaD() {
    primero = new nodo();
    ultimo = new nodo();
    primero->siguiente = ultimo;
    primero->anterior = NULL;

    ultimo->anterior = primero;
    ultimo->siguiente = NULL;



}

void listaD::insertarPrimero(char c)
{
    nodo* aux = new nodo();
    aux->letra = c;
    aux->anterior = primero;
    aux->siguiente = primero->siguiente;

    primero->siguiente->anterior = aux;
    primero->siguiente = aux;

}
void listaD::eliminarUltimo() {
    nodo* aux = new nodo();

    if (!(primero->siguiente == ultimo && ultimo->anterior == primero)) {
        aux = ultimo->anterior;

        aux->anterior->siguiente = ultimo;
        ultimo->anterior = aux->anterior;

        aux->siguiente = NULL;
        aux->anterior = NULL;


    }
    else {
        cout << "La lista esta vacia" << endl;
    }



}

void listaD::imprimir() {
    nodo* aux = new nodo();
    aux = ultimo->anterior;
    if (aux->anterior == NULL) {
        cout << "La lista esta vacia" << endl;
    }
    else {

        while (aux != primero) {
            cout << aux->letra;
            aux = aux->anterior;
        }
    }
}

void listaD::buscar(string s) {

    char buffer[100];
    int tB = 0;

    strcpy_s(buffer, s.c_str());


    nodo* aux = new nodo();
    nodo* temp = new nodo();
    aux = ultimo->anterior;

    bool match = false;

    if (aux->anterior == NULL) {
        cout << "La lista esta vacia" << endl;
    }
    else {

        while (aux != primero) {
            if (aux->letra == buffer[tB]) {

                if (tB == 0) {
                    temp = aux;
                }

                match = true;

                tB++;
            }



            aux = aux->anterior;

        }
        if (match == true) {
            cout << "La primera letra es: " << temp->letra << endl;
        }
        else {
            cout << "Palabra no encontrada" << endl;
        }
    }

}