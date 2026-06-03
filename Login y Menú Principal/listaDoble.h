#pragma once
#include "Utilidades.h"
//=============================
// PROTOTIPOS Y STRUCT LISTA DOBLE
//=============================
//Struct
struct NodoDoble {
	int id;
	string nombre;
	string descripcion;
	float precio;
	NodoDoble* siguiente;
	NodoDoble* anterior;
};

//Prototipos
void insertarDoble(NodoDoble*&);
void eliminarDoble(NodoDoble*&, int);
void mostrarDoble(NodoDoble*);
void buscarDoble(NodoDoble*, int);
void modificarDoble(NodoDoble*, int);
void vaciarDoble(NodoDoble*&);
void menuListaDoble();
