#pragma once
#include "Personaje.h"
class Vehiculo : public Base<float, int>
{
private:
	float speed;
	bool pasajero;

public:
	Vehiculo(Bitmap^ sprite, int x = 0, int y = 0) : Base() {
		this->x = x; this->y = y;
		this->newAncho = sprite->Width / 4;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho;		//ancho del zoom de la imagen
		this->alto = newAlto;		//alto del zoom de la imagen

		//Region inicial del Sprite
		i_x = 0;
		i_y = 1;

		speed = 45;

		pasajero = false;
		ancho = 100; alto = 60;
		posXprint = posYprint = 200;
	}
	~Vehiculo(){}
	void Subir(Personaje *otro) {
		pasajero = true;
		otro->enVehiculo = true;
	}
	void Bajar(Personaje *otro) {
		pasajero = false;
		otro->enVehiculo = false;
	}
	void Update(Graphics^ g, Bitmap^ Sprite1, Bitmap^ Sprite2, Personaje *otro, Control^ control, String^textEntrar, String^textSalir) {
		QuiereEntrar_Salir(g, otro, control, textEntrar, textSalir);
		Conducir(otro);
		Imprimir(g, Sprite1, Sprite2, otro);
	}
	void Conducir(Personaje *otro) {
		if (!pasajero) return;
		//Teclas
		if (otro->izq) {
			this->dx = -speed; this->dy = 0;
			i_y = 1;
		}
		if (otro->der) {
			this->dx = speed; this->dy = 0;
			i_y = 2;
		}
		if (otro->aba) {
			this->dx = 0; this->dy = speed;
			i_y = 0;
		}
		if (otro->arr) {
			this->dx = 0; this->dy = -speed;
			i_y = 3;
		}
		i_x++; i_x %= 4;
		if (!(otro->izq || otro->der || otro->aba || otro->arr)) {
			this->dx = 0; this->dy = 0;
		}

		x += dx;
		y += dy;
		otro->setX(x);
		otro->setY(y);
	}
	void QuiereEntrar_Salir(Graphics^g, Personaje* otro, Control^ c, String^ textEntrar, String^ textSalir) {
		if (!pasajero) {
			if (DetectarColision(otro, g)) {
				c->Enabled = true;	//Pongo un label que dice Pulse [E] para...
				c->Text = textEntrar;
				c->Location = Point(posXprint - 60, posYprint + alto + 10);
				return;
			}
			else {
				if (c->Text == textEntrar || c->Text == textSalir) {
					c->Location = Point(0, 600);	//Quito el label
					c->Text = "";
				}
			}
		}
		else {
			c->Enabled = true;	//Pongo un label que dice Pulse [E] para...
			c->Text = textSalir;
			c->Location = Point(g->VisibleClipBounds.Left + 200, g->VisibleClipBounds.Bottom - 30);
			return;
		}
	}
	bool DetectarColision(Personaje* otro, Graphics^g) {
		if (this->rect().IntersectsWith(otro->rect(g)))
			return true;
		return false;
	}
	void Imprimir(Graphics^ g, Bitmap^ Sprite1, Bitmap^ Sprite2, Personaje *otro) {
		//Coordenadas en el form
		CoordenadasEnElForm(g, otro);

		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		if (pasajero) g->DrawImage(Sprite2, Dibujo, Region, GraphicsUnit::Pixel);
		else g->DrawImage(Sprite1, Dibujo, Region, GraphicsUnit::Pixel);
	}
};