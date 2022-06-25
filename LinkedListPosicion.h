#ifndef __LINKEDLIST_P
#define __LINKEDLIST_P

// Defino la estructura de tipo Nodo
struct Posicion {
	int valor;
	struct Posicion* siguiente;
};

// Definio la estructura de datos que contendrá la lista
struct LinkedListPosicion {
	struct Posicion* primero;
};

// Redefino el nombre de como llamar a los tipos de datos
typedef struct Posicion Posicion;
typedef struct LinkedListPosicion LinkedListPosicion;

// Crea un nodo con un dato y un puntero a NULL
Posicion* crearNodo(int);

// Crea una lista vacia
LinkedListPosicion* crearLista(void);

// Coloca un elemento en la lista.
// Los elementos se van agregando al final de la lista.
void push(LinkedListPosicion*, int);

#endif    // __LINKEDLIST_H#pragma once
