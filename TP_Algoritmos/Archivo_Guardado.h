#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include "Base.h"

class Archivo_Guardado
{
private:
	int vida, x, y;
public:
	Archivo_Guardado() {}
	~Archivo_Guardado() {}

	void Guardar_partida() {
		string nombre_partida;

		nombre_partida = "AAA.txt";

		ofstream archivo(nombre_partida);

		archivo << vida << " " << x << " " << y;

		archivo.close();
	}

	void Cargar_partida() {
		string nombre_partida;


		nombre_partida = "AAA.txt";

		ifstream archivo(nombre_partida);

		string texto;

		getline(archivo, texto);

		string arreglo[3];
		int k = 0;

		for (int i = 0; i < texto.length(); i++) {
			arreglo[k] += texto[i];
			if (texto[i + 1] == ' ') {
				k++;
			}
		}

		vida = stoi(arreglo[0]);
		x = stoi(arreglo[1]);
		y = stoi(arreglo[2]);

		archivo.close();
	}

	void set_vida(int vidas) {
		vida = vidas;
	}
	void set_x(int pos_x) {
		x = pos_x;
	}
	void set_y(int pos_y) {
		y = pos_y;
	}
};