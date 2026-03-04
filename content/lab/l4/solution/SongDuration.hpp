#pragma once

#include <string>

class SongDuration {
private:
    unsigned int minutes;
    unsigned int seconds;

public:
    SongDuration(unsigned int minutes, unsigned int seconds) : minutes(minutes) {
        this->minutes += seconds / 60;
        this->seconds = seconds % 60;
    }

    unsigned int get_total_seconds() const {
        return minutes * 60 + seconds;
    }

    std::string get_formatted() const {
        return std::to_string(minutes) + "m " + std::to_string(seconds) + "s";
    }
};