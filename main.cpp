#include <iostream> // TODO: continue on the inging function now
#include <string>
#include <cctype>
#include <filesystem>
#include <vector>
#include <fstream>
#include <cstdlib> // EXIT_FAILURE
#include <algorithm>

namespace fs = std::filesystem;                              

struct Song {
    std::string name;
    std::vector<std::string> lyric;
};

std::vector<Song> album;

bool creatAlbum(const std::string& folderPath);
size_t selectAlbumIndex();

std::string formatSongName(std::string songName);
void upperCase(std::string& text);
bool isNumberOnly(const std::string& text);
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



int main() {
	if (!creatAlbum("./Songs-Asset")) return EXIT_FAILURE;

	std::cout << "Welcome to Singing-Battle-Bullshit!!!\n"; 

	size_t selectedIndex = selectAlbumIndex();

		// std::cout << '\n';

		// usrInp = getUSrInp();
		// std::cout << frmtsongName_str(usrInp) << '\n'; // DEBUG
		// cleanStr(usrInp);
		
		// for (size_t pointer = 0; pointer < listSongs.size(); ++pointer) {
		// 	std::string cmp_listSongs = listSongs[pointer];
		// 	cleanStr(cmp_listSongs);

		// 	if (!(usrInp == cmp_listSongs)) continue;

		// 	slct_song = listSongs[pointer];
		// 	break;
		// }

		// if (slct_song.empty()) {
		// 	errorMsg("No song file found!");
		// 	continue;
		// }

		
	
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
		for (size_t i = 0; i < album.size(); ++i) std::cout << (i + 1) << ". " <<  album[i].name << '\n';

		std::string input = getInput();
		std::string formattedInput = formatSongName(input);

		if (formattedInput.empty()) { errorMessage("Please enter a valid input"); continue;}

		if (isNumberOnly(formattedInput)) {
			size_t indexInput = static_cast<size_t>(std::stoull(formattedInput));
			if (indexInput <= album.size() && indexInput > 0) return indexInput - 1;

			errorMessage("Please enter a valid input");
			continue;
		}

		for (size_t i = 0; i < album.size(); ++i) {
			std::string formattedSongName = formatSongName(album[i].name);
			if (formattedInput == formattedSongName) return i;
		}

		errorMessage("Song not found");
	}
}

std::string formatSongName(std::string songName) {
	if (songName.empty()) return songName;

	for (char& c : songName) {
		if (c == '\n' || c == '\t' || c == '\r') c = ' ';
	}

	bool isSpaceFilledBeggining = (songName.front() == ' ');

	if (isSpaceFilledBeggining) { // Erase trailing spaces at the beggining
		size_t notSpace = songName.find_first_not_of(' ');
		
		if (notSpace != std::string::npos) songName.erase(0, notSpace);
		else {
			songName.clear();
			return songName;
		}
	}

	bool isSpaceFilledEnd = (songName.back() == ' ');

	if (isSpaceFilledEnd) { // Erase trailing spacex at the end
		size_t lastNonSpace = songName.find_last_not_of(' ');
		size_t lastSpaceTrail = songName.find_last_of(' ');
		if (lastNonSpace != std::string::npos && lastSpaceTrail != std::string::npos && lastSpaceTrail > lastNonSpace) {
			songName.erase(lastNonSpace + 1, lastSpaceTrail - lastNonSpace);
		} 
	}

	while (true) {
		static size_t actionedPos = songName.length() + 1; // first loop, makes sure actionedPos won't mistakenly get matched

		size_t pos = songName.find_first_of(" .,-");
		if (pos == std::string::npos) break;

		if (pos == actionedPos + 1) { songName.erase(pos, 1); continue; }
		
		songName.replace(pos, 1, "_");
		actionedPos = pos;
	}

	upperCase(songName);

	return songName;
}

void upperCase(std::string& text) {
	for (char& c : text) {
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }
}

bool isNumberOnly(const std::string& text) {
	return std::all_of(text.begin(), text.end(), [](unsigned char c) {
		return std::isdigit(c);
	});
}

std::string getInput() {
	std::string input;
	std::getline(std::cin, input);
	return input;
}

void errorMessage(const std::string& error) {
	std::cerr << "ERROR: " << error << '\n';
}