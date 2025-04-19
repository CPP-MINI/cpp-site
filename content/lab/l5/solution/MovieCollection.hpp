#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <optional>

#include "Movie.hpp"

class MovieCollection {
private:
    std::map<char, std::vector<Movie<double>>> moviesByLetter;

public:
    void addMovie(const Movie<double>& movie);
    std::vector<Movie<double>> getAllMovies() const;
    const std::map<char, std::vector<Movie<double>>>& getMoviesByLetter() const;

    std::optional<Movie<double>> findMovieWithAverageAbove(double threshold) const;
    void sortMovies();
    void removeMoviesOlderThan(char letter, int yearThreshold);
    double getAverageTopRating() const;
    std::vector<Movie<double>> getMoviesByDirector(const std::string& directorName) const;
};

std::ostream& operator<<(std::ostream& os, const MovieCollection& collection);
