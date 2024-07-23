#include "MainFrame.h"

#include "Pricing.h"
#include "Time.hpp"
#include <thread>
#include <format>
#include <string>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* mainPanel = new wxPanel(this);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxButton* startInitialization = new wxButton(mainPanel, wxID_ANY, "Click to start initialization", wxDefaultPosition,
		wxSize(-1, 150));
	_text = new wxTextCtrl(mainPanel, wxID_ANY, "", wxDefaultPosition, wxSize(500, 300));

	startInitialization->Bind(wxEVT_BUTTON, &MainFrame::HandleInitializationStart, this);

	wxSizerFlags flag = wxSizerFlags().CenterHorizontal().Border(wxALL, 25);
	
	mainSizer->Add(_text, flag);
	mainSizer->Add(startInitialization, flag);
	
	std::thread update(FindFlips);
	update.detach();

	mainPanel->SetSizer(mainSizer);
	mainSizer->SetSizeHints(this);
}