#pragma once
#include "Utilidades.h"
//=============================
// PROTOTIPO Y STRUCT LISTA SIMPLE
//=============================
struct NodoLista {
	int id;
	string nombre;
	string descripcion;
	float precio;
	NodoLista* siguiente;
};

void insertarOrdenado(NodoLista*&, int, string, string, float);
void mostrarLista(NodoLista*);
void eliminarNodoLista(NodoLista*&, int);
void vaciarLista(NodoLista*&);
void buscarLista(NodoLista*, int);
void modificarLista(NodoLista*, int);
void menuListaSimple();

