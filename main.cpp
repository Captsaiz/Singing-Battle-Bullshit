#include <iostream>
#include <string>
#include <cctype>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void errorMsg(const std::string& error) {
	std::cerr << "ERROR: " << error << '\n';
}

std::string getUSrInp() {
	std::string inp;
	std::getline(std::cin, inp);
	return inp;
}

void cleanStr(std::string& msg) {
	if (msg.empty()) return;

	while (true) {
		size_t pos = msg.find_first_of(".,'");
		if (pos == std::string::npos) break;
		msg.erase(pos, 1);
	}

  for (char& c : msg) {
  c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }
}

std::string frmtSngNme_str(std::string& sngNme) {
	if (sngNme.empty()) return sngNme;

	while (true) {
		static size_t actPos = sngNme.length() + 1; // first loop, makes sure actPos won't mistakenly get matched

		size_t pos = sngNme.find_first_of(" .,-");
		if (pos == std::string::npos) break;

		if (pos == actPos + 1) { sngNme.erase(pos, 1); continue; }
		
		sngNme.replace(pos, 1, "_");
		actPos = pos;
	}

	for (char& c : sngNme) {
  c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }

	return sngNme;
}

int main() {
	std::string usrInp;
	std::vector<std::string> listSongs;
	std::string slct_song;

  fs::path targetdir("./Songs-Asset");
	if (!fs::exists(targetdir) || !fs::is_directory(targetdir)) {
			errorMsg("Captsaiz, or anyone. You've fucked the Songs-Asset directionary");
			return 1;
	}

	std::cout << "Welcome to Singing-Battle-Bullshit!!!\n"; 

	for (const auto& entry : fs::directory_iterator(targetdir)) {
		if (entry.is_regular_file()) {
			listSongs.push_back(entry.path().stem().string());
		}
	}

	while (true) {
		usrInp = "";
		slct_song = "";

		std::cout << '\n';
		std::cout << "Please select a song:\n";

		for (size_t i = 0; i < listSongs.size(); ++i) {
			std::cout << "\u00B7 " << listSongs[i] << '\n';
		}

		std::cout << '\n';

		usrInp = getUSrInp();
		std::cout << frmtSngNme_str(usrInp) << '\n'; // DEBUG
		cleanStr(usrInp);
		
		for (size_t pointer = 0; pointer < listSongs.size(); ++pointer) {
			std::string cmp_listSongs = listSongs[pointer];
			cleanStr(cmp_listSongs);

			if (!(usrInp == cmp_listSongs)) continue;

			slct_song = listSongs[pointer];
			break;
		}

		if (slct_song.empty()) {
			errorMsg("No song file found!");
			continue;
		}

		
	}
	
	return 0;
}