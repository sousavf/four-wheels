// TrackEditor.cpp : main project file.

#include "stdafx.h"
#include "EditorPistas.h"

using namespace TrackEditor;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1(6, 6));
	return 0;
}
