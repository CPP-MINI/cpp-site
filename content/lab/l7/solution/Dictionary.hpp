#pragma once

#include <iostream>
#include <string>
#include "Hash.hpp"

template<typename K, typename V>
struct KeyValuePair {
    K key;
    V value;
    KeyValuePair* next;

    KeyValuePair(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template<typename K, typename V, int Capacity = 128>
class Dictionary {
private:
    KeyValuePair<K, V>* table[Capacity];

    size_t hash(const K& key) const;

public:
    Dictionary();
    ~Dictionary();

    void insert(const K& key, const V& value);
    bool get(const K& key, V& value) const;
    bool remove(const K& key);
    V& operator[](const K& key);

    template <typename _K, typename _V>
    friend std::ostream& operator<<(std::ostream& os, const Dictionary<_K,_V>& d);

    Dictionary intersect(const Dictionary& other) const;

    template <typename _K, typename _V>
    friend Dictionary<_K, _V> operator+(const Dictionary<_K,_V>& d1, const Dictionary<_K,_V>& d2);

};

template<typename K, typename V, int Capacity>
size_t Dictionary<K, V, Capacity>::hash(const K& key) const {
    static Hash<K> hasher;
    return hasher(key) % Capacity;
}

template<typename K, typename V, int Capacity>
Dictionary<K, V, Capacity>::Dictionary() {
    for (int i = 0; i < Capacity; ++i) {
        table[i] = nullptr;
    }
}

template<typename K, typename V, int Capacity>
Dictionary<K, V, Capacity>::~Dictionary() {
    for (int i = 0; i < Capacity; ++i) {
        KeyValuePair<K, V>* entry = table[i];
        while (entry) {
            KeyValuePair<K, V>* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
}

template<typename K, typename V, int Capacity>
void Dictionary<K, V, Capacity>::insert(const K& key, const V& value) {
    size_t index = hash(key);
    KeyValuePair<K, V>* prev = nullptr;
    KeyValuePair<K, V>* entry = table[index];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        entry = new KeyValuePair<K, V>(key, value);
        if (prev == nullptr) {
            table[index] = entry;
        }
        else {
            prev->next = entry;
        }
    }
    else {
        entry->value = value;
    }
}

template<typename K, typename V, int Capacity>
bool Dictionary<K, V, Capacity>::get(const K& key, V& value) const {
    size_t index = hash(key);
    KeyValuePair<K, V>* entry = table[index];

    while (entry != nullptr) {
        if (entry->key == key) {
            value = entry->value;
            return true;
        }
        entry = entry->next;
    }
    // Part 7
    throw std::runtime_error("Trying to get non-existing value!");
    return false;
}

template<typename K, typename V, int Capacity>
bool Dictionary<K, V, Capacity>::remove(const K& key) {
    size_t index = hash(key);
    KeyValuePair<K, V>* prev = nullptr;
    KeyValuePair<K, V>* entry = table[index];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {

        throw std::runtime_error("Trying to delete non-existing value!");
        return false;
    }
    else {
        if (prev == nullptr) {
            table[index] = entry->next;
        }
        else {
            prev->next = entry->next;
        }
        delete entry;
        return true;
    }
}

template<typename K, typename V, int Capacity>
V& Dictionary<K, V, Capacity>::operator[](const K& key) {
    size_t index = hash(key);
    KeyValuePair<K, V>* entry = table[index];

    while (entry != nullptr) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }

    insert(key, V());

    index = hash(key);
    entry = table[index];
    while (entry != nullptr) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }
    // This point should never be reached
    throw std::runtime_error("Insertion failed in operator[]");
}

template<typename K, typename V, int Capacity>
std::ostream& operator<<(std::ostream& os, const Dictionary<K, V>& d)
{
    for (int i = 0; i < Capacity; ++i) {
        KeyValuePair<K, V>* entry = d.table[i];
        while (entry != nullptr) {
            os << entry->key << ": " << entry->value << std::endl;
            entry = entry->next;
        }
    }
    return os;
}

template<typename K, typename V, int Capacity>
inline Dictionary<K, V, Capacity> Dictionary<K, V, Capacity>::intersect(const Dictionary& other) const
{
    Dictionary d;
    for (int i = 0; i < Capacity; ++i) {
        KeyValuePair<K, V>* entry = other.table[i];
        while (entry) {
            V value;
            // Part 7
            try {
                if (get(entry->key, value))
                    d.insert(entry->key, value);
            }
            catch (std::exception &e){
                std::cout << "Handled exception: " << e.what() << std::endl;
            }
            entry = entry->next;
        }
    }
    return d;
}

template<typename K, typename V, int Capacity>
Dictionary<K, V, Capacity> operator+(const Dictionary<K, V>& d1, const Dictionary<K, V>& d2)
{
    Dictionary<K, V> d;
    for (int i = 0; i < d1.TABLE_SIZE; ++i) {
        KeyValuePair<K, V>* entry = d1.table[i];
        while (entry) {
            d.insert(entry->key, entry->value);
            entry = entry->next;
        }
    }
    for (int i = 0; i < d2.TABLE_SIZE; ++i) {
        KeyValuePair<K, V>* entry = d2.table[i];
        while (entry) {
            d.insert(entry->key, entry->value);
            entry = entry->next;
        }
    }
    return d;
}