#pragma once
#include "Base.h"
#include "InventaryController.h"

class Personaje : public Base 
{
private:
	float speed;
	int i_x, i_y;

public:
	//Atributos publicos
	bool arr, aba, izq, der;
	InventaryController *inventary;

	Personaje(Bitmap^ sprite, Control::ControlCollection^ controls, Graphics ^g) : Base(/*200*/0, /*50*/0, 30, 30) { 
		//Dimesiones
		this->newAncho = sprite->Width / 9;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho;		//ancho del zoom de la imagen
		this->alto = newAlto;		//alto del zoom de la imagen

		//Movimiento
		arr = aba = izq = der = false;
		speed = 20;

		//Region inicial del Sprite
		i_x = 0;
		i_y = 2;

		inventary = new InventaryController();
		inventary->CrearInventario(g, controls);
	}
	~Personaje() { delete inventary; }

	void Update(Graphics ^g, Bitmap^ sprite) {
		Movimiento(g);
		Imprimir(g, sprite);
	}

	void Movimiento(Graphics ^g) {
		//Teclas
		if (izq) {
			this->dx = -speed; this->dy = 0;
			i_y = 1;
		}
		if (der) {
			this->dx = speed; this->dy = 0;
			i_y = 3;
		}
		if (aba) {
			this->dx = 0; this->dy = speed;
			i_y = 2;
		}
		if (arr) {
			this->dx = 0; this->dy = -speed;
			i_y = 0;
		}
		i_x++; i_x %= 9;
		if (!(izq || der || aba || arr)) {
			this->dx = 0; this->dy = 0;
			i_x = 0; i_y = 2;
		}

		x += dx;
		y += dy;
	}

	void Imprimir(Graphics ^g, Bitmap^ Sprite) {
		Rectangle Dibujo = Rectangle(g->VisibleClipBounds.Right/2 - (ancho/2), g->VisibleClipBounds.Bottom/2 - (alto/2), ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
	Rectangle rect(Graphics^g) {
		return Rectangle(g->VisibleClipBounds.Right / 2 - (ancho / 2), g->VisibleClipBounds.Bottom / 2 - (alto / 2), ancho, alto);
	}

};