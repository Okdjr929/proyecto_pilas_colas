#include "listaSimple.h"

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

/*void mostrarLista(NodoLista* lista) {

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

	imprimirCentradoModulo("======= LISTA SIMPLE ENLAZADA =======", 2);

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

		string actual = direccionCorta(aux, 8, 6);
		string siguiente = direccionCorta(aux->siguiente, 8, 6);

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
}*/
void dibujarNodoLista(int x, int y, NodoLista* nodo) {

	string actual = direccionCorta(nodo, 8, 6);
	string siguiente = direccionCorta(nodo->siguiente, 8, 6); // Limitar la descripción a 16 caracteres
	//y  =10
	// x = 5
	int contador = 0;

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
void mostrarLista(NodoLista* lista)
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

	imprimirCentradoModulo("======= INVENTARIO FORMA LISTA =======", 2);

	if (lista == NULL) {
		color(12);
		imprimirCentradoModulo("LISTA VACIA", 21);
		color(7);
		return;
	}

	NodoLista* aux = lista;

	int x = 5;

	int y = 10;

	while (aux != NULL) {

		dibujarNodoLista(x, y, aux);

		// ===== FLECHA =====
		if (aux->siguiente != NULL) {

			color(15);

			gotoxy(x + 21, y + 4); //x es la posición del nodo, 21 es el ancho del nodo, y+1 es para centrar la flecha verticalmente

			cout << "= ►";
		}

		x += 26;

		aux = aux->siguiente;
	}

	color(7);

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
	system("title LISTA SIMPLE");
	NodoLista* lista = NULL;
	int id;
	float precio;
	string nombre, descripcion;
	string titulo = "Lista Simple";
	string opciones[] = { "Insertar Producto","Eliminar Producto","Mostrar Lista", "Buscar Producto", "Modificar Producto","Vaciar Lista","Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones
	do {
		int opc = menu(titulo, opciones, n);
		if (opc != 3 && opc != 7) { // Opciones que NO usan las líneas
			system("cls");
			dibujarLineasModulo();
		}
		switch (opc) {
		case 1:
			//INSERTAR
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
			gotoxy(60, 37); system("pause");
			break;

		case 4:
			//BUSCAR
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			buscarLista(lista, id);
			gotoxy(60, 31); system("pause");
			break;
		case 5:
			//MODIFICAR
			imprimirCentradoModulo("Ingrese el ID del producto a modificar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarLista(lista, id);
			gotoxy(60, 31); system("pause");
			break;
		case 6:
			//VACIAR LISTA
			vaciarLista(lista);
			gotoxy(60, 31); system("pause");
			break;
		case 7:
			return;
		}

	} while (true);
}