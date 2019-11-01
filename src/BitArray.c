#include "BitArray.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef BIT_ARRAY_ASSERTS
#   include <assert.h>
#endif

struct BitArray{
    size_t length_in_bits;
    uint8_t data[];
};

BitArray* bitarray_new(size_t length) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(length);
#   endif

    BitArray* const hopefully_not_null =
        calloc(1, sizeof(BitArray) + 1 + (length - 1) / 8);
    
#   ifdef BIT_ARRAY_ASSERTS
    assert(hopefully_not_null);
#   endif

    if (hopefully_not_null) {
        hopefully_not_null->length_in_bits = length;
    }

    return hopefully_not_null;
}

void bitarray_delete(BitArray* bitarray_ptr) {
    free(bitarray_ptr);
}

bool bitarray_check(BitArray const* bitarray_ptr, size_t bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < bitarray_ptr->length_in_bits);
#   endif

    return bitarray_ptr->data[bit_idx / 8] & (1U << (bit_idx % 8));
}

bool bitarray_all(BitArray const* bitarray_ptr) {
    uint8_t const* const last_elem_it =
        bitarray_ptr->data + ((bitarray_ptr->length_in_bits - 1) / 8);

    // check the array byte by byte, excluding the last byte.
    for (uint8_t const* it = bitarray_ptr->data; it != last_elem_it; ++it) {
        if (*it != 0xFF) {
            return false;
        }
    }

    size_t const loose_bits_count = bitarray_ptr->length_in_bits % 8;

    if (loose_bits_count == 0) {
        return *last_elem_it == 0xFF;
    }

    // check the last byte, bit by bit.
    size_t const end_bit_idx = loose_bits_count - 1;
    for (size_t bit_idx = 0; bit_idx <= end_bit_idx; ++bit_idx) {
        if (!((*last_elem_it) & (1U << (bit_idx % 8)))) {
            return false;
        }
    }

    return true;
}

bool bitarray_any(BitArray const* bitarray_ptr) {
    uint8_t const* const end =
        bitarray_ptr->data + (1 + (bitarray_ptr->length_in_bits - 1) / 8);

    for (uint8_t const* it = bitarray_ptr->data; it != end; ++it) {
        if (*it) {
            return true;
        }
    }
    return false;
}

bool bitarray_none(BitArray const* bitarray_ptr) {
    uint8_t const* const end =
        bitarray_ptr->data + (1 + (bitarray_ptr->length_in_bits - 1) / 8);

    for (uint8_t const* it = bitarray_ptr->data; it != end; ++it) {
        if (*it) {
            return false;
        }
    }
    return true;
}

size_t bitarray_popcount(BitArray const* bitarray_ptr) {
#   ifndef BIT_ARRAY_USE_BUILTIN_POPCOUNT
    // mapping: index -> ammount of set bits in the index.
    // static_assert(u8_popcount_table[3] == 2) (number 3 has two set bits).
    static size_t const u8_popcount_table[256] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    };
#   endif

    size_t popcount = 0;

    uint8_t const* const end =
        bitarray_ptr->data + (1 + (bitarray_ptr->length_in_bits - 1) / 8);

    for (uint8_t const* it = bitarray_ptr->data; it != end; ++it) {
#       ifdef BIT_ARRAY_USE_BUILTIN_POPCOUNT
        popcount += __builtin_popcount(*it);
#       else
        popcount += u8_popcount_table[*it];
#       endif
    }

    return popcount;
}

size_t bitarray_length(BitArray const* bitarray_ptr) {
    return bitarray_ptr->length_in_bits;
}

size_t bitarray_capacity(BitArray const* bitarray_ptr) {
    return (1 + (bitarray_ptr->length_in_bits - 1) / 8) * 8;
}

void bitarray_set(BitArray* bitarray_ptr, size_t bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < bitarray_ptr->length_in_bits);
#   endif

    bitarray_ptr->data[bit_idx / 8] |= (1U << (bit_idx % 8));
}

void bitarray_unset(BitArray* bitarray_ptr, size_t bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < bitarray_ptr->length_in_bits);
#   endif

    bitarray_ptr->data[bit_idx / 8] &= ~(1U << (bit_idx % 8));
}

void bitarray_fill(BitArray* bitarray_ptr) {
    memset(
        bitarray_ptr->data,
        0xFF,
        1 + (bitarray_ptr->length_in_bits - 1) / 8
    );
}

void bitarray_clear(BitArray* bitarray_ptr) {
    memset(
        bitarray_ptr->data,
        0x00,
        1 + (bitarray_ptr->length_in_bits - 1) / 8
    );
}

void bitarray_flip(BitArray* bitarray_ptr, size_t bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < bitarray_ptr->length_in_bits);
#   endif

    bitarray_ptr->data[bit_idx / 8] ^= (1U << (bit_idx % 8));
}
