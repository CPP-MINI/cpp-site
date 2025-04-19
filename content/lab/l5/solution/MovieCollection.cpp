#include <algorithm>
#include <numeric>

#include "MovieCollection.hpp"

void MovieCollection::addMovie(const Movie<double>& movie) {
    if (!movie.getTitle().empty()) {
        char firstLetter = std::toupper(movie.getTitle()[0]);
        moviesByLetter[firstLetter].push_back(movie);
    }
}

std::vector<Movie<double>> MovieCollection::getAllMovies() const {
    std::vector<Movie<double>> result;
    for (const auto& [letter, movieList] : moviesByLetter) {
        result.insert(result.end(), movieList.begin(), movieList.end());
    }
    return result;
}

const std::map<char, std::vector<Movie<double>>>& MovieCollection::getMoviesByLetter() const {
    return moviesByLetter;
}

std::optional<Movie<double>> MovieCollection::findMovieWithAverageAbove(double threshold) const {
    struct HasAverageAbove {
        double threshold;
        explicit HasAverageAbove(double threshold) : threshold(threshold) {}

        bool operator()(const Movie<double>& movie) const {
            return movie.getAverageRating() > threshold;
        }
    };

    auto allMovies = getAllMovies();
    auto it = std::find_if(allMovies.begin(), allMovies.end(), HasAverageAbove(threshold));
    if (it != allMovies.end()) {
        return *it;
    }
    return std::nullopt;
}

void MovieCollection::sortMovies() {
    for (auto& [letter, movieList] : moviesByLetter) {
        std::sort(movieList.begin(), movieList.end());
    }
}

void MovieCollection::removeMoviesOlderThan(char letter, int yearThreshold) {
    struct IsOlderThan {
        int year;
        explicit IsOlderThan(int threshold) : year(threshold) {}
        bool operator()(const Movie<double>& movie) const {
            return movie.getYear() < year;
        }
    };

    letter = std::toupper(letter);

    auto it = moviesByLetter.find(letter);
    if (it != moviesByLetter.end()) {
        auto& movieList = it->second;
        movieList.erase(
                std::remove_if(movieList.begin(), movieList.end(), IsOlderThan(yearThreshold)),
                movieList.end()
        );
    }
}

double MovieCollection::getAverageTopRating() const {
    struct AddTopRating {
        double operator()(double sum, const Movie<double>& movie) const {
            return sum + movie.getTopRating();
        }
    };

    auto allMovies = getAllMovies();
    if (allMovies.empty()) {
        return 0.0;
    }
    double totalSum = std::accumulate(allMovies.begin(), allMovies.end(), 0.0, AddTopRating());
    return totalSum / allMovies.size();
}

std::vector<Movie<double>> MovieCollection::getMoviesByDirector(const std::string& directorName) const {
    struct DirectedBy {
        const std::string& name;
        explicit DirectedBy(const std::string& directorName) : name(directorName) {}
        bool operator()(const Movie<double>& movie) const {
            const auto& directorVariant = movie.getDirector();
            if (std::holds_alternative<typename Movie<double>::Director>(directorVariant)) {
                return std::get<typename Movie<double>::Director>(directorVariant).name == name;
            } else {
                return std::get<std::string>(directorVariant) == name;
            }
        }
    };

    auto allMovies = getAllMovies();
    std::vector<Movie<double>> result;
    std::copy_if(allMovies.begin(), allMovies.end(), std::back_inserter(result), DirectedBy(directorName));
    return result;
}

std::ostream& operator<<(std::ostream& os, const MovieCollection& collection) {
    const auto& data = collection.getMoviesByLetter();
    for (const auto& [letter, movieList] : data) {
        os << "=== " << letter << " ===\n";
        for (const auto& movie : movieList) {
            os << movie << "\n";
        }
    }
    return os;
}
