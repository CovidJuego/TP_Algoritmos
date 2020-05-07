#pragma once
#include<list>
#include<iterator>
#include<time.h>
#include "Enemigo.h"
using namespace System;
class Generador_Enemigos {
private:
	list<Enemigo*>lista;
public:
	Generador_Enemigos() {
		lista = list<Enemigo*>();
	}
	void Update(Graphics ^g, Bitmap^ sprite, int x_personaje, int y_personaje) {
		if (lista.size() > 0) {
			list<Enemigo*>::iterator pos;
			pos = lista.begin();
			while (pos != lista.end())
			{
				(*pos)->Update(g, sprite, x_personaje, y_personaje);
				pos++;
			}
		}
	}

	void reiniciarDirecciones() {
		if (lista.size() > 0) {
			list<Enemigo*>::iterator pos;
			pos = lista.begin();
			while (pos != lista.end())
			{
				(*pos)->reiniciarDirecciones();
				pos++;
			}
		}
	}

	bool alerta() {
		if (lista.size() > 0) {
			list<Enemigo*>::iterator pos;
			pos = lista.begin();
			while (pos != lista.end())
			{
				if((*pos)->alerta == true){
					return true;
				}
				pos++;
			}
			return false;
		}
	}

	void dir(int direccion) {
		if (lista.size() > 0) {
			list<Enemigo*>::iterator pos;
			pos = lista.begin();
			while (pos != lista.end())
			{
				if (direccion == 1) {
					(*pos)->arr = true;
				}
				if (direccion == 2) {
					(*pos)->der = true;
				}
				if (direccion == 3) {
					(*pos)->aba = true;
				}
				if (direccion == 4) {
					(*pos)->izq = true;
				}
				pos++;
			}
		}
	}

	void generar(int cuantos, Bitmap^ sprite, Graphics ^g, int tipo) {
		if (lista.size() ==  0) {
			for (int i = 0; i < cuantos; ++i) {
				std::cout << "Generando..." << "\n";
				Enemigo *aux;
				aux = new Enemigo(sprite, g, tipo, i + 1);
				lista.push_front(aux);
				std::cout << "Generando2..." << "\n";
			}
		}
	}
	void aparecer_enemigos(Bitmap^ sprite, Graphics ^g, int tipo) {
		Random r;
		srand(time(NULL));
		int cuantos = r.Next(1, 4);
		generar(cuantos,sprite,g,tipo);
	}
};