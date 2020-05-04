#pragma once
#include "Base.h"
class Escena : public Base
{
private:

public:
	Escena() : Base() {}
	~Escena(){}
	void Update(Graphics^ g, Bitmap^ sprite, int x, int y) {
		Imprimir(g, sprite, x, y);
	}
	void Imprimir(Graphics^g, Bitmap^sprite, int x, int y) {
		this->x = x; this->y = y;
		Rectangle Dibujo = Rectangle(0, 0,g->VisibleClipBounds.Right, g->VisibleClipBounds.Bottom);
		Rectangle Region = Rectangle(x, y, 1100, 495);
		g->DrawImage(sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
};