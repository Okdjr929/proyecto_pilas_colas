#include "ArbolBB.h"
NodoArbol* raiz = NULL;

//=============================
// DEFINICIÓN DE FUNCIONES ARBOL BINARIO
//=============================
// Insertar nodo
void insertarNodo(NodoArbol*& raiz, int id, string nombre, string descripcion, float precio) {

	if (raiz == NULL) { //Si el árbol está vacío, se crea el nodo raíz

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
	else { //Si el árbol no está vacío, se compara el ID para decidir si se inserta a la izquierda o a la derecha

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

//--------------------------RECORRER Y MOSTRAR SU ORDEN--------------------------
//Para las funciones de RECORRIDO
void mostrarNodoConexion(NodoArbol* nodo, int& y) {

	string actual = direccionCorta(nodo, 8, 6);

	string izq = direccionCorta(nodo->izquierdo, 8, 6);

	string der = direccionCorta(nodo->derecho, 8, 6);
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

void inOrden(NodoArbol* raiz, int& y) {
	if (raiz == NULL) return;
	//Subarbol izquierdo
	inOrden(raiz->izquierdo, y);
	//RAIZ
	mostrarNodoConexion(raiz, y);
	//Subarbol derecho
	inOrden(raiz->derecho, y);
}


//----------------DIBUJAR LA CAJA DE DATOS------------------------------
void dibujarCaja(int x, int y, int id, string direccion, float precio) {

	color(22);

	// Fuerza longitud exacta
	direccion = direccion.substr(0, 11);

	gotoxy(x, y);
	cout << "┌─────────────┐"; //15

	gotoxy(x, y + 1);
	cout << "│ID: "
		<< left << setw(9) << id
		<< "│";

	gotoxy(x, y + 2);
	cout << "│"
		<< left << setw(13) << direccion
		<< "│";

	gotoxy(x, y + 3);
	cout << "│Q = "
		<< fixed << setprecision(2)
		<< setw(9) << precio
		<< "│";

	gotoxy(x, y + 4);
	cout << "└─────────────┘";

	color(7);
}

// Función recursiva que calcula las coordenadas exactas de cada nodo y sus diagonales
void mostrarArbol(NodoArbol* raiz, int x, int y, int rangoHorizontal) {
	if (raiz == nullptr) return;

	// 1. Dibujar el nodo actual en la posición (X, Y)
	string dir = direccionCorta(raiz, 11, 8);
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

void subMenuRecorrido() {

	int opc;
	string titulo = "Recorrido de Arbol";
	string opciones[] = { "PREORDEN", "POSTORDEN", "INORDEN", "Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do
	{
		system("title RECORRIDO");
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
				system("title PREORDEN");
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
				system("cls");
				dibujarLineasModulo();
				color(12);
				imprimirCentradoModulo("El arbol esta vacio", 21);
				color(7);
			}
			else {
				system("title POSTORDEN");
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
				system("cls");
				dibujarLineasModulo();
				color(12);
				imprimirCentradoModulo("El arbol esta vacio", 21);
				color(7);
			}
			else {
				system("title INORDEN");
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

//MENU ÁRBOL
void menuArbol() {
	system("title ARBOL BB");
	int id;
	float precio;
	string nombre, descripcion;
	NodoArbol* resultado;
	int opc;
	string titulo = "Estructura de Arbol";
	string opciones[] = { "Ingreso de Datos de Arbol", "Buscar un dato", "Recorrer", "Eliminar un dato", "Eliminar todo el Arbol","Mostrar Datos del Arbol","Mostrar Estructura del Arbol", "Atras (Menu Principal)" };
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

