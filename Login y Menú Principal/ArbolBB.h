#pragma once
#include "Utilidades.h"
//=============================
// PROTOTIPOS, STRUCT, RECORRRIDOS Y VARIABLES GLOBALES DEL ÁRBOL BINARIO
//=============================
// Nodo del árbol binario
struct NodoArbol {
	int id;
	string nombre;
	string descripcion;
	float precio;

	NodoArbol* izquierdo;
	NodoArbol* derecho;
};



// Insertar y crear nodo en el árbol
void insertarNodo(NodoArbol*&, int, string, string, float);

// Buscar nodo por ID
NodoArbol* buscarNodo(NodoArbol*&, int);

// Eliminar todo el árbol
void eliminarArbol(NodoArbol*&);

//Eliminar NODO
NodoArbol* encontrarMinimo(NodoArbol*);
void eliminarNodo(NodoArbol*&, int);

void dibujarCaja(int, int, int, string, float);
void mostrarArbol(NodoArbol*, int, int, int);

//RECORRIDO DE ÁRBOL
		//----------PREORDEN------------
void preOrden(NodoArbol*, int&);
//----------POSTORDEN------------
void postOrden(NodoArbol*, int&);
//----------INORDEN------------
void inOrden(NodoArbol*, int&);

void mostrarNodo(NodoArbol*);

//Mostrar datos sin estructura
void mostrarDatosABB(NodoArbol*);
void mostrarDatosABBRec(NodoArbol*, int&);

void subMenuRecorrido();

//MENU ÁRBOL
void menuArbol();
