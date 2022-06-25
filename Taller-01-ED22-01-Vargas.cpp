// Taller-01-ED22-01-Vargas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//Autor: Blaudio Vargas // Rut:18.923.237-3

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include "Detector.hpp"
#include "Persona.hpp"

using namespace std;
using namespace cv;

typedef struct NonPC {//Esta clase es donde se guardan los datos de las personas que seguimos
    int nort;
    int south;
    int east;
    int weast;
    int x;
    int y;
    int xF;
    int yF;
}NonPC;

typedef struct Registro {//Aqui se implementa la lista enlazada para guardar los datos de los registros //{es posible que tengamos archivos basura, se debe arreglar luego}
    bool primero;
    int FPS;
    bool entrando;
    struct NonPC* NPC;
    struct Registro* next;
}Registro;

Registro addNPC(Registro *head, NonPC *p, int FPS) {//Se añada una nueva persona al registro
    Registro* npc = new Registro{ 0,FPS,0,p,NULL };
    if (!head) {
        head = npc;
        head->primero = 1;
        head->next = head;
    }
    else {
        Registro* puntero = head;
        while (puntero->next->primero != 1) {
            puntero = puntero->next;
        }
        puntero->next = npc;
        npc->next = head;
        puntero = NULL;
    }
    return *head;
}


Registro searchNPC(Registro* head, NonPC* p, int FPS) {//Se busca si existe la persona a agregar existe, en caso de que existe se actualizan sus datos, si no se agrega como nueva persona
    Registro* puntero = head->next;
    Registro* aux = puntero;
    if (puntero->primero == 0) {
        int x = p->x;
        int y = p->y;
        double distancia1 = 0;
        double distancia2 = 9999;
        int exito = 0;
        while (puntero->primero != 1) {//Se realiza una busqueda para comprobar si existe la persona
            int techo = puntero->NPC->yF+50;
            int piso = puntero->NPC->yF-50;
            int paredR = puntero->NPC->xF+50;
            int paredL = puntero->NPC->xF-50;
            int fps = puntero->FPS;
            int xP = puntero->NPC->xF;
            int yP = puntero->NPC->yF;
            if (fps < FPS && FPS < (fps + 30)) {//Se pregunta si la perosna se encuentra entre 1 o 15 imagenes de diferencia para asegurarnos de una continuidad
                if (x < techo && x > piso && y <paredR && y>paredL) {//Nos aseguramos de que la persona este dentro del radio del movimiento de busqueda
                    distancia1 = sqrt(pow(xP - x, 2) + pow(yP - y, 2));
                    if (distancia1 < distancia2) {//Se busca a la perosna mas cercana de nuestro punto de busqueda
                        aux = puntero;
                        distancia2 = distancia1;
                        exito = 1;
                    }
                }
            }
            puntero = puntero->next;
        }
        if (exito == 1) {//si se encontro a una persona que cumple con las caracterisitcas deseadas se actualzian los datos
            aux->NPC->nort= p->nort;
            aux->NPC->south = p->south;
            aux->NPC->east = p->east;
            aux->NPC->weast = p->weast;
            aux->NPC->xF = x;
            aux->NPC->yF = y;
            aux->FPS = FPS;
            return *head;
        }
        waitKey(0);
    }
    *head = addNPC(head, p, FPS);
    return *head;
}


Registro Deteccion(Registro* head, String direccion, int FPS) {
    Detector detector;
    Mat imagen;
    imagen = imread(direccion);
    detector.toggleMode();
    vector<Persona> found = detector.detect(imagen);
    for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
    {
        Persona& p = *i;
        NonPC* npc = new NonPC{ p.getYComienzo(), p.getYFin(), p.getXFin(), p.getXComienzo(), p.getXCentro(), p.getYCentro(), p.getXCentro(), p.getYCentro() };
        *head= searchNPC(head, npc, FPS);
        rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 255, 0), 2);
        circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(0, 0, 255), 3);
        circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
        circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);
    }
    return *head;
}

Registro LectorAutomatico(Registro *head,String direccion) {//Se creo un lector para las 2500 imagenes del ejercicio
    std::cout << "Lector automatico\n";
    String valor;
    int FPS = 1;
    for (int a = 0; a <= 2; a++) {
        if (a == 2) {
            for (int b = 0; b < 5; b++) {
                for (int c = 0; c <= 9; c++) {
                    for (int d = 0; d <= 9; d++) {
                        valor = to_string(a) + to_string(b) + to_string(c) + to_string(d);
                        *head =Deteccion(head, direccion + valor + ".png", FPS);
                        FPS++;
                    }
                }
            }
            valor = to_string(a) + "500";
            *head = Deteccion(head, direccion + valor + ".png", FPS);
            FPS++;
        }
        else {
            for (int b = 0; b <= 9; b++) {
                for (int c = 0; c <= 9; c++) {
                    int d = 0;
                    if (a == 0 && b == 0 && c == 0) {
                        d = 1;
                    }
                    for (d; d <= 9; d++) {
                        valor = to_string(a) + to_string(b) + to_string(c) + to_string(d);
                        *head = Deteccion(head, direccion + valor + ".png", FPS);
                        FPS++;
                    }
                }
            }
        }
    }
    return *head;
}

typedef struct Registro Registro;
typedef struct NonPC NonPC;
typedef struct Registro2 Registro2;

int main()
{
    std::cout << "Hello World!\n";
    String direccion = "C:/Ejemplo01/image";//Las imagenes cargadas son de un tamaño de 288X360 pixeles
    Registro registro = addNPC(NULL,NULL, 0);
    registro= LectorAutomatico(&registro, direccion);
    Registro* puntero = &registro;
    cout << "INFORMACION "<< endl;
    puntero = puntero->next;
    int contadorEntrando = 0;
    int contadorSaliendo=0;
    int horas = 1;
    while (puntero->primero != 1) {
        if (puntero->NPC->x < puntero->NPC->xF) {
            puntero->entrando = 1;
        }
        if ((puntero->entrando == 1) && (puntero->NPC->y < 144) && (puntero->NPC->yF > 144)) {
            contadorEntrando++;
        }
        else if((puntero->NPC->y > 144) && (puntero->NPC->yF < 144)) {
            contadorSaliendo++;
        }
        puntero = puntero->next;
    }
    cout << "Entraron un total de " << contadorEntrando << " personas lo cual nos da unos "<< contadorEntrando / horas <<" [Personas/Hora] ingresando" << endl;
    cout << "Salieron un total de " << contadorSaliendo << " personas lo cual nos da unos " << contadorSaliendo / horas << " [Personas/Hora] saliendo" << endl;
    cout << "\nTerminado";
    return 0;
}
