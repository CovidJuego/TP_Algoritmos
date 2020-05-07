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
	list<Item*> tirables;	//objetos que tira (el mismo objeto o balas)
	float tiempoEntreDisparo, tiempo, velDisparo;
	bool show, tirado;	//show para mostrar en mano si es que ha sido seleccionado desde el inventario
	// tirado es auxiliar para el tiempoEntreDisparo
	

public:
	Item(Base *otro, int x = 0, int y = 0, float disparo = 0, float velDisparo = 30, int corte = 1, Bitmap^ Sprite = nullptr, Estado e = Tirado) : Base() {
		this->x = x;
		this->y = y;
		estado = e;
		if (Sprite != nullptr) {
			newAncho = Sprite->Width / corte;
			newAlto = Sprite->Height;

			ancho = newAncho*0.1;
			alto = newAlto*0.1;
		}
		else {
			newAncho = newAlto = 30;
			ancho = newAncho;
			alto = newAlto;
		}
		dx = 0;
		show = tirado = false;

		//Coordenadas en el form
		posXprint = 0;
		posYprint = 0;

		//
		i_x = i_y = 0;

		//Disparar o tirar Items
		this->tiempoEntreDisparo = tiempo;
		this->tiempo = tiempoEntreDisparo;
		this->velDisparo = velDisparo;
	}
	~Item() {}
	void Update(Graphics ^g, Bitmap^ spriteObjecto, Bitmap^ spriteBala, Base* otro, Control^ control, String^ t, bool noDeFuego = false, bool tirable = false) {
		Inventariar(otro, control, t, g);
		if (tirable) Movimiento(g, otro, noDeFuego);	//si es tirable puede hacer animacion
		else Movimiento(g, otro, false);	//sino, definitivamente no la hace
		Imprimir(g, spriteObjecto, otro);
		if (tirables.size() > 0) {
			UpdateTirables(g, spriteBala, spriteBala, otro, noDeFuego);
			CheckItemTirable(g);
		}
		PuedeTirar();//funcion que va actualizando el tiempo para ver si ya se puede tirar otro Item
	}
	void Movimiento(Graphics ^g, Base* otro, bool noDeFuego) {
		if (estado == Tirado) {
			if (noDeFuego) {
				i_x++;
				i_x %= 8;
			}
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
		//Coordenadas en el form
		CoordenadasEnElForm(g, otro);

		//Impresion
		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);
		g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
	bool DetectarColision(Base* otro, Graphics^g) {
		if (this->rect().IntersectsWith(otro->rect(g)))
			return true;
		return false;
	}
	void Inventariar(Base* otro, Control^ c, String^ t, Graphics^g) {
		if (c == nullptr) return;
		if (estado == Tirado) {
			if (DetectarColision(otro, g)) {
				c->Enabled = true;	//Pongo un label que dice Pulse [E] para...
				c->Text = t;
				c->Location = Point(posXprint - 60, posYprint + alto + 10);
				return;
			}
		}
		if (c->Text == t) {
			c->Location = Point(0, 600);	//Quito el label
			c->Text = "";
		}
	}
	void TirarItem(Personaje *otro, Bitmap^ sprite = nullptr) {
		if (tirado) return;
		Item *nuevo = new Item(otro, otro->getX(), otro->getY(), tiempoEntreDisparo, velDisparo, 8 , sprite, Tirado);
		nuevo->ancho /= 2;
		nuevo->alto /= 2;
		switch (otro->getI_Y())	//obtengo i_y ya que es la variable que determina la direccion del jugador
		{
		case 1:	nuevo->setDX(-velDisparo); break;	//si es 1 es izquierda y asi...
		case 3: nuevo->setDX(velDisparo); break;
		case 2: nuevo->setDY(velDisparo); break;
		case 0: nuevo->setDY(-velDisparo); break;
		default:
			break;
		}
		tirables.push_back(nuevo);
	}
	void CheckItemTirable(Graphics^ g) {
		if (tirables.size() <= 0) return;	//si sale de los limites del form CHAU
		for (Item *i : tirables) {
			if ((i->getPosXPrint() + i->getAncho() < 0 || i->getPosXPrint() > g->VisibleClipBounds.Right) ||
				(i->getPosYPrint() + i->getAlto() < 0 || i->getPosYPrint() > g->VisibleClipBounds.Bottom))
				tirables.remove(i);
			break;
		}
	}
	void UpdateTirables(Graphics^ g, Bitmap^ sprite, Bitmap^ sprite2, Base* otro, bool noDeFuego = false) {
		if (tirables.size() > 0) {
			for (Item* i : tirables) {
				i->Update(g, sprite2, sprite, otro, nullptr, nullptr, noDeFuego, true);
			}
		}
	}
	bool PuedeTirar() {
		//Funcion para avanzar el contador y controlar el tiempo entre disparo de items
		if (!tirado) return true;
		if (tiempo > 0) tiempo--;
		else {
			tirado = false;
			tiempo = tiempoEntreDisparo;
		}
	}
	void setShow(bool a) { show = a; }
	void setEstado(Estado e) { 
		estado = e; 
		if (estado == Inventariado)
			tirables = list<Item*>();
	}
	Estado getEstado() { return estado; }
	bool getShow() { return show; }
	float getAncho() { return ancho; }
	float getAlto() { return alto; }
};


