#ifndef CPP23_MINI_VECTOR_HPP
#define CPP23_MINI_VECTOR_HPP

static constexpr int INIT_CAPACITY = 4;

enum class InfoPrintType {
    ADDRESS, VALUE
};

struct MiniVector {
    char* elements = nullptr;
    int capacity = INIT_CAPACITY;
    int size = 0;
};

// Adding/removing element operations
void vector_add(MiniVector& v, char el);
void vector_remove(MiniVector& v, int pos);
void vector_remove_occurrences(MiniVector& v, char c);

// Printing vector values/memory operations
void vector_print(const MiniVector& v);
void vector_print_memory(const MiniVector& v, InfoPrintType ipt = InfoPrintType::VALUE);

// Allocating new memory/deallocating operations
void vector_init(MiniVector& v, int capacity = INIT_CAPACITY);
void vector_init_fill(MiniVector& v, int capacity = INIT_CAPACITY, char init_character = '*');
void vector_shrink(MiniVector& v, int new_capacity);
void vector_expand(MiniVector& v, int new_capacity);
void vector_clear(MiniVector& v);
void vector_deallocate(MiniVector& v);


#endif //CPP23_MINI_VECTOR_HPP
