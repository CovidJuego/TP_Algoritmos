#pragma once
#include <iostream>
using std::cout;
using namespace System;
using namespace System::Drawing;
class Base
{
protected:
	float x, y, ancho, alto, dx, dy, newAncho, newAlto, i_x, i_y;

public:
	Base(int x = 0, int y = 0, int ancho = 0, int alto = 0, int dx = 0, int dy = 0, float i_x = 0, float i_y = 0) : 
		x(x), y(y), ancho(ancho), alto(alto), dx(dx), dy(dy) {}

	~Base(){}
	float getX() { return this->x; }
	float getY() { return this->y; }
	float getDX() { return this->dx; }
	float getDY() { return this->dy; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	virtual Rectangle rect() { return Rectangle(x, y, ancho, alto); }	//para colisiones
	virtual Rectangle rect(Graphics^g) { return Rectangle(); }			//x2
	void DibujarRectangulo(Graphics^g) { g->DrawRectangle(Pens::Red, rect()); }
	void DibujarRectangulo2(Graphics^g) { g->DrawRectangle(Pens::Red, rect(g)); }
};