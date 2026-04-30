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

#define arriba 72
#define abajo 80
#define enter 13

using namespace std;
string nombre; //Almacenará el nombre del usuario
string contra; //Almacenará la contraseña del usuario
string linea; //Almacenará la linea leida en el archivo
string datos[2]; //Este arreglo guarda el nombre (0) y la contraseña(1) datos[2]
int contador = 0;
size_t posicion=0;
int opc;
bool repite = true;


//COLOR DEL TEXTO
void color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//MOVILIDAD EN EL MENÚ CON FLECHAS A TRAVÉS DE GOTOXY
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//LOGIN DEL PROYECTO
int login() {
	system("title LOGIN");
	char opcion;
	int i = 0, j = 3;

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

//SIMPLIFICACION DE OPCIONES DEL MENÚ Y SUBMENÚ
int menu(string titulo, string opciones[], int n) {
	int opcionSeleccionada = 1;
	int tecla; //Tecla capturada 
	bool repite = true;

	do
	{
		system("cls");
		gotoxy(5, 3 + opcionSeleccionada); cout << "->";
		gotoxy(15, 2); cout << titulo; //Imprimimos el titulo
		//Imprimimos las opciones
		for (int i = 0; i < n; i++)
		{
			gotoxy(10, 4 + i); cout << i + 1 << ") " << opciones[i]; //Opcion i;

		}
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


//= ============================
// ESTRUCTURA COLA
//=============================
struct NodoCola {
	int id;                // Identificador del producto
	string nombre;         // Nombre del producto
	string descripcion;    // Descripción del producto
	NodoCola* siguiente;       // Puntero al siguiente nodo
};

//=============================
// VARIABLES GLOBALES COLA
//=============================
NodoCola* frente = NULL;
NodoCola* fin = NULL;

//=============================
// PROTOTIPOS 
//=============================
void encolar(int id, string nombre, string descripcion);
void mostrarCola();
void desencolar();
NodoCola* buscarCola(int id);
void modificarCola(int id);

//=============================
// FUNCIONES COLA
//=============================

// Insertar datos en la cola
void encolar(int id, string nombre, string descripcion) {
	NodoCola* nuevo = new NodoCola();

	nuevo->id = id;
	nuevo->nombre = nombre;
	nuevo->descripcion = descripcion;
	nuevo->siguiente = NULL;

	if (frente == NULL) {
		frente = nuevo;
	}
	else {
		fin->siguiente = nuevo;
	}

	fin = nuevo;
}

// Mostrar datos (horizontal)
void mostrarCola() {
	NodoCola* aux = frente;

	color(11); // Celeste
	cout << "COLA DE INVENTARIO:\n\n";

	while (aux != NULL) {

		cout << "[ID: " << aux->id
			<< " | Nombre: " << aux->nombre
			<< " | Desc: " << aux->descripcion << "]";

		if (aux->siguiente != NULL) {
			cout << " -> ";
		}

		aux = aux->siguiente;
	}

	cout << endl;
	color(7); // Blanco normal
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
		id = aux->id;
		delete aux;
		color(10);
		cout << "ID Eliminado " << id;
		color(7);
	}
	else {
		color(12);
		cout << "COLA VACIA" << endl;
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

	if (encontrado != NULL) {
		cin.ignore(10000, '\n');

		cout << "Nuevo nombre: ";
		getline(cin, encontrado->nombre);

		cout << "Nueva descripcion: ";
		getline(cin, encontrado->descripcion);

		color(10);
		cout << "Dato modificado correctamente\n";
		color(7);
	}
	else {
		color(12);
		cout << "No encontrado\n";
		color(7);
	}
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
			cout << "\n--- Registrando Nuevo Producto ---" << endl;
			cout << "Ingrese ID: "; cin >> id;//Guardar datos
			cin.ignore(1000, '\n');
			cout << "Nombre del Producto: "; getline(cin, nombre); //Guardar datos
			cout << "Descripcion: "; getline(cin, descripcion); //Guardar datos
			encolar(id, nombre, descripcion);
			color(10);
			cout << "\nDato agreagado exitosamente" << endl;
			color(7);
			break;
		case 2:
			system("cls");
			//VER DATOS EN FORMA DE PILA
			mostrarCola();
			break;
		case 3:
			//MODIFICAR UN DATO
			system("cls");
			cout << "Ingrese el ID del producto que desea MODIFICAR: ";
			cin >> id;
			modificarCola(id);
			break;
		case 4:
		{
			//BUSCAR UN DATO
			system("cls");
			cout << "Ingrese el ID para encontrar el producto: ";
			cin >> id;
			NodoCola* encontrado = buscarCola(id);

			if (encontrado != NULL) {
				color(10);
				cout << "\nProducto encontrado\n";
				color(7);
				cout << "ID: " << encontrado->id << endl;
				cout << "Nombre: " << encontrado->nombre << endl;
				cout << "Descripcion: " << encontrado->descripcion << endl;
				
			}
			else {
				color(12);
				cout << "\nProducto NO encontrado\n";
				color(7);
			}

			break;
		}
		case 5:
			//ELIMINAR UN DATO:
			system("cls");
			desencolar();
			break;

		case 6:
			return;
		}

		cout << endl << endl;
		system("pause");
	} while (true);
}




//= ============================
// ESTRUCTURA PILA
//=============================
struct NodoPila {
	int id;
	string nombre;
	string descripcion;
	NodoPila* siguiente;
};

void push(NodoPila*& pila) {
	NodoPila* nuevo_nodo = new NodoPila();

	cout << "\n--- Registrando Nuevo Producto ---" << endl;
	cout << "Ingrese ID: ";
	cin >> nuevo_nodo->id;
	cin.ignore(10000, '\n');

	cout << "Nombre del Producto: ";
	getline(cin, nuevo_nodo->nombre);

	cout << "Descripcion: ";
	getline(cin, nuevo_nodo->descripcion);

	nuevo_nodo->siguiente = pila;
	pila = nuevo_nodo;
	
	color(10);
	cout << "\n Producto agregado exitosamente." << endl;
	color(7);
}

void pop(NodoPila*& pila) {
	if (pila == NULL) {
		color(12);
		cout << "\n La pila esta vacia." << endl;
		color(7);
		return;
	}

	NodoPila* aux = pila;
	pila = aux->siguiente;
	color(10);
	cout << "\n Producto eliminado: " << aux->nombre << " (ID: " << aux->id << ")" << endl;
	color(7);
	delete aux;
	_getch();
}

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
		cout << "\nProducto encontrado:" << endl;
		cout << "ID: " << aux->id << " | Nombre: " << aux->nombre << endl;
		color(7);
	}
	else {
		color(12);
		cout << "\n Producto NO encontrado\n";
		color(7);
	}

	return;
}

void modificarPila(NodoPila* pila, int busqueda) {
	NodoPila* aux = pila;
	bool encontrado = false;

	while (aux != NULL) {
		if (aux->id == busqueda) {
			encontrado = true;
			
			cout << "\n--- Producto Encontrado ---" << endl;
			
			cout << "ID actual: " << aux->id << endl;
			cout << "Nombre actual: " << aux->nombre << endl;
			cout << "Descripcion actual: " << aux->descripcion << endl;
			cout << "\n--- Ingrese los Nuevos Datos ---" << endl;

			cin.ignore(1000, '\n');

			cout << "Nuevo Nombre: ";
			getline(cin, aux->nombre);

			cout << "Nueva Descripcion: ";
			getline(cin, aux->descripcion);
			color(10);
			cout << "\n Dato modificado correctamente." << endl;
			color(7);
			break;
		}
		aux = aux->siguiente;
	}

	if (!encontrado) {
		color(12); // Celeste
		cout << "\n\n No encontrado" << endl;
		color(7); // Celeste
	}
}

void mostrarPila(NodoPila* pila) {
	if (pila == NULL) {
		cout << "\n Pila vacia." << endl;
		return;
	}

	NodoPila* aux = pila;
	color(11); // Celeste
	cout << "\n======= INVENTARIO EN PILA (LIFO) =======" << endl;
	while (aux != NULL) {
		cout << "ID: " << aux->id << endl;
		cout << "Nombre: " << aux->nombre << endl;
		cout << "Descripcion: " << aux->descripcion << endl;
		cout << "---------------------------------------" << endl;
		aux = aux->siguiente;
	}
	color(7); 
	_getch();
}

//LISTA SIMPLE
//=============================
// ESTRUCTURA
//=============================
struct NodoLista {
	int dato;
	NodoLista* siguiente;
};

//=============================
// PROTOTIPOS
//=============================
void insertarOrdenado(NodoLista*& lista, int dato);
void mostrarLista(NodoLista* lista);
void eliminarNodo(NodoLista*& lista, int dato);
void vaciarLista(NodoLista*& lista);
void menuListaSimple();

//=============================
// INSERTAR ORDENADO (MENOR A MAYOR)
//=============================
void insertarOrdenado(NodoLista*& lista, int dato) {
	NodoLista* nuevo = new NodoLista();
	nuevo->dato = dato;

	NodoLista* aux1 = lista;
	NodoLista* aux2 = NULL;

	while (aux1 != NULL && aux1->dato < dato) {
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
}

//=============================
// MOSTRAR LISTA
//=============================
void mostrarLista(NodoLista* lista) {
	NodoLista* aux = lista;

	if (aux == NULL) {
		cout << "Lista vacia\n";
		return;
	}

	while (aux != NULL) {
		cout << aux->dato << " -> ";
		aux = aux->siguiente;
	}
	cout << "NULL\n";
}

//=============================
// ELIMINAR NODO (INICIO, MEDIO, FINAL)
//=============================
void eliminarNodo(NodoLista*& lista, int dato) {
	if (lista == NULL) {
		cout << "Lista vacia\n";
		return;
	}

	NodoLista* aux = lista;
	NodoLista* anterior = NULL;

	while (aux != NULL && aux->dato != dato) {
		anterior = aux;
		aux = aux->siguiente;
	}

	if (aux == NULL) {
		cout << "Dato no encontrado\n";
		return;
	}

	if (anterior == NULL) { // eliminar primero
		lista = lista->siguiente;
	}
	else { // eliminar medio o final
		anterior->siguiente = aux->siguiente;
	}

	delete aux;
	cout << "Dato eliminado\n";
}

//=============================
// VACIAR LISTA
//=============================
void vaciarLista(NodoLista*& lista) {
	NodoLista* aux;

	while (lista != NULL) {
		aux = lista;
		lista = lista->siguiente;
		delete aux;
	}

	cout << "Lista vaciada\n";
}

//=============================
// MENU
//=============================
void menuListaSimple() {
	NodoLista* lista = NULL;
	int dato;
	string titulo = "Lista Simple";
	string opciones[] = { "Insertar","Mostrar","Eliminar","Vaciar","Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do {
		int opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			system("cls");
			cout << "Ingrese dato: ";
			cin >> dato;
			insertarOrdenado(lista, dato);
			_getch();
			break;

		case 2:
			system("cls");
			mostrarLista(lista);
			_getch();
			break;

		case 3:
			system("cls");
			cout << "Dato a eliminar: ";
			cin >> dato;
			eliminarNodo(lista, dato);
			_getch();
			break;

		case 4:
			system("cls");
			vaciarLista(lista);
			_getch();
			break;
		case 5:
			return;
		}

	} while (true);
}

//LISTA DOBLE
/*=====================
	ESTRUCTURA NODO
=====================*/
struct NodoDoble {
	int id;
	string nombre;
	string descripcion;
	NodoDoble* siguiente;
	NodoDoble* anterior;
};

/*=====================
	  PROTOTIPOS
=====================*/
void menuListaDoble();
void insertarDoble(NodoDoble*& lista);
void eliminarDoble(NodoDoble*& lista, int id);
void mostrarDoble(NodoDoble* lista);
void buscarDoble(NodoDoble* lista, int id);
void modificarDoble(NodoDoble* lista, int id);
void vaciarDoble(NodoDoble*& lista);


/*=====================
	  INSERTAR
=====================*/
void insertarDoble(NodoDoble*& lista) {

	NodoDoble* nuevo = new NodoDoble();

	cout << "Ingrese ID: ";
	cin >> nuevo->id;
	cin.ignore();

	cout << "Nombre: ";
	getline(cin, nuevo->nombre);

	cout << "Descripcion: ";
	getline(cin, nuevo->descripcion);

	nuevo->siguiente = lista;
	nuevo->anterior = NULL;

	if (lista != NULL)
		lista->anterior = nuevo;

	lista = nuevo;

	cout << "Producto agregado correctamente\n";
}


/*=====================
	  ELIMINAR
=====================*/
void eliminarDoble(NodoDoble*& lista, int id) {

	if (!lista) {
		cout << "Lista vacia\n";
		return;
	}

	NodoDoble* aux = lista;

	while (aux && aux->id != id)
		aux = aux->siguiente;

	if (!aux) {
		cout << "ID no encontrado\n";
		return;
	}

	if (aux == lista)
		lista = aux->siguiente;

	if (aux->anterior)
		aux->anterior->siguiente = aux->siguiente;

	if (aux->siguiente)
		aux->siguiente->anterior = aux->anterior;

	cout << "Producto eliminado: " << aux->nombre << endl;

	delete aux;
}


/*=====================
	  MOSTRAR
=====================*/
void mostrarDoble(NodoDoble* lista) {

	if (!lista) {
		cout << "Lista vacia\n";
		return;
	}

	NodoDoble* aux = lista;

	while (aux) {
		cout << "ID: " << aux->id
			<< " | Nombre: " << aux->nombre
			<< " | Desc: " << aux->descripcion << endl;

		aux = aux->siguiente;
	}
}


/*=====================
		BUSCAR
=====================*/
void buscarDoble(NodoDoble* lista, int id) {

	NodoDoble* aux = lista;

	while (aux) {
		if (aux->id == id) {
			cout << "Producto encontrado\n";
			cout << aux->nombre << " | " << aux->descripcion << endl;
			return;
		}
		aux = aux->siguiente;
	}

	cout << "ID no encontrado\n";
}


/*=====================
	   MODIFICAR
=====================*/
void modificarDoble(NodoDoble* lista, int id) {

	NodoDoble* aux = lista;

	while (aux) {
		if (aux->id == id) {

			cin.ignore();

			cout << "Nuevo nombre: ";
			getline(cin, aux->nombre);

			cout << "Nueva descripcion: ";
			getline(cin, aux->descripcion);

			cout << "Producto modificado\n";
			return;
		}
		aux = aux->siguiente;
	}

	cout << "ID no encontrado\n";
}


/*=====================
		VACIAR
=====================*/
void vaciarDoble(NodoDoble*& lista) {

	NodoDoble* aux;

	while (lista) {
		aux = lista;
		lista = lista->siguiente;
		delete aux;
	}

	cout << "Lista vaciada correctamente\n";
}


/*=====================
		  MENU
=====================*/
void menuListaDoble() {

	NodoDoble* lista = NULL;
	int opc, id;
	string titulo = "Lista Doblemente Enlazadas";
	string opciones[] = {"Insertar Producto","Eliminar Producto","Mostrar Lista","Buscar Producto","Modificar Producto","Vaciar Lista","Regresar"};
	int n = sizeof(opciones) / sizeof(opciones[0]);
	do {
		opc = menu(titulo, opciones, n);
		switch (opc) {

		case 1:
			system("cls");
			insertarDoble(lista);
			_getch();
			break;

		case 2:
			system("cls");
			cout << "ID a eliminar: ";
			cin >> id;
			eliminarDoble(lista, id);
			_getch();
			break;

		case 3:
			system("cls");
			mostrarDoble(lista);
			_getch();
			break;

		case 4:
			system("cls");
			cout << "ID a buscar: ";
			cin >> id;
			buscarDoble(lista, id);
			_getch();
			break;

		case 5:
			system("cls");
			cout << "ID a modificar: ";
			cin >> id;
			modificarDoble(lista, id);
			_getch();
			break;

		case 6:
			system("cls");
			vaciarDoble(lista);
			_getch();
			break;

		case 7:
			return;
		}

	} while (true);
}


//LISTA CIRCULAR
struct nodoCircular
{
	int id;
	string nombre;
	string descripcion;
	nodoCircular* siguiente;
};

nodoCircular* primero;
nodoCircular* ultimo;

//=============================
// PROTOTIPOS
//=============================
void insertarCircular(int, string, string);
void borrarCircular(int);
void mostrarCircular();
void buscarCircular(int);
void modificarCircular(int);
void vaciarListaCircular();
void menuListaCircular();

void insertarCircular(int id, string nombre, string descripcion) {
	nodoCircular* nuevo = new nodoCircular();
	nuevo->id = id;
	nuevo->nombre = nombre;
	nuevo->descripcion = descripcion;

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
	cout << "\nID: " << nuevo->id << " ...AGREGADO" << endl;
}

void borrarCircular(int id) {
	//DEBEMOS ENCONTRAR EL NODO, RECORRER LA LISTA
	if (primero == NULL)
	{
		cout << "\nLISTA VACIA";
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
				cout << "\nID: " << actual->id << " ...ELIMINADO";
				delete actual;

			}
			else if (actual == primero) {
				primero = primero->siguiente;
				ultimo->siguiente = primero;
				cout << "\nID: " << actual->id << " ...ELIMINADO";
				delete actual;
			}
			else if (actual == ultimo)
			{
				anterior->siguiente = primero;
				ultimo = anterior;
				cout << "\nID: " << actual->id << " ...ELIMINADO";
				delete actual;
			}
			else {
				anterior->siguiente = actual->siguiente;
				cout << "\nID: " << actual->id << " ...ELIMINADO";
				delete actual;
			}
			encontrado = true;
			break;
		}
		anterior = actual; //anterior = tiene el dato de actual, 10
		actual = actual->siguiente;
	} while (actual != primero);
	if (!encontrado)
		cout << "Nodo no encontrado";
}

void mostrarCircular() {
	if (primero == NULL)
	{
		cout << "\nLista Vacía." << endl;
		return;
	}
	nodoCircular* aux = primero;
	do
	{
		cout << "|ID: " << aux->id
			<< "|Nombre: " << aux->nombre
			<< "|Desc: " << aux->descripcion
			<< "| -> ";
		aux = aux->siguiente;
	} while (aux != primero);
	cout << "(Regresa al inicio)" << endl;
}

void buscarCircular(int id) {
	if (primero == NULL)
	{
		cout << "Lista Vacía." << endl;
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
		cout << "\n|ID: " << aux->id
			<< "|Nombre: " << aux->nombre
			<< "|Desc: " << aux->descripcion
			<< "|";
	}
	else {
		cout << "\nDATO NO ENCONTRADO";
	}
}

void modificarCircular(int id) {
	if (primero == NULL)
	{
		cout << "Lista Vacía." << endl;
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
		cout << "\n|ID: " << aux->id
			<< "|Nombre: " << aux->nombre
			<< "|Desc: " << aux->descripcion
			<< "|";

		cout << "\n\n---MODIFICAR" << endl;
		cout << "Nombre: "; cin >> aux->nombre;
		cout << "Desc: "; cin >> aux->descripcion;
	}
	else {
		cout << "\nDATO NO ENCONTRADO";
	}
}

void vaciarListaCircular() {
	if (primero == NULL) {
		cout << "\nLISTA VACIA, NO HAY NADA QUE VACIAR";
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
	cout << "\nVACIADA CORRECTAMENTE";
}

void menuListaCircular() {
	int id;
	string nombre;
	string descripcion;
	string titulo = "Lista Circular";
	string opciones[] = { "Insertar","Eliminar Dato","Mostrar Datos","Buscar","Modificar","Vaciar Lista","Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do
	{
		int opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1:
			system("cls");
			cout << "Ingrese ID: ";
			cin >> id;
			cin.ignore(1000, '\n');
			cout << "Ingrese Nombre: ";
			getline(cin, nombre);
			cout << "Ingrese Descripcion: ";
			getline(cin, descripcion);
			insertarCircular(id, nombre, descripcion);
			_getch();
			break;
		case 2:
			system("cls");
			cout << "Ingrese el ID a borrar: ";
			cin >> id;
			borrarCircular(id);
			_getch();
			break;
		case 3:
			system("cls");
			mostrarCircular();
			_getch();
			break;
		case 4:
			system("cls");
			cout << "Ingrese el ID a buscar: ";
			cin >> id;
			buscarCircular(id);
			_getch();
			break;
		case 5:
			system("cls");
			cout << "Ingrese el ID a modificar: ";
			cin >> id;
			modificarCircular(id);
			_getch();
			break;
		case 6:
			system("cls");
			vaciarListaCircular();
			_getch();
			break;
		case 7: return;
		}
	} while (opc != 7);
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

//MENÚ DE LA PILA
void menuPila(){
	NodoPila* pila = NULL;

	int opc;
	string titulo = "Estructura de Pila";
	string opciones[] = { "Ingreso de Datos de Pila", "Ver Datos en forma de Pila", "Modificar un dato", "Buscar un dato", "Eliminar un dato", "Atras (Menu Principal)"};
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones

	do
	{
		opc = menu(titulo, opciones, n);
		switch (opc) {
		case 1: 
			//AGREGAR EL PRODUCTO
			system("cls");
			push(pila);
			system("pause");
			break;
		case 2:
			//MOSTRAR LA PILA
			system("cls");
			mostrarPila(pila);
			break;
		case 3:
			//MODIFICAR
			system("cls");
			int id; //ID a modificar
			cout << "Ingrese el ID del producto que desea MODIFICAR: ";
			cin >> id;
			modificarPila(pila, id);
			system("pause");
			break;
		case 4:
			//BUSCAR EL ID
			system("cls");
			int idB; //ID a buscar
			cout << "Ingrese el ID para encontrar el producto: ";
			cin >> idB;
			buscarPila(pila, idB);
			system("pause");
			break;
		case 5:
			//ELIMINAR EL ÚLTIMO
			system("cls");
			pop(pila);
			_getch();
			break;
		case 6:
			return;
		default:
			cout << "Opcion invalida." << endl;
		}
	} while (true);

	system("pause");
}

//MENÚ PRINICIPAL
int menuPrincipal() {
	int n = 4;//OPCIONES DEL MENU PRINCIPAL
	string titulo = "MEMU PRINCIPAL";
	string opciones[] = { "Estrucutura de Pila", "Estructura de Cola", "Estructura Listas", "Salir"};

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
			return 0;
		}
	} while (true);

	cout << endl;
	system("pause");
}

//PANTALLA DE INICIO
void pantallaInicio() {
	//LETRAS COLORIDAS
	int xcol;

	//CUADRO CON TEXTO
	//Primera línea
	color(14);
	gotoxy(1, 2); cout << "╔";
	gotoxy(1, 3); cout << "║";
	gotoxy(1, 4); cout << "╚";

	for (xcol =2 ; xcol<=118 ; xcol++)
	{
		gotoxy(xcol, 2); cout << "═";
		gotoxy(xcol, 4); cout << "═";
		Sleep(10);
	}
	gotoxy(119, 2); cout << "╗";
	gotoxy(119, 3); cout << "║";
	gotoxy(119, 4); cout << "╝";

	//TEXTO EN EL CUADRO
	char titulo[] = " VENTA DE AIRE ";
	int longitud;
	longitud = strlen(titulo);
	int centro = (((119-longitud)/2)+1); //CENTRO DE LA PANTALLA = 53

	for (xcol =2; xcol <= centro; xcol++)
	{
		int colorRandom = (rand() % 15) + 1;
		color(colorRandom);
		gotoxy(xcol, 3); cout << titulo;
		Sleep(80);
	}

	color(7);
	cout << "\n\n\n\n\t\t\t\t\t\tUNIVERSIDAD MARIANO GALVEZ";
	cout << "\n\t\t\t\t\t\t  Ingenieria en Sistemas";

	color(8);
	cout << "\n\t\t\t\t\t------------------------------------------";

	color(10);
	cout << "\n\t\t\t\t\t\t  PROYECTO PILAS Y COLAS";

	color(8);
	cout << "\n\t\t\t\t\t------------------------------------------";

	color(7);
	cout << "\n\t\t\t\t\tJesus Armando Pantzey Santizo - 2290-24-24601";
	cout << "\n\t\t\t\t\tMiqueas Otoniel Ixcaya Xajil - 2290-24-24181";
	cout << "\n\t\t\t\t\tEli Emanuel Rosales Bala - 2290-24-14890";

	color(14);
	cout << "\n\n\t\t\t\t\t\t     PROGRAMACION III";


	cout << endl;
	system("pause");
}

//LOGO DE LA EMPRESA
void logo() {

	color(11);

	cout << "\t\t\t================================================================================\n\n";

	cout << "\t\t               █████╗ ██╗██████╗ ███████╗    ████████╗███████╗ ██████╗██╗  ██╗\n";
	cout << "\t\t              ██╔══██╗██║██╔══██╗██╔════╝    ╚══██╔══╝██╔════╝██╔════╝██║  ██║\n";
	cout << "\t\t              ███████║██║██████╔╝█████╗         ██║   █████╗  ██║     ███████║\n";
	cout << "\t\t              ██╔══██║██║██╔══██╗██╔══╝         ██║   ██╔══╝  ██║     ██╔══██║\n";
	cout << "\t\t              ██║  ██║██║██║  ██║███████╗       ██║   ███████╗╚██████╗██║  ██║\n";
	cout << "\t\t              ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚══════╝       ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝\n\n";

	color(9);

	cout << "\t\t                            ╔═════════════════════════════╗\n";
	cout << "\t\t                        ╔═══╝   ~ ~ ~   A I R E   ~ ~ ~   ╚═══╗\n";
	cout << "\t\t                     ╔══╝     ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈     ╚══╗\n";
	cout << "\t\t                   ╔═╝      ≈     ≈     ≈     ≈     ≈     ≈      ╚═╗\n";
	cout << "\t\t                  ║         ≈        Aire embolsada       ≈         ║\n";
	cout << "\t\t                  ║         ≈     ≈     ≈     ≈     ≈     ≈         ║\n";
	cout << "\t\t                   ╚═╗        ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈        ╔═╝\n";
	cout << "\t\t                     ╚══╗      >>>>>>>>>>>>>>>>>>>>>>>>>      ╔══╝\n";
	cout << "\t\t                        ╚═══╗    >>>   >>>   >>>   >>>    ╔═══╝\n";
	cout << "\t\t                            ╚═════════════════════════════╝\n\n";

	color(10);
	cout << "\t\t\t                   \"Respira tecnologia. Controla el aire.\"\n\n";

	color(8);
	cout << "\t\t\t================================================================================\n";

	color(7);
	_getch();
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	login();
	system("cls");
	logo();
	system("cls");
	pantallaInicio();
	system("cls");
	color(7);
	menuPrincipal();
}
