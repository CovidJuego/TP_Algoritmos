#pragma once
#include "Dialogo.h"
#include "Base.h"
#include "Personaje.h"
class Doctor : public Base
{
private:

public:
	Doctor(Bitmap^sprite, int x = 0, int y = 0) : Base (){
		this->x = x; this->y = y;
		this->newAncho = sprite->Width;
		this->newAlto = sprite->Height;
		this->ancho = newAncho;
		this->alto = newAlto;

		i_x = 0;
		i_y = 0;
	}
	~Doctor(){}
	void Imprimir(Graphics^g,Bitmap^Sprite, Base *otro) {
		CoordenadasEnElForm(g, otro);

		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
	bool DetectarColision(Base *otro, Graphics^ g) {
		if (this->rect().IntersectsWith(otro->rect(g)))
			return true;
		return false;
	}
	void Update(Graphics^g,Bitmap^Sprite, Personaje *otro) {
		Imprimir(g,Sprite, otro);
	}
};

