#pragma once
#include "Dialogo.h"
#include "Base.h"
#include "Personaje.h"
class Doctor : public Base
{
private:
	bool hablando;

public:
	Doctor(Bitmap^sprite, int x = 0, int y = 0) : Base (){
		this->x = x; this->y = y;
		this->newAncho = sprite->Width;
		this->newAlto = sprite->Height;
		this->ancho = newAncho;
		this->alto = newAlto;

		i_x = 0;
		i_y = 0;
		this->hablando = false;
	}
	~Doctor(){}
	void Imprimir(Graphics^g,Bitmap^Sprite, Base *otro) {
		CoordenadasEnElForm(g, otro);

		Rectangle Dibujo = Rectangle(posXprint, posYprint, ancho, alto);
		Rectangle Region = Rectangle(i_x * newAncho, i_y * newAlto, newAncho, newAlto);

		g->DrawImage(Sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
	void AbrirDialogo(Control^ c, String^ t, int n, Personaje *otro, Graphics ^g, Dialogo* dialogo) {
		if (DetectarColision(otro, g)) {
			dialogo->AbrirConversacion(c, t, n, this->x - n, this->y + ancho + 10);
			otro->noMoverse = true;
			hablando = true;
		}
	}
	void CerrarDialogo(Control^ c, int bottom, Dialogo* dialogo, bool &ultimoDialogo, bool ultimo = false) {
		dialogo->CerrarConversacion(c, bottom);
		hablando = false;
		ultimoDialogo = ultimo;
	}
	bool DetectarColision(Base *otro, Graphics^ g) {
		if (this->rect().IntersectsWith(otro->rect(g)))
			return true;
		return false;
	}
	void Update(Graphics^g,Bitmap^Sprite, Personaje *otro, Control^ c, String^ t, int n, Dialogo *dialogo) {
		Imprimir(g,Sprite, otro);
		if (otro->enVehiculo || otro->getDialogo() || this->hablando) return;
		AbrirDialogo(c, t, n, otro, g, dialogo);
	}
	void setHablando(bool a) { hablando = a; }
	bool getHablando() { return hablando; }
};

