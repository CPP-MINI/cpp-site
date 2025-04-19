#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <variant>
#include <list>

template<typename RatingType>
class Movie {
public:
    struct Director {
        std::string name;
        int numberOfOscars;
        Director(const std::string& name_, int numberOfOscars) : name(name_), numberOfOscars(numberOfOscars) {}
    };

private:
    std::string title;
    int year;
    std::variant<Director, std::string> director;
    std::optional<std::string> description;
    std::list<RatingType> ratings;

public:
    explicit Movie(const std::string& title, int year, const std::variant<Director, std::string>& director,
                   const std::optional<std::string>& description = std::nullopt)
                   : title(title), year(year), director(director), description(description) {}

    const std::string& getTitle() const { return title; }
    int getYear() const { return year; }
    const std::optional<std::string>& getDescription() const { return description; }
    const std::variant<Director, std::string>& getDirector() const { return director; }
    const std::list<RatingType>& getRatings() const { return ratings; }

    bool operator<(const Movie& other) const {
        if (title == other.title) {
            return year < other.year;
        }
        return title < other.title;
    }

    bool operator==(const Movie& other) const {
        return title == other.title && year == other.year;
    }

    Movie& operator+(const RatingType& rating) {
        ratings.push_back(rating);
        return *this;
    }

    RatingType getAverageRating() const {
        if (ratings.empty()) {
            return RatingType(0);
        }
        RatingType sum(0);
        for (const auto& rating : ratings) {
            sum += rating;
        }
        return sum / ratings.size();
    }

    RatingType getTopRating() const {
        if (ratings.empty()) {
            return RatingType(0);
        }
        auto it = ratings.begin();
        RatingType top = *it;
        for (; it != ratings.end(); ++it) {
            if (*it > top) {
                top = *it;
            }
        }
        return top;
    }
};

template<class RatingType>
std::ostream& operator<<(std::ostream& os, const Movie<RatingType>& movie) {
    os << movie.getTitle() << " (" << movie.getYear() << "), ";

    if (std::holds_alternative<typename Movie<RatingType>::Director>(movie.getDirector())) {
        const auto& director = std::get<typename Movie<RatingType>::Director>(movie.getDirector());
        os << "Director: " << director.name << " (Oscars: " << director.numberOfOscars << "), ";
    } else {
        os << "Director: " << std::get<std::string>(movie.getDirector()) << ", ";
    }

    os << "Avg: " << movie.getAverageRating() << ", Top: " << movie.getTopRating();

    if (movie.getDescription()) {
        os << "\nDescription: " << *movie.getDescription();
    }

    return os;
}