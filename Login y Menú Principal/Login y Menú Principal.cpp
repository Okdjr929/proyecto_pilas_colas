// Login y Menú Principal.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
/*
												* COLA
	- SECCION AGREGAR PRODUCTO: camibar de color a la verificación: "Producto agregado exitosamente", talvez a un color verde
	- BUSCAR POR ID: cambiar color al aviso: "PRODUCTO NO ENCONTRADO", talvez a rojo
	- BUSCAR POR ID: cambiar color al aviso: "PRODUCTO ENCONTRADO", talvez a verde


													PILA
	- - SECCION AGREGAR PRODUCTO: camibar de color a la verificación: "Producto agregado exitosamente", talvez a un color verde
	- SECCIÓN MOSTRAR PILA: Ponerle el color que tiene la opción mostrar cola
	- PONERLE LOS MISMO COLORES DE COLA A PILA con sus mejoras
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include<string>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <limits>
#include <queue>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define arriba 72
#define abajo 80
#define enter 13
#define ANCHO 156
#define ALTO 40
#define YINICIAL 11
#define XINICIAL 64

using namespace std;

void colorFondo(int fondo) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Obtiene el color actual del texto
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	int colorTexto = csbi.wAttributes & 0x0F;

	// Mantiene el texto y cambia solo el fondo
	SetConsoleTextAttribute(hConsole, colorTexto | (fondo << 4));
}

void restaurarColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//COLOR DEL TEXTO
void color(int);

//MOVILIDAD EN EL MENÚ CON FLECHAS A TRAVÉS DE GOTOXY
void gotoxy(int, int);

//LOGIN DEL PROYECTO
int login();

//SIMPLIFICACION DE OPCIONES DEL MENÚ Y SUBMENÚ
int menu(string, string[], int);

//MENÚ PRINICIPAL
int menuPrincipal();

//PANTALLA DE INICIO
void pantallaInicio();

//LOGO DE LA EMPRESA
void logo();


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

//=============================
// VARIABLES GLOBALES COLA
//=============================
NodoCola* frente = NULL;
NodoCola* fin = NULL;

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

//=============================
// PROTOTIPOS
//=============================
void insertarOrdenado(NodoLista*&, int, string, string, float);
void mostrarLista(NodoLista*);
void eliminarNodoLista(NodoLista*&, int);
void vaciarLista(NodoLista*&);
void buscarLista(NodoLista*, int);
void modificarLista(NodoLista*, int);
void menuListaSimple();


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

//Variables globales
nodoCircular* primero;
nodoCircular* ultimo;

void insertarCircular(int, string, string, float);
void borrarCircular(int);
void mostrarCircular();
void buscarCircular(int);
void modificarCircular(int);
void vaciarListaCircular();
void menuListaCircular();

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

NodoArbol* raiz = NULL;

// Insertar y crear nodo en el árbol
void insertarNodo(NodoArbol*&, int, string, string, float);

// Buscar nodo por ID
NodoArbol* buscarNodo(NodoArbol*&, int);

// Eliminar todo el árbol
void eliminarArbol(NodoArbol*&);

//Eliminar NODO
NodoArbol* encontrarMinimo(NodoArbol*);
void eliminarNodo(NodoArbol*&, int);

string obtenerDireccion(NodoArbol*);
void dibujarCaja(int, int, int, string);
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

//MENU ÁRBOL
void menuArbol();

//=============================
// PROTOTIPOS DE FUNCIONES MENU DE LISTAS
//=============================
void subMenuRecorrido();
void menuListas();


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

NodoAVL* raizAVL = NULL;

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

NodoAVL* eliminarAVL(NodoAVL*&, int);
//--------------------------------------------------------------------------
void menuArbolAVL();


void imprimirCentradoModulo(string texto, int y) {
	int x = (ANCHO - texto.length()) / 2;
	gotoxy(x, y);
	cout << texto;
}

void dibujarLineasModulo() {
	for (int i = 28; i < 128; i++)
	{
		gotoxy(i, 10); cout << "■";
		gotoxy(i, 32); cout << "■";
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	//login();
	//PlaySound(TEXT("iron-man.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");
	//logo();
	system("cls");
	//pantallaInicio();
	system("cls");
	color(7);
	//MÚSICA AGREGADA
	//PlaySound(TEXT("ofa-mai-og-bass.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	menuPrincipal();
	
}

//-----------COLOR DE TEXTO--------------
//Función para cambiar el color del texto en la consola. 
// El parámetro 'c' representa el código de color deseado.
void color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//-----------MOVILIDAD EN EL MENÚ CON FLECHAS A TRAVÉS DE GOTOXY--------------
//Función para mover el cursor a una posición específica en la consola. 
// Los parámetros 'x' e 'y' representan las coordenadas horizontales y verticales, respectivamente.
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//-----------LOGIN--------------
//Función para manejar el proceso de inicio de sesión. 
// Permite al usuario ingresar su nombre y contraseña, y verifica los datos contra un archivo de texto. 
// El usuario tiene un número limitado de intentos para ingresar correctamente.
int login() {
	system("title LOGIN");
	char opcion;
	int i = 0, j = 3;

	// Variables específicas para el proceso de login (ámbito local)
	string nombre; //Almacenará el nombre del usuario
	string contra; //Almacenará la contraseña del usuario
	string linea; //Almacenará la linea leida en el archivo
	string datos[2]; //Este arreglo guarda el nombre (0) y la contraseña(1)
	int contador = 0;
	size_t posicion = 0;

	do
	{
		system("cls");
		cout << "\n\n\n ";
		color(6); //Amarillo
		//system("color 37"); //1er caracter es el fondo, 2do caracter es la letra
		cout << "\n\t\t\t\t\t\t LOGIN VENTA DE AIRE";
		color(7); //Blanco
		cout << "\n\t\t\t\t\t -----------------------------------";
		color(6);
		cout << "\n\t\t\t\t\t Intento: " << j;
		color(7);
		cout << "\n\t\t\t\t\t -----------------------------------";
		color(6);
		cout << "\n\t\t\t\t\t Nombre: ";
		cin >> nombre;
		cout << "\n\t\t\t\t\t Contrasenia: ";
		cin >> contra;
		color(7);
		cout << "\t\t\t\t\t -----------------------------------";

		fstream archivo("Documento.txt");

		while (getline(archivo, linea))
		{
			//La posicion antes de la coma es almacenada en 'posicion'
			while ((posicion = linea.find(",")) != string::npos) //Sí es distinto de npos, significa que sí existe dicho caracter/palabra
			{
				datos[contador] = linea.substr(0, posicion);//Extrae los caracteres en un rango definido, en este case, desde el caracter 0 hasta antes de la coma
				linea.erase(0, posicion + 1); //Borramos desde el caracter 0 hasta la coma, así lo que queda representará la contraseña
				contador++; //Este se incrementa y en la 2da vuelta almacenará la contraseña en la 2do subindicé de datos, que representa la casilla de la contraseña
			}
			contador = 0; //Es para resetear y 
			if (datos[contador] == nombre)
			{
				break;
			}
			//mundo
		}

		if (datos[0] == nombre && datos[1] == contra)
		{
			cout << "\n\n ";
			color(1); //Azul
			cout << "\n\t\t\t\t\t\t	Aceptado";
			cout << "\n\n ";
			color(7);
			system("pause");
			return EXIT_SUCCESS;
		}
		else
		{
			cout << "\n\n ";
			color(4);//Rojo
			cout << "\n\t\t\t\t\t\t   Datos Incorrectos ";
			cout << "\n\n ";
			i++;
			j--;
			color(6);
			cout << "\n\t\t\t\t\t\tIntentar otra vez [S/N] ";
			cin >> opcion;
		}

		if (i >= 3)
		{
			break;
		}

	} while (opcion == 'S' || opcion == 's');
	if (opcion == 'N' || opcion == 'n')
	{
		return 0;
	}
	color(7);
	cout << "\n\n ";
	cout << "\n\t\t\t\t\t\t **Alerta de Intruso** ";
	cout << "\n\n";

	system("PAUSE");
}

//-----------SIMPLIFICACION DE OPCIONES DEL MENÚ Y SUBMENÚ--------------0
//Función para mostrar un menú interactivo en la consola.
int menu(string titulo, string opciones[], int n) {
	int opcionSeleccionada = 1;
	int tecla; //Tecla capturada 
	bool repite = true;

	do
	{
        system("cls");

		// Selección de paleta: menú principal usa colores distintos al resto de submenús
		int titleColor, selectedColor, optionColor, arrowColor, footerColor;
		if (titulo == "MEMU PRINCIPAL") {
			titleColor = 10;     // Verde
			selectedColor = 14;  // Amarillo
			optionColor = 15;    // Blanco brillante
			arrowColor = 12;     // Rojo
			footerColor = 8;     // Gris
		} else {
			titleColor = 2;     // Verde Opaco
			selectedColor = 9;  // Azul
			optionColor = 15;    // Blanco brillante
			arrowColor = 14;     // Amarillo
			footerColor = 8;     // Gris
		}
			
		//Cuadro de olas
		//gotoxy(col, fil)
		for (int i = 28; i < 128; i++)
		{
			gotoxy(i, 8); cout << "≈";
			gotoxy(i, 9); cout << "≈";
			gotoxy(i, 28); cout << "≈";
			gotoxy(i, 29); cout << "≈";
		}
		// Título
		color(titleColor);
		for (int i = 0; i < titulo.length()+6; i++)
		{
			gotoxy((((ANCHO - titulo.length())) / 2) - 3 + i, 11); cout << "▓";
		}
		
		gotoxy((ANCHO-titulo.length())/2, 12); cout << titulo;

		for (int i = 0; i < titulo.length()+6; i++)
		{
			gotoxy((((ANCHO - titulo.length())) / 2) - 3 + i, 13); cout << "▓";
		}
		
		color(7); // reset
		//gotoxy(1, 0); cout << "▓";
		//gotoxy(1, 1); cout << "▓";
		// 	

		//Borde horizontal superior
		//gotoxy(col, fil)
		/*for (int i = 15; i < 141; i++)
		{
			gotoxy(i, 8); cout << "▓";
			gotoxy(i, 9); cout << "▓";
		}
		*/
		/*
		//Borde horizontal inferior
		for (int i = 15; i < 141; i++)
		{
			gotoxy(i, 31); cout << "▓";
			gotoxy(i, 32); cout << "▓";
			
		}
		int icol = 10;
		while (icol < 38) {
			gotoxy(0, icol); cout << "▓";
			gotoxy(155, icol); cout << "▓";
			icol++;
		}
		*/
		
		int Yinicio = (ALTO - n) / 2;

		// Imprimimos las opciones, resaltando la seleccion
		for (int i = 0; i < n; i++)
		{
			gotoxy(((ANCHO-opciones[0].length())/2)-2, Yinicio+ i);
			if (i + 1 == opcionSeleccionada) {
				color(selectedColor);
				cout << i + 1 << ") " << opciones[i];
				color(7);
			} else {
				color(optionColor);
				cout << i + 1 << ") " << opciones[i];
				color(7);
			}

		}

		// Flecha indicadora
		color(arrowColor);
		gotoxy(((ANCHO - opciones[0].length()) / 2) - 7, Yinicio + opcionSeleccionada - 1); cout << "->";
		color(7);

		// Pie de pagina con instrucciones en color tenue
		color(footerColor);
		gotoxy(5, 32); cout << "Usa las flechas para navegar, Enter para seleccionar";
		color(7);
		//------------------------------------------

		//Caputaramos la tecla
		do
		{
			tecla = _getch(); //Para capturar la tecla 
		} while ((tecla != arriba) && (tecla != abajo) && (tecla != enter));

		switch (tecla) {
		case arriba:
			opcionSeleccionada--;
			if (opcionSeleccionada == 0)
			{
				opcionSeleccionada = n;
			}
			break;
		case abajo:
			opcionSeleccionada++;
			if (opcionSeleccionada > n)
			{
				opcionSeleccionada = 1;
			}
			break;
		case enter:
			repite = false;;
		}
	} while (repite);

	return opcionSeleccionada;
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

//-----------PANTALLA DE INICIO-----------
//Función para mostrar una pantalla de inicio con un diseño visual atractivo.
void pantallaInicio() {
	//LETRAS COLORIDAS
	int xcol;

	//CUADRO CON TEXTO
	//Primera línea
	color(14);
	gotoxy(1, 5); cout << "╔";
	gotoxy(1, 6); cout << "║";
	gotoxy(1, 7); cout << "╚";

	for (xcol = 2; xcol <= 154; xcol++)
	{
		gotoxy(xcol, 5); cout << "═";
		gotoxy(xcol, 7); cout << "═";
		Sleep(10);
	}
	gotoxy(155, 5); cout << "╗";
	gotoxy(155, 6); cout << "║";
	gotoxy(155, 7); cout << "╝";

	//TEXTO EN EL CUADRO
	char titulo[] = " VENTA DE AIRE ";
	int longitud;
	longitud = strlen(titulo);
	int centro = (((155 - longitud) / 2) + 1); //CENTRO DE LA PANTALLA = 53

	for (xcol = 2; xcol <= centro; xcol++)
	{
		int colorRandom = (rand() % 15) + 1;
		color(colorRandom);
		gotoxy(xcol, 6); cout << titulo;
		//Sleep(80)
	}

	color(7);
	cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tUNIVERSIDAD MARIANO GALVEZ";
	cout << "\n\t\t\t\t\t\t\t\t  Ingenieria en Sistemas";

	color(8);
	cout << "\n\t\t\t\t\t\t\t------------------------------------------";

	color(10);
	cout << "\n\t\t\t\t\t\t\t\t  PROYECTO PILAS Y COLAS";

	color(8);
	cout << "\n\t\t\t\t\t\t\t------------------------------------------";

	color(7);
	cout << "\n\t\t\t\t\t\t\tJesus Armando Pantzey Santizo - 2290-24-24601";
	cout << "\n\t\t\t\t\t\t\tMiqueas Otoniel Ixcaya Xajil - 2290-24-24181";
	cout << "\n\t\t\t\t\t\t\tEli Emanuel Rosales Bala - 2290-24-14890";

	color(14);
	cout << "\n\n\t\t\t\t\t\t\t\t     PROGRAMACION III";

	gotoxy(1, 38);
	system("pause");
}

//------------LOGO DE LA EMPRESA--------------
//Función para mostrar el logo de la empresa con un diseño visual atractivo.
void logo() {

	color(11);

	cout << "\n\n\n\n\n\n\t\t\t\t\t================================================================================\n\n";

	cout << "\t\t\t\t               █████╗ ██╗██████╗ ███████╗    ████████╗███████╗ ██████╗██╗  ██╗\n";
	cout << "\t\t\t\t              ██╔══██╗██║██╔══██╗██╔════╝    ╚══██╔══╝██╔════╝██╔════╝██║  ██║\n";
	cout << "\t\t\t\t              ███████║██║██████╔╝█████╗         ██║   █████╗  ██║     ███████║\n";
	cout << "\t\t\t\t              ██╔══██║██║██╔══██╗██╔══╝         ██║   ██╔══╝  ██║     ██╔══██║\n";
	cout << "\t\t\t\t              ██║  ██║██║██║  ██║███████╗       ██║   ███████╗╚██████╗██║  ██║\n";
	cout << "\t\t\t\t              ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚══════╝       ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝\n\n";

	color(9);

	cout << "\t\t\t\t                               ╔═════════════════════════════╗\n";
	cout << "\t\t\t\t                           ╔═══╝   ~ ~ ~   A I R E   ~ ~ ~   ╚═══╗\n";
	cout << "\t\t\t\t                        ╔══╝     ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈     ╚══╗\n";
	cout << "\t\t\t\t                      ╔═╝      ≈     ≈     ≈     ≈     ≈     ≈      ╚═╗\n";
	cout << "\t\t\t\t                     ║         ≈        Aire embolsada       ≈         ║\n";
	cout << "\t\t\t\t                     ║         ≈     ≈     ≈     ≈     ≈     ≈         ║\n";
	cout << "\t\t\t\t                      ╚═╗        ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈        ╔═╝\n";
	cout << "\t\t\t\t                        ╚══╗      >>>>>>>>>>>>>>>>>>>>>>>>>      ╔══╝\n";
	cout << "\t\t\t\t                           ╚═══╗    >>>   >>>   >>>   >>>    ╔═══╝\n";
	cout << "\t\t\t\t                               ╚═════════════════════════════╝\n\n";

	color(10);
	cout << "\t\t\t\t\t                   \"Respira tecnologia. Controla el aire.\"\n\n";

	color(8);
	cout << "\t\t\t\t\t================================================================================\n";

	color(7);
	_getch();
}

//=============================
// DEFINICIÓN DE FUNCIONES PILA
//=============================
// Agregar un nuevo elemento a la pila (LIFO)
void push(NodoPila*& pila) {
	NodoPila* nuevo_nodo = new NodoPila();
	int y = 16;
	imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL+2);
    cout << "\n\n\t\t\t\t\t\t\t\tIngrese ID: ";
	cin >> nuevo_nodo->id;
    cin.ignore(1000, '\n');
	cout << endl;
	cout << "\t\t\t\t\t\t\t\tNombre del Producto: ";
	getline(cin, nuevo_nodo->nombre);
	cout << endl;
	cout << "\t\t\t\t\t\t\t\tDescripcion: ";
	getline(cin, nuevo_nodo->descripcion);
	cout << endl;
	cout << "\t\t\t\t\t\t\t\tPrecio: ";
	cin >> nuevo_nodo->precio;

	nuevo_nodo->siguiente = pila;
	pila = nuevo_nodo;

        // Mensaje simple y uniforme de inserción
		color(10);
		cout << "\n\t\t\t\t\t\t\t\tProducto Agregado" << endl;
		color(7);
}

// Eliminar el último elemento agregado (LIFO)
void pop(NodoPila*& pila) {
	if (pila == NULL) {
		color(12);
		imprimirCentradoModulo("La pila esta vacia.", 21);
		color(7);
		_getch();
		return;
	}

	NodoPila* aux = pila;
	pila = aux->siguiente;
	color(10);
	imprimirCentradoModulo("Producto eliminado:", YINICIAL+2);
	cout << "\n\n\t\t\t\t\t\t\t\tID: " << aux->id << endl;
	cout << "\t\t\t\t\t\t\t\tNombre: " << aux->nombre << endl;
	cout << "\t\t\t\t\t\t\t\tDescripcion: " << aux->descripcion << endl;
	cout << "\t\t\t\t\t\t\t\tPrecio: " << aux->precio << endl;
	color(7);
	delete aux;
}

// Buscar por ID
void buscarPila(NodoPila* pila, int busqueda) {
	NodoPila* aux = pila;
	bool encontrado = false;
	while (aux != NULL) {
		if (aux->id == busqueda) {
			encontrado = true;
			break;
		}

		aux = aux->siguiente;
	}
	if (encontrado) {
		color(10);
		imprimirCentradoModulo("Producto encontrado:", 16);

		cout << "\n\n\t\t\t\t\t\t\t\tID: " << aux->id << endl;
		cout << "\t\t\t\t\t\t\t\tNombre: " << aux->nombre << endl;
		cout << "\t\t\t\t\t\t\t\tDescripcion: " << aux->descripcion << endl;
		cout << "\t\t\t\t\t\t\t\tPrecio: " << aux->precio << endl;
		color(7);
	}
	else {
		color(12);
		imprimirCentradoModulo("Producto NO encontrado", 21);
		color(7);
	}

	return;
}

// Modificar un dato por ID
void modificarPila(NodoPila* pila, int busqueda) {
	NodoPila* aux = pila;
	bool encontrado = false;

	while (aux != NULL) {
		if (aux->id == busqueda) {
			encontrado = true;

			imprimirCentradoModulo("--- Producto Encontrado ---", YINICIAL);

			gotoxy(XINICIAL, YINICIAL + 2); cout << "ID actual: " << aux->id << endl;
			gotoxy(XINICIAL, YINICIAL + 3); cout << "Nombre actual: " << aux->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 4); cout << "Descripcion actual: " << aux->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 5); cout << "Precio actual: " << aux->precio << endl;

			imprimirCentradoModulo("--- Ingrese los Nuevos Datos ---", YINICIAL + 6);
			cin.ignore(1000, '\n');

			gotoxy(XINICIAL, YINICIAL + 7); cout << "Nuevo Nombre: ";
			getline(cin, aux->nombre);

			gotoxy(XINICIAL, YINICIAL + 8); cout << "Nueva Descripcion: ";
			getline(cin, aux->descripcion);

			gotoxy(XINICIAL, YINICIAL + 9); cout << "Nuevo Precio: ";
			cin >> aux->precio;
			cin.ignore(1000, '\n');

			color(10);
			gotoxy(XINICIAL, YINICIAL + 10); cout << "\nProducto modificado correctamente." << endl;
			color(7);
			break;
		}
		aux = aux->siguiente;
	}

  if (!encontrado) {
		color(12);
		imprimirCentradoModulo("Producto NO encontrado", 21);
		color(7);
	}
}

//Mostrar datos en forma de pila (LIFO)
void mostrarPila(NodoPila* pila) {

	system("cls");

	// ===== MARCO =====
	for (int i = 28; i <= 128; i++) {
		gotoxy(i, 1); cout << "■";
		gotoxy(i, 40); cout << "■";
	}

	for (int i = 2; i <= 39; i++) {
		gotoxy(28, i); cout << "■";
		gotoxy(128, i); cout << "■";
	}

	// ===== TITULO =====
	color(11);
	imprimirCentradoModulo("======= INVENTARIO EN PILA (LIFO) =======", 2);

	// ===== VALIDACION =====
	if (pila == NULL) {
		color(12);

		imprimirCentradoModulo("PILA VACIA", 21);

		color(7);
		_getch();
		return;
	}

	// ===== CONTENIDO =====
	NodoPila* aux = pila;

	int y = 5;

	while (aux != NULL && y < 30) {

		gotoxy(32, y++);
		cout << "Direccion: " << aux;

		gotoxy(32, y++);
		cout << "ID: " << aux->id;

		gotoxy(32, y++);
		cout << "Nombre: " << aux->nombre;

		gotoxy(32, y++);
		cout << "Descripcion: " << aux->descripcion;

		gotoxy(32, y++);
		cout << "Precio: " << aux->precio;

		gotoxy(32, y++);
		cout << "Apunta a: " << aux->siguiente;

		gotoxy(32, y++);
		cout << "-----------------------------------------------------";

		y++;

		aux = aux->siguiente;
	}

	color(7);

	gotoxy(55, 31);
	system("pause");
}

//MENÚ DE LA PILA
void menuPila() {
	NodoPila* pila = NULL;

	int opc;
	string titulo = "Estructura de Pila";
	string opciones[] = { "Ingreso de Datos de Pila", "Ver Datos en forma de Pila", "Modificar un dato", "Buscar un dato", "Eliminar un dato", "Atras (Menu Principal)" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones

	do
	{

		opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			//AGREGAR EL PRODUCTO
			system("cls");
			dibujarLineasModulo();
			//gotoxy((ANCHO - 35) / 2, 16);
			push(pila);
			gotoxy(60, 31); system("pause");
			break;
		case 2:
			//MOSTRAR LA PILA
			system("cls");
			mostrarPila(pila);
			break;
		case 3:
			//MODIFICAR
			system("cls");
			dibujarLineasModulo();
			int id; //ID a modificar
			imprimirCentradoModulo("Ingrese el ID del producto que desea MODIFICAR: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarPila(pila, id);
			gotoxy(60, 31); system("pause");
			break;
		case 4:
			//BUSCAR EL ID
			system("cls");
			dibujarLineasModulo();
			int idB; //ID a buscar
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", YINICIAL + 2);
			cin >> idB;
			system("cls");
			dibujarLineasModulo();
			buscarPila(pila, idB);
			gotoxy(60, 31); system("pause");
			break;
		case 5:
			//ELIMINAR EL ÚLTIMO
			system("cls");
			dibujarLineasModulo();
			pop(pila);
			gotoxy(60, 31); system("pause");
			break;
		case 6:
			return;
		default:
			cout << "Opcion invalida." << endl;
		}
	} while (true);

	system("pause");
}

//=============================
// DEFINICIÓN DE FUNCIONES COLA
//=============================
string direccionCorta(void* lista) {
	stringstream ss;
	ss << lista;
	string direccion = ss.str();
	if (direccion.length() > 8) {
		//return direccion.substr(direccion.length() - 6)+ "..";
		return ".." + direccion.substr(direccion.length() - 6);
	}
}
// Insertar datos en la cola
void encolar(int id, string nombre, string descripcion, float precio) {
	NodoCola* nuevo = new NodoCola();

	nuevo->id = id;
	nuevo->nombre = nombre;
	nuevo->descripcion = descripcion;
	nuevo->precio = precio;
	nuevo->siguiente = NULL;

	if (frente == NULL) {
		frente = nuevo;
	}
	else {
		fin->siguiente = nuevo;
	}

	fin = nuevo;
   // Mensaje simple y coloreado
	color(10);
	gotoxy(XINICIAL, YINICIAL + 12); cout << "Producto Agregado" << endl;
	color(7);
}

// Mostrar datos (horizontal)
void dibujarNodoCola(int x, int y, NodoCola* nodo) {

	string actual = direccionCorta(nodo);
	string siguiente = direccionCorta(nodo->siguiente);

	

	gotoxy(x, y);
	cout << "+------------------+";
	color(11);
	gotoxy(x, y + 1);
	cout << "| "
		<< setw(16)
		<< left
		<< actual
		<< " |";

	color(7);

	gotoxy(x, y + 2);
	cout << "| ID: "
		<< setw(12)
		<< left
		<< nodo->id
		<< " |";

	gotoxy(x, y + 3);
	cout << "| "
		<< setw(16)
		<< left
		<< nodo->nombre.substr(0, 16)
		<< " |";

	gotoxy(x, y + 4);
	cout << "| Q"
		<< setw(15) //setw es para establecer un ancho fijo para el campo
		<< left //left sirve para alinear a la izquierda, right para alinear a la derecha
		<< fixed //fixed es para mostrar el número en formato decimal fijo, sin notación científica
		<< setprecision(2) //es para mostrar el precio con 2 decimales
		<< nodo->precio
		<< " |";

	color(11);
	gotoxy(x, y + 5);
	cout << "| "
		<< setw(16)
		<< left
		<< "Sig: " + siguiente
		<< " |";

	color(7);

	gotoxy(x, y + 6);
	cout << "+------------------+";

	color(7);
	y += 5;
}

void mostrarCola()
{
	system("cls");

	// ===== MARCO PRINCIPAL =====
	for (int i = 2; i <= 150; i++) {
		gotoxy(i, 1);  cout << "■";
		gotoxy(i, 38); cout << "■";
	}

	for (int i = 2; i <= 38; i++) {
		gotoxy(2, i);   cout << "■";
		gotoxy(150, i); cout << "■";
	}

	// ===== TITULO =====
	color(11);

	imprimirCentradoModulo("======= INVENTARIO FORMA COLA =======", 2);

	if (frente == NULL) {

		cout << "COLA VACIA";

		return;
	}

	NodoCola* aux = frente;

	int x = 5;

	int y = 10;

	while (aux != NULL) {

		dibujarNodoCola(x, y, aux);

		// ===== FLECHA =====
		if (aux->siguiente != NULL) {

			color(15);

			gotoxy(x + 21, y + 3);

			cout << "--->";
		}

		x += 26;

		aux = aux->siguiente;
	}

	color(7);

	_getch();
}



// Eliminar (FIFO)
void desencolar() {
	int id;
	if (frente != NULL) { // 10 - 9 - 8
		NodoCola* aux = frente; //aux = frente = 10
		frente = frente->siguiente; //frente = 9

		if (frente == NULL) {
			fin = NULL;
		}
		color(10);
		imprimirCentradoModulo("Producto eliminado:", YINICIAL + 2);
		gotoxy(XINICIAL, YINICIAL + 4); cout << "ID: " << aux->id << endl;
		gotoxy(XINICIAL, YINICIAL + 5); cout << "Nombre: " << aux->nombre << endl;
		gotoxy(XINICIAL, YINICIAL + 6); cout << "Descripcion: " << aux->descripcion << endl;
		gotoxy(XINICIAL, YINICIAL + 7); cout << "Precio: " << aux->precio << endl;
		color(7);
		id = aux->id;
		delete aux;

	}
	else {
		color(12);
		imprimirCentradoModulo("COLA VACIA", 21);
		color(7);
	}
}

// Buscar por ID
NodoCola* buscarCola(int id) {
	NodoCola* aux = frente; //aux = frente

	while (aux != NULL) {
		if (aux->id == id) {
			return aux;
		}
		aux = aux->siguiente;
	}

	return NULL;
}

// Modificar datos
void modificarCola(int id) {
    NodoCola* encontrado = buscarCola(id);

	if (encontrado == NULL) {
		color(12);
		imprimirCentradoModulo("No encontrado", 21);
		color(7);
		return;
	}

	// Mostrar datos actuales
	imprimirCentradoModulo("--- Producto Encontrado ---", YINICIAL);
	gotoxy(XINICIAL, YINICIAL + 2); cout << "ID: " << encontrado->id << endl;
	gotoxy(XINICIAL, YINICIAL + 3); cout << "Nombre: " << encontrado->nombre << endl;
	gotoxy(XINICIAL, YINICIAL + 4); cout << "Descripcion: " << encontrado->descripcion << endl;
	gotoxy(XINICIAL, YINICIAL + 5); cout << "Precio: " << encontrado->precio << endl;

	// Pedir nuevos datos
	cin.ignore(10000, '\n');
	imprimirCentradoModulo("--- Ingrese los Nuevos Datos ---", YINICIAL + 7);
	gotoxy(XINICIAL, YINICIAL + 8); cout << "Nuevo nombre: ";
	getline(cin, encontrado->nombre);
	gotoxy(XINICIAL, YINICIAL + 9); cout << "Nueva descripcion: ";
	getline(cin, encontrado->descripcion);
	gotoxy(XINICIAL, YINICIAL + 10); cout << "Nuevo precio: ";
	cin >> encontrado->precio;

	color(10);
	imprimirCentradoModulo("Producto modificado correctamente", YINICIAL + 12);
	color(7);
}

//MENÚ DE LA COLA LISTOOOOOOOOOOO
void menuCola() {
	int opc;
	int id;
	string nombre;
	string descripcion;
	string titulo = "Estructura de Cola";
	string opciones[] = { "Ingreso de Datos de Cola", "Ver Datos en forma de Cola", "Modificar un dato", "Buscar un dato", "Eliminar un dato", "Atras (Menu Principal)" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones

	do
	{
		system("cls");
		opc = menu(titulo, opciones, n);
		switch (opc)
		{
		case 1:
			//ENCOLAR DATOS
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL+2);
			gotoxy(XINICIAL, YINICIAL + 4); cout << "Ingrese ID: "; cin >> id;//Guardar datos
			cin.ignore(1000, '\n');
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre del Producto: "; getline(cin, nombre); //Guardar datos
            gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: "; getline(cin, descripcion); //Guardar datos
			float precio;
			gotoxy(XINICIAL, YINICIAL + 10); cout << "Precio: "; cin >> precio;
			encolar(id, nombre, descripcion, precio);
			gotoxy(60, 31); system("pause");
			break;
		case 2:
			system("cls");
			//VER DATOS EN FORMA DE COLA
			mostrarCola();
			gotoxy(60, 38); system("pause");
			break;
		case 3:
			//MODIFICAR UN DATO
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto que desea MODIFICAR: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarCola(id);
			gotoxy(60, 31); system("pause");
			break;
		case 4:
		{
			//BUSCAR UN DATO
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			NodoCola* encontrado = buscarCola(id);

			if (encontrado != NULL) {
				system("cls");
				dibujarLineasModulo();
				color(10);
				imprimirCentradoModulo("Producto encontrado:", YINICIAL+5);
				gotoxy(XINICIAL, YINICIAL + 6); cout << "ID: " << encontrado->id << endl;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Nombre: " << encontrado->nombre << endl;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: " << encontrado->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL + 9); cout << "Precio: " << encontrado->precio << endl;
				gotoxy(60, 31); system("pause");

			}
			else {
				system("cls");
				dibujarLineasModulo();
				color(12);
				imprimirCentradoModulo("Producto NO encontrado", 21);
				color(7);
				gotoxy(60, 31); system("pause");
			}
			break;
		}
		case 5:
			//ELIMINAR UN DATO:
			system("cls");
			dibujarLineasModulo();
			desencolar();
			gotoxy(60, 31); system("pause");
			break;

		case 6:
			return;
		}

	} while (true);
}

//=============================
// DEFINICIÓN DE FUNCIONES LISTA-SIMPLE
//=============================

// INSERTAR ORDENADO (MENOR A MAYOR)
void insertarOrdenado(NodoLista*& lista, int id, string nombre, string descripcion, float precio) {
	NodoLista* nuevo = new NodoLista();
	nuevo->id = id;
	nuevo->nombre = nombre;
	nuevo->descripcion = descripcion;
	nuevo->precio = precio;

	NodoLista* aux1 = lista;
	NodoLista* aux2 = NULL;

	while (aux1 != NULL && aux1->id < id) {
		aux2 = aux1;
		aux1 = aux1->siguiente;
	}

	if (lista == aux1) { // insertar al inicio
		lista = nuevo;
	}
	else {
		aux2->siguiente = nuevo;
	}

	nuevo->siguiente = aux1;

    // Mensaje simple y coloreado
	color(10);
	gotoxy(XINICIAL, YINICIAL + 12); cout << "Producto Agregado" << endl;
	color(7);
}

void mostrarLista(NodoLista* lista) {

	system("cls");

	// ===== MARCO =====
	for (int i = 20; i <= 130; i++) {
		gotoxy(i, 1);  cout << "■";
		gotoxy(i, 40); cout << "■";
	}

	for (int i = 2; i <= 39; i++) {
		gotoxy(20, i);  cout << "■";
		gotoxy(130, i); cout << "■";
	}

	color(11);

	imprimirCentradoModulo("======= LISTA SIMPLE ENLAZADA =======",2);

	if (lista == NULL) {

		color(12);

		imprimirCentradoModulo("LISTA VACIA", 20);

		color(7);

		_getch();
		return;
	}

	NodoLista* aux = lista;

	int y = 5;

	while (aux != NULL && y < 35) {

		string actual = direccionCorta(aux);
		string siguiente = direccionCorta(aux->siguiente);

		// ===== LINEA PRINCIPAL =====
		gotoxy(25, y);

		color(11);
		cout << "[" << actual << "]";

		color(15);
		cout << " -> ";

		color(14);
		cout << "[" << aux->id << "]";

		color(15);
		cout << " -> ";

		color(10);
		cout << "[" << siguiente << "]";

		// ===== DATOS =====
		color(7);

		gotoxy(35, y + 1);
		cout << "Nombre: " << aux->nombre.substr(0, 40);

		gotoxy(35, y + 2);
		cout << "Descripcion: " << aux->descripcion.substr(0, 40);

		gotoxy(35, y + 3);
		cout << "Precio: Q" << aux->precio;

		// ===== SEPARADOR =====
		color(8);

		gotoxy(25, y + 4);
		cout << "-----------------------------------------------------------";

		y += 6;

		aux = aux->siguiente;
	}

	color(7);

	gotoxy(50, 38);
	system("pause");
}

// ELIMINAR NODO (INICIO, MEDIO, FINAL)
void eliminarNodoLista(NodoLista*& lista, int id) {
	if (lista == NULL) {
		color(12);
		imprimirCentradoModulo("Lista vacia", 21);
		color(7);
		return;
	}

	NodoLista* aux = lista;
	NodoLista* anterior = NULL;

	while (aux != NULL && aux->id != id) {
		anterior = aux;
		aux = aux->siguiente;
	}

	if (aux == NULL) {
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
		return;
	}

	if (anterior == NULL) { // eliminar primero
		lista = lista->siguiente;
	}
	else { // eliminar medio o final
		anterior->siguiente = aux->siguiente;
	}
	color(10);
	imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
	gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << aux->id << endl;
	gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << aux->nombre << endl;
	gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << aux->descripcion << endl;
	gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << aux->precio << endl;
	delete aux;
	color(7);
}

// VACIAR LISTA
void vaciarLista(NodoLista*& lista) {
	NodoLista* aux;

	while (lista != NULL) {
		aux = lista;
		lista = lista->siguiente;
		delete aux;
	}
	color(10);
	imprimirCentradoModulo("Lista vaciada", 21);
	color(7);
}

//VOID BUSCAR EN LA LISTA
void buscarLista(NodoLista* lista, int id) {
    NodoLista* aux = lista;
	while (aux != NULL) {
		if (aux->id == id) {

			imprimirCentradoModulo("--- Producto encontrado ---", YINICIAL+5);
			gotoxy(XINICIAL, YINICIAL + 6); cout << "ID: " << aux->id << endl;
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Nombre: " << aux->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: " << aux->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 9); cout << "Precio: " << aux->precio << endl;
			return;
		}
		aux = aux->siguiente;
	}
	color(12);
	imprimirCentradoModulo("ID no encontrado", 21);
	color(7);
}
void modificarLista(NodoLista* lista, int id) {
    NodoLista* aux = lista;
	while (aux != NULL) {
		if (aux->id == id) {
			imprimirCentradoModulo("--- Producto Encontrado ---", YINICIAL);
			gotoxy(XINICIAL, YINICIAL + 2); cout << "ID: " << aux->id << endl;
			gotoxy(XINICIAL, YINICIAL + 3); cout << "Nombre: " << aux->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 4); cout << "Descripcion: " << aux->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 5); cout << "Precio: " << aux->precio << endl;

			cin.ignore(1000, '\n');
			imprimirCentradoModulo("--- Ingrese los Nuevos Datos ---", YINICIAL + 7);
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Nuevo nombre: ";
			getline(cin, aux->nombre);
			gotoxy(XINICIAL, YINICIAL + 9); cout << "Nueva descripcion: ";
			getline(cin, aux->descripcion);
			gotoxy(XINICIAL, YINICIAL + 10); cout << "Nuevo precio: ";
			cin >> aux->precio;

			color(10);
			gotoxy(XINICIAL, YINICIAL + 12); cout << "Producto modificado correctamente" << endl;
			color(7);
			return;
		}
		aux = aux->siguiente;
	}
	color(12);
	imprimirCentradoModulo("ID no encontrado", 21);
	color(7);
}

// MENU LISTA SIMPLE
void menuListaSimple() {
	NodoLista* lista = NULL;
	int id;
	float precio;
	string nombre, descripcion;
	string titulo = "Lista Simple";
	string opciones[] = { "Insertar Producto","Eliminar Producto","Mostrar Lista", "Buscar Producto", "Modificar Producto","Vaciar Lista","Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do {
		int opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			//INSERTAR
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL + 2);
			gotoxy(XINICIAL, YINICIAL + 4); cout << "Ingrese ID: ";
			cin >> id;
			cin.ignore(1000, '\n');
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Ingrese nombre: ";
			getline(cin, nombre);
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Ingrese descripcion: ";
			getline(cin, descripcion);
			gotoxy(XINICIAL, YINICIAL + 10); cout << "Ingrese precio: ";
			cin >> precio;
			insertarOrdenado(lista, id, nombre, descripcion, precio);
			gotoxy(60, 31); system("pause");
			break;

		case 2:
			//ELIMINAR UN NODO
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a eliminar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			eliminarNodoLista(lista, id);
			gotoxy(60, 31); system("pause");
			break;


		case 3:
			//MOSTRAR
			system("cls");
			mostrarLista(lista);
			break;

		case 4:
			//BUSCAR
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			buscarLista(lista, id);
			gotoxy(60, 31); system("pause");
			break;
		case 5:
			//MODIFICAR
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a modificar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarLista(lista, id);
			gotoxy(60, 31); system("pause");
			break;
		case 6:
			//VACIAR LISTA
			system("cls");
			dibujarLineasModulo();
			vaciarLista(lista);
			gotoxy(60, 31); system("pause");
			break;
		case 7:
			return;
		}

	} while (true);
}

//=============================
// DEFINICIÓN DE FUNCIONES LISTA-DOBLE
//=============================
//INSERTAR
void insertarDoble(NodoDoble*& lista) {

	NodoDoble* nuevo = new NodoDoble();
	imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL + 2);
    gotoxy(XINICIAL, YINICIAL + 4); cout << "Ingrese ID: ";
	cin >> nuevo->id;
	cin.ignore(1000, '\n');

	gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: ";
	getline(cin, nuevo->nombre);

	gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: ";
	getline(cin, nuevo->descripcion);

	gotoxy(XINICIAL, YINICIAL + 10); cout << "Precio: ";
	cin >> nuevo->precio;
	cin.ignore(1000, '\n');

	nuevo->siguiente = lista;
	nuevo->anterior = NULL;

	if (lista != NULL)
		lista->anterior = nuevo;

	lista = nuevo;

    color(10);
	gotoxy(XINICIAL, YINICIAL + 12); cout << "Producto Agregado" << endl;
	color(7);
}

//ELIMINAR
void eliminarDoble(NodoDoble*& lista, int id) {

	if (!lista) {
		color(12);
		imprimirCentradoModulo("Lista vacia", 21);
		color(7);
		return;
	}

	NodoDoble* aux = lista;

	while (aux && aux->id != id)
		aux = aux->siguiente;

	if (!aux) {
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
		return;
	}

	if (aux == lista)
		lista = aux->siguiente;

	if (aux->anterior)
		aux->anterior->siguiente = aux->siguiente;

	if (aux->siguiente)
		aux->siguiente->anterior = aux->anterior;

	color(10);
	imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
	gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << aux->id << endl;
	gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << aux->nombre << endl;
	gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << aux->descripcion << endl;
	gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << aux->precio << endl;
	color(7);
	delete aux;
}

//MOSTRAR
void mostrarDoble(NodoDoble* lista) {

	system("cls");

	// ===== MARCO =====
	for (int i = 20; i <= 130; i++) {
		gotoxy(i, 1);  cout << "■";
		gotoxy(i, 40); cout << "■";
	}

	for (int i = 2; i <= 39; i++) {
		gotoxy(20, i);  cout << "■";
		gotoxy(130, i); cout << "■";
	}

	// ===== TITULO =====
	color(11);

	imprimirCentradoModulo("======= LISTA DOBLE ENLAZADA =======",2);

	// ===== VALIDACION =====
	if (lista == NULL) {

		color(12);
		imprimirCentradoModulo("LISTA DOBLE VACIA",20);
		color(7);
		return;
	}

	NodoDoble* aux = lista;

	int y = 5;

	while (aux != NULL && y < 35) {

		string actual = direccionCorta(aux);

		string anterior = direccionCorta(aux->anterior);

		string siguiente = direccionCorta(aux->siguiente);

		// ===== CONEXIONES =====
		gotoxy(24, y);

		color(8);
		cout << "[" << anterior << "]";

		color(15);
		cout << " <-> ";

		color(11);
		cout << "[" << actual << "]";

		color(15);
		cout << " <-> ";

		color(10);
		cout << "[" << siguiente << "]";

		// ===== DATOS =====
		color(14);

		gotoxy(35, y + 1);
		cout << "ID: " << aux->id;

		color(7);

		gotoxy(35, y + 2);
		cout << "Nombre: " << aux->nombre.substr(0, 40);

		gotoxy(35, y + 3);
		cout << "Descripcion: " << aux->descripcion.substr(0, 40);

		gotoxy(35, y + 4);
		cout << "Precio: Q" << aux->precio;

		// ===== SEPARADOR =====
		color(8);

		gotoxy(24, y + 5);
		cout << "---------------------------------------------------------------";

		y += 6;

		aux = aux->siguiente;
	}

	color(7);
}

//BUSCAR
void buscarDoble(NodoDoble* lista, int id) {
	NodoDoble* aux = lista;

	while (aux) {
		if (aux->id == id) {
			imprimirCentradoModulo("--- Producto encontrado ---", YINICIAL + 5);
			gotoxy(XINICIAL, YINICIAL + 6); cout << "ID: " << aux->id << endl;
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Nombre: " << aux->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: " << aux->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 9); cout << "Precio: " << aux->precio << endl;
			return;
		}
		aux = aux->siguiente;
	}
	color(12);
	imprimirCentradoModulo("ID no encontrado", 21);
	color(7);
}

//MODIFICAR
void modificarDoble(NodoDoble* lista, int id) {
	NodoDoble* aux = lista;

	while (aux) {
		if (aux->id == id) {
			imprimirCentradoModulo("--- Producto Encontrado ---", YINICIAL);
			gotoxy(XINICIAL, YINICIAL + 1); cout << "ID actual: " << aux->id << endl;
			gotoxy(XINICIAL, YINICIAL + 2); cout << "Nombre actual: " << aux->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 3); cout << "Descripcion actual: " << aux->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 4); cout << "Precio actual: " << aux->precio << endl;

			imprimirCentradoModulo("--- Ingrese los nuevos datos ---", YINICIAL + 6);
			cin.ignore(1000, '\n');
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Nuevo nombre: ";
			getline(cin, aux->nombre);
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Nueva descripcion: ";
			getline(cin, aux->descripcion);
			gotoxy(XINICIAL, YINICIAL + 9); cout << "Nuevo precio: ";
			cin >> aux->precio;

			color(10);
			gotoxy(XINICIAL, YINICIAL + 11);
			cout << "Producto modificado correctamente" << endl;
			color(7);
			return;
		}
		aux = aux->siguiente;
	}

	color(12);
	imprimirCentradoModulo("ID no encontrado", 21);
	color(7);
}

//VACIAR
void vaciarDoble(NodoDoble*& lista) {

	NodoDoble* aux;

	while (lista) {
		aux = lista;
		lista = lista->siguiente;
		delete aux;
	}
	
	color(10);
	imprimirCentradoModulo("Lista vaciada correctamente", 21);
	color(7);
}

//MENU
void menuListaDoble() {

	NodoDoble* lista = NULL;
	int opc, id;
	string titulo = "Lista Doblemente Enlazadas";
	string opciones[] = { "Insertar Producto","Eliminar Producto","Mostrar Lista","Buscar Producto","Modificar Producto","Vaciar Lista","Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]);
	do {
		opc = menu(titulo, opciones, n);
		switch (opc) {

		case 1:
			//INSERTAR
			system("cls");
			dibujarLineasModulo();
			insertarDoble(lista);
			gotoxy(60, 31); system("pause");
			break;

		case 2:
			//ELIMINAR UN NODO
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a eliminar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			eliminarDoble(lista, id);
			gotoxy(60, 31); system("pause");
			break;

		case 3:
			//MOSTRAR
			system("cls");
			mostrarDoble(lista);

			gotoxy(50, 38); system("pause");
			break;

		case 4:
			//BUSCAR
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			buscarDoble(lista, id);
			gotoxy(60, 31); system("pause");
			break;

		case 5:
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a modificar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarDoble(lista, id);
			gotoxy(60, 31); system("pause");
			break;

		case 6:
			system("cls");
			dibujarLineasModulo();
			vaciarDoble(lista);
			gotoxy(60, 31); system("pause");
			break;

		case 7:
			return;
		}

	} while (true);
}

//=============================
// DEFINICIÓN DE FUNCIONES LISTA-CIRCULAR
//=============================
//Insertar Lista Circular
void insertarCircular(int id, string nombre, string descripcion, float precio) {
	nodoCircular* nuevo = new nodoCircular();
	nuevo->id = id;
	nuevo->nombre = nombre;
	nuevo->descripcion = descripcion;
    nuevo->precio = precio;

	if (primero == NULL) {
		primero = nuevo;
		nuevo->siguiente = primero; //Hace referencia al primer nodo
		ultimo = nuevo;
	}
	else if (primero->id > id)
	{
		nuevo->siguiente = primero;
		primero = nuevo;
		ultimo->siguiente = primero;

	}
	else {
		nodoCircular* anterior = primero;
		while (anterior->siguiente != primero && anterior->siguiente->id < id)
			anterior = anterior->siguiente;
		nuevo->siguiente = anterior->siguiente;
		anterior->siguiente = nuevo;

		if (anterior == ultimo)
			ultimo = nuevo;
    }
    color(10);
	gotoxy(XINICIAL, YINICIAL + 12);
	cout << "Producto Agregado" << endl;
	color(7);
}

//Borrar Un Nodo
void borrarCircular(int id) {
	//DEBEMOS ENCONTRAR EL NODO, RECORRER LA LISTA
	if (primero == NULL)
	{
		color(12);
		imprimirCentradoModulo("Lista vacia", 21);
		color(7);
		return;
	}
	nodoCircular* actual = primero;
	nodoCircular* anterior = ultimo;
	bool encontrado = false;
	//10, 20, 30, 40, 50
	//BORRAR 30
	do {
		if (actual->id == id) { //Verifico que el nodo n +1 sea igual al dato
			if (primero == ultimo)
			{
				primero = NULL;
				color(10);
				imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
				gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << actual->id << endl;
				gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << actual->nombre << endl;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << actual->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << actual->precio << endl;
				color(7);
				delete actual;

			}
			else if (actual == primero) {
				primero = primero->siguiente;
				ultimo->siguiente = primero;
				color(10);
				imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
				gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << actual->id << endl;
				gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << actual->nombre << endl;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << actual->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << actual->precio << endl;
				color(7);
				delete actual;
			}
			else if (actual == ultimo)
			{
				anterior->siguiente = primero;
				ultimo = anterior;
				color(10);
				imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
				gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << actual->id << endl;
				gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << actual->nombre << endl;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << actual->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << actual->precio << endl;
				color(7);
				delete actual;
			}
			else {
				anterior->siguiente = actual->siguiente;
				color(10);
				imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
				gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << actual->id << endl;
				gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << actual->nombre << endl;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << actual->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << actual->precio << endl;
				color(7);
				delete actual;
			}
			encontrado = true;
			break;
		}
		anterior = actual; //anterior = tiene el dato de actual, 10
		actual = actual->siguiente;
	} while (actual != primero);
	if (!encontrado){
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
	}
}

//Mostrar Lista Circular
void mostrarCircular() {

	system("cls");

	// ===== MARCO =====
	for (int i = 20; i <= 130; i++) {
		gotoxy(i, 1);  cout << "■";
		gotoxy(i, 40); cout << "■";
	}

	for (int i = 2; i <= 39; i++) {
		gotoxy(20, i);  cout << "■";
		gotoxy(130, i); cout << "■";
	}

	// ===== TITULO =====
	color(11);

	imprimirCentradoModulo(
		"======= LISTA CIRCULAR =======",
		2
	);

	// ===== VALIDACION =====
	if (primero == NULL) {

		color(12);

		imprimirCentradoModulo(
			"LISTA CIRCULAR VACIA",
			20
		);

		color(7);
		return;
	}

	nodoCircular* aux = primero;

	int y = 5;

	do {

		string actual = direccionCorta(aux);

		string siguiente = direccionCorta(aux->siguiente);

		// ===== CONEXION =====
		gotoxy(25, y);

		color(11);
		cout << "[" << actual << "]";

		color(15);
		cout << " -> ";

		color(14);
		cout << "[" << aux->id << "]";

		color(15);
		cout << " -> ";

		color(10);
		cout << "[" << siguiente << "]";

		// ===== DATOS =====
		color(7);

		gotoxy(35, y + 1);
		cout << "Nombre: "
			<< aux->nombre.substr(0, 40);

		gotoxy(35, y + 2);
		cout << "Descripcion: "
			<< aux->descripcion.substr(0, 40);

		gotoxy(35, y + 3);
		cout << "Precio: Q" << aux->precio;

		// ===== SI REGRESA AL INICIO =====
		if (aux->siguiente == primero) {
			color(13);
			gotoxy(35, y + 4);
			cout << "REGRESA AL INICIO";
			color(7);
		}

		// ===== SEPARADOR =====
		color(8);
		gotoxy(25, y + 5);
		cout << "-----------------------------------------------------------";
		y += 6;
		aux = aux->siguiente;

	} while (aux != primero && y < 35);

	color(7);
}

//Buscar en Lista Circular
void buscarCircular(int id) {
	if (primero == NULL)
	{
		color(12);
		imprimirCentradoModulo("Lista vacia", 21);
		color(7);
		return;
	}
	bool encontrado = false;
	nodoCircular* aux = primero;
	do
	{
		if (aux->id == id) {
			encontrado = true;
			break;
		}

		aux = aux->siguiente;
	} while (aux != primero);

	if (encontrado == true)
	{
		imprimirCentradoModulo("--- Producto encontrado ---", YINICIAL + 5);
		gotoxy(XINICIAL, YINICIAL + 6); cout << "ID: " << aux->id << endl;
		gotoxy(XINICIAL, YINICIAL + 7); cout << "Nombre: " << aux->nombre << endl;
		gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: " << aux->descripcion << endl;
		gotoxy(XINICIAL, YINICIAL + 9); cout << "Precio: " << aux->precio << endl;
	}
	else {
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
	}
}

//Modificar en Lista Circular
void modificarCircular(int id) {
	if (primero == NULL)
	{
		color(12);
		imprimirCentradoModulo("Lista vacia", 21);
		color(7);
		return;
	}
	bool encontrado = false;
	nodoCircular* aux = primero;
	do
	{
		if (aux->id == id) {
			encontrado = true;
			break;
		}

		aux = aux->siguiente;
	} while (aux != primero);

	if (encontrado == true)
	{
		imprimirCentradoModulo("--- Producto Encontrado ---", YINICIAL);
		gotoxy(XINICIAL, YINICIAL + 1); cout << "ID actual: " << aux->id << endl;
		gotoxy(XINICIAL, YINICIAL + 2); cout << "Nombre actual: " << aux->nombre << endl;
		gotoxy(XINICIAL, YINICIAL + 3); cout << "Descripcion actual: " << aux->descripcion << endl;
		gotoxy(XINICIAL, YINICIAL + 4); cout << "Precio actual: " << aux->precio << endl;

		imprimirCentradoModulo("--- Ingrese los nuevos datos ---", YINICIAL + 6);
		gotoxy(XINICIAL, YINICIAL + 7); cout << "Nuevo nombre: "; cin.ignore(1000, '\n'); getline(cin, aux->nombre);
		gotoxy(XINICIAL, YINICIAL + 8); cout << "Nueva descripcion: "; getline(cin, aux->descripcion);
		gotoxy(XINICIAL, YINICIAL + 9); cout << "Nuevo precio: "; cin >> aux->precio;

		color(10);
		gotoxy(XINICIAL, YINICIAL + 11);
		cout << "Producto modificado correctamente" << endl;
		color(7);
	}
	else {
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
	}
}

//Vaciar Lista Circular
void vaciarListaCircular() {
	if (primero == NULL) {
		color(12);
		imprimirCentradoModulo("Lista vacia", 21);
		color(7);
		return;
	}
	nodoCircular* aux = primero;
	nodoCircular* siguiente;
	do
	{
		siguiente = aux->siguiente;
		delete aux;
		aux = siguiente;
	} while (aux != primero);
	primero = NULL;
	ultimo = NULL;
	color(10);
	imprimirCentradoModulo("Lista vaciada correctamente", 21);
	color(7);
}

//Menu Lista Circular
void menuListaCircular() {
	int id, opc;
	float precio;
	string nombre;
	string descripcion;
	string titulo = "Lista Circular";
	string opciones[] = { "Insertar Producto","Eliminar Producto","Mostrar Lista","Buscar Producto","Modificar","Vaciar Lista","Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones

	do
	{
		opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			//INSERTAR
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL + 2);
			gotoxy(XINICIAL, YINICIAL + 4); cout << "Ingrese ID: ";
			cin >> id;
			cin.ignore(1000, '\n');
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Ingrese Nombre: ";
			getline(cin, nombre);
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Ingrese Descripcion: ";
			getline(cin, descripcion);
			gotoxy(XINICIAL, YINICIAL + 10); cout << "Ingrese Precio: ";
			cin >> precio;
			insertarCircular(id, nombre, descripcion, precio);
			gotoxy(60, 31); system("pause");
			break;
		case 2:
			//ELIMINAR UN NODO
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a eliminar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			borrarCircular(id);
			gotoxy(60, 31); system("pause");
			break;
		case 3:
			//MOSTRAR LA LISTA
			system("cls");
			mostrarCircular();
			gotoxy(50, 38);
			system("pause");
			break;
		case 4:
			//BUSCAR
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			buscarCircular(id);
			gotoxy(60, 31); system("pause");
			break;
		case 5:
			//MODIFICAR
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a modificar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarCircular(id);
			gotoxy(60, 31); system("pause");
			break;
		case 6:
			system("cls");
			dibujarLineasModulo();
			vaciarListaCircular();
			gotoxy(60, 31); system("pause");
			break;
		case 7: return;
		}
	} while (true);
}


//--------DEFINICIÓN DE FUNCIONES MENU DE LISTAS
void subMenuRecorrido() {
	int opc;
	string titulo = "Recorrido de Arbol";
	string opciones[] = { "PREORDEN", "POSTORDEN", "INORDEN", "Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do
	{
		system("cls");
		opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			if (raiz == NULL)
			{
				system("cls");
				dibujarLineasModulo();
				color(12);
				imprimirCentradoModulo("El arbol esta vacio", 21);
				color(7);
			}
			else {
				system("cls");
				for (int i = 0; i < 41; i++)
				{
					gotoxy(30, i); cout << "■";
					gotoxy(126, i); cout << "■";
				}
				int y = 12;
				imprimirCentradoModulo("--- RECORRIDO PREORDEN ---", 10);
				preOrden(raiz, y);
			}
			_getch();
			break;
		case 2:
			if (raiz == NULL)
			{
				cout << "\nEl arbol esta vacio\n";
			}
			else {
				system("cls");
				int y = 12;
				for (int i = 0; i < 41; i++)
				{
					gotoxy(30, i); cout << "■";
					gotoxy(126, i); cout << "■";
				}
				imprimirCentradoModulo("--- RECORRIDO POSTORDEN ---", 10);
				postOrden(raiz, y);
			}
			_getch();
			break;
		case 3:
			if (raiz == NULL)
			{
				cout << "\nEl arbol esta vacio\n";
			}
			else {
				system("cls");
				int y = 12;
				for (int i = 0; i < 41; i++)
				{
					gotoxy(30, i); cout << "■";
					gotoxy(126, i); cout << "■";
				}
				imprimirCentradoModulo("--- RECORRIDO INORDEN ---", 10);
				inOrden(raiz, y);
			}
			_getch();
			break;
		case 4:
			return;
		}
	} while (true);
}
void menuListas() {
	int n = 4;//OPCIONES del submenú listas
	string titulo = "MEMU LISTAS";
	string opciones[] = { "Lista Simple", "Lista Doble", "Lista Circular", "Regresar" };

	do
	{
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

//=============================
// DEFINICIÓN DE FUNCIONES ARBOL BINARIO
//=============================
// Insertar nodo
void insertarNodo(NodoArbol*& raiz, int id, string nombre, string descripcion, float precio) {

	if (raiz == NULL) {

		NodoArbol* nuevo = new NodoArbol();

		nuevo->id = id;
		nuevo->nombre = nombre;
		nuevo->descripcion = descripcion;
		nuevo->precio = precio;

		nuevo->izquierdo = NULL;
		nuevo->derecho = NULL;

        raiz = nuevo;

		color(10);
		gotoxy(XINICIAL, YINICIAL + 12);
		cout << "Producto agregado." << endl;
		color(7);

	}
	else {

		if (id < raiz->id) {

			insertarNodo(raiz->izquierdo, id, nombre, descripcion, precio);

		}
		else if (id > raiz->id) {

			insertarNodo(raiz->derecho, id, nombre, descripcion, precio);

		}
		else {
			
			color(12);
			gotoxy(XINICIAL, YINICIAL + 12);
			cout << "El ID ya existe";
			color(7);
		}
	}
}

// Buscar nodo
NodoArbol* buscarNodo(NodoArbol*& raiz, int id) {

	if (raiz == NULL) {

		return NULL;
	}

	if (raiz->id == id) {

		return raiz;
	}

	if (id < raiz->id) {

		return buscarNodo(raiz->izquierdo, id);

	}
	else {

		return buscarNodo(raiz->derecho, id);
	}
}

//Eliminar Todo el árbol
void eliminarArbol(NodoArbol*& raiz) {
	if (raiz == NULL) return;
	eliminarArbol(raiz->izquierdo);
	eliminarArbol(raiz->derecho);

	delete raiz;

	raiz = NULL;
}

//Eliminar un Nodo del árbol
NodoArbol* encontrarMinimo(NodoArbol* nodo) {
	while (nodo->izquierdo != NULL) {
		nodo = nodo->izquierdo;
	}
	return nodo;
}
void eliminarNodo(NodoArbol*& raiz, int id) {
	if (raiz == NULL) {
		color(12);
		imprimirCentradoModulo("Arbol Vacio", 21);
		color(7);
		return;
	} 

	if (id < raiz->id) {
		eliminarNodo(raiz->izquierdo, id);
	}
	else if (id > raiz->id) {
		eliminarNodo(raiz->derecho, id);
	}
	else {

		if (raiz->izquierdo == NULL) {
			NodoArbol* temp = raiz->derecho;
			color(10);
			imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
			gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << raiz->id << endl;
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << raiz->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << raiz->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << raiz->precio << endl;
			color(7);
			delete raiz;
			raiz = temp;
		}
		else if (raiz->derecho == NULL) {
			NodoArbol* temp = raiz->izquierdo;
			color(10);
			imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
			gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << raiz->id << endl;
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << raiz->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << raiz->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << raiz->precio << endl;
			color(7);
			delete raiz;
			raiz = temp;
		}

		else {

			NodoArbol* temp = encontrarMinimo(raiz->derecho);

			color(10);
			imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
			gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << raiz->id << endl;
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << raiz->nombre << endl;
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << raiz->descripcion << endl;
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << raiz->precio << endl;
			color(7);

			raiz->id = temp->id;
			raiz->nombre = temp->nombre;
			raiz->descripcion = temp->descripcion;
			raiz->precio = temp->precio;

			eliminarNodo(raiz->derecho, temp->id);
		}
	}
}

//Para las funciones de RECORRIDO
void mostrarNodo(NodoArbol* nodo) {
	cout << "ID: " << nodo->id
		<< " | Nombre: " << nodo->nombre
		<< " | Descripcion: " << nodo->descripcion << endl;
}
string direccionCorta(NodoArbol* raiz) {
	stringstream ss;
	ss << raiz;
	string direccion = ss.str();
	if (direccion.length() > 8) {
		//return direccion.substr(direccion.length() - 6)+ "..";
		return ".." + direccion.substr(direccion.length() - 6);
	}
}
void mostrarNodoConexion(NodoArbol* nodo, int &y) {

	string actual = direccionCorta(nodo);

	string izq = direccionCorta(nodo->izquierdo);

	string der = direccionCorta(nodo->derecho);
		color(11);
		int i = 1;
		gotoxy(52, y); cout << "[" << actual << "]";
		color(15);

		cout << " -> ";

		color(14);

		cout << "[" << nodo->id << "]";

		color(15);

		cout << " -> ";

		color(10);

		cout << "[I:" << izq
			<< " | D:" << der << "]";

		color(7);
		y++;
}

//FUNCIONES DE RECORRIDO
void preOrden(NodoArbol* raiz, int& y) {
	if (raiz == NULL) return;
	// Mostrar raíz		
	mostrarNodoConexion(raiz, y);
	// Recorrer subárbol izquierdo
	preOrden(raiz->izquierdo, y);
	// Recorrer subárbol derecho
	preOrden(raiz->derecho, y);
}

void postOrden(NodoArbol* raiz, int& y) {
	if (raiz == NULL) return;
	postOrden(raiz->izquierdo, y);
	postOrden(raiz->derecho, y);
	mostrarNodoConexion(raiz, y);
}

void inOrden(NodoArbol*raiz, int& y) {
	if (raiz == NULL) return;
	//Subarbol izquierdo
	inOrden(raiz->izquierdo, y);
	//RAIZ
	mostrarNodoConexion(raiz, y);
	//Subarbol derecho
	inOrden(raiz->derecho, y);
}


//----------------DIBUJAR LA CAJA DE DATOS-------------------------------
string obtenerDireccion(NodoArbol* raiz) {
	stringstream ss;
	ss << raiz;
	string direccion = ss.str();
	if (direccion.length() > 11) {
		//return direccion.substr(direccion.length() - 6)+ "..";
		return ".." + direccion.substr(direccion.length() - 8);
	}
}

/*
// Dibuja una caja ASCII de tamaño fijo (15 de ancho, 4 de alto)
void dibujarCaja(int x, int y, int id, string direccion, float precio){
	color(22);
	gotoxy(x, y);     cout << "+-------------+";
	gotoxy(x, y + 1); cout << "| ID: " << id << "       |";
	gotoxy(x, y + 2); cout << "|" << direccion << "   |";
	gotoxy(x, y + 3); cout << "|Precio: " << precio << " |";
	gotoxy(x, y + 4); cout << "+-------------+";
}
*/

void dibujarCaja(int x, int y, int id, string direccion, float precio) {

	color(22);

	// Fuerza longitud exacta
	direccion = direccion.substr(0, 11);

	gotoxy(x, y);
	cout << "+-------------+";

	gotoxy(x, y + 1);
	cout << "|ID: "
		<< left << setw(9) << id
		<< "|";

	gotoxy(x, y + 2);
	cout << "|"
		<< left << setw(13) << direccion
		<< "|";

	gotoxy(x, y + 3);
	cout << "|Q = "
		<< fixed << setprecision(2)
		<< setw(9) << precio
		<< "|";

	gotoxy(x, y + 4);
	cout << "+-------------+";

	color(7);
}


// Función recursiva que calcula las coordenadas exactas de cada nodo y sus diagonales
void mostrarArbol(NodoArbol* raiz, int x, int y, int rangoHorizontal) {
	if (raiz == nullptr) return;

	// 1. Dibujar el nodo actual en la posición (X, Y)
	string dir = obtenerDireccion(raiz);
	// Restamos 6 a 'x' para que el centro del nodo quede alineado con la coordenada X dada
	dibujarCaja(x - 7, y, raiz->id, dir, raiz->precio);
	// El siguiente nivel bajará 7 líneas en la pantalla (5 de la caja + 2 de las diagonales)
	int siguienteY = y + 7;
	// El rango de apertura horizontal se reduce a la mitad para los hijos
	int nuevoRango = rangoHorizontal / 2;

	// 2. Procesar y conectar al Hijo Izquierdo
	if (raiz->izquierdo != nullptr) {
		int destinoX = x - nuevoRango;

		color(15);
		// Dibujamos las diagonales '/' de forma escalonada bajando
		gotoxy(x - 6, y + 5);       cout << "/"; //Entre más resto a x, más se alejará al centro del rectángulo correspondiente
		gotoxy(destinoX + 6, y + 6); cout << "/"; //Entre más le sumo a destinoX más cerca estará del rectángulo
		color(7);
		// Llamada recursiva para el hijo izquierdo
		mostrarArbol(raiz->izquierdo, destinoX, siguienteY, nuevoRango);
	}

	// 3. Procesar y conectar al Hijo Derecho
	if (raiz->derecho != nullptr) {
		int destinoX = x + nuevoRango;

		color(15);
		// Dibujamos las diagonales '\' de forma escalonada bajando
		gotoxy(x + 6, y + 5);       cout << "\\"; //Entre más sumo a x, más se alejará al centro del rectángulo correspondiente
		gotoxy(destinoX - 6, y + 6); cout << "\\"; //Entre más le resto a destinoX más cerca estará del rectángulo
		color(7);
		// Llamada recursiva para el hijo derecho
		mostrarArbol(raiz->derecho, destinoX, siguienteY, nuevoRango);
	}
}
//--------------------------------------------------------------------

void mostrarDatosABB(NodoArbol* raiz) {

	system("cls");

	// ===== MARCO =====
	for (int i = 28; i <= 128; i++) {
		gotoxy(i, 1);  cout << "■";
		gotoxy(i, 40); cout << "■";
	}

	for (int i = 2; i <= 39; i++) {
		gotoxy(28, i);  cout << "■";
		gotoxy(128, i); cout << "■";
	}

	// ===== TITULO =====
	color(11);
	imprimirCentradoModulo("======= INVENTARIO EN ABB =======", 2);

	// ===== VALIDACION =====
	if (raiz == NULL) {

		color(12);

		imprimirCentradoModulo("ARBOL VACIO", 21);

		color(7);
		return;
	}

	// ===== POSICION INICIAL =====
	int y = 5;

	// ===== RECORRIDO =====
	mostrarDatosABBRec(raiz, y);

	color(7);
}
void mostrarDatosABBRec(NodoArbol* raiz, int& y) {

	if (raiz == NULL || y >= 35)
		return;

	// ===== IZQUIERDA =====
	mostrarDatosABBRec(raiz->izquierdo, y);

	color(11);

	gotoxy(32, y++);
	cout << "Direccion: " << raiz;

	gotoxy(32, y++);
	cout << "ID: " << raiz->id;

	gotoxy(32, y++);
	cout << "Nombre: "
		<< raiz->nombre.substr(0, 60);

	gotoxy(32, y++);
	cout << "Descripcion: "
		<< raiz->descripcion.substr(0, 55);

	gotoxy(32, y++);
	cout << fixed << setprecision(2);
	cout << "Precio: Q" << raiz->precio;

	gotoxy(32, y++);
	cout << "Izquierda: " << raiz->izquierdo;

	gotoxy(32, y++);
	cout << "Derecha: " << raiz->derecho;

	gotoxy(32, y++);
	cout << "-------------------------------------------------------------";

	y++;

	color(7);

	// ===== DERECHA =====
	mostrarDatosABBRec(raiz->derecho, y);
}

//MENU ÁRBOL
void menuArbol() {
	int id;
	float precio;
	string nombre, descripcion;
	NodoArbol* resultado;
	int opc;
	string titulo = "Estructura de Arbol";
	string opciones[] = { "Ingreso de Datos de Arbol", "Buscar un dato", "Recorrer", "Eliminar un dato", "Eliminar todo el Arbol","Mostrar Datos del Arbol","Mostrar Estructura del Arbol", "Atras (Menu Principal)"};
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do
	{
		opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			//INSERTAR DATOS
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL + 2);
			gotoxy(XINICIAL, YINICIAL + 4); cout << "Ingrese ID: "; cin >> id;//Guardar datos
			cin.ignore(1000, '\n');
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre del Producto: "; getline(cin, nombre); //Guardar datos
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: "; getline(cin, descripcion); //Guardar datos
			gotoxy(XINICIAL, YINICIAL + 10); cout << "Precio: "; cin >> precio;
			insertarNodo(raiz, id, nombre, descripcion, precio);
			gotoxy(60, 31); system("pause");
			break;
		case 2:
			//BUSCAR EN EL ARBOL
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			resultado = buscarNodo(raiz, id);
			if (resultado != NULL) {
				system("cls");
				dibujarLineasModulo();
				imprimirCentradoModulo("--- Producto encontrado ---", YINICIAL + 5);
				gotoxy(XINICIAL, YINICIAL + 6); cout << "ID: " << resultado->id;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Nombre: " << resultado->nombre;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: " << resultado->descripcion;
				gotoxy(XINICIAL, YINICIAL + 9); cout << "Precio: " << resultado->precio;
			}
			else {
				system("cls");
				dibujarLineasModulo();
				color(12);
				imprimirCentradoModulo("ID no encontrado", 21);
				color(7);
			}
			gotoxy(60, 31); system("pause");
			break;
		case 3:
			//RECORRER
			system("cls");
			subMenuRecorrido();
			break;
		case 4:
			//ELIMINAR UN NODO
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a eliminar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			eliminarNodo(raiz, id);
			gotoxy(60, 31); system("pause");
			break;
		case 5:
			//ELIMINAR TODO EL ARBOL
			system("cls");
			dibujarLineasModulo();
			eliminarArbol(raiz);
			if (raiz == NULL)
			{
				color(10);
				imprimirCentradoModulo("Arbol eliminado correctamente", 21);
				color(7);
			}
			gotoxy(60, 31); system("pause");
			break;
		case 6:
			//MOSTRAR LOS DATOS DEL ARBOL
			mostrarDatosABB(raiz);
			gotoxy(60, 40); system("pause");
			break;
		case 7:
			system("cls");
			for (int i = 0; i < 41; i++)
			{
				gotoxy(2, i); cout << "■";
				gotoxy(154, i); cout << "■";
			}
			mostrarArbol(raiz, 78, 3, 65);//78 es el centro de la pantalla, 3 es la altura inicial, 75 es el rango horizontal inicial
			_getch();
			break;
		case 8:
			return;
		}
	} while (true);
	system("pause");
}



//=============================
// DEFINICIÓN DE FUNCIONES ARBOL AVL
//=============================
int obtenerAltura(NodoAVL* raiz) {
	if (raiz == NULL) return 0;

	return raiz->altura;
}

int obtenerFactorEquilibrio(NodoAVL* raiz) {
	if (raiz == NULL) {
		return 0;
	}
	return obtenerAltura(raiz->derecha) - obtenerAltura(raiz->izquierda);
}


//Cuando el árbol está cargado a la derecha
void rotacionSimpleDerecha(NodoAVL*& raiz) {
	NodoAVL* aux = raiz->derecha;  // aux se convertirá en la nueva raíz
	raiz->derecha = aux->izquierda; // El subárbol izquierdo de aux se convierte en el subárbol derecho de la antigua raíz
	aux->izquierda = raiz; // La antigua raíz se convierte en el hijo izquierdo de aux
	raiz = aux; // Actualizamos la raíz para que apunte a aux
	
}

//Cuando el árbol está cargado a la izquierda
void rotacionSimpleIzquierda(NodoAVL*& raiz) {
	NodoAVL* aux = raiz->izquierda;  // aux se convertirá en la nueva raíz
	raiz->izquierda = aux->derecha; // El subárbol derecho de aux se convierte en el subárbol izquierdo de la antigua raíz
	aux->derecha = raiz; // La antigua raíz se convierte en el hijo derecho de aux
	raiz = aux; // Actualizamos la raíz para que apunte a aux
}

void rotacionDerechaIzquierda(NodoAVL*& raiz) {
	NodoAVL* aux = raiz->derecha;
	NodoAVL* aux2 = aux->izquierda;

	aux->izquierda = aux2->derecha;
	raiz->derecha = aux2->izquierda;

	aux2->derecha = aux;
	aux2->izquierda = raiz;

	raiz = aux2;
}

void rotacionIzquierdaDerecha(NodoAVL*& raiz) {
	NodoAVL* aux = raiz->izquierda;
	NodoAVL* aux2 = aux->derecha;

	aux->derecha = aux2->izquierda;
	raiz->izquierda = aux2->derecha;

	aux2->izquierda = aux;
	aux2->derecha = raiz;

	raiz = aux2;
}

//----------------DIBUJAR LA CAJA DE DATOS-------------------------------
string obtenerDireccionAVL(NodoAVL* raiz) {
	stringstream ss;
	ss << raiz;
	string direccion = ss.str();
	if (direccion.length() > 11) {
		//return direccion.substr(direccion.length() - 6)+ "..";
		return ".." + direccion.substr(direccion.length() - 8);
	}
	return direccion;
}

// Dibuja una caja ASCII de tamaño fijo (12 de ancho, 4 de alto)
/*void dibujarCajaAVL(int x, int y, int id, string direccion) {
	color(11);
	gotoxy(x, y);     cout << "+----------+";
	gotoxy(x, y + 1); cout << "| ID: " << id << "    |";
	gotoxy(x, y + 2); cout << "|" << direccion << "|";
	gotoxy(x, y + 3); cout << "+----------+";
}
*/

void dibujarCajaAVL(int x, int y, int id, string direccion, float precio, int fe) {

	color(22);

	// Fuerza longitud exacta
	direccion = direccion.substr(0, 11);

	gotoxy(x, y);
	cout << "+-------------+";

	gotoxy(x, y + 1);
	cout << "|ID "
		<< left << setw(5) << id
		<< "["
		<< setw(3) << fe
		<< "]|";

	gotoxy(x, y + 2);
	cout << "|"
		<< left << setw(13) << direccion
		<< "|";

	gotoxy(x, y + 3);
	cout << "|Q = "
		<< fixed << setprecision(2)
		<< setw(9) << precio
		<< "|";

	gotoxy(x, y + 4);
	cout << "+-------------+";

	color(7);
}

// Función recursiva que calcula las coordenadas exactas de cada nodo y sus diagonales
void mostrarArbolAVL(NodoAVL* raiz, int x, int y, int rangoHorizontal) {
	if (raiz == nullptr) return;

	// 1. Dibujar el nodo actual en la posición (X, Y)
	string dir = obtenerDireccionAVL(raiz);
	// Restamos 7 a 'x' para que el centro del nodo quede alineado con la coordenada X dada
	dibujarCajaAVL(x - 7, y, raiz->id, dir, raiz->precio, obtenerFactorEquilibrio(raiz));

	// El siguiente nivel bajará 7 líneas en la pantalla (5 de la caja + 2 de las diagonales)
	int siguienteY = y + 7;
	// El rango de apertura horizontal se reduce a la mitad para los hijos
	int nuevoRango = rangoHorizontal / 2;

	// 2. Procesar y conectar al Hijo Izquierdo
	if (raiz->izquierda != nullptr) {
		int destinoX = x - nuevoRango;

		color(8);
		// Dibujamos las diagonales '/' de forma escalonada bajando
		gotoxy(x - 6, y + 5);       cout << "/";
		gotoxy(destinoX + 6, y + 6); cout << "/";
		color(7);
		// Llamada recursiva para el hijo izquierdo
		mostrarArbolAVL(raiz->izquierda, destinoX, siguienteY, nuevoRango);
	}

	// 3. Procesar y conectar al Hijo Derecho
	if (raiz->derecha != nullptr) {
		int destinoX = x + nuevoRango;

		color(8);
		// Dibujamos las diagonales '\' de forma escalonada bajando
		gotoxy(x + 6, y + 5);       cout << "\\";
		gotoxy(destinoX - 6, y + 6); cout << "\\";
		color(7);
		// Llamada recursiva para el hijo derecho
		mostrarArbolAVL(raiz->derecha, destinoX, siguienteY, nuevoRango);
	}
}
//--------------------------------------------------------------------

// Recalcular alturas de la raíz de subárbol y sus hijos inmediatos
void actualizarAlturasPostRotacion(NodoAVL* raiz) {
	if (raiz == NULL) return; // Si la raíz es nula, no hay nada que actualizar
	// Actualizamos la altura del hijo izquierdo de la raíz, si existe
	if (raiz->izquierda != NULL) {
		// La altura de un nodo es 1 + la altura máxima de sus hijos
		raiz->izquierda->altura = 1 + max(obtenerAltura(raiz->izquierda->izquierda), obtenerAltura(raiz->izquierda->derecha));
	}
	// Actualizamos la altura del hijo derecho de la raíz, si existe
	if (raiz->derecha != NULL) {
		// La altura de un nodo es 1 + la altura máxima de sus hijos
		raiz->derecha->altura = 1 + max(obtenerAltura(raiz->derecha->izquierda), obtenerAltura(raiz->derecha->derecha));
	}
	// Finalmente, actualizamos la altura de la raíz del subárbol
	raiz->altura = 1 + max(obtenerAltura(raiz->izquierda), obtenerAltura(raiz->derecha));
}
//Insertar
void insertarAVL(NodoAVL*& raiz, int id, string nombre, string descripcion, float precio) {
	if (raiz == NULL) {
		NodoAVL* nuevo = new NodoAVL();

		nuevo->id = id;
		nuevo->nombre = nombre;
		nuevo->descripcion = descripcion;
		nuevo->precio = precio;
		nuevo->izquierda = NULL;
		nuevo->derecha = NULL;
		nuevo->altura = 1;

		raiz = nuevo;

		color(10);
		gotoxy(XINICIAL, YINICIAL + 12);
		cout << "Producto Agregado" << endl;
		color(7);
		return;
	}
	if (id < raiz->id) {
		insertarAVL(raiz->izquierda, id, nombre, descripcion, precio);
	}
	else if (id > raiz->id) {
		insertarAVL(raiz->derecha, id, nombre, descripcion, precio);
	}
	else {
		color(12);
		gotoxy(XINICIAL, YINICIAL + 12);
		cout << "El ID ya existe";
		color(7);
		return;
	}
	//2. Actualizar la altura de la raiz
	raiz->altura = 1 + max(obtenerAltura(raiz->izquierda), obtenerAltura(raiz->derecha));

	//3. Obtener el factor de equilibrio para verificar 
	int fe = obtenerFactorEquilibrio(raiz);

	//4. Balancear el árbol si el factor de equilibro está fuera de rango
	// Caso Izquierda Izquierda
	if (fe < -1 && id < raiz->izquierda->id) {
		color(14);
		dibujarLineasModulo();
		//Después de ingresar los datos aparecen debajo de ellos estos 2 mensajes.
		gotoxy(60, YINICIAL + 16); cout << "DESBALANCE DETECTADO";
		gotoxy(60, YINICIAL + 17); cout << "Arbol Cargado a la IZQUIERDA";
		gotoxy(60, YINICIAL + 18); cout << "Desea ver el arbol antes de la rotacion [S/N]: ";
		char opcion;
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			//Imprime le árbol, luego los mensaje de las intrucciones para la rotación
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
			color(14);
			cout << "\n\t\t\t\t\t\t\tNodo afectado: " << raiz->id;
			cout << "\n\t\t\t\t\t\t\tFactor de equilibrio: " << fe;
			cout << "\n\t\t\t\t\t\t\tTipo: Izquierda-Izquierda";
			cout << "\n\t\t\t\t\t\t\tSe realizara una ROTACION SIMPLE IZQUIERDA";
			cout << "\n\t\t\t\t\t\t\tPresione una tecla para continuar...";
			_getch();
			color(7);
			rotacionSimpleIzquierda(raiz);
			cout << "\n\n\t\t\t\t\t\t\tRotación simple izquierda realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		else {
			//En caso que no imprima el árbol, solo se imprimen los mensajes de las intrucciones para la rotación
			system("cls");
			dibujarLineasModulo();
			color(14);
			gotoxy(60, YINICIAL + 4); cout << "Nodo afectado: " << raiz->id;
			gotoxy(60, YINICIAL + 5); cout << "Factor de equilibrio: " << fe;
			gotoxy(60, YINICIAL + 6); cout << "Tipo: Izquierda-Izquierda";
			gotoxy(60, YINICIAL + 7); cout << "Se realizara una ROTACION SIMPLE IZQUIERDA";
			gotoxy(60, YINICIAL + 8); cout << "Presione una tecla para continuar...";
			_getch();
			color(7);
			rotacionSimpleIzquierda(raiz);
			gotoxy(60, YINICIAL + 10); cout << "Rotación simple izquierda realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		//después de la rotación, se muestra el árbol actualizado y se dan las instrucciones para continuar
		cout << "\n\t\t\t\t\t\tDesea ver el arbol despues de la rotacion [S/N]: ";
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
		}
		else {
			return;
		}
		
	}

	//Caso Derecha Derecha
	if (fe > 1 && id > raiz->derecha->id) {
		color(14);
		dibujarLineasModulo();
		//Después de ingresar los datos aparecen debajo de ellos estos 2 mensajes.
		gotoxy(60, YINICIAL + 16); cout << "DESBALANCE DETECTADO";
		gotoxy(60, YINICIAL + 17); cout << "Arbol Cargado a la DERECHA";
		gotoxy(60, YINICIAL + 18); cout << "Desea ver el arbol antes de la rotacion [S/N]: ";
		char opcion;
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			//Imprime le árbol, luego los mensaje de las intrucciones para la rotación
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
			color(14);
			cout << "\n\t\t\t\t\t\t\tNodo afectado: " << raiz->id;
			cout << "\n\t\t\t\t\t\t\tFactor de equilibrio: " << fe;
			cout << "\n\t\t\t\t\t\t\tTipo: Derecha-Derecha";
			cout << "\n\t\t\t\t\t\t\tSe realizara una ROTACION SIMPLE DERECHA";
			cout << "\n\t\t\t\t\t\t\tPresione una tecla para continuar...";
			_getch();
			color(7);
			rotacionSimpleDerecha(raiz);
			cout << "\n\n\t\t\t\t\t\t\tRotación simple derecha realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		else {
			//En caso que no imprima el árbol, solo se imprimen los mensajes de las intrucciones para la rotación
			system("cls");
			dibujarLineasModulo();
			color(14);
			gotoxy(60, YINICIAL+4); cout << "Nodo afectado: " << raiz->id;
			gotoxy(60, YINICIAL + 5); cout << "Factor de equilibrio: " << fe;
			gotoxy(60, YINICIAL + 6); cout << "Tipo: Derecha-Derecha";
			gotoxy(60, YINICIAL + 7); cout << "Se realizara una ROTACION SIMPLE DERECHA";
			gotoxy(60, YINICIAL + 8); cout << "Presione una tecla para continuar...";
			_getch();
			color(7);
			rotacionSimpleDerecha(raiz);
			gotoxy(60, YINICIAL + 10); cout << "Rotación simple derecha realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		//después de la rotación, se muestra el árbol actualizado y se dan las instrucciones para continuar
		cout << "\n\t\t\t\t\t\tDesea ver el arbol despues de la rotacion [S/N]: ";
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
		}
		else {
			return;
		}
	}

	//Caso Izquierda Derecha
	if (fe < -1 && id > raiz->izquierda->id) {
		color(14);
		dibujarLineasModulo();
		//Después de ingresar los datos aparecen debajo de ellos estos 2 mensajes.
		gotoxy(60, YINICIAL + 16); cout << "DESBALANCE DETECTADO";
		gotoxy(60, YINICIAL + 17); cout << "Arbol Cargado a la IZQUIERDA";
		gotoxy(60, YINICIAL + 18); cout << "Desea ver el arbol antes de la rotacion [S/N]: ";
		char opcion;
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
			color(14);
			cout << "\n\t\t\t\t\t\t\tNodo afectado: " << raiz->id;
			cout << "\n\t\t\t\t\t\t\tFactor de equilibrio: " << fe;
			cout << "\n\t\t\t\t\t\t\tTipo: Izquierda-Derecha";
			cout << "\n\t\t\t\t\t\t\tSe realizara una ROTACION IZQUIERDA-DERECHA";
			cout << "\n\t\t\t\t\t\t\tPresione una tecla para continuar...";
			_getch();
			color(7);
			rotacionIzquierdaDerecha(raiz);
			cout << "\n\n\t\t\t\t\t\t\tRotación izquierda-derecha realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		else {
			//En caso que no imprima el árbol, solo se imprimen los mensajes de las intrucciones para la rotación
			system("cls");
			dibujarLineasModulo();
			color(14);
			gotoxy(60, YINICIAL + 4); cout << "Nodo afectado: " << raiz->id;
			gotoxy(60, YINICIAL + 5); cout << "Factor de equilibrio: " << fe;
			gotoxy(60, YINICIAL + 6); cout << "Tipo: Izquierda-Derecha";
			gotoxy(60, YINICIAL + 7); cout << "Se realizara una ROTACION IZQUIERDA-DERECHA";
			gotoxy(60, YINICIAL + 8); cout << "Presione una tecla para continuar...";
			_getch();
			color(7);
			rotacionSimpleDerecha(raiz);
			gotoxy(60, YINICIAL + 10); cout << "Rotación izquierda-derecha realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		//después de la rotación, se muestra el árbol actualizado y se dan las instrucciones para continuar
		cout << "\n\t\t\t\t\t\tDesea ver el arbol despues de la rotacion [S/N]: ";
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
		}
		else {
			return;
		}
	}

	//Caso Derecha Izquierda
	if (fe > 1 && id < raiz->derecha->id) {
		color(14);
		dibujarLineasModulo();
		//Después de ingresar los datos aparecen debajo de ellos estos 2 mensajes.
		gotoxy(60, YINICIAL + 16); cout << "DESBALANCE DETECTADO";
		gotoxy(60, YINICIAL + 17); cout << "Arbol Cargado a la DERECHA";
		gotoxy(60, YINICIAL + 18); cout << "Desea ver el arbol antes de la rotacion [S/N]: ";

		char opcion;
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
			color(14);
			cout << "\n\t\t\t\t\t\t\tNodo afectado: " << raiz->id;
			cout << "\n\t\t\t\t\t\t\tFactor de equilibrio: " << fe;
			cout << "\n\t\t\t\t\t\t\tTipo: Derecha-Izquierda";
			cout << "\n\t\t\t\t\t\t\tSe realizara una ROTACION DERECHA-IZQUIERDA";
			cout << "\n\t\t\t\t\t\t\tPresione una tecla para continuar...";
			_getch();
			color(7);
			rotacionDerechaIzquierda(raiz);
			cout << "\n\n\t\t\t\t\t\t\tRotación derecha-izquierda realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		else {
			//En caso que no imprima el árbol, solo se imprimen los mensajes de las intrucciones para la rotación
			system("cls");
			dibujarLineasModulo();
			color(14);
			gotoxy(60, YINICIAL + 4); cout << "Nodo afectado: " << raiz->id;
			gotoxy(60, YINICIAL + 5); cout << "Factor de equilibrio: " << fe;
			gotoxy(60, YINICIAL + 6); cout << "Tipo: Derecha-Izquierda";
			gotoxy(60, YINICIAL + 7); cout << "Se realizara una ROTACION DERECHA-IZQUIERDA";
			gotoxy(60, YINICIAL + 8); cout << "Presione una tecla para continuar...";
			_getch();
			color(7);
			rotacionDerechaIzquierda(raiz);
			gotoxy(60, YINICIAL + 10); cout << "Rotación derecha-izquierda realizada\n";
			actualizarAlturasPostRotacion(raiz);
		}
		//después de la rotación, se muestra el árbol actualizado y se dan las instrucciones para continuar
		cout << "\n\t\t\t\t\t\tDesea ver el arbol despues de la rotacion [S/N]: ";
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			system("cls");
			mostrarArbolAVL(raiz, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
		}
		else {
			return;
		}
	}
}
//Buscar
NodoAVL* buscarAVL(NodoAVL* raiz, int idBuscar) {

	if (raiz == NULL) {
		return NULL;
	}

	if (raiz->id == idBuscar) {
		return raiz;
	}

	if (idBuscar < raiz->id) {
		return buscarAVL(raiz->izquierda, idBuscar);
	}
	else {
		return buscarAVL(raiz->derecha, idBuscar);
	}
}
//Mostrar sin estructura de árbol
void mostrarAVL(NodoAVL* raiz) {
	if (raiz != NULL) {

		mostrarAVL(raiz->izquierda);

		cout << "\nID: " << raiz->id << endl;
		cout << "Nombre: " << raiz->nombre << endl;
		cout << "Descripcion: " << raiz->descripcion << endl;
		cout << "Altura: " << raiz->altura << endl;
		cout << "-------------------" << endl;

		mostrarAVL(raiz->derecha);
	}
}
//Eliminar todo el árbol AVL
void vaciarAVL(NodoAVL*& nodo) {
	if (nodo == NULL) return;

	vaciarAVL(nodo->izquierda);
	vaciarAVL(nodo->derecha);

	delete nodo;
	nodo = NULL;
}


//---------MÉTODOS PROPIOS PARA ELIMINAR UN NODO------------------------
int obtenerAlturaE(NodoAVL* nodo) {
	return (nodo == NULL) ? 0 : nodo->altura;
}

int obtenerBalance(NodoAVL* nodo) {
	return (nodo == NULL) ? 0 : obtenerAlturaE(nodo->izquierda) - obtenerAlturaE(nodo->derecha);
}

NodoAVL* nodoMenorValor(NodoAVL* nodo) {
	NodoAVL* actual = nodo;
	while (actual->izquierda != NULL) {
		actual = actual->izquierda;
	}
	return actual;
}

NodoAVL* rotarDerecha(NodoAVL* y) {
	NodoAVL* x = y->izquierda;
	NodoAVL* T2 = x->derecha;

	x->derecha = y;
	y->izquierda = T2;

	y->altura = 1 + max(obtenerAlturaE(y->izquierda), obtenerAlturaE(y->derecha));
	x->altura = 1 + max(obtenerAlturaE(x->izquierda), obtenerAlturaE(x->derecha));

	return x;
}

NodoAVL* rotarIzquierda(NodoAVL* x) {
	NodoAVL* y = x->derecha;
	NodoAVL* T2 = y->izquierda;

	y->izquierda = x;
	x->derecha = T2;

	x->altura = 1 + max(obtenerAlturaE(x->izquierda), obtenerAlturaE(x->derecha));
	y->altura = 1 + max(obtenerAlturaE(y->izquierda), obtenerAlturaE(y->derecha));

	return y;
}

NodoAVL* eliminarAVL(NodoAVL*& raiz, int id) {
	if (raiz == NULL) {
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
		return raiz;
	}

	//Buscar el nodo a eliminar
	if (id < raiz->id) {
		raiz->izquierda = eliminarAVL(raiz->izquierda, id);
	}
	else if (id > raiz->id) {
		raiz->derecha = eliminarAVL(raiz->derecha, id);
	}

	//Nodo encontrado
	else {
		if ((raiz->izquierda == NULL) || (raiz->derecha == NULL)) {

			NodoAVL* temp = raiz;

			// Nodo sin hijo
			if (raiz->izquierda == NULL && raiz->derecha == NULL) {
				raiz = NULL;
			}

			// Solo hijo derecho
			else if (raiz->izquierda == NULL) {
				raiz = raiz->derecha;
			}

			// Solo hijo izquierdo
			else {
				raiz = raiz->izquierda;
			}
			color(10);
			dibujarLineasModulo();
			imprimirCentradoModulo("Producto eliminado", YINICIAL+4);
			gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << temp->id;
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << temp->nombre;
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << temp->descripcion;
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << temp->precio;
			color(7);
			_getch();
			delete temp;

		}
		else {
			NodoAVL* temporal = nodoMenorValor(raiz->derecha);

			raiz->id = temporal->id;
			raiz->nombre = temporal->nombre;
			raiz->descripcion = temporal->descripcion;
			raiz->precio = temporal->precio;
			raiz->derecha = eliminarAVL(raiz->derecha, temporal->id);
		}
	}

	if (raiz == NULL) return raiz;

	//Actualizar altura del nodo actual
	raiz->altura = 1 + max(obtenerAlturaE(raiz->izquierda), obtenerAlturaE(raiz->derecha));

	int balance = obtenerBalance(raiz);

	//Rotación Derecha
	if (balance > 1 && obtenerBalance(raiz->izquierda) >= 0) {
		system("cls");
		dibujarLineasModulo();
		imprimirCentradoModulo("[DESBALANCE DETECTADO]", YINICIAL + 2);
		imprimirCentradoModulo("El arbol quedo cargado a la izquierda.", YINICIAL + 3);
		imprimirCentradoModulo("[REBALANCEO]", YINICIAL + 5);
		imprimirCentradoModulo("Aplicando rotacion derecha.", YINICIAL + 6);
		return rotarDerecha(raiz);
	}
	//Rotación izquierda-derecha
	if (balance > 1 && obtenerBalance(raiz->izquierda) < 0) {
		system("cls");
		dibujarLineasModulo();
		imprimirCentradoModulo("[DESBALANCE DETECTADO]", YINICIAL + 2);
		imprimirCentradoModulo("El arbol quedo cargado a la izquierda.", YINICIAL + 3);

		raiz->izquierda = rotarIzquierda(raiz->izquierda);

		imprimirCentradoModulo("[REBALANCEO]", YINICIAL + 5);
		imprimirCentradoModulo("Aplicando rotacion izquierda-derecha.", YINICIAL + 6);

		return rotarDerecha(raiz);
	}

	//Rotación izquierda
	if (balance < -1 && obtenerBalance(raiz->derecha) <= 0) {
		system("cls");
		dibujarLineasModulo();
		imprimirCentradoModulo("[DESBALANCE DETECTADO]", YINICIAL + 2);
		imprimirCentradoModulo("El arbol quedo cargado a la derecha.", YINICIAL + 3);

		imprimirCentradoModulo("[REBALANCEO]", YINICIAL + 5);
		imprimirCentradoModulo("Aplicando rotacion izquierda.", YINICIAL + 6);

		return rotarIzquierda(raiz);
	}

	//Rotación derecha-izquierda
	if (balance < -1 && obtenerBalance(raiz->derecha) > 0) {
		system("cls");
		dibujarLineasModulo();
		imprimirCentradoModulo("[DESBALANCE DETECTADO]", YINICIAL + 2);
		imprimirCentradoModulo("El arbol quedo cargado a la derecha.", YINICIAL + 3);

		raiz->derecha = rotarDerecha(raiz->derecha);
		
		imprimirCentradoModulo("[REBALANCEO]", YINICIAL + 5);
		imprimirCentradoModulo("Aplicando rotacion derecha-izquierda.", YINICIAL + 6);

		return rotarIzquierda(raiz);

	}

	return raiz;
}
//--------------------------------------------------------------------------


void mostrarDatosAVLRec(NodoAVL* raiz, int& y) {

	if (raiz == NULL || y >= 35)
		return;

	// ===== IZQUIERDA =====
	mostrarDatosAVLRec(raiz->izquierda, y);

	color(11);

	gotoxy(32, y++);
	cout << "Direccion: " << raiz;

	gotoxy(32, y++);
	cout << "ID: " << raiz->id;

	gotoxy(32, y++);
	cout << "Nombre: "
		<< raiz->nombre.substr(0, 60);

	gotoxy(32, y++);
	cout << "Descripcion: "
		<< raiz->descripcion.substr(0, 55);

	gotoxy(32, y++);
	cout << fixed << setprecision(2);
	cout << "Precio: Q" << raiz->precio;

	gotoxy(32, y++);
	cout << "Izquierda: " << raiz->izquierda;

	gotoxy(32, y++);
	cout << "Derecha: " << raiz->derecha;

	gotoxy(32, y++);
	cout << "-------------------------------------------------------------";

	y++;

	color(7);

	// ===== DERECHA =====
	mostrarDatosAVLRec(raiz->derecha, y);
}
void mostrarDatosAVL(NodoAVL* raiz) {

	system("cls");

	// ===== MARCO =====
	for (int i = 28; i <= 128; i++) {
		gotoxy(i, 1);  cout << "■";
		gotoxy(i, 40); cout << "■";
	}

	for (int i = 2; i <= 39; i++) {
		gotoxy(28, i);  cout << "■";
		gotoxy(128, i); cout << "■";
	}

	// ===== TITULO =====
	color(11);
	imprimirCentradoModulo("======= INVENTARIO EN AVL =======", 2);

	// ===== VALIDACION =====
	if (raiz == NULL) {

		color(12);

		imprimirCentradoModulo("ARBOL VACIO", 21);

		color(7);
		return;
	}

	// ===== POSICION INICIAL =====
	int y = 5;

	// ===== RECORRIDO =====
	mostrarDatosAVLRec(raiz, y);

	color(7);
}


void menuArbolAVL() {
	int id;
	float precio;
	string nombre, descripcion;
	NodoAVL* resultado1;
	char respuesta;
	int opc;
	string titulo = "Estructura de Arbol AVL";
	string opciones[] = { "Ingreso de Datos de Arbol AVL", "Buscar un dato","Eliminar todo el Arbol AVL", "Eliminar un dato","Mostrar Datos Arbol AVL","Mostrar Estructura Arbol AVL", "Atras (Menu Principal)"};
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do
	{
		opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			//INSERTAR DATOS
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL + 2);

			gotoxy(XINICIAL, YINICIAL + 4); cout << "Ingrese ID: "; cin >> id;//Guardar datos
			cin.ignore(1000, '\n');
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre del Producto: "; getline(cin, nombre); //Guardar datos
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: "; getline(cin, descripcion); //Guardar datos
			gotoxy(XINICIAL, YINICIAL + 10); cout << "Precio: "; cin >> precio;
			insertarAVL(raizAVL, id, nombre, descripcion, precio);
			gotoxy(60, 31);
			system("pause");
			break;
		case 2:
			//BUSCAR EN EL ARBOL
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			resultado1 = buscarAVL(raizAVL, id);
			if (resultado1 != NULL) {
				system("cls");
				dibujarLineasModulo();
				color(10);
				imprimirCentradoModulo("Producto encontrado:", YINICIAL+5);
				gotoxy(XINICIAL, YINICIAL + 6); cout << "ID: " << resultado1->id << endl;
				gotoxy(XINICIAL, YINICIAL+7); cout << "Nombre: " << resultado1->nombre << endl;
				gotoxy(XINICIAL, YINICIAL+8); cout << "Descripcion: " << resultado1->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL+9); cout << "Precio: " << resultado1->precio << endl;
				color(7);
			}
			else {
				system("cls");
				dibujarLineasModulo();
				color(12);
				imprimirCentradoModulo("ID no encontrado", 21);
				color(7);
			}
			gotoxy(60, 31); system("pause");
			break;
		case 3:

			//ELIMINAR ARBOL
			system("cls");
			dibujarLineasModulo();
			vaciarAVL(raizAVL);
			if (raizAVL == NULL)
			{
				color(10);
				imprimirCentradoModulo("ARBOL ELIMINADO CORRECTAMENTE", 21);
				color(7);
			}
			gotoxy(60, 31); system("pause");
			break;
		case 4:
			//Eliminar un nodo específico
			system("cls");
			dibujarLineasModulo();
			imprimirCentradoModulo("Ingrese el ID del producto a eliminar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			raizAVL = eliminarAVL(raizAVL, id);
			imprimirCentradoModulo("Desea ver el árbol actualizado? [S/N]: ", YINICIAL + 10);
			cin >> respuesta;
			if (respuesta == 'S' || respuesta == 's') {
				system("cls");
				mostrarArbolAVL(raizAVL, 78, 3, 65); //78 es el centro de la pantalla, 3 es la altura inicial, 65 es el rango horizontal inicial
			}
			gotoxy(XINICIAL, 31); system("pause");
			break;
		case 5:
			if (raizAVL == NULL)
			{
				color(12);
				imprimirCentradoModulo("ARBOL VACIO", 21);
				color(7);
			}
			else {
				mostrarDatosAVL(raizAVL);
			}
			gotoxy(60, 40); system("pause");
			break;
		case 6:
			system("cls");
			for (int i = 0; i < 41; i++)
			{
				gotoxy(2, i); cout << "■";
				gotoxy(154, i); cout << "■";
			}
			mostrarArbolAVL(raizAVL, 78, 3, 65);
			_getch();
			break;
		case 7:
			return;
		}
	} while (true);

	system("pause");

}