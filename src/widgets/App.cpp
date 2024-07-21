#include "App.h"
#include "MainFrame.h"
#include "Windows.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Flip-Flop");
	mainFrame->SetClientSize(1000, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}