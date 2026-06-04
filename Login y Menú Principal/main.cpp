// Login y Menú Principal.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "Utilidades.h"
#include "Login.h"
#include "pantallasInicio.h"
#include "Pila.h"
#include "Cola.h"
#include "listaSimple.h"
#include "listaDoble.h"
#include "listaCircular.h"
#include "ArbolBB.h"
#include "ArbolAVL.h"
#include <mmsystem.h> //Para reproducir sonidos
#pragma comment(lib, "winmm.lib") //Para reproducir sonidos


//MENÚ PRINICIPAL
int menuPrincipal();

//Submenú de listas
void menuListas();


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	login();
	PlaySound(TEXT("iron-man.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");
	logo();
	system("cls");
	pantallaInicio();
	system("cls");
	color(7);
	menuPrincipal();
	
}

//-------------MENÚ PRINCIPAL--------------
//Función para mostrar el menú principal del programa, que permite al usuario 
// seleccionar entre diferentes estructuras de datos o salir del programa.
int menuPrincipal() {
	
	int n = 6;//OPCIONES DEL MENU PRINCIPAL
	string titulo = "MEMU PRINCIPAL";
	string opciones[] = { "Estrucutura de Pila", "Estructura de Cola", "Estructura Listas", "Estructura de Arbol","Estructura de Arbol AVL","Salir"};

	do
	{
		system("title MENU PRINCIPAL");
		system("cls");
		int opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			menuPila();
			break;
		case 2:
			menuCola();
			break;
		case 3:
			menuListas();
			break;
		case 4:
			menuArbol();
			break;
		case 5:
			menuArbolAVL();
			break;
		case 6:
			return 0;
		}
	} while (true);

	cout << endl;
	system("pause");
}

//--------DEFINICIÓN DE FUNCIONES MENU DE LISTAS
void menuListas() {

	int n = 4;//OPCIONES del submenú listas
	string titulo = "MEMU LISTAS";
	string opciones[] = { "Lista Simple", "Lista Doble", "Lista Circular", "Regresar" };

	do
	{
		system("title LISTAS");
		int opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			system("cls");
			menuListaSimple();
			break;
		case 2:
			system("cls");
			menuListaDoble();
			break;
		case 3:
			system("cls");
			menuListaCircular();
			break;
		case 4:
			return;
		}
	} while (true);
}







