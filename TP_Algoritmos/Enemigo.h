#pragma once
#include "Base.h"
class Enemigo : Base<double,int> {
private:
	double speed;
	int i_x, i_y;
public:
	bool arr, aba, izq, der, alerta;
	Enemigo(Bitmap^ sprite, Graphics ^g, int tipo, int zona) : Base() {
		//Dimensiones Base
		if (zona == 1) { x = g->VisibleClipBounds.Left + 10; y = g->VisibleClipBounds.Top + 10; }
		if (zona == 2) { x = g->VisibleClipBounds.Right - 10; y = g->VisibleClipBounds.Top + 10; }
		if (zona == 3) { x = g->VisibleClipBounds.Left + 10; y = g->VisibleClipBounds.Bottom - 10; }
		if (zona == 4) { x = g->VisibleClipBounds.Right - 10; y = g->VisibleClipBounds.Bottom - 10; }
		ancho = 22;
		alto = 31;
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

	void Update(Graphics ^g, Bitmap^ sprite, int x_personaje, int y_personaje) {
		Estado(g);
		Imprimir(g, sprite);
		Movimiento(g, x_personaje, y_personaje);
	}

	void Estado(Graphics ^g) {
		if (x - abs(g->VisibleClipBounds.Width / 2) < 10 || y - abs(g->VisibleClipBounds.Height / 2) < 10) {
			alerta = true;
		}
	}

	void reiniciarDirecciones() {
		arr = der = izq = aba = false;
	}

	void Movimiento(Graphics ^g, int x_personaje, int y_personaje) {
		if (!alerta) {
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

		}
		else {
			std::cout << "X: " << x_personaje << " Y: " << y_personaje;
			std::cout << "X: " << x << " Y: " << y;
			if (x + dx > x_personaje) {
				this->dx = -speed;
				i_y = 3;
			}
			else {
				this->dx = speed;
				i_y = 1;
			}
			if (y + dy < y_personaje) {
				this->dy = speed;
				i_y = 2;
			}
			else {
				this->dy = -speed;
				i_y = 0;
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