#pragma once
#include "Utilidades.h"

//=============================
// PROTOTIPOS, STRUCT, RECORRRIDOS Y VARIABLES GLOBALES DEL ÁRBOL AVL
//=============================
struct NodoAVL {
	int id;
	string nombre;
	string descripcion;
	float precio;
	NodoAVL* izquierda;
	NodoAVL* derecha;
	int altura = 1;
};


//------------PROTOTIPOS DE FUNCIONES PARA EL ÁRBOL AVL----------------
int obtenerAltura(NodoAVL*);
int obtenerFactorEquilibrio(NodoAVL*);

//Cuando el árbol está cargado a la derecha
void rotacionSimpleDerecha(NodoAVL*&);

//Cuando el árbol está cargado a la izquierda
void rotacionSimpleIzquierda(NodoAVL*&);

void rotacionDerechaIzquierda(NodoAVL*&);

void rotacionIzquierdaDerecha(NodoAVL*&);


//----------------DIBUJAR LA CAJA DE DATOS-------------------------------
string obtenerDireccionAVL(NodoAVL*);
void dibujarCajaAVL(int, int, int, string, float, int);
// Función recursiva que calcula las coordenadas exactas de cada nodo y sus diagonales
void mostrarArbolAVL(NodoAVL*, int, int, int);
//--------------------------------------------------------------------


// Recalcular alturas de la raíz de subárbol y sus hijos inmediatos
void actualizarAlturasPostRotacion(NodoAVL*);
//Insertar
void insertarAVL(NodoAVL*&, int, string, string, float);
//Buscar
NodoAVL* buscarAVL(NodoAVL*, int);
//Mostrar sin estructura de árbol
void mostrarAVL(NodoAVL*);


void vaciarAVL(NodoAVL*&);

//---------MÉTODOS PROPIOS PARA ELIMINAR UN NODO------------------------
int obtenerAlturaE(NodoAVL*);

int obtenerBalance(NodoAVL*);

NodoAVL* nodoMenorValor(NodoAVL*);

NodoAVL* rotarDerecha(NodoAVL*);

NodoAVL* rotarIzquierda(NodoAVL*);

NodoAVL* eliminarAVL(NodoAVL*&, int, bool);
//--------------------------------------------------------------------------
void menuArbolAVL();
