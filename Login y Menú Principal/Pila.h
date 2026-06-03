#pragma once
#include "Utilidades.h"

//=============================
// PROTOTIPOS Y ESTRUCT PILA
//=============================
//NODO-PILA
struct NodoPila {
	int id;
	string nombre;
	string descripcion;
	float precio;
	NodoPila* siguiente;
};
void push(NodoPila*&);
void pop(NodoPila*&);
void buscarPila(NodoPila*, int);
void modificarPila(NodoPila*, int);
void mostrarPila(NodoPila*);
void menuPila();

