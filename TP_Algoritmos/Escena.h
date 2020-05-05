#pragma once
#include "Base.h"
class Escena : public Base
{
private:
	int difX, difY; /*Diferencia entre donde empieza a imprimirse el mapa y donde empieza a imprimirse el personaje*/

public:
	Escena() : Base() {}
	~Escena(){}
	void Update(Graphics^ g, Bitmap^ sprite, int x, int y) {
		Imprimir(g, sprite, x, y);
		/*ImprimirMiniMapa(g, sprite);*/
	}
	void Imprimir(Graphics^g, Bitmap^sprite, int x, int y) {
		this->x = x; this->y = y;
		Rectangle Dibujo = Rectangle(0, 0,g->VisibleClipBounds.Right, g->VisibleClipBounds.Bottom);
		Rectangle Region = Rectangle(x, y, 1100, 495);
		g->DrawImage(sprite, Dibujo, Region, GraphicsUnit::Pixel);
	}
	void ImprimirMiniMapa(Graphics^g, Bitmap^sprite) {
		Pen^lapiz = gcnew Pen(Color::Black, 2);
		Rectangle Dibujo = Rectangle(10, 10, 100, 100);
		Rectangle Region = Rectangle(x, y, 500, 500);
		g->DrawRectangle(lapiz, 8, 8, 104, 104);
		g->DrawImage(sprite, Dibujo, Region, GraphicsUnit::Pixel);
		delete lapiz;
	}
};