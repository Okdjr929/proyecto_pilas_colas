#include "ArbolAVL.h"
NodoAVL* raizAVL = NULL;

//=============================
// DEFINICIÓN DE FUNCIONES ARBOL AVL
//=============================

//-----------------------------FACTOR DE EQUILIBRIO-----------------------------
int obtenerAltura(NodoAVL* raiz) {
	if (raiz == NULL) return 0;

	return raiz->altura; //La altura se almacena en cada nodo y se actualiza durante las inserciones y eliminaciones
}

int obtenerFactorEquilibrio(NodoAVL* raiz) {
	if (raiz == NULL) {
		return 0;
	}
	return obtenerAltura(raiz->derecha) - obtenerAltura(raiz->izquierda); //
}

//-----------------------------ROTACIONES-----------------------------
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

//-----------------------------ACTUALIZAR ALTURAS E INSERTAR-----------------------------
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
	if (fe < -1 && id < raiz->izquierda->id) { //Cuando "fe" es menor a -1 = árbol está cargado a la izquierda. Si el ID del nuevo nodo es menor al ID del hijo izquierdo de la raíz, entonces se trata de un caso izquierda-izquierda.
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
			gotoxy(60, YINICIAL + 4); cout << "Nodo afectado: " << raiz->id;
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


//----------------DIBUJAR LA CAJA DE DATOS-------------------------------
void dibujarCajaAVL(int x, int y, int id, string direccion, float precio, int fe) {

	color(22);

	// Fuerza longitud exacta
	direccion = direccion.substr(0, 11);

	gotoxy(x, y);
	cout << "┌─────────────┐"; //15

	gotoxy(x, y + 1);
	cout << "│ID "
		<< left << setw(5) << id //left alinea a la izquierda, setw(5) reserva 5 espacios para el ID
		<< " ["
		<< setw(2) << fe
		<< "]│";
	gotoxy(x, y + 2);
	cout << "│"
		<< left << setw(13) << direccion
		<< "│";
	gotoxy(x, y + 3);
	cout << "│ Q"
		<< fixed << setprecision(3) //fixed y setprecision(3) para mostrar el precio con 3 decimales
		<< setw(10) << precio
		<< " │";

	gotoxy(x, y + 4);
	cout << "└─────────────┘";

	color(7);
}

// Función recursiva que calcula las coordenadas exactas de cada nodo y sus diagonales
void mostrarArbolAVL(NodoAVL* raiz, int x, int y, int rangoHorizontal) {
	if (raiz == nullptr) return;

	// 1. Dibujar el nodo actual en la posición (X, Y)
	string dir = direccionCorta(raiz, 13, 12); //11 es
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

NodoAVL* eliminarAVL(NodoAVL*& raiz, int id, bool mostrarMensaje = true) {
	if (raiz == NULL) {
		color(12);
		imprimirCentradoModulo("ID no encontrado", 21);
		color(7);
		return raiz;
	}

	//Buscar el nodo a eliminar
	if (id < raiz->id) {
		raiz->izquierda = eliminarAVL(raiz->izquierda, id, mostrarMensaje);
	}
	else if (id > raiz->id) {
		raiz->derecha = eliminarAVL(raiz->derecha, id, mostrarMensaje);
	}

	//Nodo encontrado
	else {
		if (mostrarMensaje) {
			color(10);
			dibujarLineasModulo();
			imprimirCentradoModulo("Producto eliminado", YINICIAL + 4);
			gotoxy(XINICIAL, YINICIAL + 5); cout << "ID: " << raiz->id;
			gotoxy(XINICIAL, YINICIAL + 6); cout << "Nombre: " << raiz->nombre;
			gotoxy(XINICIAL, YINICIAL + 7); cout << "Descripcion: " << raiz->descripcion;
			gotoxy(XINICIAL, YINICIAL + 8); cout << "Precio: " << raiz->precio;
			color(7);
			_getch();
		}

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
			delete temp;

		}
		else {
			NodoAVL* temporal = nodoMenorValor(raiz->derecha);

			raiz->id = temporal->id;
			raiz->nombre = temporal->nombre;
			raiz->descripcion = temporal->descripcion;
			raiz->precio = temporal->precio;
			raiz->derecha = eliminarAVL(raiz->derecha, temporal->id, false);
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




void menuArbolAVL() {
	system("title ARBOL AVL");
	int id;
	float precio;
	string nombre, descripcion;
	NodoAVL* resultado1;
	char respuesta;
	int opc;
	string titulo = "Estructura de Arbol AVL";
	string opciones[] = { "Ingreso de Datos de Arbol AVL", "Buscar un dato","Eliminar todo el Arbol AVL", "Eliminar un dato","Mostrar Datos Arbol AVL","Mostrar Estructura Arbol AVL", "Atras (Menu Principal)" };
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
				imprimirCentradoModulo("Producto encontrado:", YINICIAL + 5);
				gotoxy(XINICIAL, YINICIAL + 6); cout << "ID: " << resultado1->id << endl;
				gotoxy(XINICIAL, YINICIAL + 7); cout << "Nombre: " << resultado1->nombre << endl;
				gotoxy(XINICIAL, YINICIAL + 8); cout << "Descripcion: " << resultado1->descripcion << endl;
				gotoxy(XINICIAL, YINICIAL + 9); cout << "Precio: " << resultado1->precio << endl;
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