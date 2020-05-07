#pragma once
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;


class InventaryController
{
private:
	int espaciosInventario;

public:

	InventaryController() { 
		espaciosInventario = 7;
	}
	~InventaryController(){}

	void CrearInventario(Graphics ^g, Control::ControlCollection^ control) {
		array<Button^>^inventarySpace = gcnew array<Button^>(espaciosInventario);
		for (int i = 0; i < espaciosInventario; i++)
		{
			inventarySpace[i] = gcnew Button();
			inventarySpace[i]->Name = "button"+i;
			inventarySpace[i]->Size = System::Drawing::Size(50, 50);
			inventarySpace[i]->Text = "";
			inventarySpace[i]->BackColor = System::Drawing::Color::FromArgb(150, Color::Green);
			control->Add(inventarySpace[i]);
			if (i < espaciosInventario - 3) {
				inventarySpace[i]->BackColor = System::Drawing::Color::FromArgb(150, Color::Green);
				inventarySpace[i]->Location = System::Drawing::Point(g->VisibleClipBounds.Right - 55 - (i * 55), g->VisibleClipBounds.Bottom - 55);
			}
			else { 
				inventarySpace[i]->BackColor = System::Drawing::Color::FromArgb(150, Color::Aqua);
				inventarySpace[i]->Location = System::Drawing::Point(10 + ((i - (espaciosInventario - 3)) * 55), g->VisibleClipBounds.Bottom - 55); 
			}
		}
	}
	void AgregarItem(array<Button^>^invButtons, Bitmap ^sprite, String ^t) {
		for (int i = 0; i < espaciosInventario - 3; i++) {
			if (invButtons[i]->Text == ""){
				invButtons[i]->Text = " ";
				invButtons[i]->Name = t;	//Le pongo de nombre el nombre del Item para que despues identifique que item quiero seleccionar
				invButtons[i]->Image = sprite;
				break;
			}
		}
	}
	void AgregarElemento(array<Button^>^invButtons, Bitmap ^sprite, String ^t) {
		for (int i = espaciosInventario - 3; i < espaciosInventario; i++) {
			if (invButtons[i]->Text == "") {
				invButtons[i]->Text = " ";
				invButtons[i]->Name = t;	//Le pongo de nombre el nombre del Item para que despues identifique que item quiero seleccionar
				invButtons[i]->Image = sprite;
				break;
			}
		}
	}

	int getEspacios() { return espaciosInventario; }
};
