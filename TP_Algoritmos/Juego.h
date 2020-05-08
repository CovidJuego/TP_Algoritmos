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
	list<Item*> *items;
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
	bool haConversado;	//determina si steph ya ha conversado con el Dock
	Colision *colisionA, *colisionB, *colisionC;	//colisiones que spawnean a los enemigos
	bool zonaA, zonaB, zonaC; //determinan si los enemigos de cada zona han sido activados

public:
	Juego(Graphics^g, array<Bitmap^>^sprites, Control::ControlCollection^ Controls){
		dialogo = new Dialogo();
		steph = new Personaje(sprites[1], Controls, g, 6900, 700/* 9000, 3700*/);

		adn = new Item(steph, 11535, 720/*9000, 3800*/, 3950, 10, 1, sprites[17], Tirado, 0.2);
		counter = new Item(steph, 1845, 8795, /*9000, 3870,*/ 3950, 10, 1, sprites[18], Tirado, 0.2);
		quina = new Item(steph, 12100, 11485, /*9000, 3920,*/ 3950, 10, 1, sprites[19], Tirado, 0.2);

		mapa = new Escena();
		moto = new Vehiculo(sprites[4], 6800, 750/*, 8900, 3700*/);
		colisiones = new Colisiones();
		doctor = new Doctor(sprites[6], 9205, 4095);
		items = new list<Item*>();
		items->push_back(new Item(steph, 9000, 4000, 13, 30, 8, sprites[7]));	//items[0] Cono
		items->push_back(new Item(steph, 9000, 4070, 13, 30, 8, sprites[8]));		//items[1] Porra
		items->push_back(new Item(steph, 9000, 4150, 4, 28, 4, sprites[9]));		//items[2] SubFusil
		items->push_back(new Item(steph, 9000, 4210, 18, 35, 4, sprites[10]));	//items[3] Pistola
		items->push_back(new Item(steph, 9000, 4290, 8, 40, 4, sprites[11]));	//items[4] Fusil
		save = new Archivo_Guardado();
		enemigos = new Generador_Enemigos();
		//Otros
		haConversado = false;
		colisionA = new Colision(11500, 1000, 950, 300, true);
		colisionB = new Colision(12000, 11650, 600, 280, true);
		colisionC = new Colision(1880, 8915, 800, 400, true);
		zonaA = zonaB = zonaC = false;
	}
	~Juego(){
		delete steph;
		delete mapa;
		delete dialogo;
		delete doctor;
		delete moto;
		delete colisiones;
		delete items;
		delete enemigos;
	}
	void Update(Graphics^ g, array<Bitmap^>^sprites, Control^ interaction_txt, queue<String^>*dialogos) {

		mapa->Update(g, sprites[0], sprites[25], steph->getX(), steph->getY());
		adn->Update(g, sprites[17], sprites[17], steph, interaction_txt, "Pulse [E] para obtener ADN");
		counter->Update(g, sprites[18], sprites[18], steph, interaction_txt, "Pulse [E] para obtener CounterOmega");
		quina->Update(g, sprites[19], sprites[19], steph, interaction_txt, "Pulse [E] para obtener Quina");
		moto->Update(g, sprites[4], sprites[5], steph, interaction_txt, "Pulse [E] para subir a la moto", "Pulse [E] para bajarse de la moto");
		enemigos->Update(g, sprites[23], sprites[24], steph, getTirablesDeItems(), RemoverItem);
		steph->Update(g, sprites[1], colisiones);
		list<Item*>::iterator it = items->begin();
		(*it++)->Update(g, sprites[7], sprites[7], steph, interaction_txt, "Pulse [E] para obtener Cono", true);
		(*it++)->Update(g, sprites[8], sprites[8], steph, interaction_txt, "Pulse [E] para obtener Porra", true);
		(*it++)->Update(g, sprites[9], sprites[2], steph, interaction_txt, "Pulse [E] para obtener SubFusil");
		(*it++)->Update(g, sprites[10], sprites[2], steph, interaction_txt, "Pulse [E] para obtener Pistola");
		(*it++)->Update(g, sprites[11], sprites[2], steph, interaction_txt, "Pulse [E] para obtener Fusil");
		doctor->Update(g, sprites[6], steph);
		colisiones->Update(g, steph);

		colisionA->Update(g, steph);
		colisionB->Update(g, steph);
		colisionC->Update(g, steph);

		if (colisionA->CheckColision(steph) && !zonaA) {	
			zonaA = true;
			enemigos->GenerarEnemigos(sprites[23], g, 11035, 12035, 500, 800);
		}
		if (colisionB->CheckColision(steph) && !zonaB) {
			zonaB = true;
			enemigos->GenerarEnemigos(sprites[23], g, 11700, 12300, 11250, 11560);
		}
		if (colisionC->CheckColision(steph) && !zonaC) {
			zonaC = true;
			enemigos->GenerarEnemigos(sprites[23], g, 1480, 2600, 8315, 9215);
		}

		if (doctor->DetectarColision(steph, g) && (dialogos->size() > 0) && dialogos->front() != " ") {
			steph->noMoverse = true;
			dialogo->AbrirConversacion(interaction_txt, dialogos->front(), steph->getX() - 20, steph->getY() + 50);
		}
		else steph->noMoverse = false;
		
		dialogo->Animacion(interaction_txt, g, steph);
		Perdiste(interaction_txt);

		colisionA->DibujarRectangulo(g);
		colisionB->DibujarRectangulo(g);
		colisionC->DibujarRectangulo(g);

		Console::SetCursorPosition(0, 0); cout << "                                       ";
		Console::SetCursorPosition(0, 0); cout << "Personaje: " << steph->getX() << " / " << steph->getY();
	}
	Item* getItem(int pos) {
		list<Item*>::iterator it = items->begin();
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
	void SiguienteDialogo(Control^c, Graphics^ g, queue<String^>* dialogos) {
		dialogo->CerrarConversacion(c, g->VisibleClipBounds.Bottom);
		if (dialogos->front() != " " && dialogos->size() > 1) {
			dialogos->pop();
		}
		if (dialogos->front() == " ") {
			haConversado = true; 
			if (adn->getEstado() == Inventariado && counter->getEstado() == Inventariado && quina->getEstado() == Inventariado) {
				c->Enabled = true;
				c->Location = Point(200, 150);
				c->AutoSize = true;
				c->Text = "GANASTE";
			}
		}
	}
	void HabilitarDialogo(queue<String^>* dialogos) {
		dialogos->pop();
		haConversado = false;
	}
	void TirarItem(Bitmap^ sprite) {
		int i = 0;
		for (list<Item*>::iterator it = items->begin(); it != items->end(); it++) {
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
	list<Item*>*getTirablesDeItems() {
		list<Item*>*aux = new list<Item*>();
		for (list<Item*>::iterator it = items->begin(); it != items->end(); it++) {
			if ((*it)->getEstado() == Inventariado) {
				if ((*it)->getTirables()->size() > 0) {
					list<Item*>*tirables = (*it)->getTirables();
					for (Item*i : (*tirables)) {
						aux->push_back(i);
					}
				}
			}
		}
		return aux;		//devuelve un arreglo con todos los tirables que existen
	}
	function<void(Item*tirable)> RemoverItem = [&](Item*tirable) {
		for (Item* i : (*items)) {
			if (i->getEstado() == Inventariado) {
				i->getTirables()->remove(tirable); 
			}
		}
	};
	void Perdiste(Control^ c) {
		if (steph->getSalud() <= 0) {
			c->Enabled = true;
			c->Location = Point(200, 150);
			c->AutoSize = true;
			c->Text = "PERDISTE";
		}
	}
};