#include "Pila.h"
#include "Utilidades.h"

//=============================
// DEFINICIÓN DE FUNCIONES PILA
//=============================
// Agregar un nuevo elemento a la pila (LIFO)
void push(NodoPila*& pila) {
	NodoPila* nuevo_nodo = new NodoPila();
	int y = 16;
	imprimirCentradoModulo("--- Registrando Nuevo Producto ---", YINICIAL + 2);
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
	imprimirCentradoModulo("Producto eliminado:", YINICIAL + 2);
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

			imprimirCentradoModulo("--- Ingrese los Nuevos Datos ---", YINICIAL + 7);
			cin.ignore(1000, '\n');

			gotoxy(XINICIAL, YINICIAL + 8); cout << "Nuevo Nombre: ";
			getline(cin, aux->nombre);

			gotoxy(XINICIAL, YINICIAL + 9); cout << "Nueva Descripcion: ";
			getline(cin, aux->descripcion);

			gotoxy(XINICIAL, YINICIAL + 10); cout << "Nuevo Precio: ";
			cin >> aux->precio;
			cin.ignore(1000, '\n');

			color(10);
			gotoxy(XINICIAL, YINICIAL + 12); cout << "Producto modificado correctamente." << endl;
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

		return;
	}

	// ===== CONTENIDO =====
	NodoPila* aux = pila;

	int x = 51; //X fijo para mostrar los datos en columna
	int y = 3;
	/*
	while (aux != NULL && y < 32) {

		gotoxy(x, y++);
		cout << "Direccion: " << aux;

		gotoxy(x, y++);
		cout << "ID: " << aux->id;

		gotoxy(x, y++);
		cout << "Nombre: " << aux->nombre;

		gotoxy(x, y++);
		cout << "Descripcion: " << aux->descripcion;

		gotoxy(x, y++);
		cout << "Precio: " << aux->precio;

		gotoxy(x, y++);
		cout << "Apunta a: " << aux->siguiente;

		gotoxy(x, y++);
		cout << "-----------------------------------------------------"; //De punta a punta (54 caracteres)

		y++;

		aux = aux->siguiente;
	}
	*/
	while (aux != NULL && y < 32) {
		if (aux == pila) {
			gotoxy(x + 42, y+1); cout << "<--- INICIO";
		}
		// Línea superior
		gotoxy(x, y++);
		cout << "┌──────────────────────────────────────┐"; //40

		gotoxy(x, y++);
		cout << "│ Direccion : " << left << setw(25) << aux << "│";

		gotoxy(x, y++);
		cout << "│ ID        : " << left << setw(25) << aux->id << "│";

		gotoxy(x, y++);
		cout << "│ Nombre    : " << left << setw(25) << aux->nombre << "│";

		gotoxy(x, y++);
		cout << "│ Descrip...: " << left << setw(25) << aux->descripcion << "│";

		gotoxy(x, y++);
		cout << "│ Precio    : " << left << setw(25) << aux->precio << "│";

		gotoxy(x, y++);
		cout << "│ Apunta a  : " << left << setw(25) << aux->siguiente << "│";

		// Línea inferior
		gotoxy(x, y++);
		cout << "└──────────────────────────────────────┘";

		// Flecha hacia el siguiente nodo
		if (aux->siguiente != NULL) {
			gotoxy(x + 20, y++);
			cout << "▼";
		}
		if (aux->siguiente == NULL) {
			gotoxy(x + 42, y - 2);
			cout << "<-- FIN";
		}

		aux = aux->siguiente;
	}

	color(7);

	gotoxy(55, 40);
	system("pause");
}

//MENÚ DE LA PILA
void menuPila() {
	system("title PILA");
	NodoPila* pila = NULL;

	int opc;
	string titulo = "Estructura de Pila";
	string opciones[] = { "Ingreso de Datos de Pila", "Ver Datos en forma de Pila", "Modificar un dato", "Buscar un dato", "Eliminar un dato", "Atras (Menu Principal)" };
	int n = sizeof(opciones) / sizeof(opciones[0]); //Tamaño del arreglo, que representa el # de opciones

	do
	{

		opc = menu(titulo, opciones, n);

		if (opc != 2 && opc != 6) { // Opciones que NO usan las líneas
			system("cls");
			dibujarLineasModulo();
		}

		switch (opc) {
		case 1:
			//AGREGAR EL PRODUCTO
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