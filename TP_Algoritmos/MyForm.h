#pragma once
#include "Juego.h"

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
				delete inventaryButtons;
				delete g;
				delete buffer;
				delete context;
				delete juego;
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

			 //Arrays
			 array<Bitmap^> ^sprites;
			 array<Button^> ^inventaryButtons;
			 array<String^> ^dialogos;

			 //Game
			 Juego *juego;

	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer1;
	private: System::Windows::Forms::Panel^  Menu_pnl;
	private: System::Windows::Forms::Button^  Play_btn;
	private: System::Windows::Forms::Timer^  timer2;



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
			this->Menu_pnl = (gcnew System::Windows::Forms::Panel());
			this->Play_btn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->BeginInit();
			this->Menu_pnl->SuspendLayout();
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
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// Menu_pnl
			// 
			this->Menu_pnl->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->Menu_pnl->Controls->Add(this->Play_btn);
			this->Menu_pnl->Location = System::Drawing::Point(192, 78);
			this->Menu_pnl->Name = L"Menu_pnl";
			this->Menu_pnl->Size = System::Drawing::Size(200, 100);
			this->Menu_pnl->TabIndex = 2;
			// 
			// Play_btn
			// 
			this->Play_btn->Location = System::Drawing::Point(122, 64);
			this->Play_btn->Name = L"Play_btn";
			this->Play_btn->Size = System::Drawing::Size(75, 23);
			this->Play_btn->TabIndex = 0;
			this->Play_btn->Text = L"Jugar";
			this->Play_btn->UseVisualStyleBackColor = true;
			this->Play_btn->Click += gcnew System::EventHandler(this, &MyForm::Play_btn_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(712, 306);
			this->Controls->Add(this->Menu_pnl);
			this->Controls->Add(this->interaction_txt);
			this->Controls->Add(this->axWindowsMediaPlayer1);
			this->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->Name = L"MyForm";
			this->Text = L"Coronavirus: The Game";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->EndInit();
			this->Menu_pnl->ResumeLayout(false);
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
			sprites = gcnew array<Bitmap^>(17);
			sprites[0] = gcnew Bitmap("ChocolateCity.jpg");
			sprites[1] = gcnew Bitmap("StephMarlonso.png");
			sprites[2] = gcnew Bitmap("ImagenTemp1.png");
			sprites[3] = gcnew Bitmap("ImagenTemp2.png");
			sprites[4] = gcnew Bitmap("Moto.png");
			sprites[5] = gcnew Bitmap("StephEnMoto.png");
			sprites[6] = gcnew Bitmap("Doctor.png");
			sprites[7] = gcnew Bitmap("Cono.png");
			sprites[8] = gcnew Bitmap("Porra.png");
			sprites[9] = gcnew Bitmap("SubFusil.png");
			sprites[10] = gcnew Bitmap("Pistola.png");
			sprites[11] = gcnew Bitmap("Fusil.png");
			sprites[12] = gcnew Bitmap("Icono1.png");
			sprites[13] = gcnew Bitmap("Icono2.png");
			sprites[14] = gcnew Bitmap("Icono3.png");
			sprites[15] = gcnew Bitmap("Icono4.png");
			sprites[16] = gcnew Bitmap("Icono5.png");

			//Juego
			juego = new Juego(buffer->Graphics, sprites, Controls);

			//InventaryButtons
			inventaryButtons = gcnew array<Button^>(4);
			for (int i = 0; i < juego->getPersonaje()->inventary->getEspacios(); i++) {
				inventaryButtons[i] = (Button^)Controls->Find("button" + i, false)[0];
				inventaryButtons[i]->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
				inventaryButtons[i]->TabStop = false;
			}

			//Dialogos
			dialogos = gcnew array<String^>(13);
			dialogos[0] = "Disculpe, es usted el Dr.Flint?";
			dialogos[1] = "Pero claro que soy el Dr. Flint, no has visto mi bata?";
			dialogos[2] = "Sospecho que estas aquí porque me vas a ayudar a terminar con este caos";
			dialogos[3] = "Si, ya no aguanto más";
			dialogos[4] = "Ok, pero no va ser sencillo";
			dialogos[5] = "Yo podre con todo, no se preocupe";
			dialogos[6] = "Bueno, he aquí los objetos que necesito: una quina, el adn de un paciente con Covid-19, y el CounterOmega-19";
			dialogos[7] = "Entendido, hasta luego doctor";
			dialogos[8] = "Ve con Dios";
			dialogos[9] = " ";
			dialogos[10] = "Doctor! Encontre los objetos";
			dialogos[11] = "Excelente. Es hora de salvar al mundo al fin";
			dialogos[12] = "Podre morir en paz";


			//Ajustes iniciales
			this->axWindowsMediaPlayer1->Location = Point(0, 0);
			this->axWindowsMediaPlayer1->Size = System::Drawing::Size(712, 372);

			Menu_pnl->Dock = DockStyle::Fill;
			
		}
		void PasarAlJuego() {
			this->axWindowsMediaPlayer1->Ctlcontrols->stop();
			this->axWindowsMediaPlayer1->Location = Point(0, g->VisibleClipBounds.Bottom + 1);
			this->axWindowsMediaPlayer1->Visible = false;
			this->axWindowsMediaPlayer1->Enabled = false;
			interaction_txt->Location = Point(0, g->VisibleClipBounds.Bottom + 1);
			timer2->Stop();
			timer1->Start();
			delete axWindowsMediaPlayer1;
		}
		void setItemVisible(String^ s) {
			juego->getItem1()->setShow(s == "Circulo");
			juego->getItem2()->setShow(s == "Cuadrado");
			juego->getItem(0)->setShow(s == "Cono");
			juego->getItem(1)->setShow(s == "Porra");
			juego->getItem(2)->setShow(s == "SubFusil");
			juego->getItem(3)->setShow(s == "Pistola");
			juego->getItem(4)->setShow(s == "Fusil");
		}

#pragma endregion

	private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (this->axWindowsMediaPlayer1->playState == WMPLib::WMPPlayState::wmppsStopped) {
			PasarAlJuego();
		}
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		buffer->Graphics->Clear(Color::Black);

		juego->Update(buffer->Graphics, sprites, interaction_txt, dialogos);

		buffer->Render(g);
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::W)
		{
			juego->getPersonaje()->arr = true;
		}
		if (e->KeyCode == Keys::A)
		{
			juego->getPersonaje()->izq = true;
		}
		if (e->KeyCode == Keys::S)
		{
			juego->getPersonaje()->aba = true;
		}
		if (e->KeyCode == Keys::D)
		{
			juego->getPersonaje()->der = true;
		}
		if (e->KeyCode == Keys::E) {
			if (interaction_txt->Text == "Pulse [E] para obtener Circulo") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[2], "Circulo");
				juego->getItem1()->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para obtener Cuadrado") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[3], "Cuadrado");
				juego->getItem2()->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para obtener Cono") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[12], "Cono");
				juego->getItem(0)->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para obtener Porra") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[13], "Porra");
				juego->getItem(1)->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para obtener SubFusil") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[14], "SubFusil");
				juego->getItem(2)->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para obtener Pistola") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[15], "Pistola");
				juego->getItem(3)->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para obtener Fusil") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[16], "Fusil");
				juego->getItem(4)->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para subir a la moto") {
				juego->getMoto()->Subir(juego->getPersonaje());
			}
			if (interaction_txt->Text == "Pulse [E] para bajarse de la moto") {
				juego->getMoto()->Bajar(juego->getPersonaje());
			}
		}
		if (e->KeyCode == Keys::Space) {
			juego->SiguienteDialogo(interaction_txt, buffer->Graphics);
		}
		if (e->KeyCode == Keys::C) {
			juego->TirarItem(sprites[7]);
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::W)
		{
			juego->getPersonaje()->arr = false;
		}
		if (e->KeyCode == Keys::A)
		{
			juego->getPersonaje()->izq = false;
		}
		if (e->KeyCode == Keys::S)
		{
			juego->getPersonaje()->aba = false;
		}
		if (e->KeyCode == Keys::D)
		{
			juego->getPersonaje()->der = false;
		}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		interaction_txt->Enabled = true;
		Control ^b = (Control^)sender;
		setItemVisible(b->Name);
		interaction_txt->Focus();
		interaction_txt->Enabled = false;
	}
	
	private: System::Void axWindowsMediaPlayer1_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
		if (e->KeyCode == Keys::Space) {
			PasarAlJuego();
		}
	}
	private: System::Void Play_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		Menu_pnl->Visible = false;
		this->axWindowsMediaPlayer1->Focus();
		this->axWindowsMediaPlayer1->Ctlcontrols->play();
		timer2->Start();
	}
};
}
