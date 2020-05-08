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

			 //Otras variables
			 bool played;
			 bool menu;

	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer1;
	private: System::Windows::Forms::Panel^  Menu_pnl;
	private: System::Windows::Forms::Button^  Play_btn;
	private: System::Windows::Forms::Label^  interaction2_txt;
	private: System::Windows::Forms::Button^  Reanudar_btn;
	private: System::Windows::Forms::Button^  Guardar_btn;
	private: System::Windows::Forms::Button^  Salir_btn;
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
				 this->interaction2_txt = (gcnew System::Windows::Forms::Label());
				 this->Reanudar_btn = (gcnew System::Windows::Forms::Button());
				 this->Guardar_btn = (gcnew System::Windows::Forms::Button());
				 this->Salir_btn = (gcnew System::Windows::Forms::Button());
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
				 this->Menu_pnl->Location = System::Drawing::Point(389, 89);
				 this->Menu_pnl->Name = L"Menu_pnl";
				 this->Menu_pnl->Size = System::Drawing::Size(55, 99);
				 this->Menu_pnl->TabIndex = 2;
				 // 
				 // Play_btn
				 // 
				 this->Play_btn->Location = System::Drawing::Point(326, 138);
				 this->Play_btn->Name = L"Play_btn";
				 this->Play_btn->Size = System::Drawing::Size(75, 23);
				 this->Play_btn->TabIndex = 0;
				 this->Play_btn->Text = L"JUGAR";
				 this->Play_btn->UseVisualStyleBackColor = true;
				 this->Play_btn->Click += gcnew System::EventHandler(this, &MyForm::Play_btn_Click);
				 // 
				 // interaction2_txt
				 // 
				 this->interaction2_txt->AutoSize = true;
				 this->interaction2_txt->Location = System::Drawing::Point(9, 351);
				 this->interaction2_txt->Name = L"interaction2_txt";
				 this->interaction2_txt->Size = System::Drawing::Size(151, 13);
				 this->interaction2_txt->TabIndex = 3;
				 this->interaction2_txt->Text = L"Pulsa [Espacio] para continuar";
				 // 
				 // Reanudar_btn
				 // 
				 this->Reanudar_btn->Location = System::Drawing::Point(21, 69);
				 this->Reanudar_btn->Name = L"Reanudar_btn";
				 this->Reanudar_btn->Size = System::Drawing::Size(75, 23);
				 this->Reanudar_btn->TabIndex = 4;
				 this->Reanudar_btn->Text = L"Reanudar";
				 this->Reanudar_btn->UseVisualStyleBackColor = true;
				 this->Reanudar_btn->Click += gcnew System::EventHandler(this, &MyForm::Reanudar_btn_Click);
				 // 
				 // Guardar_btn
				 // 
				 this->Guardar_btn->Location = System::Drawing::Point(21, 103);
				 this->Guardar_btn->Name = L"Guardar_btn";
				 this->Guardar_btn->Size = System::Drawing::Size(75, 23);
				 this->Guardar_btn->TabIndex = 5;
				 this->Guardar_btn->Text = L"Guardar";
				 this->Guardar_btn->UseVisualStyleBackColor = true;
				 this->Guardar_btn->Click += gcnew System::EventHandler(this, &MyForm::Guardar_btn_Click);
				 // 
				 // Salir_btn
				 // 
				 this->Salir_btn->Location = System::Drawing::Point(21, 137);
				 this->Salir_btn->Name = L"Salir_btn";
				 this->Salir_btn->Size = System::Drawing::Size(75, 23);
				 this->Salir_btn->TabIndex = 6;
				 this->Salir_btn->Text = L"Salir";
				 this->Salir_btn->UseVisualStyleBackColor = true;
				 this->Salir_btn->Click += gcnew System::EventHandler(this, &MyForm::Salir_btn_Click);
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(712, 306);
				 this->Controls->Add(this->Menu_pnl);
				 this->Controls->Add(this->interaction_txt);
				 this->Controls->Add(this->axWindowsMediaPlayer1);
				 this->Controls->Add(this->Salir_btn);
				 this->Controls->Add(this->Guardar_btn);
				 this->Controls->Add(this->Reanudar_btn);
				 this->Controls->Add(this->interaction2_txt);
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
				 sprites = gcnew array<Bitmap^>(26);
				 sprites[0] = gcnew Bitmap("ChocolateCity.jpg"); sprites[1] = gcnew Bitmap("StephMarlonso.png");
				 sprites[2] = gcnew Bitmap("ImagenTemp1.png");	sprites[3] = gcnew Bitmap("ImagenTemp2.png");
				 sprites[4] = gcnew Bitmap("Moto.png");			sprites[5] = gcnew Bitmap("StephEnMoto.png");
				 sprites[6] = gcnew Bitmap("Doctor.png");		sprites[7] = gcnew Bitmap("Cono.png");
				 sprites[8] = gcnew Bitmap("Porra.png");		sprites[9] = gcnew Bitmap("SubFusil.png");
				 sprites[10] = gcnew Bitmap("Pistola.png");		sprites[11] = gcnew Bitmap("Fusil.png");
				 sprites[12] = gcnew Bitmap("Icono1.png");		sprites[13] = gcnew Bitmap("Icono2.png");
				 sprites[14] = gcnew Bitmap("Icono3.png");		sprites[15] = gcnew Bitmap("Icono4.png");
				 sprites[16] = gcnew Bitmap("Icono5.png");		sprites[17] = gcnew Bitmap("Adn.png");
				 sprites[18] = gcnew Bitmap("Virus.png");		sprites[19] = gcnew Bitmap("Quina.png");
				 sprites[20] = gcnew Bitmap("Icono6.png");		sprites[21] = gcnew Bitmap("Icono7.png");
				 sprites[22] = gcnew Bitmap("Icono8.png");		sprites[23] = gcnew Bitmap("policia.png");
				 sprites[24] = gcnew Bitmap("policiaAlerta.png"); sprites[25] = gcnew Bitmap("Island.png");

				 //Juego
				 juego = new Juego(buffer->Graphics, sprites, Controls);

				 //InventaryButtons
				 inventaryButtons = gcnew array<Button^>(juego->getPersonaje()->inventary->getEspacios());
				 for (int i = 0; i < inventaryButtons->Length; i++) {
					 inventaryButtons[i] = (Button^)Controls->Find("button" + i, false)[0];
					 inventaryButtons[i]->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
					 inventaryButtons[i]->TabStop = false;
				 }

				 //Dialogos
				 dialogos = gcnew array<String^>(28);
				 dialogos[0] = "Disculpe, es usted el Dr. Flint?S";
				 dialogos[1] = "Pero claro que soy el Dr. Flint, no has visto mi bata?D";
				 dialogos[2] = "Sospecho que estas aquí porque me vas a ayudar a terminar con el caos de este mundoD";
				 dialogos[3] = "Si, ya no aguanto másS";
				 dialogos[4] = "Ok, pero no va ser sencilloD";
				 dialogos[5] = "Yo podre con todo, no se preocupeS";
				 dialogos[6] = "Bueno, he aquí los objetos que necesito: una quina, el ADN de un paciente con Covid-19, y el CounterOmega-19D";
				 dialogos[7] = "Primero, anda al hospital de la ciudad, ahí encontraras al paciente. Cuidado con los policías que lo cuidanD";
				 dialogos[8] = "EntendidoS";
				 dialogos[9] = " ";
				 dialogos[10] = "Aquí esta docS";
				 dialogos[11] = "Perfecto. Ahora ve al bosque. Ahí estará la quina con grandes sustancia curativasD";
				 dialogos[12] = "Al bosque? Este va ser sencilloS";
				 dialogos[13] = "No te confíes. Ve con DiosD";
				 dialogos[14] = " ";
				 dialogos[15] = "Uf, volví. Tuve que arreglar un puente y fue agotadorS";
				 dialogos[16] = "Jajaja, te dije.D";
				 dialogos[17] = "Bueno, el ultimo objeto es el más difícilD";
				 dialogos[18] = "Tienes que ir al desierto. Por ahí, se cayó un helicóptero con el CounterOmega-19, un ingrediente muy importante para la curaD";
				 dialogos[19] = "Pero cuidado, el helicóptero lo atacaron unos mercenarios. Deben estar por ahí.D";
				 dialogos[20] = "Tranquilo doc, me las arreglareS";
				 dialogos[21] = " ";
				 dialogos[22] = "Doc ya está la última piezaS";
				 dialogos[23] = "Magnifico. Podre hacer la cura al finD";
				 dialogos[24] = "Gracias a ti, habrá un mañana para todosD";
				 dialogos[25] = "Es hora de salvar al mundo al finD";
				 dialogos[26] = "Podre morir en pazD";
				 dialogos[27] = " ";

				 //Ajustes iniciales
				 played = false;
				 menu = false;

				 Menu_pnl->Dock = DockStyle::Fill;
				 ActivarMenu(false);

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
			 void setItemVisible(String^ s) {
				 juego->getItem(0)->setShow(s == "Cono");
				 juego->getItem(1)->setShow(s == "Porra");
				 juego->getItem(2)->setShow(s == "SubFusil");
				 juego->getItem(3)->setShow(s == "Pistola");
				 juego->getItem(4)->setShow(s == "Fusil");
			 }
			 void ActivarMenuButtons(bool a) {
				 Reanudar_btn->Visible = a; Reanudar_btn->Enabled = a;
				 Guardar_btn->Visible = a; Guardar_btn->Enabled = a;
				 Salir_btn->Visible = a; Salir_btn->Enabled = a;
			 }

			 void ActivarMenu(bool a) {
				 if (a) {
					 timer1->Stop();
					 DibujarMenu();
				 }
				 else {
					 timer1->Start();
				 }
				 ActivarMenuButtons(a);
			 }

			 void DibujarMenu() {
				 SolidBrush^ solid = gcnew SolidBrush(Color::FromArgb(80, Color::Red));
				 buffer->Graphics->FillRectangle(solid, 10, 40, 100, 150);
				 buffer->Render(g);
				 delete solid;
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
			if (interaction_txt->Text == "Pulse [E] para obtener Cono") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[12], "Cono");
				juego->getItem(0)->setEstado(Estado::Inventariado);
			}
			else if (interaction_txt->Text == "Pulse [E] para obtener Porra") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[13], "Porra");
				juego->getItem(1)->setEstado(Estado::Inventariado);
			}
			else if (interaction_txt->Text == "Pulse [E] para obtener SubFusil") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[14], "SubFusil");
				juego->getItem(2)->setEstado(Estado::Inventariado);
			}
			else if (interaction_txt->Text == "Pulse [E] para obtener Pistola") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[15], "Pistola");
				juego->getItem(3)->setEstado(Estado::Inventariado);
			}
			else if (interaction_txt->Text == "Pulse [E] para obtener Fusil") {
				juego->getPersonaje()->inventary->AgregarItem(inventaryButtons, sprites[16], "Fusil");
				juego->getItem(4)->setEstado(Estado::Inventariado);
			}
			if (interaction_txt->Text == "Pulse [E] para subir a la moto") {
				juego->getMoto()->Subir(juego->getPersonaje());
			}
			else if (interaction_txt->Text == "Pulse [E] para bajarse de la moto") {
				juego->getMoto()->Bajar(juego->getPersonaje());
			}
			if (interaction_txt->Text == "Pulse [E] para obtener ADN" && juego->getHaConversado()) {
				juego->getPersonaje()->inventary->AgregarElemento(inventaryButtons, sprites[20], "ADN");
				juego->getADN()->setEstado(Estado::Inventariado);
				juego->HabilitarDialogo();
			}
			else if (interaction_txt->Text == "Pulse [E] para obtener CounterOmega"&& juego->getHaConversado()) {
				juego->getPersonaje()->inventary->AgregarElemento(inventaryButtons, sprites[21], "CounterOmega");
				juego->getCounter()->setEstado(Estado::Inventariado);
				juego->HabilitarDialogo();
			}
			else if (interaction_txt->Text == "Pulse [E] para obtener Quina"&& juego->getHaConversado()) {
				juego->getPersonaje()->inventary->AgregarElemento(inventaryButtons, sprites[22], "Quina");
				juego->getQuina()->setEstado(Estado::Inventariado);
				juego->HabilitarDialogo();
			}
		}
		if (e->KeyCode == Keys::Space) {
			juego->SiguienteDialogo(interaction_txt, buffer->Graphics, dialogos);
		}
		if (e->KeyCode == Keys::C) {
			juego->TirarItem(sprites[7]);
		}
		if (e->KeyCode == Keys::Escape) {
			/*menu = !menu;*/
			ActivarMenu(menu = !menu);
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
		if (e->KeyCode == Keys::Space && played) {
			PasarAlJuego();
		}
	}
	private: System::Void Play_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		Menu_pnl->Visible = false;
		this->interaction_txt->Location = System::Drawing::Point(569, 284);
		this->axWindowsMediaPlayer1->Focus();
		this->axWindowsMediaPlayer1->Ctlcontrols->play();
		this->axWindowsMediaPlayer1->Location = Point(0, 0);
		this->axWindowsMediaPlayer1->Size = System::Drawing::Size(712, 372);
		this->axWindowsMediaPlayer1->Visible = true;
		this->axWindowsMediaPlayer1->Enabled = true;
		timer2->Start();
		played = true;
	}
	private: System::Void Reanudar_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		ActivarMenu(false);
		menu = false;
	}
	private: System::Void Guardar_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		juego->GuardarPartida();
	}
	private: System::Void Salir_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		ActivarMenu(false);
		menu = false;
		timer1->Stop();
		Menu_pnl->Visible = true;
		played = false;
	}
};
}
