#pragma once
#include "Base.h"
class Dialogo
{
private:
	bool conversacionAbierta;
	float velocidadDeAnimacion, maxWidht;
	float posXprint, posYprint, x, y;

public:
	Dialogo(){
		conversacionAbierta = false;
		velocidadDeAnimacion = 10;
		x = y = posXprint = posYprint = 0;
	}
	~Dialogo(){}
	void AbrirConversacion(Control^ c, String^ t, float x, float y) {
		if (conversacionAbierta) return;
		this->maxWidht = (t->Length * 5) + 5;
		c->Enabled = true;
		if (t[t->Length - 1] == 'S') c->ForeColor = Color::Green;
		else c->ForeColor = Color::Blue;
		t = t->Remove(t->Length - 1);
		c->Text = t;
		c->AutoSize = false;
		c->Size = Size(0, c->Height);
		conversacionAbierta = true;
		this->x = x; this->y = y;
	}
	void Animacion(Control ^c, Graphics^ g, Base<float, int> *otro) {
		if (!conversacionAbierta) return;

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
		if (!conversacionAbierta) return;
		c->ForeColor = Color::Black;
		c->Location = Point(0, bottom + 1);
		c->Text = "";
		c->AutoSize = true;
		conversacionAbierta = false;
	}
};

