#pragma once
#include "Base.h"
#include "InventaryController.h"
#include "Dialogo.h"

class Personaje : public Base 
{
private:
	float speed;
	float posItemX, posItemY;
	bool abrirDialogo;

public:
	//Atributos publicos
	bool arr, aba, izq, der, enVehiculo, noMoverse;
	InventaryController *inventary;

	Personaje(Bitmap^ sprite, Control::ControlCollection^ controls, Graphics ^g, int x = 0, int y = 0) : Base() { 
		this->x = x; this->y = y;
		//Dimesiones
		this->newAncho = sprite->Width / 9;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho;		//ancho del zoom de la imagen
		this->alto = newAlto;		//alto del zoom de la imagen

		//Movimiento
		arr = aba = izq = der = false;	//teclas
		enVehiculo = noMoverse = abrirDialogo =	false;	//determinan si NO tiene libertad para moverse
		speed = 20;

		//Region inicial del Sprite
		i_x = 0;
		i_y = 2;

		inventary = new InventaryController();
		inventary->CrearInventario(g, controls);
	}
	~Personaje() { delete inventary; }

	void Update(Graphics ^g, Bitmap^ sprite, Control^ c, String^ t, int n, Dialogo *d) {
		Movimiento(g);
		Imprimir(g, sprite);
		if (this->enVehiculo) return;
		AbrirDialogo(c, t, n, d);
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
			i_x = 0; i_y = 2;
		}

		x += dx;
		y += dy;
	}

	void Imprimir(Graphics ^g, Bitmap^ Sprite) {
		if (enVehiculo) return;
		Rectangle Dibujo = Rectangle(g->VisibleClipBounds.Right/2 - (ancho/2), g->VisibleClipBounds.Bottom/2 - (alto/2), ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
	Rectangle rect(Graphics^g) {
		return Rectangle(g->VisibleClipBounds.Right / 2 - (ancho / 2), g->VisibleClipBounds.Bottom / 2 - (alto / 2), ancho, alto);
	}

	void AbrirDialogo(Control^ c, String^ t, int n, Dialogo* dialogo) {
		if (abrirDialogo) {
			dialogo->AbrirConversacion(c, t, n, this->x - n, this->y + ancho + 10);
			this->noMoverse = true;
		}
	}
	void CerrarDialogo(Control^ c, int bottom, Dialogo* dialogo, bool &ultimoDialogo, bool ultimo = false) {
		dialogo->CerrarConversacion(c, bottom);
		this->noMoverse = false;
		ultimoDialogo = ultimo;
	}

	void setDialogo(bool a) { abrirDialogo = a; }
	float getAncho() { return ancho; }
	float getAlto() { return alto; }
	bool getDialogo() { return abrirDialogo; }
};