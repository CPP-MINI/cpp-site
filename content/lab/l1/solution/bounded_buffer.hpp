#ifndef _BOUNDED_BUFFER_HPP
#define _BOUNDED_BUFFER_HPP

#include <string>
#include <vector>

struct bounded_buffer {
    std::vector<std::string> buffer;
    int capacity; // Rozmiar bufora, przy którym należy wykonać wypisanie
};

// Zwróć ilośc zgromadzonych linii w buforze
int buffer_size(const bounded_buffer* buffer);

// Zwróć maksymalny rozmiar bufora
int buffer_capacity(const bounded_buffer* buffer);

// Wypisz zawartośc bufora na standardowe wyjście i zwolnij zawartość bufora
void flush_buffer(bounded_buffer* buffer);

// Dodaj linie do bufora. Jeśli limit bufora został osiągniety, zwróć false i nie modyfikuj zawartości
bool add_to_buffer(bounded_buffer* buffer, std::string line);

#endif