//
// Created by Павел Пономарев on 2019-05-23.
//

#include "UniqCounter.h"
#include <cstddef>
#include <algorithm>
#include <cmath>

UniqCounter::UniqCounter() {
    mStorage.resize(REGISTER_SIZE, 0);
}

int UniqCounter::get_uniq_num() const {
    double power_sum = 0;
    uint32_t v = 0;
    for (auto cell : mStorage) {
        v += cell == 0 ? 1 : 0;
        power_sum += 1.0 / (1 << cell);
    }
    double alpha = get_alpha();
    double e = alpha * REGISTER_SIZE * REGISTER_SIZE / power_sum;
    if (e <= static_cast<double>(5 * REGISTER_SIZE) / 2) {
        if (v != 0) {
            return static_cast<int> (REGISTER_SIZE *
                                     std::log(static_cast<double>(REGISTER_SIZE) / v));
        } else {
            return static_cast<int>(e);
        }
    } else if (e <= static_cast<double>(1 << 31) / 15) {
        return static_cast<int>(e);
    }
    return static_cast<int>(-2 * static_cast<double> (1 << 31) *
                            std::log((1 - (e / (1 << 31)) / 2)));
}

void UniqCounter::add(int x) {
    auto hx = hash(x);
    auto id = hx & (REGISTER_SIZE - 1);
    auto w = (hx >> POWER) | (1 << (BITS - POWER));
    mStorage[id] = std::max(mStorage[id], lowest_bit(w));
}

uint32_t UniqCounter::hash(int32_t num) {
    num = ((num >> 16) ^ num) * PRIME;
    num = ((num >> 16) ^ num) * PRIME;
    num = ((num >> 16) ^ num);
    return static_cast<uint32_t>(num);
}

uint8_t UniqCounter::lowest_bit(uint32_t number) {
    if (number == 0) {
        return BITS;
    }
    return static_cast<uint8_t>(log2(number & -number) + 1);
}

/**
 * REGISTER_SIZE can be changed due to specific goals, this method will
 * calculate alpha for different REGISTER_SIZE
 */

double UniqCounter::get_alpha() const {
    switch (REGISTER_SIZE) {
        case 16:
            return 0.673;
        case 32:
            return 0.697;
        case 64:
            return 0.709;
        default:
            return 0.7213 / (1 + 1.079 / REGISTER_SIZE);
    }
}

