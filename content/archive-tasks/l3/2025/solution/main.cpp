#include <iostream>
#include "mini_vector.hpp"

int main()
{
    // ETAP 1
    std::cout << "-----------------------------------ETAP 1-----------------------------------" << std::endl;

    MiniVector vec;
    // TODO: Zainicjalizuj wektor domyślnymi wartościami. Wypisz zawartość.
    vector_init(vec);
    vector_print(vec);
    vector_deallocate(vec);

    MiniVector filled_vec;
    // TODO: Zainicjalizuj wektor wartością "*". Wypisz zawartość.
    vector_init_fill(filled_vec);
    vector_print(filled_vec);
    vector_deallocate(filled_vec);

    // ETAP 2
    std::cout << "-----------------------------------ETAP 2-----------------------------------" << std::endl;

    MiniVector a_filled_vec;
    vector_init_fill(a_filled_vec, 4, 'a');
    vector_print(a_filled_vec);
    vector_print_memory(a_filled_vec, InfoPrintType::ADDRESS);
    vector_print_memory(a_filled_vec, InfoPrintType::VALUE);
    vector_expand(a_filled_vec, 8);
    vector_print(a_filled_vec);
    vector_print_memory(a_filled_vec, InfoPrintType::ADDRESS);
    vector_print_memory(a_filled_vec, InfoPrintType::VALUE);
    vector_shrink(a_filled_vec, 2);
    vector_shrink(a_filled_vec, 10);
    vector_shrink(a_filled_vec, 6);
    vector_print(a_filled_vec);
    vector_print_memory(a_filled_vec, InfoPrintType::ADDRESS);
    vector_print_memory(a_filled_vec, InfoPrintType::VALUE);
    vector_expand(a_filled_vec, 3);
    vector_expand(a_filled_vec, 10);
    vector_print_memory(a_filled_vec, InfoPrintType::ADDRESS);
    vector_print_memory(a_filled_vec, InfoPrintType::VALUE);
    // TODO:
    vector_deallocate(a_filled_vec);

    // ETAP 3
    std::cout << "-----------------------------------ETAP 3-----------------------------------" << std::endl;

    // TODO:
    vector_init_fill(filled_vec, 4, '0');
    // END TODO
    vector_add(filled_vec, 'H');
    vector_add(filled_vec, 'e');
    vector_add(filled_vec, 'l');
    vector_add(filled_vec, 'l');
    vector_add(filled_vec, 'o');
    vector_add(filled_vec, '!');
    vector_print(filled_vec);
    vector_print_memory(filled_vec, InfoPrintType::ADDRESS);
    vector_print_memory(filled_vec, InfoPrintType::VALUE);
    vector_clear(filled_vec);
    vector_print(filled_vec);
    vector_print_memory(filled_vec, InfoPrintType::ADDRESS);
    vector_print_memory(filled_vec, InfoPrintType::VALUE);
    // TODO:
    vector_deallocate(filled_vec);

    // ETAP 4
    std::cout << "-----------------------------------ETAP 4-----------------------------------" << std::endl;

    // TODO:
    vector_init(vec);
    // END TODO
    for (auto& character : "My First Vector in C++")
        if(character != '\0')
            vector_add(vec, character);
    vector_remove(vec, 25);
    vector_remove(vec, 4);
    vector_print(vec);
    vector_remove_occurrences(vec, ' ');
    vector_print(vec);
    vector_print_memory(vec);
    for (auto& character : "First Vector in")
        vector_remove_occurrences(vec, character);
    vector_print(vec);
    vector_print_memory(vec);
    vector_clear(vec);
    vector_print(vec);
    vector_print_memory(vec);
    // TODO:
    vector_deallocate(vec);
}