#pragma once
#include "Personaje.h"
#include "Item.h"
#include "Escena.h"
#include "Vehiculo.h"
#include "FuncionesHistoria.h"

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

			 Personaje *steph;
			 Item *item;
			 Item *item2;
			 Escena *mapa;
			 FuncionesHistoria* funciones;


	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer1;
	private: System::Windows::Forms::Timer^  timer2;


			 Vehiculo *moto;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->interaction_txt = (gcnew System::Windows::Forms::Label());
			this->axWindowsMediaPlayer1 = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// interaction_txt
			// 
			this->interaction_txt->AutoSize = true;
			this->interaction_txt->Location = System::Drawing::Point(569, 284);
			this->interaction_txt->Name = L"interaction_txt";
			this->interaction_txt->Size = System::Drawing::Size(131, 13);
			this->interaction_txt->TabIndex = 0;
			this->interaction_txt->Text = L"Pulsa [Espacio] para omitir";
			// 
			// axWindowsMediaPlayer1
			// 
			this->axWindowsMediaPlayer1->Enabled = true;
			this->axWindowsMediaPlayer1->Location = System::Drawing::Point(0, 338);
			this->axWindowsMediaPlayer1->Name = L"axWindowsMediaPlayer1";
			this->axWindowsMediaPlayer1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer1.OcxState")));
			this->axWindowsMediaPlayer1->Size = System::Drawing::Size(36, 34);
			this->axWindowsMediaPlayer1->TabIndex = 1;
			this->axWindowsMediaPlayer1->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MyForm::axWindowsMediaPlayer1_PreviewKeyDown);
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(712, 306);
			this->Controls->Add(this->interaction_txt);
			this->Controls->Add(this->axWindowsMediaPlayer1);
			this->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->Name = L"MyForm";
			this->Text = L"Coronavirus: The Game";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->EndInit();
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
			sprites[4] = gcnew Bitmap("Moto.png");

			//GameObjects
			inventaryButtons = gcnew array<Button^>(4);

			funciones = new FuncionesHistoria();
			steph = new Personaje(sprites[1], Controls, g);
			item = new Item(steph, 150, 0);
			item2 = new Item(steph, 100, 200);
			mapa = new Escena();
			moto = new Vehiculo(sprites[4]);

			for (int i = 0; i < steph->inventary->getEspacios(); i++) {
				inventaryButtons[i] = (Button^)Controls->Find("button" + i, false)[0];
				inventaryButtons[i]->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
				inventaryButtons[i]->TabStop = false;
			}

			this->axWindowsMediaPlayer1->Location = Point(0, 0);
			this->axWindowsMediaPlayer1->Size = System::Drawing::Size(712, 372);
			
		}
		void PasarAlJuego() {
			this->axWindowsMediaPlayer1->Ctlcontrols->stop();
			this->axWindowsMediaPlayer1->Location = Point(0, g->VisibleClipBounds.Bottom + 1);
			this->axWindowsMediaPlayer1->Visible = false;
			this->axWindowsMediaPlayer1->Enabled = false;
			interaction_txt->Location = Point(0, g->VisibleClipBounds.Bottom + 1);
			timer2->Stop();
			timer1->Start();
		}

#pragma endregion

	private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (this->axWindowsMediaPlayer1->playState == WMPLib::WMPPlayState::wmppsStopped) {
			PasarAlJuego();
		}
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		buffer->Graphics->Clear(Color::Black);

		mapa->Update(buffer->Graphics, sprites[0], steph->getX(), steph->getY());

		item->Update(buffer->Graphics, sprites[2], steph, interaction_txt, "Pulse [E] para obtener Circulo");
		item2->Update(buffer->Graphics, sprites[3], steph, interaction_txt, "Pulse [E] para obtener Cuadrado");
		steph->Update(buffer->Graphics, sprites[1]);
		moto->Update(buffer->Graphics, sprites[4], steph, interaction_txt, "Pulse [E] para subir a la moto", "Pulse [E] para bajarse de la moto");

		item->DibujarRectangulo(buffer->Graphics);
		item2->DibujarRectangulo(buffer->Graphics);
		steph->DibujarRectangulo2(buffer->Graphics);
		moto->DibujarRectangulo(buffer->Graphics);	

		funciones->Animacion(interaction_txt, buffer->Graphics, steph);

		Console::SetCursorPosition(0, 0); cout << "Mapa: " << mapa->getX() << " / " << mapa->getY();
		Console::SetCursorPosition(0, 2); cout << "Personaje: " << steph->getX() << " / " << steph->getY();

		Console::SetCursorPosition(0, 3); cout << "Circulo: " << item->getX() << " / " << item->getY();/*
		Console::SetCursorPosition(0, 4); cout << "Circulo / en form: " << item->posXprint << " / " << item->posYprint;*/

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
			if (interaction_txt->Text == "Pulse [E] para subir a la moto") {
				moto->Subir(steph);
			}
			if (interaction_txt->Text == "Pulse [E] para bajarse de la moto") {
				moto->Bajar(steph);
			}
		}
		if (e->KeyCode == Keys::U) {
			funciones->AbrirConversacion(interaction_txt, "Hola amigo que tal", 100, steph);
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
		this->Focus();
		interaction_txt->Focus();
		interaction_txt->Enabled = false;
	}
	
	private: System::Void axWindowsMediaPlayer1_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
		if (e->KeyCode == Keys::Space) {
			PasarAlJuego();
		}
	}
};
}
