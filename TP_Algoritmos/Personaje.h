#pragma once
#include "Base.h"
#include "InventaryController.h"
#include "Dialogo.h"
#include "Colisiones.h"

class Personaje : public Base<float, int>
{
private:
	float speed;
	float posItemX, posItemY;

public:
	//Atributos publicos
	bool arr, aba, izq, der, enVehiculo, noMoverse;
	int x_pantalla, y_pantalla, x_mapa, y_mapa;
	bool enemigosCerca;
	InventaryController *inventary;

	Personaje(Bitmap^ sprite, Control::ControlCollection^ controls, Graphics ^g, int x = 0, int y = 0) : Base() { 
		this->x = x; this->y = y;
		//Dimesiones
		this->newAncho = sprite->Width / 9;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho;		//ancho del zoom de la imagen
		this->alto = newAlto;		//alto del zoom de la imagen
		//x,y mapa
		x_mapa = x;
		y_mapa = y;
		//x,y cuando hay enemigos cerca
		x_pantalla = 345;
		y_pantalla = 115;
		//Movimiento
		arr = aba = izq = der = false;	//teclas
		enVehiculo = noMoverse =	false;	//determinan si NO tiene libertad para moverse
		speed = 20;

		//Region inicial del Sprite
		i_x = 0;
		i_y = 2;

		inventary = new InventaryController();
		inventary->CrearInventario(g, controls);
	}
	~Personaje() { delete inventary; }

	int getX_pantalla() {
		return x_pantalla;
	}

	int getY_pantalla() {
		return y_pantalla;
	}

	int getX_mapa() {
		return x_mapa;
	}

	int getY_mapa() {
		return y_mapa;
	}

	void cambiarValores() {
		if (enemigosCerca) {
			x = x_pantalla;
			y = y_pantalla;
		}
		else {
			x = x_mapa;
			y = y_mapa;
		}
	}

	void Update(Graphics ^g, Bitmap^ sprite, Colisiones *col) {
		cambiarValores();
		Movimiento(g);
		ChequearPared(col);
		Imprimir(g, sprite);
	}

	void Movimiento(Graphics ^g) {
		//Teclas
		if (izq) {
			if (x + dx > g->VisibleClipBounds.Left || !enemigosCerca) {
				this->dx = -speed; this->dy = 0;
				i_y = 1;
			}
			else {
				dx = 0;
			}
		}
		if (der) {
			if (x + dx + 50 < g->VisibleClipBounds.Right || !enemigosCerca) {
				this->dx = speed; this->dy = 0;
				i_y = 3;
			}
			else {
				dx = 0;
			}
		}
		if (aba) {
			if (y + dy + 50 < g->VisibleClipBounds.Bottom || !enemigosCerca) {
				this->dx = 0; this->dy = speed;
				i_y = 2;
			}
			else {
				dy = 0;
			}
		}
		if (arr) {
			if (y + dy > g->VisibleClipBounds.Top || !enemigosCerca) {
				this->dx = 0; this->dy = -speed;
				i_y = 0;
			}
			else {
				dy = 0;
			}
		}
		i_x++; i_x %= 9;
		if ((!(izq || der || aba || arr)) || enVehiculo || noMoverse) {
			this->dx = 0; this->dy = 0;
			i_x = 0; i_y = 2;
		}
		if (enemigosCerca) {
			x_pantalla += dx;
			y_pantalla += dy;
		}
		else {
			x_mapa += dx;
			y_mapa += dy;
		}

	}
	void ChequearPared(Colisiones* colisiones) {
		if (colisiones->CheckColision(this)) {
			this->dx = 0;
			this->dy = 0;
		}
	}

	void Imprimir(Graphics ^g, Bitmap^ Sprite) {
		if (enVehiculo) return;
		if (enemigosCerca) {
			Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);
			g->DrawImage(Sprite, x * 1.0, y * 1.0, Region, System::Drawing::GraphicsUnit::Pixel);
		}
		else {
			Rectangle Dibujo = Rectangle(g->VisibleClipBounds.Right / 2 - (ancho / 2), g->VisibleClipBounds.Bottom / 2 - (alto / 2), ancho, alto);
			Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);
			g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
		}
	}
	Rectangle rect(Graphics^g) {
		return Rectangle(g->VisibleClipBounds.Right / 2 - (ancho / 2) + this->dx, g->VisibleClipBounds.Bottom / 2 - (alto / 2) + this->dy, ancho, alto);
	}
	float getAncho() { return ancho; }
	float getAlto() { return alto; }
	int getI_Y() { return i_y; }
};