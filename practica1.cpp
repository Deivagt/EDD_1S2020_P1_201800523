#include "curses.h"
#include <stdlib.h>
#include <time.h>
#include "listaD.h"
#include "pila.h"
#include "listaSimple.h"
#include "listaCircular.h"




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

int main()
{
    listaCaracteres = new listaD();
    cambios1 = new pila();
    cambios2 = new pila();
    repPalOrd = new listaSimple();


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
    mvwprintw(win, 13, 5, "3. Abrir Archivos Recientes");
    mvwprintw(win, 14, 5, "4. Salir");

    wrefresh(win);

    while (true) {
        int c = wgetch(win);
        

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
        else if (c == 3) {/*CTRL+C*/
   
          

        }
        else if (c == 19) {/*CTRL+S*/

           

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
           
                
            
            
           
            cambios1->rePush(t);
            break;

        }
        else {
            entrada = entrada + (char)c;
        }
    }

    refrescar();
}
void abrirArchivo() {
  
    wclear(win);
    
    mvwprintw(win, 2, 5, "Menu Abrir Archivo");
    wrefresh(win);
    
 

    while (true) {
       
        char c = wgetch(win);
        wprintw(win, "%d", c);

        if (c == 52) {
            menuPrincipal();
            break;
          
        }
    }

}

void abrirRecientes() {
}









