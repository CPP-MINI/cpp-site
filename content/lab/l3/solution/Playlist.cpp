#include <iostream>

#include "Playlist.hpp"

Playlist::Playlist(unsigned int initial_capacity) : capacity(initial_capacity), size(0) {
    songs = new Song[capacity];
}

Playlist::Playlist(const Playlist& other) : capacity(other.capacity), size(other.size) {
    songs = new Song[capacity];
    for (unsigned int i = 0; i < size; ++i) {
        songs[i] = other.songs[i];
    }
}

Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        delete[] songs;
        capacity = other.capacity;
        size = other.size;
        songs = new Song[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            songs[i] = other.songs[i];
        }
    }
    return *this;
}

Playlist::Playlist(Playlist&& other) : songs(other.songs), capacity(other.capacity), size(other.size) {
    other.songs = nullptr;
    other.capacity = 0;
    other.size = 0;
}

Playlist& Playlist::operator=(Playlist&& other) {
    if (this != &other) {
        delete[] songs;
        songs = other.songs;
        capacity = other.capacity;
        size = other.size;
        other.songs = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

Playlist::~Playlist() {
    delete[] songs;
}

void Playlist::resize(unsigned int new_capacity) {
    Song* new_songs = new Song[new_capacity];
    for (unsigned int i = 0; i < size; ++i) {
        new_songs[i] = songs[i];
    }
    songs = new_songs;
    capacity = new_capacity;
}

void Playlist::add_song(const Song& song) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    songs[size++] = song;
}

unsigned int Playlist::get_size() const {
    return size;
}

void Playlist::print() const {
    if (size == 0) {
        std::cout << "Playlist is empty" << std::endl;
    }
    for (unsigned int i = 0; i < size; ++i) {
        std::cout << i + 1 << ". ";
        songs[i].print();
    }
}