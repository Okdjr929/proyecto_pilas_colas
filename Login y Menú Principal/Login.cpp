#include "Login.h"
#include "Utilidades.h"


int login() {

	system("title LOGIN");

	char opcion;

	int i = 0, j = 3;

	string nombre;
	string contra;
	string linea;
	string datos[2];

	int contador = 0;

	size_t posicion = 0;

	do {

		system("cls");

		// ===== MARCO =====
		for (int k = 20; k <= 136; k++) {

			gotoxy(k, 3);
			cout << "■";

			gotoxy(k, 30);
			cout << "■";
		}

		for (int k = 4; k <= 30; k++) {
			gotoxy(20, k);
			cout << "■";

			gotoxy(136, k);
			cout << "■";
		}

		// ===== TITULO =====
		color(6);

		imprimirCentradoModulo("LOGIN VENTA DE AIRE", 6);

		color(7);

		imprimirCentradoModulo("===================================", 8);

		// ===== INTENTO =====
		color(14);

		imprimirCentradoModulo("Intento: " + to_string(j), 11);

		// ===== NOMBRE =====
		color(11);
		imprimirCentradoModulo("Nombre:", 15);
		gotoxy(68, 16);
		cin >> nombre;

		// ===== CONTRASENIA =====
		imprimirCentradoModulo("Contrasenia:", 19);
		gotoxy(68, 20);
		cin >> contra;

		color(7);

		// ===== VALIDACION =====
		fstream archivo("Documento.txt");

		while (getline(archivo, linea)) {

			while ((posicion = linea.find(",")) != string::npos) {

				datos[contador] =
					linea.substr(0, posicion);

				linea.erase(0, posicion + 1);

				contador++;
			}

			contador = 0;

			if (datos[contador] == nombre) {
				break;
			}
		}

		// ===== LOGIN CORRECTO =====
		if (datos[0] == nombre &&
			datos[1] == contra)
		{
			color(10);
			imprimirCentradoModulo("ACCESO CONCEDIDO", 24);

			color(7);

			gotoxy(65, 27);

			system("pause");

			return EXIT_SUCCESS;
		}

		// ===== LOGIN INCORRECTO =====
		else {
			color(4);
			imprimirCentradoModulo("DATOS INCORRECTOS", 24);
			i++;
			j--;

			// ===== SALIR =====
			color(14);
			imprimirCentradoModulo("Intentar otra vez [S/N] ", 26);
			cin >> opcion;
			if (opcion == 'N' || opcion == 'n') {
				color(4);
				imprimirCentradoModulo("SALIENDO DEL LOGIN...", 28);
				color(7);
				cout << "\n\n\n\n";
				exit(EXIT_FAILURE);
				return 0;
			}
		}

		if (i >= 3) {
			system("cls");
			// ===== MARCO =====
			for (int k = 20; k <= 136; k++) {

				gotoxy(k, 3);
				cout << "■";

				gotoxy(k, 30);
				cout << "■";
			}

			for (int k = 4; k <= 30; k++) {
				gotoxy(20, k);
				cout << "■";

				gotoxy(136, k);
				cout << "■";
			}

			// ===== ALERTA =====
			color(4);

			imprimirCentradoModulo(
				"** ALERTA DE INTRUSO **",
				18
			);
			gotoxy(0, 35);
			color(7);
			exit(EXIT_FAILURE);
			return 0;
		}

	} while (opcion == 'S' || opcion == 's');


	color(7);

	gotoxy(65, 22);

	system("pause");
}