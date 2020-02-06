#include "BitArray.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef BIT_ARRAY_ASSERTS
#   include <assert.h>
#endif

struct BitArray {
    size_t length_in_bits;
    uint8_t data[];
};

// Returns a byte where every bit except the one at bit_idx is unset.
// Does not check whether bit_idx is in the interval [0, 8).
// Index starts from the right.
// byte_set_at(2) = b00000100
static inline uint8_t byte_set_at(size_t const bit_idx) {
    return UINT8_C(1) << bit_idx;
}

static inline size_t bitarray_capacity_in_bytes(BitArray const* const ba) {
    return 1 + (ba->length_in_bits - 1) / 8;
}

// Returns a pointer to the byte following the last byte of the bitarray.
static inline uint8_t const* bitarray_end(BitArray const* const ba) {
    return ba->data + bitarray_capacity_in_bytes(ba);
}

// Returns the number of set bits in a byte.
static size_t byte_popcount(uint8_t const byte) {
#   ifdef BIT_ARRAY_USE_BUILTIN_POPCOUNT
    return __builtin_popcount(byte);
#   else
    // u8_popcount_table[byte] -> ammount of set bits in the byte.
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
    // static_assert(u8_popcount_table[3] == 2) (number 3 has two set bits).
    return u8_popcount_table[byte];
#   endif
}

BitArray* bitarray_new(size_t const length) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(length);
#   endif

    BitArray* const ba = calloc(
        1,
        sizeof(BitArray) +
            1 + (length - 1) / 8  // converting bits to bytes
    );

#   ifdef BIT_ARRAY_ASSERTS
    assert(ba);
#   endif

    if (ba) {
        ba->length_in_bits = length;
    }

    return ba;
}

void bitarray_delete(BitArray* const ba) {
    free(ba);
}

bool bitarray_check(BitArray const* const ba, size_t const bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < ba->length_in_bits);
#   endif

    return ba->data[bit_idx / 8] & byte_set_at(bit_idx % 8);
}

bool bitarray_all(BitArray const* const ba) {
    uint8_t const* const last_elem_it =
        ba->data + ((ba->length_in_bits - 1) / 8);

    // check the array byte by byte, excluding the last byte.
    for (uint8_t const* it = ba->data; it != last_elem_it; ++it) {
        if (*it != 0xFF) {
            return false;
        }
    }

    size_t const loose_bits_count = ba->length_in_bits % 8;

    if (loose_bits_count == 0) {
        return *last_elem_it == 0xFF;
    }

    // check the last byte, bit by bit.
    size_t const end_bit_idx = loose_bits_count - 1;
    for (size_t bit_idx = 0; bit_idx <= end_bit_idx; ++bit_idx) {
        if (!((*last_elem_it) & byte_set_at(bit_idx % 8))) {
            return false;
        }
    }

    return true;
}

bool bitarray_any(BitArray const* const ba) {
    uint8_t const* const end = bitarray_end(ba);

    for (uint8_t const* it = ba->data; it != end; ++it) {
        if (*it) {
            return true;
        }
    }

    return false;
}

bool bitarray_none(BitArray const* const ba) {
    uint8_t const* const end = bitarray_end(ba);

    for (uint8_t const* it = ba->data; it != end; ++it) {
        if (*it) {
            return false;
        }
    }

    return true;
}

size_t bitarray_popcount(BitArray const* const ba) {
    size_t total_popcount = 0;
    uint8_t const* const end = bitarray_end(ba);

    for (uint8_t const* it = ba->data; it != end; ++it) {
        total_popcount += byte_popcount(*it);
    }

    return total_popcount;
}

size_t bitarray_length(BitArray const* const ba) {
    return ba->length_in_bits;
}

size_t bitarray_capacity(BitArray const* const ba) {
    return bitarray_capacity_in_bytes(ba) * 8;
}

void bitarray_set(BitArray* const ba, size_t const bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < ba->length_in_bits);
#   endif

    ba->data[bit_idx / 8] |= byte_set_at(bit_idx % 8);
}

void bitarray_unset(BitArray* const ba, size_t const bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < ba->length_in_bits);
#   endif

    ba->data[bit_idx / 8] &= ~byte_set_at(bit_idx % 8);
}

void bitarray_fill(BitArray* const ba) {
    memset(ba->data, 0xFF, bitarray_capacity_in_bytes(ba));
}

void bitarray_clear(BitArray* const ba) {
    memset(ba->data, 0x00, bitarray_capacity_in_bytes(ba));
}

void bitarray_flip(BitArray* const ba, size_t const bit_idx) {
#   ifdef BIT_ARRAY_ASSERTS
    assert(bit_idx < ba->length_in_bits);
#   endif

    ba->data[bit_idx / 8] ^= byte_set_at(bit_idx % 8);
}
