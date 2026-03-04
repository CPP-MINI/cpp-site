#pragma once

#include <cstring>
#include "Song.hpp"

class Playlist {
private:
    Song* songs;
    unsigned int capacity;
    unsigned int size;

public:
    Playlist(unsigned int capacity = 10);

    Playlist(const Playlist& other);
    Playlist& operator=(const Playlist& other);

    Playlist(Playlist&& other);
    Playlist& operator=(Playlist&& other);

    ~Playlist();

    void add_song(const Song& song);
    unsigned int get_size() const;
    void print() const;

private:
    void resize(unsigned int new_capacity);
};