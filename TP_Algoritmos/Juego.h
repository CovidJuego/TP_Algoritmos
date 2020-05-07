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
	//Clases
	Personaje *steph;
	Item *item;
	Item *item2;
	list<Item*> items;


	Escena *mapa;
	Dialogo* dialogo;
	Colisiones *colisiones;
	Doctor *doctor;
	Vehiculo *moto;
	
	//Otros
	int conversaciones;
	bool itemsConseguidos;

public:
	Juego(Graphics^g, array<Bitmap^>^sprites, Control::ControlCollection^ Controls){
		dialogo = new Dialogo();
		steph = new Personaje(sprites[1], Controls, g /*6900, 700*/,9000, 4000);
		item = new Item(steph, 9000,3950);
		item2 = new Item(steph, 100, 200);
		mapa = new Escena();
		moto = new Vehiculo(sprites[4]/*, 6900, 750*/);
		colisiones = new Colisiones();
		doctor = new Doctor(sprites[6], 9205, 4095);
		items = list<Item*>();
		items.push_back(new Item(steph, 9000, 4000, 0, 10, 8, sprites[7]));	//items[0] Cono
		items.push_back(new Item(steph, 9000, 4070, 0, 10, 8, sprites[8]));	//items[1] Porra
		items.push_back(new Item(steph, 9000, 4150, 0, 10, 4, sprites[9]));	//items[2] SubFusil
		items.push_back(new Item(steph, 9000, 4210, 0, 10, 4, sprites[10]));	//items[3] Pistola
		items.push_back(new Item(steph, 9000, 4290, 0, 10, 4, sprites[11]));	//items[4] Fusil
		conversaciones = 0;
	}
	~Juego(){
		delete steph;
		delete mapa;
		delete dialogo;
		delete doctor;
		delete moto;
		delete colisiones;
	}
	void Update(Graphics^ g, array<Bitmap^>^sprites, Control^ interaction_txt, array<String^>^dialogos) {

		mapa->Update(g, sprites[0], steph->getX(), steph->getY());

		item->Update(g, sprites[2], sprites[2], steph, interaction_txt, "Pulse [E] para obtener Circulo");
		item2->Update(g, sprites[3], sprites[3], steph, interaction_txt, "Pulse [E] para obtener Cuadrado");
		
		moto->Update(g, sprites[4], sprites[5], steph, interaction_txt, "Pulse [E] para subir a la moto", "Pulse [E] para bajarse de la moto");
		steph->Update(g, sprites[1], colisiones);
		
		//Recorremos la lista
		list<Item*>::iterator it = items.begin();
		while (it != items.end()) {
			(*it++)->Update(g, sprites[7], sprites[7], steph, interaction_txt, "Pulse [E] para obtener Cono", true);
			(*it++)->Update(g, sprites[8], sprites[8], steph, interaction_txt, "Pulse [E] para obtener Porra", true);
			(*it++)->Update(g, sprites[9], sprites[2], steph, interaction_txt, "Pulse [E] para obtener SubFusil");
			(*it++)->Update(g, sprites[10], sprites[2], steph, interaction_txt, "Pulse [E] para obtener Pistola");
			(*it++)->Update(g, sprites[11], sprites[2], steph, interaction_txt, "Pulse [E] para obtener Fusil");
		}
		doctor->Update(g, sprites[6], steph);
		colisiones->Update(g, steph);

		if (doctor->DetectarColision(steph, g) && (conversaciones < dialogos->Length)) {
			steph->noMoverse = true;
			if (conversaciones % 2 == 0) {
				dialogo->AbrirConversacion(interaction_txt, dialogos[conversaciones], dialogos[conversaciones]->Length * 5, doctor->getX() - 20, doctor->getY() + 50);
			}
			else {
				dialogo->AbrirConversacion(interaction_txt, dialogos[conversaciones], dialogos[conversaciones]->Length * 5, steph->getX() - 20, steph->getY() + 50);
			}
		}
		else
		{
			steph->noMoverse = false;
		}

		item->DibujarRectangulo(g);
		item2->DibujarRectangulo(g);
		steph->DibujarRectangulo2(g);
		moto->DibujarRectangulo(g);
		doctor->DibujarRectangulo(g);
		for (Item* i : items) { i->DibujarRectangulo(g); }

		dialogo->Animacion(interaction_txt, g, steph);
	}
	Item* getItem(int pos) {
		list<Item*>::iterator it = items.begin();
		while (pos > 0) { (*it++); pos--; }
		return (*it);
	}
	Personaje* getPersonaje() { return steph; }
	Item* getItem1() { return item; }
	Item* getItem2() { return item2; }
	Vehiculo* getMoto() { return moto; }
	Dialogo *getDialogo() { return dialogo; }
	void SiguienteDialogo(Control^c, Graphics^ g) {
		dialogo->CerrarConversacion(c, g->VisibleClipBounds.Bottom);
		conversaciones++;
	}
	void TirarItem(Bitmap^ sprite) {
		if (item->getShow()) {
			item->TirarItem(steph);
		}
		else if (item2->getShow()) {
			item2->TirarItem(steph);
		}
		else {
			int i = 0;
			for (list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
				if ((*it)->getShow()) {
					if (i == 0) {
						(*it)->TirarItem(steph, sprite);	//paso el mismo sprite porque solo necesito las dimensiones
					}											//que son iguales en ambos (Cono y Porra)
					else if (i == 1) {
						(*it)->TirarItem(steph, sprite);
					}
					else
						(*it)->TirarItem(steph);
				}
				i++;
			}
		}
	}
};