#pragma once

#include <string>
#include "SongDuration.hpp"

class Song {
private:
    std::string title;
    std::string artist;
    SongDuration duration;

public:
    static unsigned int count_songs;

    Song();
    Song(const std::string& title, const SongDuration& duration, const std::string& artist = "Unknown");
    Song(const std::string& title, unsigned int minutes, unsigned int seconds = 0, const std::string& artist = "Unknown");
    ~Song();

    const std::string& get_title() const { return this->title; }
    const std::string& get_artist() const { return this->artist; }
    const unsigned int get_duration() const { return this->duration.get_total_seconds(); }

    void set_title(const std::string& title) { this->title = title; }
    void set_artist(const std::string& artist) { this->artist = artist; }
    void set_duration(const unsigned int seconds) { duration = SongDuration(0, seconds); }

    void print() const;

    static unsigned int get_total_songs();
};
