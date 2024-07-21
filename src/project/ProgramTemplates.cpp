#pragma once
#include "Program.hpp"
#include <string>
#include <sstream>
#include <locale>

template <typename Number>
std::string Program::AddCommas(const Number number)
{
	std::stringstream stream;
	stream.imbue(std::locale(""));

	stream << number;
	return stream.str();
}