#pragma once

#include "wx/wx.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void HandleInitializationStart(wxCommandEvent& evt);
	void FindFlips();
private:
	wxTextCtrl* _text;
};