#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

struct Song {
    std::string name;
    std::vector<std::string> lyric;
};

std::vector<Song> album;

void upperCase(std::string& text) {
	for (char& c : text) {
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
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

    upperCase(songName);

	return songName;
}

bool creatAlbum(const std::string& folderPath) {
    std::vector<std::string> songNames;
    std::vector<std::string> songLyric;

    fs::path targetdir(folderPath);
    std::ifstream filePath("");

    if (!fs::exists(targetdir) || !fs::is_directory(targetdir)) {
        return false;
    }

    for (const auto& entry : fs::directory_iterator(targetdir)) {
        if (!entry.is_regular_file()) continue;

        std::ifstream filePath(entry.path());
        std::string adaptorLyric((std::istreambuf_iterator<char>(filePath)), std::istreambuf_iterator<char>());

        songNames.push_back(entry.path().stem().string());
        songLyric.push_back(adaptorLyric);
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

int main() {
    if (!creatAlbum("./Songs-Asset")) EXIT_FAILURE;

    std::cout << "type: ";
    std::string input;
    std::getline(std::cin, input);

    for (size_t i = 0; i < album.size(); ++i) {
        if (input == formatSongName(album[i].name)) break;
        break;
    }

    std::cout << album[0].name << '\n';
    return 0;
}