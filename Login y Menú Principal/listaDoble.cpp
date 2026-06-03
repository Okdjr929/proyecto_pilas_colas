#include "listaDoble.h"

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
/*void mostrarDoble(NodoDoble* lista) {

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

	imprimirCentradoModulo("======= LISTA DOBLE ENLAZADA =======", 2);

	// ===== VALIDACION =====
	if (lista == NULL) {

		color(12);
		imprimirCentradoModulo("LISTA DOBLE VACIA", 20);
		color(7);
		return;
	}

	NodoDoble* aux = lista;

	int y = 5;

	while (aux != NULL && y < 35) {

		string actual = direccionCorta(aux, 8, 6);

		string anterior = direccionCorta(aux->anterior, 8, 6);

		string siguiente = direccionCorta(aux->siguiente, 8, 6);
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
}*/
void dibujarNodoListaDoble(int x, int y, NodoDoble* nodo) {

	string actual = direccionCorta(nodo, 8, 6);
	string siguiente = direccionCorta(nodo->siguiente, 8, 6); // Limitar la descripción a 16 caracteres
	string anterior = direccionCorta(nodo->anterior, 8, 6); // Limitar la descripción a 16 caracteres
	//y  =10
	// x = 12, 12-8 = 3

	if (nodo->anterior == NULL && nodo->siguiente != NULL || nodo->anterior == NULL && nodo->siguiente == NULL) { //Uno nodo
		gotoxy(3, y + 3); cout << "┌────┐";
		gotoxy(3, y + 4); cout << "│NULL│◄►";
		gotoxy(3, y + 5); cout << "└────┘";
	}
	if (nodo->anterior == NULL && nodo->siguiente == NULL) { //Parte final
		gotoxy(x + 20, 10 + 3); cout << "  ┌────┐";
		gotoxy(x + 20, 10 + 4); cout << "◄►│NULL│";
		gotoxy(x + 20, 10 + 5); cout << "  └────┘";
	}
	if (nodo->anterior != NULL && nodo->siguiente == NULL) {
		gotoxy(x + 20, 10 + 3); cout << "  ┌────┐";
		gotoxy(x + 20, 10 + 4); cout << "◄►│NULL│";
		gotoxy(x + 20, 10 + 5); cout << "  └────┘";
	}

	gotoxy(x, y);
	cout << "┌──────────────────┐";

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
		<< setw(15)
		<< left
		<< fixed
		<< setprecision(2)
		<< nodo->precio
		<< " │";

	color(11);
	gotoxy(x, y + 6);
	cout << "│ "
		<< setw(16)
		<< left
		<< ("Ant: " + anterior)
		<< " │";

	gotoxy(x, y + 7);
	cout << "│ "
		<< setw(16)
		<< left
		<< ("Sig: " + siguiente)
		<< " │";

	color(7);
	gotoxy(x, y + 8);
	cout << "└──────────────────┘";
	color(7);

	color(7);
	y += 8;

}
void mostrarListaDoble(NodoDoble* lista)
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

	imprimirCentradoModulo("======= INVENTARIO FORMA LISTA DOBLE =======", 2);

	if (lista == NULL) {
		color(12);
		imprimirCentradoModulo("LISTA VACIA", 21);
		color(7);
		return;
	}

	NodoDoble* aux = lista;

	int x = 12;

	int y = 10;

	while (aux != NULL) {

		dibujarNodoListaDoble(x, y, aux);

		// ===== FLECHA =====
		if (aux->siguiente != NULL) {

			color(15);

			gotoxy(x + 21, y + 4); //x es la posición del nodo, 21 es el ancho del nodo, y+1 es para centrar la flecha verticalmente

			cout << "◄=►";
		}

		x += 26;

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
	system("title LISTA DOBLE");
	NodoDoble* lista = NULL;
	int opc, id;
	string titulo = "Lista Doblemente Enlazadas";
	string opciones[] = { "Insertar Producto","Eliminar Producto","Mostrar Lista","Buscar Producto","Modificar Producto","Vaciar Lista","Regresar" };
	int n = sizeof(opciones) / sizeof(opciones[0]);
	do {
		opc = menu(titulo, opciones, n);
		if (opc != 3 && opc != 7) {
			system("cls");
			dibujarLineasModulo();
		}
		switch (opc) {

		case 1:
			//INSERTAR
			insertarDoble(lista);
			gotoxy(60, 31); system("pause");
			break;

		case 2:
			//ELIMINAR UN NODO
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
			mostrarListaDoble(lista);

			gotoxy(50, 38); system("pause");
			break;

		case 4:
			//BUSCAR
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			buscarDoble(lista, id);
			gotoxy(60, 31); system("pause");
			break;

		case 5:
			imprimirCentradoModulo("Ingrese el ID del producto a modificar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarDoble(lista, id);
			gotoxy(60, 31); system("pause");
			break;

		case 6:
			vaciarDoble(lista);
			gotoxy(60, 31); system("pause");
			break;

		case 7:
			return;
		}

	} while (true);
}