#pragma once

template <typename K>
struct Hash {
    size_t operator()(const K& key) const {
        return std::hash<K>{}(key);
    }
};
