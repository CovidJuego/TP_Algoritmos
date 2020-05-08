#pragma once
#include "Base.h"
#include "InventaryController.h"
#include "Dialogo.h"
#include "Colisiones.h"

class Personaje : public Base<float, int>
{
private:
	float speed;
	float tiempoInvensible;
	int salud, MaxSalud;

public:
	//Atributos publicos
	bool arr, aba, izq, der, enVehiculo, noMoverse;
	bool invensible;
	InventaryController *inventary;

	Personaje(Bitmap^ sprite, Control::ControlCollection^ controls, Graphics ^g, int x = 0, int y = 0, int MaxSalud = 5) : Base() { 
		this->x = x; this->y = y;
		//Dimesiones
		this->newAncho = sprite->Width / 9;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho;		//ancho del zoom de la imagen
		this->alto = newAlto;		//alto del zoom de la imagen

		//Movimiento
		arr = aba = izq = der = false;	//teclas
		enVehiculo = noMoverse = false;	//determinan si NO tiene libertad para moverse
		speed = 20;

		//Invensibilidad
		invensible = false;
		tiempoInvensible = 20;

		//Region inicial del Sprite
		i_x = 0;
		i_y = 2;

		//Otros ajustes
		this->MaxSalud = MaxSalud;
		salud = this->MaxSalud;
		inventary = new InventaryController();
		inventary->CrearInventario(g, controls);
	}
	~Personaje() { delete inventary; }

	void Update(Graphics ^g, Bitmap^ sprite, Colisiones *col) {
		Movimiento(g);
		ChequearPared(col);
		Imprimir(g, sprite);
		puedeSerAtacado();
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
		if ((!(izq || der || aba || arr)) || enVehiculo || noMoverse) {
			this->dx = 0; this->dy = 0;
			this->i_x = 0;
		}
	}
	void ChequearPared(Colisiones* colisiones) {
		if (colisiones->CheckColision(this)) {
			this->dx = 0;
			this->dy = 0;
		}
	}

	void Imprimir(Graphics ^g, Bitmap^ Sprite) {
		if (salud <= 0) return;
		posXprint = g->VisibleClipBounds.Right / 2 - (ancho / 2);
		posYprint = g->VisibleClipBounds.Bottom / 2 - (alto / 2);
		if (salud < MaxSalud) {
			g->FillRectangle(Brushes::Red, posXprint, posYprint - 10, 38.0, 6.0);
			g->FillRectangle(Brushes::Green, posXprint, posYprint - 10, (float)((38 * salud) / MaxSalud), 6.0);
			g->DrawRectangle(Pens::Black, posXprint, posYprint - 10, 38.0, 6.0);
		}
		x += dx;
		y += dy;
		if (enVehiculo) return;
		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
	void puedeSerAtacado() {
		if (invensible && tiempoInvensible > 0) {
			tiempoInvensible--;
		}
		if (invensible && tiempoInvensible <= 0) {
			invensible = false;
			tiempoInvensible = 20;
		}
	}
	Rectangle rect(Graphics^g) {
		return Rectangle(g->VisibleClipBounds.Right / 2 - (ancho / 2) + this->dx, g->VisibleClipBounds.Bottom / 2 - (alto / 2) + this->dy, ancho, alto);
	}
	float getAncho() { return ancho; }
	float getAlto() { return alto; }
	int getI_Y() { return i_y; }
	void setDaño(int daño) {
		this->salud-=daño;
	}
	int getSalud() { return salud; }
};