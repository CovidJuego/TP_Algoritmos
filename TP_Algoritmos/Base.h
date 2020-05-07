#pragma once
#include <stack>
#include <queue>
#include <list>
#include <iostream>
#include <functional>
using std::queue;
using std::stack;
using std::list;
using std::function;
using std::string;

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

template<typename T, typename R>
class Base
{
protected:
	T x, y, posXprint, posYprint, ancho, alto, dx, dy, newAncho, newAlto;
	R i_x, i_y;

public:
	Base(int x = 0, int y = 0, int ancho = 0, int alto = 0, int dx = 0, int dy = 0) : 
		x(x), y(y), ancho(ancho), alto(alto), dx(dx), dy(dy) {}

	~Base(){}
	float getX() { return this->x; }
	float getY() { return this->y; }
	float getDX() { return this->dx; }
	float getDY() { return this->dy; }
	float getPosXPrint() { return posXprint; }
	float getPosYPrint() { return posYprint; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setDX(float dx) { this->dx = dx; }
	void setDY(float dy) { this->dy = dy; }
	virtual Rectangle rect() { return Rectangle(posXprint, posYprint, ancho, alto); }	//para colisiones
	virtual Rectangle rect(Graphics^g) { return Rectangle(); }			//x2
	void DibujarRectangulo(Graphics^g) { g->DrawRectangle(Pens::Red, rect()); }
	void DibujarRectangulo2(Graphics^g) { g->DrawRectangle(Pens::Red, rect(g)); }
	void CoordenadasEnElForm(Graphics^ g, Base *otro){
		//Coordenadas en el form
		float right = g->VisibleClipBounds.Right, bottom = g->VisibleClipBounds.Bottom;
		posXprint = x + (right*0.5 - (ancho / 2) - otro->getX());
		posYprint = y + (bottom*0.5 - (ancho / 2) - otro->getY());

		if (posXprint + ancho < -1 || posXprint > right) return;
		if (posYprint + alto < -1 || posYprint > bottom) return;
	}
};