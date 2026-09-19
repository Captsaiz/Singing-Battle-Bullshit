#include <iostream>
#include <string>
#include <cctype>
#include <filesystem>

namespace fs = std::filesystem;

void errorMsg(const std::string& error) {
	std::cerr << "ERROR: " << error << '\n';
}

void tfm_upperStr(std::string& msg) {
  for (char& c : msg) {
  c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }
}

int main() {
  fs::path targetdir("./Songs-Asset");
	if (!fs::exists(targetdir) || !fs::is_directory(targetdir)) {
			errorMsg("Captsaiz, or anyone. You've fucked the Songs-Asset directionary");
			return 1;
	}

	std::cout << "Welcome to Singing-Battle-Bullshit!!!\n\n";
	std::cout << "Please select a song:\n";

	for (const auto& entry : fs::directory_iterator(targetdir)) {
		if (entry.is_regular_file()) {
			std::cout << "\u00B7 " << entry.path().stem().string() << '\n';
		}
	}

	return 0;
}