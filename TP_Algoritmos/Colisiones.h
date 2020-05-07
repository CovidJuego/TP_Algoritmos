#pragma once
#include "Base.h"

class Colision : public Base<float, int>
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
	bool CheckColision(Base *per) {
		if (this->rect().IntersectsWith(per->rect()))
			return true;
		return false;
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
		AgregarColision(240, 286, 240, 20);
		AgregarColision(840, 516, 830, 20);
		AgregarColision(1860, 710, 1100, 20);
		AgregarColision(8000, 6100, 12000, 20);
		AgregarColision(90, 200, 20, 20);
		AgregarColision(-180, 180, 20, 14240);
		AgregarColision(7000, 21570, 14500, 20);
		AgregarColision(14080, 120, 20, 14240);
		AgregarColision(-40, 286, 240, 20);
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
	void Update(Graphics^g, Base<float, int> *otro) {
		for (int i = 0; i < nroColisionadores; i++) {
			colisionadores[i]->Update(g, otro);
			colisionadores[i]->DibujarRectangulo(g);
		}
	}
	bool CheckColision(Base<float, int> *per) {
		for (int i = 0; i < nroColisionadores; i++) {
			if (colisionadores[i]->CheckColision(per))
				return true;
		}
		return false;
	}
};

