#pragma once
#include "Personaje.h"
#include "Item.h"
#include "Escena.h"
#include<time.h>
#include "Enemigo.h"
#include "Vehiculo.h"
namespace TPAlgoritmos {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			Start();
			contador = new int;
			*contador = 0;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
				delete sprites;
				delete steph;
				delete mapa;
				delete inventaryButtons;
				delete g;
				delete buffer;
				delete context;
			}
		}

	protected:

	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Label^  interaction_txt;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


	private: System::Windows::Forms::Timer^  timer1;

			 //Graphics
			 Graphics ^g;
			 BufferedGraphics ^buffer;
			 BufferedGraphicsContext ^context;
			 
			 //Sprites
			 array<Bitmap^> ^sprites;
			 array<Button^>^inventaryButtons;
			 Bitmap ^ poli;
			 Personaje *steph;
			 Enemigo * policia;
			 Item *item;
			 Item *item2;
			 Escena *mapa;
			 //Variables Especiales
			 int * contador;//Contador para reedifinir la direccion de los enemigos
			 
			 Vehiculo *moto;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->interaction_txt = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// interaction_txt
			// 
			this->interaction_txt->AutoSize = true;
			this->interaction_txt->Location = System::Drawing::Point(47, 209);
			this->interaction_txt->Name = L"interaction_txt";
			this->interaction_txt->Size = System::Drawing::Size(0, 13);
			this->interaction_txt->TabIndex = 0;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(712, 306);
			this->Controls->Add(this->interaction_txt);
			this->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region MyFunctions

		void Start() {
			//Graphics
			g = this->CreateGraphics();
			context = BufferedGraphicsManager::Current;
			buffer = context->Allocate(g, ClientRectangle);
			
			//Sprites
			sprites = gcnew array<Bitmap^>(5);

			sprites[0] = gcnew Bitmap("ChocolateCity.jpg");
			sprites[1] = gcnew Bitmap("StephMarlonso.png");
			sprites[2] = gcnew Bitmap("ImagenTemp1.png");
			sprites[3] = gcnew Bitmap("ImagenTemp2.png");
			sprites[4] = gcnew System::Drawing::Bitmap("policia.png");
			sprites[5] = gcnew Bitmap("Moto.jpeg");
			//GameObjects
			inventaryButtons = gcnew array<Button^>(4);

			steph = new Personaje(sprites[1], Controls, g);
			item = new Item(steph);
			item2 = new Item(steph, 100, 200);
			mapa = new Escena();
			policia = new Enemigo(sprites[4],g,1);
			//Inventario
			moto = new Vehiculo(sprites[5]);
			for (int i = 0; i < steph->inventary->getEspacios(); i++) {
				inventaryButtons[i] = (Button^)Controls->Find("button" + i, false)[0];
				inventaryButtons[i]->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
				inventaryButtons[i]->TabStop = false;
			}
		}

#pragma endregion


	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		buffer->Graphics->Clear(Color::Black);

		mapa->Update(buffer->Graphics, sprites[0], steph->getX(), steph->getY());

		item->Update(buffer->Graphics, sprites[2], steph, interaction_txt, "Pulse [E] para obtener Circulo");
		item2->Update(buffer->Graphics, sprites[3], steph, interaction_txt, "Pulse [E] para obtener Cuadrado");
		steph->Update(buffer->Graphics, sprites[1]);
		policia->Update(buffer->Graphics, sprites[4]);
		moto->Update(buffer->Graphics, sprites[5], steph);

		item->DibujarRectangulo(buffer->Graphics);
		item2->DibujarRectangulo(buffer->Graphics);
		steph->DibujarRectangulo2(buffer->Graphics);
		

		Console::SetCursorPosition(0, 0); cout << "Mapa: " << mapa->getX() << " / " << mapa->getY();
		Console::SetCursorPosition(0, 2); cout << "Personaje: " << steph->getX() << " / " << steph->getY();
		/*FUNCION QUE DETERMINA ALEATORIDAD DE LOS ENEMIGOS*/
		if (*contador == 10) {
			srand(time(NULL));
			Random r;
			int direccion = r.Next(1, 4);
			Console::SetCursorPosition(7, 8); cout << "Direccion: " << direccion;
			policia->reiniciarDirecciones();
			if (direccion == 1) {
				policia->arr = true;
			}
			else if(direccion == 2) {
				policia->der = true;
			}
			else if (direccion == 3) {
				policia->izq = true;
			}
			else {
				policia->aba = true;
			}
			*contador = 0;
		}
		//Console::SetCursorPosition(7, 4); cout << "Contador: " << *contador;
		*contador+=1;

		Console::SetCursorPosition(0, 3); cout << "Circulo: " << item->getX() << " / " << item->getY();
		Console::SetCursorPosition(0, 4); cout << "Circulo / en form: " << item->posXprint << " / " << item->posYprint;

		buffer->Render(g);
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::W)
		{
			steph->arr = true;
		}
		if (e->KeyCode == Keys::A)
		{
			steph->izq = true;
		}
		if (e->KeyCode == Keys::S)
		{
			steph->aba = true;
		}
		if (e->KeyCode == Keys::D)
		{
			steph->der = true;
		}
		if (e->KeyCode == Keys::E) {
			if (interaction_txt->Text == "Pulse [E] para obtener Circulo") {
				steph->inventary->AgregarItem(inventaryButtons, sprites[2], "Circulo");
				item->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para obtener Cuadrado") {
				steph->inventary->AgregarItem(inventaryButtons, sprites[3], "Cuadrado");
				item2->setEstado(Estado::Inventariado);
			}
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::W)
		{
			steph->arr = false;
		}
		if (e->KeyCode == Keys::A)
		{
			steph->izq = false;
		}
		if (e->KeyCode == Keys::S)
		{
			steph->aba = false;
		}
		if (e->KeyCode == Keys::D)
		{
			steph->der = false;
		}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		interaction_txt->Enabled = true;
		Control ^b = (Control^)sender;
		if (b->Name == "Circulo") {
			item->setShow(true);
			item2->setShow(false);
		}
		else if (b->Name == "Cuadrado") {
			item->setShow(false);
			item2->setShow(true);
		}
		else {
			item->setShow(false);
			item2->setShow(false);
		}
		interaction_txt->Focus();
		interaction_txt->Enabled = false;
	}
};
}
