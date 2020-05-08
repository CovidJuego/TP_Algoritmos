#pragma once
#include "Base.h"

enum EstadoE	//Estado del Enemigo
{
	Patrulla, Alerta, Ninguno
};

class Enemigo : Base<float, int> {
private:
	EstadoE estado;
	float speed;
	int movimientos, salud, MaxSalud;
	bool alertado;

public:
	Enemigo(Bitmap^ sprite, Graphics ^g, int x = 0, int y = 0, int MaxSalud = 3) : Base() {
		//Coordenadas iniciales
		this->x = x;
		this->y = y;
		//DimensionesIniciales
		this->newAncho = sprite->Width / 3;
		this->newAlto = sprite->Height / 4;
		this->ancho = newAncho * 2;		//ancho del zoom de la imagen
		this->alto = newAlto * 2;		//alto del zoom de la imagen

		//Movimiento
		speed = 10;

		//Region inicial del Sprite
		i_x = 1;
		i_y = 2;

		//Estado del enemigo
		estado = Ninguno;
		alertado = false;


		//Otros ajustes
		this->MaxSalud = MaxSalud;
		salud = this->MaxSalud;
		movimientos = 0;
	}
	~Enemigo() {}

	void Update(Graphics ^g, Bitmap^ sprite, Base *otro,int x_personaje,int y_personaje) {
		Estado(otro);
		Movimiento(g,x_personaje,y_personaje);
		Imprimir(g, sprite, otro);
		movimientos++;
	}
	bool getAlerta() {
		return alertado;
	}
	void Estado(Base *personaje) {
		if (alertado) return;
		int dif = 0;	//determina si el personaje esta arriba o abajo o izquierda o derecha del jugador

		if (abs(personaje->getX() - this->x) < 10) {
			dif = this->y - personaje->getY();
			if ((this->i_y == 0 && dif > 0) || (this->i_y == 2 && dif < 0)) { //si esta mirando pa arriba y el personaje está arriba o si esta mirando pa abajo y está abajo
				estado = Alerta; alertado = true;
				return;
			}
		}
		else if (abs(personaje->getY() - this->y) < 10) {	//lo mismo aca con derecha e izquierda
			dif = this->x - personaje->getX();
			if ((this->i_y == 1 && dif < 0) || (this->i_y == 3 && dif > 0)) {
				estado = Alerta; alertado = true;
				return;
			}
		}
		estado = Patrulla;
	}

	void Movimiento(Graphics ^g,int x_personaje,int y_personaje) {
		if (!alertado) {
			if (movimientos % 5 == 0) {	//Cada 5 movimientos se desplaza en X
				this->dy = 0;
				do {
					dx = GenerarRandom(-1, 2) * speed;	//dx = -speed || dx = speed
				} while (dx == 0);
			}
			if (movimientos % 10 == 0) {	//Cada 10 movimientos se desplaza en Y
				this->dx = 0;
				do {
					dy = GenerarRandom(-1, 2) * speed;	//dy = -speed || dy = speed
				} while (dy == 0);
			}
			
		}
		else {
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
		function<int(int, int)>getNewI_Y = [&](int dx, int dy) {
			if (dx > 0) { return 1; }
			if (dx < 0) { return 3; }
			if (dy > 0) { return 2; }
			else return 0;
		};
		i_y = getNewI_Y(dx, dy);
		i_x++; i_x %= 3;

		x += dx;
		y += dy;
	}
	void Imprimir(Graphics ^g, Bitmap^ Sprite, Base *otro) {
		//Coordenadas en el Form
		CoordenadasEnElForm(g, otro);
		if (salud < MaxSalud) {
			g->FillRectangle(Brushes::Red, posXprint, posYprint - 10, 38.0, 6.0);
			g->FillRectangle(Brushes::Green, posXprint, posYprint - 10, (float)((38 * salud) / MaxSalud), 6.0);
			g->DrawRectangle(Pens::Black, posXprint, posYprint - 10, 38.0, 6.0);
		}
		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);
		g->DrawImage(Sprite, Dibujo, Region, System::Drawing::GraphicsUnit::Pixel);
	}
	bool CheckColision(Base *otro, Graphics^g = nullptr) {
		if (g != nullptr) {
			if (this->rect().IntersectsWith(otro->rect(g))) {	//colision con personaje
				return true;
			}
		}
		else
			if (this->rect().IntersectsWith(otro->rect())) {	//colision con bala
				return true;
			}
		return false;
	}
	void setDaño(int daño) {
		this->salud -= daño;
	}
	int getSalud() { return salud; }
};