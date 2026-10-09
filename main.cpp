#include <iostream> // TODO: continue on the inging function now
#include <string>
#include <cctype>
#include <filesystem>
#include <vector>
#include <fstream>
#include <cstdlib> // EXIT_FAILURE
#include <algorithm>
#include <thread>
#include <chrono>


namespace fs = std::filesystem;                              

struct Song {
    std::string name;
    std::vector<std::string> lyric;
};

std::vector<Song> album;


bool creatAlbum(const std::string& folderPath);
size_t selectAlbumIndex();
void startSingingBattle(const size_t& albumIndex);

std::string formatSongName(std::string songName);
std::string formatLyric(std::string& text);
void cleanUnwantedChar(std::string& text);
void upperCase(std::string& text);
bool isNumberOnly(const std::string& text);
std::string getInput();
void errorMessage(const std::string& error);


int main() {

	while (true) {
		if (!creatAlbum("./Songs-Asset")) return EXIT_FAILURE;

		std::cout << '\n';
		std::cout << "Welcome to Singing-Battle-Bullshit!!!\n"; 

		startSingingBattle(selectAlbumIndex());

		std::this_thread::sleep_for(std::chrono::seconds(3));
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

void startSingingBattle(const size_t& albumIndex) {
	std::vector<std::string> enemyLyrics;
	std::vector<std::string> playerLyrics;

	for (size_t i = 0; i < album[albumIndex].lyric.size(); ++i) {
		if (i % 2 == 0) enemyLyrics.push_back(album[albumIndex].lyric[i]);
		else playerLyrics.push_back(formatLyric(album[albumIndex].lyric[i]));
	}

	bool playerWon;
	std::string playerInput;

	for (size_t i = 0; i < enemyLyrics.size(); ++i) {
		std::cout << enemyLyrics[i] << '\n';

		if (!(i < playerLyrics.size())) { playerWon = true; break; }

		playerInput = getInput();
		playerInput = formatLyric(playerInput);

		if (playerInput != playerLyrics[i]) { playerWon = false; break; }

		if (i == playerLyrics.size() - 1) { playerWon = true; break; }

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::cout << '\n';

	if (playerWon) {
		
		std::cout << "Wow amazing\n";
		std::cout << "You won :D\n";
		return;
	}

	std::cout << "Beep boom fuck uo wrong lyric\n";
	std::cout << "Try again :(\n";
}

std::string formatSongName(std::string songName) {
	if (songName.empty()) return songName;

	cleanUnwantedChar(songName);
		
	bool lastWasSeperator = false;

	auto it = std::remove_if(songName.begin(), songName.end(), [&](char& c) {
		if (c == ' ' || c == '.' || c == ',' || c == '-' || c == '\'') {

			if (lastWasSeperator) return true;

			c = '_';
			lastWasSeperator = true;
			return false;
		}

		lastWasSeperator = false;
		return false;
	});

	songName.erase(it, songName.end());

	upperCase(songName);

	return songName;
}

std::string formatLyric(std::string& text) {
	if (text.empty()) return text;

	cleanUnwantedChar(text);

	text.erase(std::remove_if(text.begin(), text.end(), [](char c) {
		return c == '.' || c == ',' || c == '\'';
	}), text.end());

  upperCase(text);

	return text;
}

void cleanUnwantedChar(std::string& text) {
	for (char& c : text) {
		if (c == '\n' || c == '\t' || c == '\r') c = ' ';
	}

	bool isSpaceFilledBeggining = (text.front() == ' ');

	if (isSpaceFilledBeggining) { // Erase trailing spaces at the beggining
		size_t notSpace = text.find_first_not_of(' ');
		
		if (notSpace != std::string::npos) text.erase(0, notSpace);
		else {
			text.clear();
			return;
		}
	}

	bool isSpaceFilledEnd = (text.back() == ' ');

	if (isSpaceFilledEnd) { // Erase trailing spaces at the end
		size_t lastNonSpace = text.find_last_not_of(' ');
		size_t lastSpaceTrail = text.find_last_of(' ');
		if (lastNonSpace != std::string::npos && lastSpaceTrail != std::string::npos && lastSpaceTrail > lastNonSpace) {
			text.erase(lastNonSpace + 1, lastSpaceTrail - lastNonSpace);
		}  
	}
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