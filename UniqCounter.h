//
// Created by Павел Пономарев on 2019-05-24.
//

#ifndef VK_INTERNSHIP_UNIQCOUNTER_H
#define VK_INTERNSHIP_UNIQCOUNTER_H

#include <stdint.h>
#include <vector>

/**
 * Memory usage: no more than 32kb should be used.
 * Article: https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/40671.pdf
 */
class UniqCounter {
public:
    UniqCounter();
    ~UniqCounter() = default;
    void add(int);
    int get_uniq_num() const;
private:
    uint32_t hash(int32_t);
    uint8_t lowest_bit(uint32_t);
    double get_alpha() const;

    std::vector<uint8_t> mStorage;

    const static uint8_t BITS = 32;
    const static uint8_t POWER = 14;
    const static uint32_t REGISTER_SIZE = 1 << POWER;
    const static uint32_t PRIME = 0x01000193;
};

#endif //VK_INTERNSHIP_UNIQCOUNTER_H
