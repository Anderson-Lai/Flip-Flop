#include "Program.hpp"

#include <Windows.h>
#include <codecvt>
#include <iostream>
#include <thread>
#include "curl/curl.h"

void Program::Error(const std::string& ErrorMessage)
{
	std::cerr << ErrorMessage << "\n";
}

void Program::Println(const std::string& Message)
{
	std::cout << Message << "\n";
}

Program& Program::GetInstance()
{
	static Program instance;
	return instance;
}

void Program::WriteToClipboard(const std::string& text)
{
	if (!OpenClipboard(nullptr))
	{
		Program::Error("Could not open clipboard");
		return;
	}
	EmptyClipboard();

	size_t bufferSize = text.size() + 1;

	// malloc global memory (memory that can be accessed by any program) to hold clipboard text
	HGLOBAL clipboardMemory = GlobalAlloc(GMEM_MOVEABLE, (bufferSize) * sizeof(char));
	if (clipboardMemory == nullptr)
	{
		CloseClipboard();
		return;
	}

	// type cast the global memory to a char* pointer
	// lock the memory since ALL programs can access this memory
	char* clipboardText = (char*)GlobalLock(clipboardMemory);

	// checks if the lock failed
	if (!clipboardText)
	{
		GlobalFree(clipboardMemory);
		CloseClipboard();
		return;
	}

	// copy text to buffer
	if (strcpy_s(clipboardText, (bufferSize), text.c_str()) != 0)
	{
		Program::Error("Error copying text to clipboardText buffer");
		GlobalFree(clipboardText);
		CloseClipboard();
		return;
	}

	GlobalUnlock(clipboardMemory);
	// ownership of clipboardMemory is transferred
	SetClipboardData(CF_TEXT, clipboardText);

	// clean up
	CloseClipboard();
}

std::wstring Program::ConvertToWString(const std::string& string)
{
	const int wStringSize = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, nullptr, 0);

	std::unique_ptr<wchar_t[]> result = std::make_unique<wchar_t[]>(wStringSize);
	MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, result.get(), wStringSize);

	std::wstring str(result.get());
	return str;
}

std::string Program::ConvertToString(const std::wstring& wstring)
{
	const int stringSize = WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), -1, nullptr, 0, nullptr, nullptr);

	std::string result(stringSize - 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), -1, &result[0], stringSize, nullptr, nullptr);

	return result;
}

void Program::Sleep(unsigned long long milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

Program::Program()
{
	// initialize curl once when program starts
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

Program::~Program()
{
	// cleanup at end of program automatically
	curl_global_cleanup();
}