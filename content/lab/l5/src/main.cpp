#include <iostream>
#include <iomanip>

//#include "Movie.hpp"
//#include "MovieCollection.hpp"

int main() {

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "*************** PART 1 (Movie) ***************\n\n";
    /*
    Movie<double>::Director director1("Christopher Nolan", 2);
    Movie<double> movie1("Inception", 2010, director1, "Paprika and HSM3 rip-off");
    Movie<double> movie2("Interstellar", 2014, director1.name);

    std::cout << "Movie1 info:\n";
    std::cout << "Title: " << movie1.getTitle() << "\n";
    std::cout << "Year: " << movie1.getYear() << "\n";

    auto directorVariant = movie1.getDirector();
    if (std::holds_alternative<Movie<double>::Director>(directorVariant)) {
        auto director = std::get<Movie<double>::Director>(directorVariant);
        std::cout << "Director: " << director.name << " (Oscars: " << director.numberOfOscars << ")\n";
    } else {
        auto directorName = std::get<std::string>(directorVariant);
        std::cout << "Director: " << directorName << "\n";
    }

    if (movie1.getDescription()) {
        std::cout << "Description: " << *movie1.getDescription() << "\n";
    }

    std::cout << "\nMovie2 info:\n";
    std::cout << "Title: " << movie2.getTitle() << "\n";
    std::cout << "Year: " << movie2.getYear() << "\n";

    auto directorVariant2 = movie2.getDirector();
    if (std::holds_alternative<Movie<double>::Director>(directorVariant2)) {
        auto director = std::get<Movie<double>::Director>(directorVariant2);
        std::cout << "Director: " << director.name << " (Oscars: " << director.numberOfOscars << ")\n";
    } else {
        auto directorName = std::get<std::string>(directorVariant2);
        std::cout << "Director: " << directorName << "\n";
    }

    if (movie2.getDescription()) {
        std::cout << "Description: " << *movie2.getDescription() << "\n";
    }
    */
    std::cout << "\n*************** PART 2 (Movie - additional functionality) ***************\n\n";
    /*
    movie1 + 8.0 + 9.0 + 8.5;
    movie2 + 7.5 + 7.0 + 8.0;

    std::cout << "Movie1 Average Rating: " << movie1.getAverageRating() << "\n";
    std::cout << "Movie1 Top Rating: " << movie1.getTopRating() << "\n";

    std::cout << "Movie2 Average Rating: " << movie2.getAverageRating() << "\n";
    std::cout << "Movie2 Top Rating: " << movie2.getTopRating() << "\n";

    std::cout << "\nMovie1 operator<< output:\n";
    std::cout << movie1 << "\n";
    std::cout << "\nMovie2 operator<< output:\n";
    std::cout << movie2 << "\n\n";

    if (movie1 == movie2) {
        std::cout << "Movies are equal\n";
    } else {
        std::cout << "Movies are not equal\n";
    }
    if (movie1 < movie2) {
        std::cout << "Movie1 comes before Movie2\n";
    } else {
        std::cout << "Movie2 comes before Movie1\n";
    }
    */
    std::cout << "\n*************** PART 3 (MovieCollection) ***************\n\n";
    /*
    MovieCollection collection;

    Movie<double> dunkirk("Dunkirk", 2017, director1);
    dunkirk + 8.0 + 8.5 + 9.0;
    collection.addMovie(dunkirk);

    Movie<double> darkKnight("The Dark Knight", 2008, director1, "We live in a society.");
    darkKnight + 9.0 + 9.5 + 9.0;
    collection.addMovie(darkKnight);

    Movie<double> tenet("Tenet", 2020, director1.name, "Don't even try to understand it.");
    tenet + 7.0 + 7.5 + 8.0;
    collection.addMovie(tenet);

    Movie<double> grandBudapest("The Grand Budapest Hotel", 2014, Movie<double>::Director("Wes Anderson", 1), "Pastel chaos and fancy mustaches.");
    grandBudapest + 8.0 + 8.5 + 8.5;
    collection.addMovie(grandBudapest);

    Movie<double> isleOfDogs("Isle of Dogs", 2018, "Wes Anderson");
    isleOfDogs + 7.5 + 7.0 + 7.5;
    collection.addMovie(isleOfDogs);

    collection.addMovie(movie2);
    collection.addMovie(movie1);

    std::cout << "All movies in collection:\n";
    std::cout << collection << "\n";

    auto allMovies = collection.getAllMovies();
    std::cout << "Total number of movies: " << allMovies.size() << "\n\n";

    std::cout << "Movies under letter 'I':\n";
    auto it = collection.getMoviesByLetter().find('I');
    if (it != collection.getMoviesByLetter().end()) {
        for (const auto& movie : it->second) {
            std::cout << movie << "\n";
        }
    }
    */
    std::cout << "\n*************** PART 4 (MovieCollection  - additional functionality) ***************\n\n";
    /*
    auto foundMovie = collection.findMovieWithAverageAbove(8.0);
    if (foundMovie) {
        std::cout << "Found a movie with average rating above 8.0:\n" << *foundMovie << "\n";
    } else {
        std::cout << "No movie found with average rating above 8.0.\n";
    }

    collection.sortMovies();
    std::cout << "\nMovies after sorting:\n";
    std::cout << collection << "\n";

    collection.removeMoviesOlderThan('I', 2015);
    std::cout << "Movies after removing movies before 2015 under letter 'I':\n";
    std::cout << collection << "\n";

    double averageTop = collection.getAverageTopRating();
    std::cout << "Average of top ratings across all movies: " << averageTop << "\n";

    auto nolanMovies = collection.getMoviesByDirector("Christopher Nolan");
    std::cout << "\nMovies directed by Christopher Nolan:\n";
    for (const auto& movie : nolanMovies) {
        std::cout << movie << "\n";
    }

    auto andersonMovies = collection.getMoviesByDirector("Wes Anderson");
    std::cout << "\nMovies directed by Wes Anderson:\n";
    for (const auto& movie : andersonMovies) {
        std::cout << movie << "\n";
    }
    */
    return 0;
}
