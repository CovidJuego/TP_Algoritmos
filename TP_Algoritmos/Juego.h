#pragma once
#include "Personaje.h"
#include "Item.h"
#include "Escena.h"
#include "Vehiculo.h"
#include "Dialogo.h"
#include "Colisiones.h"
#include "Doctor.h"
#include "Archivo_Guardado.h"
#include "Generador_Enemigos.h"

class Juego
{
private:
	//Elementos / Items
	Item *adn;
	Item *counter;
	Item *quina;
	list<Item*> items;
	//Objetos de Escena
	Personaje *steph;
	Escena *mapa;
	Doctor *doctor;
	Vehiculo *moto;
	Generador_Enemigos *enemigos;
	//Otros
	Colisiones *colisiones;
	Dialogo *dialogo;
	Archivo_Guardado *save;
	int conversaciones;
	bool haConversado;	//determina si steph ya ha conversado con el Dock

public:
	Juego(Graphics^g, array<Bitmap^>^sprites, Control::ControlCollection^ Controls) {
		dialogo = new Dialogo();
		steph = new Personaje(sprites[1], Controls, g /*6900, 700*/, 8900, 4000);

		adn = new Item(steph, 9000, 3800, 3950, 10, 1, sprites[17]);
		counter = new Item(steph, 9000, 3870, 3950, 10, 1, sprites[18]);
		quina = new Item(steph, 9000, 3920, 3950, 10, 1, sprites[19]);

		mapa = new Escena();
		moto = new Vehiculo(sprites[4]/*, 6900, 750*/, 8700, 4100);
		colisiones = new Colisiones();
		doctor = new Doctor(sprites[6], 9205, 4095);
		items = list<Item*>();
		items.push_back(new Item(steph, 9000, 4000, 13, 30, 8, sprites[7]));	//items[0] Cono
		items.push_back(new Item(steph, 9000, 4070, 13, 30, 8, sprites[8]));		//items[1] Porra
		items.push_back(new Item(steph, 9000, 4150, 4, 28, 4, sprites[9]));		//items[2] SubFusil
		items.push_back(new Item(steph, 9000, 4210, 18, 35, 4, sprites[10]));	//items[3] Pistola
		items.push_back(new Item(steph, 9000, 4290, 8, 40, 4, sprites[11]));	//items[4] Fusil
		save = new Archivo_Guardado();
		enemigos = new Generador_Enemigos();
		//Otros
		conversaciones = 0;
		haConversado = false;

		enemigos->GenerarEnemigos(sprites[23], g, 8000, 10000, 3800, 4300);
	}
	~Juego() {
		delete steph;
		delete mapa;
		delete dialogo;
		delete doctor;
		delete moto;
		delete colisiones;
	}
	void Update(Graphics^ g, array<Bitmap^>^sprites, Control^ interaction_txt, array<String^>^dialogos) {

		mapa->Update(g, sprites[0], steph->getX(), steph->getY());

		adn->Update(g, sprites[17], sprites[17], steph, interaction_txt, "Pulse [E] para obtener ADN");
		counter->Update(g, sprites[18], sprites[18], steph, interaction_txt, "Pulse [E] para obtener CounterOmega");
		quina->Update(g, sprites[19], sprites[19], steph, interaction_txt, "Pulse [E] para obtener Quina");

		moto->Update(g, sprites[4], sprites[5], steph, interaction_txt, "Pulse [E] para subir a la moto", "Pulse [E] para bajarse de la moto");
		if (enemigos->alerta()) {
			enemigos->Update(g, sprites[24], steph, adn);
		}
		else {
			enemigos->Update(g, sprites[23], steph, adn);
		}
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

		if (doctor->DetectarColision(steph, g) && (conversaciones < dialogos->Length) && dialogos[conversaciones] != " ") {
			steph->noMoverse = true;
			dialogo->AbrirConversacion(interaction_txt, dialogos[conversaciones], steph->getX() - 20, steph->getY() + 50);
		}
		else {
			steph->noMoverse = false;
		}

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
	bool getHaConversado() { return haConversado; }
	Personaje* getPersonaje() { return steph; }
	Item* getADN() { return adn; }
	Item* getCounter() { return counter; }
	Item* getQuina() { return quina; }
	Vehiculo* getMoto() { return moto; }
	Dialogo *getDialogo() { return dialogo; }
	void SiguienteDialogo(Control^c, Graphics^ g, array<String^>^ dialogos) {
		dialogo->CerrarConversacion(c, g->VisibleClipBounds.Bottom);
		if (dialogos[conversaciones] != " " && conversaciones <= dialogos->Length - 2) {
			conversaciones++;
		}
		if (dialogos[conversaciones] == " ") {
			haConversado = true;
		}
	}
	void HabilitarDialogo() {
		conversaciones++;
		haConversado = false;
	}
	void TirarItem(Bitmap^ sprite) {
		int i = 0;
		for (list<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if ((*it)->getShow()) {
				if (i < 2) {
					(*it)->TirarItem(steph, sprite);	//paso el mismo sprite porque solo necesito las dimensiones
				}											//que son iguales en ambos (Cono y Porra)
				else
					(*it)->TirarItem(steph);
			}
			i++;
		}
	}
	void GuardarPartida() {
		save->set_vida(0);
		save->set_x(steph->getX());
		save->set_y(steph->getY());
		save->Guardar_partida();
	}
	void CargarPartida() {
		save->Cargar_partida();
	}
};