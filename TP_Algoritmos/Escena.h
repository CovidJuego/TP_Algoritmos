#pragma once
#include "Base.h"
class Escena : public Base<float, int>
{
private:
	int difX, difY; /*Diferencia entre donde empieza a imprimirse el mapa y donde empieza a imprimirse el personaje*/
	int objetivo;

public:
	Escena(Graphics^g) : Base() {
		posXprint = g->VisibleClipBounds.Right / 2;
		posYprint = g->VisibleClipBounds.Bottom / 2;
		objetivo = 0;
	}
	~Escena(){}
	void Update(Graphics^ g, Bitmap^ sprite1, Bitmap^ sprite2, int x, int y, Base*ob1, Base*ob2, Base*ob3, Base*ob4) {
		Imprimir(g, sprite1, x, y);
		ImprimirMiniMapa(g, sprite2);
		Camino(g, ob1, ob2, ob3, ob4);
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
		Rectangle Region = Rectangle(x/100 + 100, y/100 + 100, 100, 100);
		g->DrawRectangle(lapiz, 8, 8, 104, 104);
		g->DrawImage(sprite, Dibujo, Region, GraphicsUnit::Pixel);
		delete lapiz;
	}
	void Camino(Graphics^g, Base*ob1, Base*ob2, Base*ob3, Base*ob4) {
		Pen^p = gcnew Pen(Color::Red);
		if (objetivo == 0 || objetivo == 2 || objetivo == 4 || objetivo == 6) {
			g->DrawLine(p, posXprint, posYprint, ob1->getPosXPrint(), ob1->getPosYPrint());
		}
		if (objetivo == 1) {
			g->DrawLine(p, posXprint, posYprint, ob2->getPosXPrint(), ob2->getPosYPrint());
		}
		if (objetivo == 3) {
			g->DrawLine(p, posXprint, posYprint, ob3->getPosXPrint(), ob3->getPosYPrint());
		}
		if (objetivo == 5) {
			g->DrawLine(p, posXprint, posYprint, ob4->getPosXPrint(), ob4->getPosYPrint());
		}
		delete p;
	}
	void CambiarObjetivo() {
		objetivo++;
	}
};