#include "Utilidades.h"

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

void imprimirCentradoModulo(string texto, int y) {
	int x = (ANCHO - texto.length()) / 2;
	gotoxy(x, y);
	cout << texto;
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
		}
		else {
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
		for (int i = 0; i < titulo.length() + 6; i++)
		{
			gotoxy((((ANCHO - titulo.length())) / 2) - 3 + i, 11); cout << "▓";
		}

		gotoxy((ANCHO - titulo.length()) / 2, 12); cout << titulo;

		for (int i = 0; i < titulo.length() + 6; i++)
		{
			gotoxy((((ANCHO - titulo.length())) / 2) - 3 + i, 13); cout << "▓";
		}

		color(7);

		int Yinicio = (ALTO - n) / 2;

		// Imprimimos las opciones, resaltando la seleccion
		for (int i = 0; i < n; i++)
		{
			gotoxy(((ANCHO - opciones[0].length()) / 2) - 2, Yinicio + i);
			if (i + 1 == opcionSeleccionada) {
				color(selectedColor);
				cout << i + 1 << ") " << opciones[i];
				color(7);
			}
			else {
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

void dibujarLineasModulo() {
	for (int i = 28; i < 128; i++)
	{
		gotoxy(i, 10); cout << "■";
		gotoxy(i, 32); cout << "■";
	}
}

string direccionCorta(void* lista, int longitud, int caracteresFinales) {
	stringstream ss; //sirve para convertir cualquier tipo de dato a string
	ss << lista; //convertimos la direccion a string
	string direccion = ss.str(); //obtenemos la direccion en formato string
	if (direccion.length() > longitud) {
		return ".." + direccion.substr(direccion.length() - caracteresFinales); //si la direccion es muy larga, mostramos solo los últimos 6 caracteres precedidos por ".."
	}
}

