#include "MainFrame.h"

//#include "Pricing.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* mainPanel = new wxPanel(this);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	mainPanel->SetSizer(mainSizer);
	mainSizer->SetSizeHints(this);
}