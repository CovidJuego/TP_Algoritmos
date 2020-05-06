#pragma once
#include "Base.h"

class Colision : public Base
{
private:
	bool isTrigger;

public:
	Colision(float x, float y, float ancho, float alto, bool t = false) {
		this->x = x;
		this->y = y;
		this->ancho = ancho;
		this->alto = alto;
		this->isTrigger = t;
	}
	void Update(Graphics^g, Base *otro) {
		CoordenadasEnElForm(g, otro);
	}
	~Colision() {}

};

class Colisiones
{
private:
	int nroColisionadores;
	Colision **colisionadores;

public:
	Colisiones() {
		nroColisionadores = 0;
		colisionadores = new Colision*[nroColisionadores];
	}
	~Colisiones(){
		delete colisionadores;
	}
	void AgregarColision(float x, float y, float ancho, float alto, bool t = false) {
		auto aux = new Colision*[nroColisionadores + 1];
		if (nroColisionadores > 0) {
			for (int i = 0; i < nroColisionadores; i++) {
				aux[i] = colisionadores[i];
			}
		}
		aux[nroColisionadores] = new Colision(x, y, ancho, alto, t);
		nroColisionadores++;
		if (colisionadores != nullptr) delete colisionadores;
		colisionadores = aux;
	}
	void Update(Graphics^g, Base *otro) {
		for (int i = 0; i < nroColisionadores; i++) {
			colisionadores[i]->Update(g, otro);
			colisionadores[i]->DibujarRectangulo(g);
		}
	}
};

