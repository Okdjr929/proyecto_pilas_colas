#pragma once
#include "Utilidades.h"


//= ============================
// PROTOTIPOS Y STRUCT COLA
//=============================
struct NodoCola {
	int id;                // Identificador del producto
	string nombre;         // Nombre del producto
	string descripcion;    // Descripción del producto
	float precio;          // Precio del producto
	NodoCola* siguiente;       // Puntero al siguiente nodo
};


void encolar(int, string, string, float);
void mostrarCola();
void desencolar();
NodoCola* buscarCola(int id);
void modificarCola(int id);
void menuCola();

