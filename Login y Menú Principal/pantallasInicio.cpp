#include "Utilidades.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

//-----------PANTALLA DE INICIO-----------
//Función para mostrar una pantalla de inicio con un diseño visual atractivo.
void pantallaInicio() {
	//LETRAS COLORIDAS
	int xcol;
	system("title INICIO");
	//CUADRO CON TEXTO
	//Primera línea
	color(14);
	gotoxy(1, 5); cout << "╔";
	gotoxy(1, 6); cout << "║";
	gotoxy(1, 7); cout << "╚";

	for (xcol = 2; xcol <= 154; xcol++)
	{
		gotoxy(xcol, 5); cout << "═";
		gotoxy(xcol, 7); cout << "═";
		Sleep(10);
	}
	gotoxy(155, 5); cout << "╗";
	gotoxy(155, 6); cout << "║";
	gotoxy(155, 7); cout << "╝";

	//TEXTO EN EL CUADRO
	char titulo[] = " VENTA DE AIRE ";
	int longitud;
	longitud = strlen(titulo);
	int centro = (((155 - longitud) / 2) + 1); //CENTRO DE LA PANTALLA = 53

	for (xcol = 2; xcol <= centro; xcol++)
	{
		int colorRandom = (rand() % 15) + 1;
		color(colorRandom);
		gotoxy(xcol, 6); cout << titulo;
		Sleep(80);
	}

	color(7);
	cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tUNIVERSIDAD MARIANO GALVEZ";
	cout << "\n\t\t\t\t\t\t\t\t  Ingenieria en Sistemas";

	color(8);
	cout << "\n\t\t\t\t\t\t\t------------------------------------------";

	color(10);
	cout << "\n\t\t\t\t\t\t\t\tPROYECTO PROGRAMACION III";

	color(8);
	cout << "\n\t\t\t\t\t\t\t------------------------------------------";

	color(7);
	cout << "\n\t\t\t\t\t\t\tJesus Armando Pantzey Santizo - 2290-24-24601";
	cout << "\n\t\t\t\t\t\t\tMiqueas Otoniel Ixcaya Xajil - 2290-24-24181";
	cout << "\n\t\t\t\t\t\t\tEli Emanuel Rosales Bala - 2290-24-14890";

	color(14);
	cout << "\n\n\t\t\t\t\t\t\t\t     PROGRAMACION III";

	gotoxy(1, 38);
	system("pause");
}

//------------LOGO DE LA EMPRESA--------------
//Función para mostrar el logo de la empresa con un diseño visual atractivo.
void logo() {
	system("title LOGO");
	color(11);

	cout << "\n\n\n\n\n\n\t\t\t\t\t================================================================================\n\n";

	cout << "\t\t\t\t               █████╗ ██╗██████╗ ███████╗    ████████╗███████╗ ██████╗██╗  ██╗\n";
	cout << "\t\t\t\t              ██╔══██╗██║██╔══██╗██╔════╝    ╚══██╔══╝██╔════╝██╔════╝██║  ██║\n";
	cout << "\t\t\t\t              ███████║██║██████╔╝█████╗         ██║   █████╗  ██║     ███████║\n";
	cout << "\t\t\t\t              ██╔══██║██║██╔══██╗██╔══╝         ██║   ██╔══╝  ██║     ██╔══██║\n";
	cout << "\t\t\t\t              ██║  ██║██║██║  ██║███████╗       ██║   ███████╗╚██████╗██║  ██║\n";
	cout << "\t\t\t\t              ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚══════╝       ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝\n\n";

	color(9);

	cout << "\t\t\t\t                               ╔═════════════════════════════╗\n";
	cout << "\t\t\t\t                           ╔═══╝   ~ ~ ~   A I R E   ~ ~ ~   ╚═══╗\n";
	cout << "\t\t\t\t                        ╔══╝     ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈     ╚══╗\n";
	cout << "\t\t\t\t                      ╔═╝      ≈     ≈     ≈     ≈     ≈     ≈      ╚═╗\n";
	cout << "\t\t\t\t                     ║         ≈        Aire embolsada       ≈         ║\n";
	cout << "\t\t\t\t                     ║         ≈     ≈     ≈     ≈     ≈     ≈         ║\n";
	cout << "\t\t\t\t                      ╚═╗        ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈        ╔═╝\n";
	cout << "\t\t\t\t                        ╚══╗      >>>>>>>>>>>>>>>>>>>>>>>>>      ╔══╝\n";
	cout << "\t\t\t\t                           ╚═══╗    >>>   >>>   >>>   >>>    ╔═══╝\n";
	cout << "\t\t\t\t                               ╚═════════════════════════════╝\n\n";

	color(10);
	cout << "\t\t\t\t\t                   \"Respira tecnologia. Controla el aire.\"\n\n";

	color(8);
	cout << "\t\t\t\t\t================================================================================\n";

	color(7);
	_getch();
}