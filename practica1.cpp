
#include <iostream>
#include "listaD.h"
using namespace std;



int main()
{
    listaD* hola = new listaD;
    string s = "hola";
    hola->insertarPrimero(' ');
   
    hola->insertarPrimero('h');
    hola->insertarPrimero('o');
    hola->insertarPrimero('l');
    hola->insertarPrimero('e');
    hola->imprimir();
  
    hola->buscar(s);
}

