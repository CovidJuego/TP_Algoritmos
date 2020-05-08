#pragma once
#include "Enemigo.h"

class Generador_Enemigos {
private:
	list<Enemigo*> *lista;
public:
	Generador_Enemigos() {
		lista = new list<Enemigo*>();
	}
	~Generador_Enemigos() {
		delete lista;
	}
	void GenerarEnemigos(Bitmap^ sprite, Graphics^ g, int x1, int x2, int y1, int y2, int nEnemigos = -1) {
		/*if (lista != nullptr) { lista->clear(); }*/

		if (nEnemigos < 0) nEnemigos = GenerarRandom(7, 16);
		for (int i = 0; i < nEnemigos; ++i) {
			Enemigo *aux = new Enemigo(sprite, g, GenerarRandom(x1, x2), GenerarRandom(y1, y2));
			lista->push_back(aux);
		}
	}
	bool alerta() {
		if (lista->size() > 0) {
			list<Enemigo*>::iterator pos;
			pos = lista->begin();
			while (pos != lista->end())
			{
				if ((*pos)->getAlerta() == true) {
					std::cout << "Alerta: " << (*pos)->getAlerta() << "\n";
					return true;
				}
				pos++;
			}
			return false;
		}
	}
	void Update(Graphics ^g, Bitmap^ sprite, Personaje* personaje, Base<float, int>* bala) {
		if (lista->size() > 0) {
			for (Enemigo* e : (*lista)) {
				if (e->CheckColision(bala)) {	//Colision con bala
					e->setDaño(1);
				}
				if (e->CheckColision(personaje, g)) {	//Colision con personaje
					personaje->setDaño(1);
				}
				if (e->getSalud() <= 0) {	//Borrar de la lista si es que ha palmao
					lista->remove(e);
				}
				else e->Update(g, sprite, personaje,personaje->getX(),personaje->getY());
			}
		}
	}
};