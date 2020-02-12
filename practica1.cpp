
#include <iostream>

#include "listaD.h"
#include "pila.h"
#include "nodoNoRev.h"

using namespace std;



int main()
{
    pila* hola = new pila();
   
        hola->push("Hola", "Adios",false, "kien", 5);
        hola->push("Si", "No", false, "kien", 5);
        
        hola->imprimir();
        nodoNoRev* aux = hola->pop();
 
        hola->imprimir();
        hola->rePush(aux);
        hola->imprimir();
}

