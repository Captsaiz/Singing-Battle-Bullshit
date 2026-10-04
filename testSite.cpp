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


void creatAlbum() {
    std::vector<std::string> songNames;
    std::vector<std::string> songLyric;

    fs::path targetdir("./Songs-Asset");
    std::ifstream filePath("");

    for (const auto& entry : fs::directory_iterator(targetdir)) {
        
        if (entry.is_regular_file()) {
            std::ifstream filePath(entry.path());
            std::string adaptorLyric((std::istreambuf_iterator<char>(filePath)), std::istreambuf_iterator<char>());

            songNames.push_back(entry.path().stem().string());
            songLyric.push_back(adaptorLyric);
        }
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

    std::cout << album[0].name << '\n'; // DEBUG

    for (size_t i = 0; i < album[0].lyric.size(); ++i) { // DEBUG
        std::cout << album[0].lyric[i] << '\n';
    }

    // TODO: clean and put this in main.cpp
}

int main() {
    creatAlbum();

    return 0;
}