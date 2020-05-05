#pragma once
#include "Personaje.h"
class Vehiculo : public Base
{
private:
	float posXasiento, posYasiento;
	float posXprint, posYprint;
	bool pasajero;

public:
	Vehiculo(Bitmap^ sprite) : Base(100, 15) {
		this->newAncho = sprite->Width / 4;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho;		//ancho del zoom de la imagen
		this->alto = newAlto;		//alto del zoom de la imagen

		//Region inicial del Sprite
		i_x = 0;
		i_y = 0;

		posXasiento = 0;
		posYasiento = 0;
		pasajero = false;
		ancho = 100; alto = 60;
		posXprint = posYprint = 200;
	}
	~Vehiculo(){}
	void Subir(Personaje *otro) {
		otro->setX(posXasiento);
		otro->setY(posYasiento);
		pasajero = true;
	}
	void Bajar(Personaje *otro) {
		otro->setX(posXasiento);
		otro->setY(posYasiento);
		pasajero = false;
	}
	void Update(Graphics^ g, Bitmap^ Sprite, Personaje *otro) {
		Imprimir(g, Sprite, otro);
	}
	void Conducir(Personaje *otro) {
		if (!pasajero) return;
		if (otro->arr) {

		}
		if (otro->aba) {

		}
		if (otro->izq) {

		}
		if (otro->der) {

		}
	}
	void Imprimir(Graphics^ g, Bitmap^Sprite, Personaje *otro) {
		//Coordenadas en el form
		float right = g->VisibleClipBounds.Right, bottom = g->VisibleClipBounds.Bottom;
		posXprint = x + (right*0.5 - (ancho / 2) - otro->getX());
		posYprint = y + (bottom*0.5 - (ancho / 2) - otro->getY());

		if (posXprint + ancho < -1 || posXprint > right) return;
		if (posYprint + alto < -1 || posYprint > bottom) return;

		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
};