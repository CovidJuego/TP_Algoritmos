#pragma once
#include "Base.h"
class FuncionesHistoria
{
private:
	bool abrirConversacion;
	float velocidadDeAnimacion, maxWidht;
	float posXprint, posYprint, x, y;

public:
	FuncionesHistoria(){
		abrirConversacion = false;
		velocidadDeAnimacion = 5;
		x = y = posXprint = posYprint = 0;
	}
	~FuncionesHistoria(){}
	void AbrirConversacion(Control^ c, String^ t, float maxWidht, Base *p = nullptr) {
		this->maxWidht = maxWidht;
		c->Text = t;
		c->AutoSize = false;
		c->Size = Size(0, c->Height);
		abrirConversacion = true;
		if (p != nullptr) {
			x = p->getX(); y = p->getY();
		}
		else {
			x = 100; y = 50;
		}
	}
	void Animacion(Control ^c, Graphics^ g, Base *otro) {
		if (!abrirConversacion) return;

		//Coordenadas en el form
		float right = g->VisibleClipBounds.Right, bottom = g->VisibleClipBounds.Bottom;
		posXprint = x + (right*0.5 - (maxWidht / 2) - otro->getX());
		posYprint = y + (bottom*0.5 - otro->getY());

		if (posXprint + maxWidht < -1 || posXprint > right) return;
		if (posYprint + 10 < -1 || posYprint > bottom) return;

		c->Location = Point(posXprint, posYprint);
		if (c->Width < maxWidht) {
			c->Size = Size(c->Width+velocidadDeAnimacion, c->Height);
		}
	}
	void CerrarConversacion(Control ^c, int bottom) {
		c->Location = Point(0, bottom + 1);
		c->Text = "";
		c->AutoSize = true;
	}
};

