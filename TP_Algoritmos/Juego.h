#pragma once
#include "Personaje.h"
#include "Item.h"
#include "Escena.h"
#include "Vehiculo.h"
#include "Dialogo.h"
#include "Colisiones.h"
#include "Doctor.h"

class Juego
{
private:
	Personaje *steph;
	Item *item;
	Item *item2;
	Escena *mapa;
	Dialogo* dialogo;
	Colisiones *colisiones;
	Doctor *doctor;
	Vehiculo *moto;
	bool ultimoDialogo;

public:
	Juego(Graphics^g, array<Bitmap^>^sprites, Control::ControlCollection^ Controls){
		dialogo = new Dialogo();
		steph = new Personaje(sprites[1], Controls, g, /*6900, 700*/9000, 4095);
		item = new Item(steph, 150, 0);
		item2 = new Item(steph, 100, 200);
		mapa = new Escena();
		moto = new Vehiculo(sprites[4], 6900, 750);
		colisiones = new Colisiones();
		doctor = new Doctor(sprites[6], 9205, 4095);
		ultimoDialogo = false;

		for (int i = 0; i < 4; i++) {
			colisiones->AgregarColision(i * 10, i * 10, i + 10, i + 10);
		}
	}
	~Juego(){
		delete steph;
		delete mapa;
		delete dialogo;
		delete doctor;
		delete moto;
		delete colisiones;
	}
	void Update(Graphics^ g, array<Bitmap^>^sprites, Control^ interaction_txt) {

		mapa->Update(g, sprites[0], steph->getX(), steph->getY());

		item->Update(g, sprites[2], steph, interaction_txt, "Pulse [E] para obtener Circulo");
		item2->Update(g, sprites[3], steph, interaction_txt, "Pulse [E] para obtener Cuadrado");
		moto->Update(g, sprites[4], sprites[5], steph, interaction_txt, "Pulse [E] para subir a la moto", "Pulse [E] para bajarse de la moto");
		steph->Update(g, sprites[1], interaction_txt, "Hola webon que tal", 120, dialogo);
		doctor->Update(g, sprites[6], steph, interaction_txt, "Hola Amiguito", 100, dialogo);
		colisiones->Update(g, steph);

		item->DibujarRectangulo(g);
		item2->DibujarRectangulo(g);
		steph->DibujarRectangulo2(g);
		moto->DibujarRectangulo(g);
		doctor->DibujarRectangulo(g);

		dialogo->Animacion(interaction_txt, g, steph);

		//Console::SetCursorPosition(0, 0); cout << "Mapa: " << mapa->getX() << " / " << mapa->getY();
		Console::SetCursorPosition(0, 2); cout << "Personaje: " << steph->getX() << " / " << steph->getY();
		//Console::SetCursorPosition(0, 3); cout << "Circulo: " << item->getX() << " / " << item->getY();*/
	}
	void CambiarTurnoDeHablar(Control^ c, Graphics^ g) {
		if (doctor->getHablando()) {
			doctor->setHablando(false);
			doctor->CerrarDialogo(c, g->VisibleClipBounds.Bottom, dialogo, ultimoDialogo);
			steph->setDialogo(true);
		}
		if (steph->getDialogo()) {
			doctor->setHablando(true);
			steph->setDialogo(false);
			steph->CerrarDialogo(c, g->VisibleClipBounds.Bottom, dialogo, ultimoDialogo);
		}
	}

	bool alguienHablando() { return (doctor->getHablando() || steph->getDialogo()); }
	Personaje* getPersonaje() { return steph; }
	Item* getItem1() { return item; }
	Item* getItem2() { return item2; }
	Vehiculo* getMoto() { return moto; }
	Dialogo *getFunciones() { return dialogo; }
};