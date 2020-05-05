#pragma once
#include "Base.h"

enum  Estado
{
	Tirado, Inventariado
};

class Item : public Base
{
private:
	Estado estado;
	bool show;
	float inicialOtroX, inicialOtroY;
	float posXprint, posYprint;

public:
	Item(Base *otro, int x = 400, int y = 115) : Base() {
		this->x = x;
		this->y = y;
		estado = Tirado;
		ancho = 20;
		alto = 20;
		dx = 0;
		show = false;

		//Intento fallido para hacer que se muevan en la pantalla
		inicialOtroX = otro->getX();
		inicialOtroY = otro->getY();
	}
	~Item(){}
	void Update(Graphics ^g, Bitmap^ sprite, Base* otro, Control^ control, String^ t) {
		Inventariar(otro, control, t, g);
		Movimiento(g, otro);
		Imprimir(g, sprite, otro);
	}
	void Movimiento(Graphics ^g, Base* otro) {
		if (estado == Tirado) {
			if (x + dx + ancho < 0 || x > g->VisibleClipBounds.Right) return;
			if (y + dy + alto < 0 || y > g->VisibleClipBounds.Bottom) return;
			x += dx;
			y += dy;
		}
		else {
			this->x = otro->getX() + 5;
			this->y = otro->getY() + 5;
		}
	}
	void Imprimir(Graphics ^g, Bitmap^ Sprite, Base *otro) {
		if (estado == Inventariado && !show) return;
		//Intento fallido para hacer que se muevan en la pantalla
		posXprint = this->x - inicialOtroX - otro->getX();
		posYprint = this->y - inicialOtroY - otro->getY();
		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		g->DrawImage(Sprite, Dibujo);
	}
	bool DetectarColision(Base* otro, Graphics^g) {
		if (this->rect().IntersectsWith(otro->rect(g)))
			return true;
		return false;
	}
	void Inventariar(Base* otro, Control^ c, String^ t, Graphics^g) {
		if (estado == Tirado) {
			if (DetectarColision(otro, g)) {
				c->Enabled = true;	//Pongo un label que dice Pulse [E] para...
				c->Text = t;
				c->Location = Point(x - ancho, y + alto + 2);
				return;
			}
		}
		if (c->Text == t) {
			c->Location = Point(0, 600);	//Quito el label
			c->Text = "";
		}
	}

	void setShow(bool a) { show = a; }
	void setEstado(Estado e) { estado = e; }
	Estado getEstado() { return estado; }
	bool getShow() { return show; }
};