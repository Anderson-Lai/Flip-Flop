#include "MainFrame.h"

void MainFrame::FindFlips()
{
	_text->Clear();
	while (true)
	{
		auto now = Time::SecondsSinceEpoch();
		if (now % 60 == 0)
		{
			auto flips = Pricing::GetFlips();
			std::wstring result = L"";

			for (const auto& flip : flips)
			{
				result += flip.itemName;
			}
			_text->Clear();
			_text->AppendText(result);
			Time::Sleep(50'000);
		}
		else
		{
			_text->Clear();
			_text->AppendText(std::format("Current second: {}", Time::SecondsSinceEpoch() % 60));
			Time::Sleep(1'000);
		}
	}
}