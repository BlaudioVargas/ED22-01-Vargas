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

Registro addNPC(Registro *head, NonPC *p, int FPS, bool entrando) {//Se añada una nueva persona al registro
    Registro* npc = new Registro{ 0,FPS,entrando,p,NULL };
    if (!head) {//se agrega un header a la lista enlazada // este header no posee ningun dato importante
        head = npc;
        head->primero = 1;
        head->next = head;
    }
    else {//se agrega un elemento al final de la lista
        Registro* puntero = head;
        while (puntero->next->primero != 1) {//se busca el ultimo elemento de la lista
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
    if (puntero->primero == 0) {//nos aseguramos que no estemos en la cabeza del listado
        int x = p->x;
        int y = p->y;
        double distancia1 = 0;
        double distancia2 = 30;
        int exito = 0;
        //cout << "fps " << FPS << endl;
        while (puntero->primero != 1) {//Se realiza una busqueda para comprobar si existe la persona
            int fps = puntero->FPS;
            int xP = puntero->NPC->xF;
            int yP = puntero->NPC->yF;
            if (fps < FPS && FPS < (fps + 10)) {//Se pregunta si la perosna se encuentra entre 1 o 15 imagenes de diferencia para asegurarnos de una continuidad
                distancia1 = sqrt(pow(xP - x, 2) + pow(yP - y, 2));
                //cout << "distanciaA " << distancia1 << endl;
                if (distancia1 < distancia2) {//Se busca a la perosna mas cercana de nuestro punto de busqueda
                    aux = puntero;
                    distancia2 = distancia1;
                    exito = 1;
                }
            }
            puntero = puntero->next;
        }
        if (exito == 1) {//si se encontro a una persona que cumple con las caracterisitcas deseadas se actualzian los datos
            aux->FPS = FPS;
            NonPC* NPC= aux->NPC;
            NPC->xF = x;
            NPC->yF = y;
            return *head;
        }
    }
    * head = addNPC(head, p, FPS,0);//Si no se actualizaron los datos se agrega una nueva persona al luistado
    return *head;
}


Registro Deteccion(Registro* head, String direccion, int FPS, bool registro) {//Se carga la imagen y se realiza el reconocimiento de personas
    Detector detector;
    Mat imagen;
    //cout << direccion << endl;
    imagen = imread(direccion);
    detector.toggleMode();
    vector<Persona> found = detector.detect(imagen);

    int contador=0;

    for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
    {
        Persona& p = *i;
        NonPC* npc = new NonPC{ p.getXCentro(), p.getYCentro(), p.getXCentro(), p.getYCentro() };
        *head= searchNPC(head, npc, FPS);//Se procede a agregar/actualizar los datos de las personas, con la lista los datps de la persona y el frame de la imagen
        rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(20, 20, 250), 2);
        contador++;
    }
    if (contador > 0 && registro) {
        cout << "\n" <<direccion << endl;
        imshow("People detector", imagen);
        waitKey(0);
    }
    return *head;
}

Registro LectorAutomatico(Registro* head, String direccion, int start, int size, bool registro) {//Se creo un lector para las 2500 imagenes del ejercicio
    int FPS = 1;
    String load ="Loading";
    int puntuacion = 0;
    for (int i = start; i <= size; i += 5) {
        cout << load;
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << i;
        std::string valor = ss.str();
        *head = Deteccion(head, direccion + valor + ".png", FPS, registro);

        system("CLS");
        if (puntuacion < 5) {
            load = load + ".";
            puntuacion++;
        }
        else {
            load = "Loading.";
            puntuacion = 1;
        }
        FPS++;
    }
    cout << "Registro Completo" << endl;
    return *head;
}

Registro CleanList(Registro* head) {//se borran a las personas que no tuvieron ingun movimineto
    Registro* puntero = head;
    while (puntero->next->primero != 1) {
        if ((puntero->next->NPC->x == puntero->next->NPC->xF) && (puntero->next->NPC->y = puntero->next->NPC->yF)) {
            puntero->next = puntero->next->next;
        }
        else {
            if (puntero->next->NPC->x < puntero->next->NPC->xF) {
                puntero->entrando = 1;
            }
            puntero = puntero->next;
        }
    }
    return *head;
}
int Contador(Registro* head, bool entrada) {//Se cuenta las entradas o salidas, eso depende de lo que se desa contar
    Registro* puntero = head;
    int conteo = 0;
    puntero = puntero->next;
    while (puntero->primero != 1) {
        if ((puntero->entrando == entrada)) {
            conteo++;
        }
        puntero = puntero->next;
    }
    return conteo;
}

void Flujo(Registro* head, bool entrada) {
    int hora=-1;
    do {
        cout << "Indique la cantidad de horas del registro" << endl;
        cin >> hora;
    } while (hora<0);
    if (entrada) {
        cout << "El flujo de entrada es: ";
    }
    else {
        cout << "El flujo de salida es: ";
    }
    float flujo = Contador(head, entrada) / hora;
    cout << flujo <<" [Personas/Hora]" << endl;
}

Registro LectorDirigido(String direccion, Registro* head) {
    int entrada = -1;
    do {
        cout << "Indique el numero de imagen del programa para la entrada" << endl;
        cin >> entrada;
        if (entrada < 0 || entrada >2500) {
            cout << "VALOR INVALIDO" << endl;
            entrada = -1;
        }
    } while (entrada < 0);
    int salida = -1;
    do {
        cout << "Indique el numero de imagen del programa para la salida" << endl;
        cin >> salida;
        if (salida < entrada || salida >2500) {
            cout << "VALOR INVALIDO" << endl;
            salida = -1;
        }
    } while (entrada >= salida);
    cout << "Entrada: " << entrada << "Saldia: "<< salida <<endl;
    *head = LectorAutomatico(head, direccion, entrada, salida, 0);//Se procede a crear el listado de personas con los parametros dados
    return *head;
}

typedef struct Registro Registro;
typedef struct NonPC NonPC;
typedef struct Registro2 Registro2;

void menu(String direccion, Registro* head) {
    int seleccion = 0;
    do {
        cout << "OPCIONES" << endl;
        cout << "0] Registro rapido del trafico de personas" << endl;
        cout << "1] Registro con visualizacion de trafico de personas" << endl;
        cout << "2] Contar entradas" << endl;
        cout << "3] Contar salidas" << endl;
        cout << "4] Flujo de entrada" << endl;
        cout << "5] Flujo de salida" << endl;
        cout << "6] Registro por direccion manual" << endl;
        cout << "7] Salir" << endl;
        cin >> seleccion;
        if (seleccion == 0) {
            head->next = head;
            *head = LectorAutomatico(head, direccion, 1, 2500, 0);//Se procede a crear el listado de personas
        }
        else if (seleccion == 1) {
            head->next = head;
            *head = LectorAutomatico(head, direccion, 1, 2500, 1);//Se procede a crear el listado de personas con pausas cuando aparecen personas en pantalla
        }
        else if (seleccion == 2) {
            cout << "Entrada de personas: " << Contador(head, 1) << endl << endl;//Se cuentan las entradas al recinto
        }
        else if (seleccion == 3) {
            cout << "Salida de personas: " << Contador(head, 0) << endl << endl;//Se cuentan las salidas al recinto
        }
        else if (seleccion == 4) {
            Flujo(head, 1);//Se calcula el flujo de entrada de personas
        }
        else if (seleccion == 5) {
            Flujo(head, 0);//Se calcula el flujo de salida de personas
        }
        else if (seleccion == 6) {
            head->next = head;
            *head = LectorDirigido(direccion, head);//Se realiza una registro guiado de la base de datos
        }
        *head = CleanList(head);//Se limpia la lista
    } while (seleccion != 7);
}

int main()
{
    std::cout << "Hello World!\n";
    std::cout << "TALLER CONTAR PERSONAS\n";
    std::cout << "Blaudio Vargas Montano\n";
    String direccion = "C:/Ejemplo01/image";//Las imagenes cargadas son de un tamaño de 288X360 pixeles// si se desea cambianr la direccion de las imagenes se cambian aqui
    Registro registro = addNPC(NULL,NULL, 0,0);//Se crea el header
    menu(direccion, &registro);
    cout << "\nTerminado";
    return 0;
}
