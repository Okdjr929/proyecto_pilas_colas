#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <iomanip>


#define ANCHO 156
#define ALTO 40

#define YINICIAL 11
#define XINICIAL 64

#define arriba 72
#define abajo 80
#define enter 13

using namespace std;
//COLOR DEL TEXTO
void color(int);

//MOVILIDAD EN EL MENÚ CON FLECHAS A TRAVÉS DE GOTOXY
void gotoxy(int, int);

void imprimirCentradoModulo(string, int);

//SIMPLIFICACION DE OPCIONES DEL MENÚ Y SUBMENÚ
int menu(string, string[], int);

void dibujarLineasModulo();

string direccionCorta(void*, int, int);


