#include "Song.hpp"
#include <iostream>

int Song::count_songs = 0;

Song::Song() : title("Untitled"), artist("Unknown"), duration(0, 0) {
    Song::count_songs++;
}

Song::Song(const std::string& title, const SongDuration& duration, const std::string& artist)
        : title(title), artist(artist), duration(duration) {
    Song::count_songs++;
}

Song::Song(const std::string& title, unsigned int minutes, unsigned int seconds, const std::string& artist)
        : title(title), artist(artist), duration(minutes, seconds) {
    Song::count_songs++;
}

Song::~Song() {
    Song::count_songs--;
}

int Song::get_total_songs() { return Song::count_songs; }

void Song::print() const {
    std::cout << title << ", Artist: " << artist << " [" << duration.get_formatted() << "]" << std::endl;
}




