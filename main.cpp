#include <iostream> // TODO: contineu songName parsing and format in testSite
#include <string>
#include <cctype>
#include <filesystem>
#include <vector>
#include <fstream>
#include <cstdlib> // EXIT_FAILURE

namespace fs = std::filesystem;                              

struct Song {
    std::string name;
    std::vector<std::string> lyric;
};

std::vector<Song> album;

bool creatAlbum(const std::string& folderPath);
size_t selectAlbumIndex();

void upperCase(std::string& text);
std::string getInput();
void errorMessage(const std::string& error);




void cleanStr(std::string& text) {
	if (text.empty()) return;

	while (true) {
		size_t index = text.find_first_of(".,'");
		if (index == std::string::npos) break;
		text.erase(index, 1);
	}

  upperCase(text);
}

std::string formatSongName(std::string& songName) {
	if (songName.empty()) return songName;

	while (true) {
		static size_t actPos = songName.length() + 1; // first loop, makes sure actPos won't mistakenly get matched

		size_t pos = songName.find_first_of(" .,-");
		if (pos == std::string::npos) break;

		if (pos == actPos + 1) { songName.erase(pos, 1); continue; }
		
		songName.replace(pos, 1, "_");
		actPos = pos;
	}

	for (char& c : songName) {
  c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }

	return songName;
}

int main() {
	if (!creatAlbum("./Songs-Asset")) return EXIT_FAILURE;

	std::cout << "Welcome to Singing-Battle-Bullshit!!!\n"; 

	size_t selectedIndex = selectAlbumIndex();
	

		std::cout << '\n';

		usrInp = getUSrInp();
		std::cout << frmtsongName_str(usrInp) << '\n'; // DEBUG
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

bool creatAlbum(const std::string& folderPath) {
	std::vector<std::string> songNames;
	std::vector<std::string> songLyric;

	fs::path targetdir(folderPath);
	std::ifstream filePath("");

	if (!fs::exists(targetdir) || !fs::is_directory(targetdir)) {
		errorMessage("Captsaiz, or anyone. You've fucked the Songs-Asset directionary");
		return false;
	}

	for (const auto& entry : fs::directory_iterator(targetdir)) {
		if (!entry.is_regular_file()) continue;

		std::ifstream filePath(entry.path());
		std::string adaptorLyric((std::istreambuf_iterator<char>(filePath)), std::istreambuf_iterator<char>());

		songNames.push_back(entry.path().stem().string());
		songLyric.push_back(adaptorLyric);
	}

	if (songNames.size() == 0) {
		errorMessage("No suitable file found");
		return false;
	}

	album.clear();
	album.resize(songNames.size());
	for (size_t i = 0; i < album.size(); ++i) {
		album[i].name = songNames[i];

		if (album[i].lyric.empty()) album[i].lyric.push_back("");
		size_t j = 0;
		for (std::string::iterator it = songLyric[i].begin(); it != songLyric[i].end(); ++it) {
			if (*it != '\n') { album[i].lyric[j] += *it; continue; }
			
			album[i].lyric.push_back("");
			++j;
		}
	}

	return true;
}

size_t selectAlbumIndex() {
	while (true) {
		std::cout << "Please select a song:\n";
		for (const auto& songName : album) std::cout << songName.name << '\n';

		std::string input = formatSongName(getInput());
		for (size_t i = 0; i < album.size(); ++i) {
			std::string formatted;
			if (input == album[i].name)
		}
	}
}

void upperCase(std::string& text) {
	for (char& c : text) {
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }
}

std::string getInput() {
	std::string input;
	std::getline(std::cin, input);
	return input;
}

void errorMessage(const std::string& error) {
	std::cerr << "ERROR: " << error << '\n';
}