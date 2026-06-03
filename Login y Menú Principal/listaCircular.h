#pragma once
#include "Utilidades.h"

//=============================
// PROTOTIPOS, STRUCT Y VARIABLES GLOBALES LISTA CIRCULAR
//=============================
struct nodoCircular
{
	int id;
	string nombre;
	string descripcion;
	float precio;
	nodoCircular* siguiente;
};



void insertarCircular(int, string, string, float);
void borrarCircular(int);
void mostrarCircular();
void buscarCircular(int);
void modificarCircular(int);
void vaciarListaCircular();
void menuListaCircular();
