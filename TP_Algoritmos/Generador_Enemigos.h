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
		if (lista->size() > 0) lista->clear();
		if (nEnemigos < 0) nEnemigos = GenerarRandom(7, 16);
		for (int i = 0; i < nEnemigos; ++i) {
			Enemigo *aux = new Enemigo(sprite, g, GenerarRandom(x1, x2), GenerarRandom(y1, y2));
			lista->push_back(aux);
		}
	}
	void Update(Graphics ^g, Bitmap^ sprite, Bitmap^ sprite2, Personaje* personaje, list<Item*> *balas, function<void(Item*tirable)> removeItem) {
		if (lista->size() > 0) {
			for (Enemigo* e : (*lista)) {
				bool chequeado = false;
				for (Item*i : (*balas)) {
					if (chequeado) break;
					if (e->CheckColision(i)) {	//Chequeo si alguna bala impacta en el enemigo
						e->setDaño(1);
						removeItem(i);
						chequeado = true;
					}
				}
				if (e->CheckColision(personaje, g) && !personaje->invensible) {	//Colision con personaje
					personaje->setDaño(1); personaje->invensible = true;
				}
				else {
					if (e->getAlerta()) {
						e->Update(g, sprite2, personaje);
					}
					else {
						e->Update(g, sprite, personaje);
					}
				}
			}
		}
		EliminarCaidos();
	}
	void EliminarCaidos() {
		if (lista->size() > 0) {
			for (Enemigo* e : (*lista)) {
				if (e->getSalud() <= 0) {	//Borrar de la lista si es que ha palmao
					lista->remove(e);
					break;
				}
			}
		}
	}
};