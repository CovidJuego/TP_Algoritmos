#pragma once
#include "Generador_Enemigos.h"
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

	Item *adn;
	Item *counter;
	Item *quina;
	list<Item*> items;

	Escena *mapa;
	Dialogo* dialogo;
	Colisiones *colisiones;
	Doctor *doctor;
	Vehiculo *moto;
	
	Generador_Enemigos * generador;

	//Otros
	int conversaciones;
	bool haConversado;	//determina si steph ya ha conversado con el Dock
	int * contador;
public:
	Juego(Graphics^g, array<Bitmap^>^sprites, Control::ControlCollection^ Controls){
		dialogo = new Dialogo();
		steph = new Personaje(sprites[1], Controls, g /*6900, 700*/,8900, 4000);
		item = new Item(steph, 9000,3950);
		item2 = new Item(steph, 100, 200);

		adn = new Item(steph, 9000, 3800, 3950, 10, 1, sprites[17]);
		counter = new Item(steph, 9000, 3870, 3950, 10, 1, sprites[18]);
		quina = new Item(steph, 9000, 3920, 3950, 10, 1, sprites[19]);

		generador = new Generador_Enemigos();
		contador = new int;
		*contador = 0;

		mapa = new Escena();
		moto = new Vehiculo(sprites[4]/*, 6900, 750*/);
		colisiones = new Colisiones();
		doctor = new Doctor(sprites[6], 9205, 4095);
		items = list<Item*>();
		items.push_back(new Item(steph, 9000, 4000, 13, 30, 8, sprites[7]));	//items[0] Cono
		items.push_back(new Item(steph, 9000, 4070, 13, 30, 8, sprites[8]));		//items[1] Porra
		items.push_back(new Item(steph, 9000, 4150, 4, 28, 4, sprites[9]));		//items[2] SubFusil
		items.push_back(new Item(steph, 9000, 4210, 18, 35, 4, sprites[10]));	//items[3] Pistola
		items.push_back(new Item(steph, 9000, 4290, 8, 40, 4, sprites[11]));	//items[4] Fusil
		conversaciones = 0;
		haConversado = false;
	}
	~Juego(){
		delete steph;
		delete mapa;
		delete dialogo;
		delete doctor;
		delete moto;
		delete colisiones;
	}

	void generarEnemigos(Bitmap^ sprite, Graphics ^g, int tipo) {
		generador->aparecer_enemigos(sprite, g, tipo);
	}

	void Update(Graphics^ g, array<Bitmap^>^sprites, Control^ interaction_txt, array<String^>^dialogos) {

		mapa->Update(g, sprites[0], steph->getX(), steph->getY());

		item->Update(g, sprites[2], sprites[2], steph, interaction_txt, "Pulse [E] para obtener Circulo");
		item2->Update(g, sprites[3], sprites[3], steph, interaction_txt, "Pulse [E] para obtener Cuadrado");
		
		adn->Update(g, sprites[17], sprites[17], steph, interaction_txt, "Pulse [E] para obtener ADN");
		counter->Update(g, sprites[18], sprites[18], steph, interaction_txt, "Pulse [E] para obtener CounterOmega");
		quina->Update(g, sprites[19], sprites[19], steph, interaction_txt, "Pulse [E] para obtener Quina");

		moto->Update(g, sprites[4], sprites[5], steph, interaction_txt, "Pulse [E] para subir a la moto", "Pulse [E] para bajarse de la moto");
		steph->Update(g, sprites[1], colisiones);

		if (generador->alerta() == false) {
			generador->Update(g, sprites[23], steph->getX_pantalla(), steph->getY_pantalla());
			steph->enemigosCerca = false;
		}
		else {
			generador->Update(g, sprites[24], steph->getX_pantalla(), steph->getY_pantalla());
			steph->enemigosCerca = true;
		}
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
		/*FUNCION QUE DETERMINA ALEATORIDAD DE LOS ENEMIGOS*/
		if (*contador == 20) {
			srand(time(NULL));
			Random r;
			int direccion = r.Next(1, 4);
			Console::SetCursorPosition(7, 8); std::cout << "Direccion: " << direccion;
			generador->reiniciarDirecciones();
			if (direccion == 1) {
				generador->dir(1);
			}
			else if (direccion == 2) {
				generador->dir(2);
			}
			else if (direccion == 3) {
				generador->dir(3);
			}
			else {
				generador->dir(4);
			}
			*contador = 0;
		}
		*contador += 1;
		/*item->DibujarRectangulo(g);
		item2->DibujarRectangulo(g);
		steph->DibujarRectangulo2(g);
		moto->DibujarRectangulo(g);
		doctor->DibujarRectangulo(g);
		for (Item* i : items) { i->DibujarRectangulo(g); }*/
		
		dialogo->Animacion(interaction_txt, g, steph);
	}
	Item* getItem(int pos) {
		list<Item*>::iterator it = items.begin();
		while (pos > 0) { (*it++); pos--; }
		return (*it);
	}
	bool getHaConversado() { return haConversado; }
	Personaje* getPersonaje() { return steph; }
	Item* getItem1() { return item; }
	Item* getItem2() { return item2; }
	Item* getADN() { return adn; }
	Item* getCounter() { return counter; }
	Item* getQuina() { return quina; }
	Vehiculo* getMoto() { return moto; }
	Dialogo *getDialogo() { return dialogo; }
	void SiguienteDialogo(Control^c, Graphics^ g, array<String^>^ dialogos) {
		dialogo->CerrarConversacion(c, g->VisibleClipBounds.Bottom);
		if (dialogos[conversaciones] != " " && conversaciones <= dialogos->Length-2) {
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
					if (i < 2) {
						(*it)->TirarItem(steph, sprite);	//paso el mismo sprite porque solo necesito las dimensiones
					}											//que son iguales en ambos (Cono y Porra)
					else
						(*it)->TirarItem(steph);
				}
				i++;
			}
		}
	}
};