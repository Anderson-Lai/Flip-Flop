#pragma once

#include <string>
#include <array>

class Program {
public:
	void Run();
	static void Error(const std::string& ErrorMessage);
	static void Println(const std::string& Message = "");

	template <typename Number>
	static std::string AddCommas(const Number number);
	static Program& GetInstance();
	static std::wstring ConvertToWString(const std::string& string);
	static std::string ConvertToString(const std::wstring& wstring);
	static void Sleep(unsigned long long milliseconds);
private:
	static void ReadFileData();
	static void UpdateFile();
	static void UpdateLbins();
	static void WriteToClipboard(const std::string& text);

	// singleton design for the Program object
	Program();
	~Program();
	
	// delete move and copy constructor, along with the = operator
	Program(const Program& copy) = delete;
	Program(Program&& move) = delete;
	Program& operator=(const Program& copy) = delete;
	Program& operator=(Program&& move) = delete;
};

// to fix templating
#include "ProgramTemplates.cpp"