#include "vectors.hpp"

namespace vectors {
    std::vector<int> reverse(std::vector<int>* old) {
        std::vector<int> reversed;

        if (old->size() == 0) {
            return {};
        }

        for (int i = old->size() - 1; i >= 0; --i) {
            reversed.push_back((*old)[i]);
        }

        return reversed;
    }

    int max(std::vector<int>* vec) {
        int max = (*vec)[0];

        for (int i = 1; i < vec->size(); ++i) {
            if (max < (*vec)[i]) {
                max = (*vec)[i];
            }
        }

        return max;
    }
}
