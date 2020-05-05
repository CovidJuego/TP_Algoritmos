#pragma once
#include "Base.h"
class Enemigo : Base{
private:
	double speed;
	int i_x, i_y;
	bool alerta;
public:
	bool arr, aba, izq, der;
	Enemigo(Bitmap^ sprite,  Graphics ^g,int tipo) : Base(50, 50, 22, 31) {
		//Dimensiones
		this->newAncho = sprite->Width / 3;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho;		//ancho del zoom de la imagen
		this->alto = newAlto;		//alto del zoom de la imagen

		//Movimiento
		arr = izq = aba = false;
		der = true;
		speed = 10;

		//Region inicial del Sprite
		i_x = 0;
		i_y = 2;

		//Estado del enemigo
		alerta = false;
	}
	~Enemigo() {}

	void Update(Graphics ^g, Bitmap^ sprite) {
		Imprimir(g, sprite);
		Movimiento(g);
	}

	void reiniciarDirecciones() {
		arr = der = izq = aba = false;
	}

	void Movimiento(Graphics ^g) {
		//Teclas
		cout << "Y" << y << " +DY: " << dy << " < " << g->VisibleClipBounds.Top;
		if (izq) {
			if (x + dx > g->VisibleClipBounds.Left) {
				this->dx = -speed; this->dy = 0;
				i_y = 3;
			}
			else {
				izq = false; der = true;
			}
		}
		if (der) {
			if (x + dx < g->VisibleClipBounds.Right) {
				this->dx = speed; this->dy = 0;
				i_y = 1;
			}
			else {
				der = false; izq = true;
			}
		}
		if (aba) {
			if (y + dy < g->VisibleClipBounds.Bottom) {
				this->dx = 0; this->dy = speed;
				i_y = 2;
			}
			else {
				aba = false; arr = true;
			}
		}
		if (arr) {
			if (y + dy > g->VisibleClipBounds.Top) {
				this->dx = 0; this->dy = -speed;
				i_y = 0;
			}
			else {
				arr = false; aba = true;
			}
		}
		i_x++; i_x %= 3;

		x += dx;
		y += dy;
	}

	void Imprimir(Graphics ^g, Bitmap^ Sprite) {
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);
		g->DrawImage(Sprite, x * 1.0, y * 1.0, Region, System::Drawing::GraphicsUnit::Pixel);
	}
	Rectangle rect(Graphics^g) {
		return Rectangle(i_x * ancho, i_y * alto, ancho, alto);
	}
};