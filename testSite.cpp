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
    std::string unformattedLyric;

    fs::path targetdir("./Songs-Asset");

    for (const auto& entry : fs::directory_iterator(targetdir)) {
        if (entry.is_regular_file()) {
            songNames.push_back(entry.path().stem();
        }
    }

    album.clear();
    album.resize(songNames.size());
    for (size_t i = 0; i < songNames.size(); ++i) {
        album[i] = Song mySong;
        album[i].name = songNames[i];
    }

    for (const auto& song : album) {
        std::cout << song << '\n';
    }

    // unformattedLyric = std::string(std::istreambuf_iterator<char>("./M.Sasuse - GG EZ"), std::istreambuf_iterator<char>());
    // std::cout << unformattedLyric << '\n';

}

int main() {
    creatAlbum();

    return 0;
}