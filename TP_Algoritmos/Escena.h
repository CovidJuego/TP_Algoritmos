#pragma once
#include "Base.h"
class Escena : public Base
{
private:
	int difX, difY; /*Diferencia entre donde empieza a imprimirse el mapa y donde empieza a imprimirse el personaje*/

public:
	Escena() : Base() {}
	~Escena(){}
	void Update(Graphics^ g, Bitmap^ sprite, int x, int y, int x_mapa, int y_mapa, bool cercaEnemigos) {
		Imprimir(g, sprite, x, y,x_mapa,y_mapa,cercaEnemigos);
		/*ImprimirMiniMapa(g, sprite);*/
	}
	void Imprimir(Graphics^g, Bitmap^sprite, int x, int y,int x_mapa,int y_mapa, bool cercaEnemigos) {
		cout << "XMAP: " << x_mapa << "YMAP: " << y_mapa;
		if (!cercaEnemigos) {
			this->x = x; this->y = y;
		}
		else {
			this->x = x_mapa; this->y = y_mapa;
		}
		Rectangle Dibujo = Rectangle(0, 0, g->VisibleClipBounds.Right, g->VisibleClipBounds.Bottom);
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