#include "Program.hpp"

/*
Libraries used:

installing curl with vcpkg (i never want to do this again)
https://stackoverflow.com/questions/53861300/how-do-you-properly-install-libcurl-for-use-in-visual-studio-2017

fmt
1. cd to vckpg directory
2. vcpkg install fmg

nlohman::json (download json.hpp off github)
*/

int main(int argc, char** argv) {
	
	Program& Instance = Program::GetInstance();
	
	Instance.Run();

	return 0;
}