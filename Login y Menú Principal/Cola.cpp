#include "Cola.h"
#include <iomanip>
NodoCola* frente = NULL;
NodoCola* fin = NULL;

//=============================
// DEFINICIÓN DE FUNCIONES COLA
//=============================
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

	string actual = direccionCorta(nodo, 8, 6);
	string siguiente = direccionCorta(nodo->siguiente, 8, 6); // Limitar la descripción a 16 caracteres
	//y  =10
	// x = 5
	int contador = 0;
	if (frente == nodo) {
		gotoxy(x + 7, y - 1); cout << "FRENTE";
		if(fin == nodo){
			gotoxy(x + 8, y + 8); cout << "FIN";
		}
	}else if (fin == nodo && nodo->siguiente == NULL){
			gotoxy(x + 8, y - 1);
			cout << "FIN";
	}

	gotoxy(x, y);
	cout << "┌──────────────────┐"; //20 de punta a punta
	color(11);
	gotoxy(x, y + 1);
	cout << "│ "
		<< setw(16)
		<< left
		<< actual
		<< " │";
	color(7);

	gotoxy(x, y + 2);
	cout << "│ ID: "
		<< setw(12)
		<< left
		<< nodo->id
		<< " │";
	gotoxy(x, y + 3);
	cout << "│ "
		<< setw(16)
		<< left
		<< nodo->nombre.substr(0, 16)
		<< " │";
	gotoxy(x, y + 4);
	cout << "│ "
		<< setw(16)
		<< left
		<< nodo->descripcion.substr(0, 16)
		<< " │";
	gotoxy(x, y + 5);
	cout << "│ Q"
		<< setw(15) //setw es para establecer un ancho fijo para el campo
		<< left //left sirve para alinear a la izquierda, right para alinear a la derecha
		<< fixed //fixed es para mostrar el número en formato decimal fijo, sin notación científica
		<< setprecision(2) //es para mostrar el precio con 2 decimales
		<< nodo->precio
		<< " │";

	color(11);
	gotoxy(x, y + 6);
	cout << "│ "
		<< setw(16)
		<< left
		<< "Sig: " + siguiente
		<< " │";
	color(7);

	gotoxy(x, y + 7);
	cout << "└──────────────────┘";
	color(7);
	y += 6;
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
		color(12);
		imprimirCentradoModulo("COLA VACIA", 21);
		color(7);
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
	system("title COLA");
	int opc;
	int id;
	string nombre;
	string descripcion;
	string titulo = "Estructura de Cola";
	string opciones[] = { "Ingreso de Datos de Cola", "Ver Datos en forma de Cola", "Modificar un dato", "Buscar un dato", "Eliminar un dato", "Atras (Menu Principal)" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones

	do
	{
		opc = menu(titulo, opciones, n);
		if (opc != 2 && opc != 6) { // Opciones que NO usan las líneas
			system("cls");
			dibujarLineasModulo();
		}
		switch (opc)
		{
		case 1:
			//ENCOLAR DATOS
			imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL + 2);
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
			gotoxy(60, 37); system("pause");
			break;
		case 3:
			//MODIFICAR UN DATO
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
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			NodoCola* encontrado = buscarCola(id);

			if (encontrado != NULL) {
				system("cls");
				dibujarLineasModulo();
				color(10);
				imprimirCentradoModulo("Producto encontrado:", YINICIAL + 5);
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
			desencolar();
			gotoxy(60, 31); system("pause");
			break;

		case 6:
			return;
		}

	} while (true);
}