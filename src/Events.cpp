#include "MainFrame.h"
#include "wx/wx.h"
#include "Pricing.h"
#include <thread>

void MainFrame::HandleInitializationStart(wxCommandEvent& evt)
{
	std::thread([this]()
		{
			_text->AppendText("Starting application");
			Pricing::Start();
			_text->Clear();
			_text->AppendText("Done initialization");
		}).detach();
	evt.Skip();
}