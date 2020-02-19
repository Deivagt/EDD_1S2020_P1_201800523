#include "curses.h"
#include <stdlib.h>
#include <time.h>
#include "listaD.h"
#include "pila.h"
#include "listaSimple.h"
#include "listaCircular.h"
#include <iostream>
#include <fstream>
#include<string>



WINDOW* win;

listaD* listaCaracteres;
pila* cambios1;
pila* cambios2;
listaSimple* repPalOrd;
listaCircular* archiRec;
nodo* aux = new nodo();
int px = 0;
int py = 0;

void menuPrincipal();
void editor();
void abrirArchivo();
void abrirRecientes();
void refrescar();
void deshacer();
void rehacer();
void buscarReemplazar();
void guardar();
int repitoxd(int x, int y);
string graficarLd();
void generarGrafoLd(string e);
string graficarPila();
void generarGrafoPila(string e);
string graficarPila2();
void generarGrafoPila2(string e);
string graficarRecientes();
void generarGrafoRecientes(string e);
void graficasion();

int main()
{
    listaCaracteres = new listaD();
    cambios1 = new pila();
    cambios2 = new pila();
    repPalOrd = new listaSimple();
    archiRec = new listaCircular();

    initscr();
    refresh();
    cbreak();
    raw();
   
    srand(time(NULL));

    constexpr int str_length = 11;

    constexpr int min_width = 13;
    constexpr int min_height = 3;
    constexpr int min_x = 0;
    constexpr int min_y = 0;

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    box(stdscr, 0, 0);
    
    int x = 0;
    int y = 0;

    win = newwin(yMax - 6, xMax - 6, 3, 3);
  
    refresh();
    wrefresh(win);

    keypad(win, true);

    menuPrincipal();
   
    endwin();

    return 0;
}

void menuPrincipal() {

    wclear(win);
    refresh();
   
    mvwprintw(win, 2, 5, "UNIVERSIDAD DE SAN CARLOS DE GUATEMALA");
    mvwprintw(win, 3, 5, "FACULTAD DE INGENIERIA");
    mvwprintw(win, 4, 5, "ESTRUCTURAS DE DATOS");
    mvwprintw(win, 5, 5, "PRACTICA 1");
    mvwprintw(win, 6, 5, "DAVID ALBERTO AVILA BELISLE");
    mvwprintw(win, 7, 5, "201800523");

    mvwprintw(win, 10, 5, "MENU");
    mvwprintw(win, 11, 5, "1. Crear Archivo");
    mvwprintw(win, 12, 5, "2. Abrir Archivo");
    mvwprintw(win, 13, 5, "3. Archivos Recientes");
    mvwprintw(win, 14, 5, "4. Salir");

    wrefresh(win);

    while (true) {
        int c = wgetch(win);
        
        /*wprintw(win, "%i", c);*/
        if (c == 49) {
            
            editor();
            break;
        }
        else if (c == 50) {
            

            abrirArchivo();
            break;
        }
        else if (c == 51) {

            abrirRecientes();
            break;
        }
        else if (c == 52) {
            exit(0);
            break;
        }
    }
}

void editor() {

     px = 0;
     py = 0;
    
    wclear(win);
    
    mvwprintw(win, 23, 15, "CTRL+w (BUSCAR Y REEMPLAZAR)             CTRL+c(REPORTES)            CTRL+s(GUARDAR)");
    wrefresh(win);
    wmove(win, px, py);
    refrescar();
    while (true) {

        int c = wgetch(win);
       
       
         /*if (c == KEY_LEFT) {
             if (py > 0) {
                 py = py - 1;

                 wmove(win, px, py);
          }
           

        }
        else if (c == KEY_RIGHT) {

             if (py < 113) {
                 py = py + 1;

                 wmove(win, px, py);
         }

        }
        else if (c == KEY_UP) {

             if (px > 0) {
                 px = px - 1;

                 wmove(win, px, py);
             }

        }else if (c == 13) {
            if (px <= 25) {
                px = px + 1;
                py = 0;
                wmove(win, px, py);
            }
            listaCaracteres->insertarUltimo((char) c);
            
           

        }
        else if (c == KEY_DOWN) {
             if (px <= 100) {
                 px = px + 1;

                 wmove(win, px, py);
             }


         }
        else */
        if (c == 24) {
            menuPrincipal();
            break;

        }
        else
        if (c == 8) {
            nodoNoRev* t = new nodoNoRev();
            t->palabra = listaCaracteres->getUltimo()->anterior->letra;
            t->posicion = px;
            t->revertido = false;
            t->tipo = 1;
            cambios1->rePush(t); 
             listaCaracteres->eliminarUltimo();
             if (py > 0) {
                 py = py - 1;

                 wmove(win, px, py);
             }
             else {
                 if (px > 0) {
                     py = 112;
                     px = px - 1;

                     wmove(win, px, py);
                 }
             }
             refrescar();

         }
        else if (c == 23) {/*CTRL+W*/
          
            buscarReemplazar();
           
         
        }
        else if (c == 26) {/*CTRL+Z*/

            deshacer();
            refrescar();

        }
        else if (c == 25) {/*CTRL+Y*/

            rehacer();
            refrescar();

        }
        else if (c == 17) {/*CTRL+V*/
   
            graficasion();
            refrescar();
            


        }
        else if (c == 19) {/*CTRL+S*/

            guardar();
            refrescar();
            menuPrincipal();
            break;
        }
        else {
             listaCaracteres->insertarUltimo((char)c);
             nodoNoRev* t = new nodoNoRev();
             t->palabra = c;
             t->posicion = px;
             t->revertido = false;
             t->tipo = 0;
             cambios1->rePush(t);
             
             py = py + 1;
             if (py == 113) {

                 py = 0;
                 px = px + 1;
             }

             if (cambios2->cabeza->siguiente != NULL) {
              
                 while (cambios2->cabeza->siguiente != NULL) {
                     cambios2->pop();
                    
                 }
             }
           
             refrescar();

        }
    }
}

void refrescar() {
    wclear(win);

    aux = listaCaracteres->getPrimero();

    if (aux->siguiente == listaCaracteres->getUltimo()) {
    }
    else {
        int xt = 0;
        int yt = 0;

        while (aux->siguiente != listaCaracteres->getUltimo()) {
            aux = aux->siguiente;
            mvwprintw(win, xt, yt, "%c%", aux->letra);
            yt = yt + 1;
            if (yt == 113) {
                yt = 0;
                xt = xt + 1;
            }
            px = xt;
            py = yt;
        }
    }

    mvwprintw(win, 23, 15, "CTRL+w (BUSCAR Y REEMPLAZAR)             CTRL+c(REPORTES)            CTRL+s(GUARDAR)");
    wrefresh(win);
    wmove(win, px, py);
}

void deshacer() {
    nodoNoRev* t = cambios1->pop();
    t->revertido = true;
    

    switch (t->tipo) {
    case 0:
        listaCaracteres->eliminarUltimo();

        cambios2->rePush(t);
        break;
    case 1:

        char buffer[50];
        strcpy_s(buffer, t->palabra.c_str());
        listaCaracteres->insertarUltimo(buffer[0]);
        cambios2->rePush(t);
        break;
    case 2:
   
        listaCaracteres = t->temp;
        /*->reemplazar(t->palabraReemplazada, t->palabraBuscada, t->cR);*/
        cambios2->rePush(t);
        break;
    case 3:
        break;
    default:
        break;
    }

    
}

void rehacer() {
    nodoNoRev* t = cambios2->pop();
    t->revertido = false;


    switch (t->tipo) {
    case 0:
        char buffer[50];
        strcpy_s(buffer, t->palabra.c_str());
        listaCaracteres->insertarUltimo(buffer[0]);
        cambios1->rePush(t);
        break;
    case 1:
        listaCaracteres->eliminarUltimo();
        cambios1->rePush(t);
        break;
    case 2:
        listaCaracteres = t->temp1;
       /* listaCaracteres->reemplazar(t->palabraBuscada, t->palabraReemplazada, t->cR);*/
        cambios1->rePush(t);
        break;
    case 3:
        break;
    default:
        break;
    }
}

void buscarReemplazar() {

    string entrada = "";
    wclear(win);

    aux = listaCaracteres->getPrimero();

    if (aux->siguiente == listaCaracteres->getUltimo()) {
    }
    else {
        int xt = 0;
        int yt = 0;

        while (aux->siguiente != listaCaracteres->getUltimo()) {
            aux = aux->siguiente;
            mvwprintw(win, xt, yt, "%c%", aux->letra);
            yt = yt + 1;
            if (yt == 113) {
                yt = 0;
                xt = xt + 1;
            }
            px = xt;
            py = yt;
        }
    }
    mvwprintw(win, 20, 15, "Buscar y reemplazar(B;R):");
    mvwprintw(win, 23, 15, "CTRL+w (BUSCAR Y REEMPLAZAR)             CTRL+c(REPORTES)            CTRL+s(GUARDAR)");
    wrefresh(win);
 
    wmove(win, 20, 40);

    while (true) {

        int c = wgetch(win);
      /*  wprintw(win, "%i", c);*/
        if (c == 13) {
            string b;
            string r;

           
           string separador = ";";
           
            size_t pos = 0;
           string token;
            while ((pos = entrada.find(separador)) != string::npos) {
                token = entrada.substr(0, pos);
            
                    b = token;
             
                entrada.erase(0, pos + separador.length());
                
            }
            r = entrada;
            
            nodoNoRev* t = new nodoNoRev();
            t->palabraBuscada = b;
            t->palabraReemplazada = r;
            t->revertido = false;
            t->tipo = 2;
            t->temp = listaCaracteres->duplicar();
            int a = listaCaracteres->reemplazar(b, r);
            t->temp1 = listaCaracteres->duplicar();
            t->cR = a;
           
                
            
            
            if (t->cR != 0) {
                if (cambios2->cabeza->siguiente != NULL) {

                    while (cambios2->cabeza->siguiente != NULL) {
                        cambios2->pop();

                    }
                }
           }
            cambios1->rePush(t);
            break;

        }
        else if (c == 24) {

            break;
        }
        else {
            entrada = entrada + (char)c;
        }
    }

    refrescar();
}

void abrirArchivo() {
    string entrada = "";
    string cuerpo = "";
    string salida = "";
    wclear(win);
    
   
   
    mvwprintw(win, 23, 15, "Abrir Archivo [RUTA]: ");
    wrefresh(win);
    wmove(win, 23, 37);
 

    while (true) {

        int c = wgetch(win);
        if (c == 24) {
            menuPrincipal();
            break;

        }
        else
            if (c == 13) {
                ifstream file;
                file.open(entrada);
                while (!file.eof()) {
                    file >> cuerpo;

                    salida = salida + cuerpo + " ";
                    if (cuerpo == "") {
                        break;
                    }
                }
            
                file.close();

                string nombre = "";
                string ruta = "";


                string separador = "\\";

                size_t pos = 0;
                string token;
                while ((pos = entrada.find(separador)) != string::npos) {
                    token = entrada.substr(0, pos);

                    ruta = ruta +token +"\\\\";

                    entrada.erase(0, pos + separador.length());

                }
                nombre = entrada;


                listaD* nuevo = new listaD();
                for (int i = 0; i < salida.length() - 1; i++) {
                    nuevo->insertarUltimo(salida[i]);
                }
                listaCaracteres = nuevo;
                nodoLC* n = new nodoLC();
                n->rutaArchivo = ruta;
                n->nombreArchivo = nombre;
                
                archiRec->insertarPrimero(n);
                
                editor();
                break;
            
           
            /*D:\salida\b.txt*/

        }
        else {
            entrada = entrada + (char)c;
        }
    }

}

int repitoxd(int x, int y) {
    int tx = 4;
    int ty = 7;
    int id = 4;
    nodoLC* aux = new nodoLC();
    aux = archiRec->getPrimero();
    wclear(win);
    mvwprintw(win, x, y, "*");
   

    while (aux->siguiente != archiRec->getUltimo()) {
        aux = aux->siguiente;
        aux->id = id;
        string auxi = "";
        char buffer[100];
        auxi = auxi + aux->nombreArchivo + "         " + aux->rutaArchivo;
        strcpy_s(buffer, auxi.c_str());
        mvwprintw(win, id, ty, buffer);
        id++;
    }

    mvwprintw(win, 2, 5, "ARCHIVOS RECIENTES");
    mvwprintw(win, 23, 5, "X. Generar reporte de archivos recientes");
    wrefresh(win);
    
    return id;
}

void abrirRecientes() {
    int x = 4;
    int y = 5;
  
   
   int id =  repitoxd(x, y);


    while (true) {
       

        int c = wgetch(win);

    
        if (c == 24) {
            menuPrincipal();
            break;

        }
        else if (c == KEY_UP) {

            if (x > 4) {
                x = x - 1;

               
            }
             repitoxd(x, y);
        }
        else if (c == KEY_DOWN) {
            if (x <= id-2) {
                x = x + 1;
              
                
            }
         
           repitoxd(x, y);

        }
        else if (c == 13) {
            string cuerpo;
            string entrada;
            string salida;
            nodoLC* t = new nodoLC();
            if (archiRec->getPrimero()->siguiente != archiRec->getPrimero()) {
                t = archiRec->buscar(x);
              
                
            }
           


            if (t->rutaArchivo != "") {
                ifstream file;
                file.open(t->rutaArchivo);
                while (!file.eof()) {
                    file >> cuerpo;
                    salida = salida + cuerpo + " ";
                    
                }
                file.close();


                listaD* nuevo = new listaD();
                for (int i = 0; i < salida.length() - 1; i++) {
                    nuevo->insertarUltimo(salida[i]);
                }
                listaCaracteres = nuevo;

                editor();
                break;
            }
            else {
                menuPrincipal();
                break;
            }
            
        


        }
        else if(c== 24){
            if (archiRec->getPrimero()->siguiente != archiRec->getUltimo()) {
                generarGrafoRecientes(graficarRecientes());
            }
            
            abrirRecientes();
        }
     
    }
}

void guardar() {
    string entrada = "";
    string cuerpo = "";
    wclear(win);

    aux = listaCaracteres->getPrimero();

    if (aux->siguiente == listaCaracteres->getUltimo()) {
    }
    else {
        int xt = 0;
        int yt = 0;

        while (aux->siguiente != listaCaracteres->getUltimo()) {
            aux = aux->siguiente;
            mvwprintw(win, xt, yt, "%c%", aux->letra);
            yt = yt + 1;
            if (yt == 113) {
                yt = 0;
                xt = xt + 1;
            }
            px = xt;
            py = yt;
        }
    }
    mvwprintw(win, 20, 15, "Guardar: ");
    mvwprintw(win, 23, 15, "CTRL+w (BUSCAR Y REEMPLAZAR)             CTRL+c(REPORTES)            CTRL+s(GUARDAR)");
    wrefresh(win);

    wmove(win, 20, 25);

    while (true) {

        int c = wgetch(win);

        if (c == 13) {
            ofstream file;
            file.open("D:/salida/" + entrada + ".txt");
            cuerpo = listaCaracteres->texto();

            file << cuerpo;
            file.close();

            break;

        }if (c == 24) {
            editor();
            
            break;
        }
        else {
            entrada = entrada + (char)c;
        }
    }

   
}

string graficarLd(){
    string encabezado = " digraph G {";
 
    encabezado = encabezado + "rankdir=LR;";
    encabezado = encabezado + "node0 [label =\"null\"];";
  

    nodo* aux = listaCaracteres->getPrimero()->siguiente;
  
    int i = 1;
    string nodos = "";
    string dir = "";

    while (aux!= listaCaracteres->getUltimo()) {
       
        nodos = nodos + "node" + to_string(i) + "[label = \"" + aux->letra + "\"];";
        if (i - 1 != 0) {
            dir = dir + "node" + to_string(i) + " -> node" + to_string(i - 1) + ";";
        }
        dir = dir + "node" + to_string(i) + " -> node" + to_string(i + 1) + ";";
        i = i + 1;
        aux = aux->siguiente;
    }

    nodos = nodos + "node" + to_string(i) + "[label = \"null\",width=0.5];";
    string fi = "node1 ->node0;";
    string fin = "}";
    encabezado = encabezado + nodos + fi +dir+ fin;

    return encabezado;
}

void generarGrafoLd(string e) {
    ofstream file;
    file.open("listaDoble.txt", ios::out);

    file << e;
    file.close();

    string s1 = "dot -Tpng listaDoble.txt -o D:/grafos/listaDoble.png";
   
    system(s1.c_str());
    system("start D:/grafos/listaDoble.png");
    
   

}

void graficasion() {
    wclear(win);

    aux = listaCaracteres->getPrimero();

    if (aux->siguiente == listaCaracteres->getUltimo()) {
    }
    else {
        int xt = 0;
        int yt = 0;

        while (aux->siguiente != listaCaracteres->getUltimo()) {
            aux = aux->siguiente;
            mvwprintw(win, xt, yt, "%c%", aux->letra);
            yt = yt + 1;
            if (yt == 113) {
                yt = 0;
                xt = xt + 1;
            }
            px = xt;
            py = yt;
        }
    }
    mvwprintw(win, 20, 15, "1) Lista       2) Palabras Reemplazadas      3) Palabras Ordenadas");
    mvwprintw(win, 23, 15, "CTRL+w (BUSCAR Y REEMPLAZAR)        CTRL+q(REPORTES)            CTRL+s(GUARDAR)");
    wrefresh(win);
 
    wmove(win, 21, 15);

    while (true) {
        int c = wgetch(win);

     
        if (c == 49) {
            generarGrafoLd(graficarLd());

            break;
        }
        else if (c == 50) {
           
            if(cambios1->cabeza->siguiente != NULL)
            {
                generarGrafoPila(graficarPila());
            }
            if (cambios2->cabeza->siguiente != NULL)
            {
                generarGrafoPila2(graficarPila2());
            }
            
            break;
        }
        else if (c == 51) {

        }
        else if (c == 24) {
           
            break;
        }
    }

}

string graficarPila() {
    string encabezado = " digraph G {";

    encabezado = encabezado + "rankdir=LR;";
   


    nodoNoRev* aux =cambios1->peek();

    int i = 0;
    string nodos = "";
    string dir = "";
    string rev;
    string pos;
    while (aux != NULL) {
        if (aux->palabraBuscada != "" ) {
            if (aux->revertido == true) { rev = "Revertido"; }
            else { rev = "No Revertido"; }
            pos = aux->posicion;
            nodos = nodos + "node" + to_string(i) + "[label = \"" +"Palabra Buscada: "+ aux->palabraBuscada + "\n" + 
                +"Palabra Reemplazada: "+aux->palabraReemplazada + "\n" +
                +"Estado: " + rev+"\n" +
                +"Palabra: " + aux->palabra + "\n" +
                +"Posicion: " + pos + "\n" +

                
                "\"];";
            if (i != 0) {
                dir = dir + "node" + to_string(i-1) + " -> node" + to_string(i) + ";";
            }

            i = i + 1;
        }
        rev = "";
        aux = aux->siguiente;
    }

  
  
    string fin = "}";
    encabezado = encabezado + nodos  + dir + fin;

    return encabezado;
}

string graficarPila2() {
    string encabezado = " digraph G {";

    encabezado = encabezado + "rankdir=LR;";



    nodoNoRev* aux = cambios2->peek();

    int i = 0;
    string nodos = "";
    string dir = "";
    string rev;
    string pos;
    while (aux != NULL) {
        if (aux->palabraBuscada != "") {
            if (aux->revertido == true) { rev = "Revertido"; }
            else { rev = "No Revertido"; }
            pos = aux->posicion;
            nodos = nodos + "node" + to_string(i) + "[label = \"" + "Palabra Buscada: " + aux->palabraBuscada + "\n" +
                +"Palabra Reemplazada: " + aux->palabraReemplazada + "\n" +
                +"Estado: " + rev + "\n" +
                +"Palabra: " + aux->palabra + "\n" +
                +"Posicion: " + pos + "\n" +


                "\"];";
            if (i != 0) {
                dir = dir + "node" + to_string(i - 1) + " -> node" + to_string(i) + ";";
            }

            i = i + 1;
        }
        rev = "";
        aux = aux->siguiente;
    }



    string fin = "}";
    encabezado = encabezado + nodos + dir + fin;

    return encabezado;
}

void generarGrafoPila(string e) {
    ofstream file;
    file.open("pila.txt", ios::out);

    file << e;
    file.close();

    string s1 = "dot -Tpng pila.txt -o D:/grafos/pila.png";

    system(s1.c_str());
    system("start D:/grafos/pila.png");

}

void generarGrafoPila2(string e) {
    ofstream file;
    file.open("pila2.txt", ios::out);

    file << e;
    file.close();

    string s1 = "dot -Tpng pila2.txt -o D:/grafos/pila2.png";

    system(s1.c_str());
    system("start D:/grafos/pila2.png");

}

string graficarRecientes() {
    string encabezado = " digraph G {";

    encabezado = encabezado + "rankdir=LR;";



    nodoLC* aux = archiRec->getPrimero()->siguiente;

    int i = 0;
    string nodos = "";
    string dir = "";

    while (aux != archiRec->getUltimo()) {
    
       
            nodos = nodos + "node" + to_string(i) + "[label = \""  + aux->nombreArchivo + "\n" +
                +"" + aux->rutaArchivo + "\n" +
                

                "\"];";
            if (i != 0) {
                dir = dir + "node" + to_string(i - 1) + " -> node" + to_string(i) + ";";
            }

            i = i + 1;
        
            aux = aux->siguiente;
       
    }
    if (i != 1) {
        dir = dir + "node" + to_string(i-1) + " -> node0" + ";";
    }

    string fin = "}";
    encabezado = encabezado + nodos + dir + fin;

    return encabezado;
}

void generarGrafoRecientes(string e) {
    ofstream file;
    file.open("archioRec.txt", ios::out);

    file << e;
    file.close();

    string s1 = "dot -Tpng archioRec.txt -o D:/grafos/archioRec.png";

    system(s1.c_str());
    system("start D:/grafos/archioRec.png");


}


