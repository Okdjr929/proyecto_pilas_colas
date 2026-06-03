#include "listaCircular.h"
//Variables globales
nodoCircular* primero;
nodoCircular* ultimo;

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

	if (primero == NULL) { //En caso de que la lista esté vacía
		primero = nuevo;
		nuevo->siguiente = primero; //Hace referencia al primer nodo
		ultimo = nuevo;
	}
	else if (primero->id > id) //En caso de que el nuevo nodo deba ser el nuevo primero
	{
		//primero = 10
		//nuevo = 5
		nuevo->siguiente = primero;
		primero = nuevo;
		ultimo->siguiente = primero;

	}
	else { //En caso de que el nuevo nodo deba ser el nuevo último o un nodo intermedio
		nodoCircular* anterior = primero; //anterior = 5
		while (anterior->siguiente != primero && anterior->siguiente->id < id) //while(si, 10 < 6)
			anterior = anterior->siguiente; //anterior = 10
		nuevo->siguiente = anterior->siguiente; //nuevo = 6, anterior->siguiente = 10
		anterior->siguiente = nuevo; //anterior->siguiente = nuevo, anterior = 5, nuevo = 6

		if (anterior == ultimo) //En caso de que el nuevo nodo deba ser el nuevo último
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
	//10, 20, 40, 50
	//BORRAR 30
	do {
		if (actual->id == id) { //Verifico que el nodo n +1 sea igual al dato
			if (primero == ultimo) //En caso de que solo haya un nodo en la lista
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
			else if (actual == primero) { //En caso de que el nodo a eliminar sea el primero
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
			else if (actual == ultimo) //En caso de que el nodo a eliminar sea el último
			{
				anterior->siguiente = primero; //el nodo anterior al último ahora apunta al primero
				ultimo = anterior; //el nodo anterior al último ahora es el nuevo último
				color(10);
				imprimirCentradoModulo("Producto eliminado:", YINICIAL + 4);
				gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << actual->id << endl;
				gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << actual->nombre << endl;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << actual->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << actual->precio << endl;
				color(7);
				delete actual;
			}
			else { //En caso de que el nodo a eliminar sea un nodo intermedio
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
		anterior = actual;
		actual = actual->siguiente;
	} while (actual != primero);
	if (!encontrado) {
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
	}
}

//Mostrar Lista Circular
/*void mostrarCircular() {

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

		string actual = direccionCorta(aux, 8, 6);

		string siguiente = direccionCorta(aux->siguiente, 8, 6);

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
}*/
void dibujarNodoListaCircular(int x, int y, nodoCircular* nodo) {

	string actual = direccionCorta(nodo, 8, 6);
	string siguiente = direccionCorta(nodo->siguiente, 8, 6); // Limitar la descripción a 16 caracteres
	//y  =10
	// x = 5
	

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

	if (nodo->siguiente == primero && nodo != primero)
	{
		// Baja desde el último nodo
		for (int i = y + 8; i <= y + 12; i++)
		{
			gotoxy(x + 9, i);
			cout << "│";
		}

		// Línea horizontal hacia el primer nodo
		for (int i = 15; i <= x + 9; i++)
		{
			gotoxy(i, y + 12);
			cout << "─";
		}

		// Sube hasta el primer nodo
		for (int i = y + 11; i >= y + 9; i--)
		{
			gotoxy(15, i);
			cout << "│";
		}

		// Flecha al primer nodo
		gotoxy(15, y + 8);
		cout << "▲";
	}
	color(7);
	y += 6;
}
void mostrarListaCircular()
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

	if (primero == NULL) {
		color(12);
		imprimirCentradoModulo("LISTA VACIA", 21);
		color(7);
		return;
	}

	nodoCircular* aux = primero;

	int x = 5;

	int y = 10;

	do
	{
		dibujarNodoListaCircular(x, y, aux);

		// ===== FLECHA =====
		if (aux->siguiente != primero) {

			color(15);

			gotoxy(x + 21, y + 4); //x es la posición del nodo, 21 es el ancho del nodo, y+1 es para centrar la flecha verticalmente

			cout << "= ►";
		}

		x += 26;

		aux = aux->siguiente;
	} while (aux != primero);
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
	system("title LISTA CIRCULAR");
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
		if (opc != 3 && opc != 7) {
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
			mostrarListaCircular();
			gotoxy(50, 38);
			system("pause");
			break;
		case 4:
			//BUSCAR
			imprimirCentradoModulo("Ingrese el ID para encontrar el producto: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			buscarCircular(id);
			gotoxy(60, 31); system("pause");
			break;
		case 5:
			//MODIFICAR
			imprimirCentradoModulo("Ingrese el ID del producto a modificar: ", 16);
			cin >> id;
			system("cls");
			dibujarLineasModulo();
			modificarCircular(id);
			gotoxy(60, 31); system("pause");
			break;
		case 6:
			vaciarListaCircular();
			gotoxy(60, 31); system("pause");
			break;
		case 7: return;
		}
	} while (true);
}