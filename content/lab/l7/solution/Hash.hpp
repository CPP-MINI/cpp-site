#pragma once

template <typename K>
struct Hash {
    size_t operator()(const K& key) const {
        return std::hash<K>{}(key);
    }
};

// Part 4
template <>
struct Hash<int> {
    size_t operator()(const int& key) const {
        return key;
    }
};