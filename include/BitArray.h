#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

/**
 * A compact, fixed size heap array of bit values.
 */
typedef struct BitArray BitArray;

/**
 * Constructs an empty bitarray.
 * @param length the length, in bits, of the bitarray.
 * <b>The length must be positive</b>.
 * @return a pointer to the constructed bitarray.
 * If an error occurs allocating memory, NULL may be returned.
 */
BitArray* bitarray_new(size_t length);

/**
 * Deallocates the storage used by the bitarray.
 * @param bitarray_ptr a pointer to the bitarray.
 */
void bitarray_delete(BitArray* bitarray_ptr);

/**
 * Checks if the bit at the index bit_idx is set.
 * Does not check whether bit_idx is a valid index in the bitarray.
 * @param bitarray_ptr a pointer to the bitarray.
 * @param bit_idx the index of the bit to be checked.
 * bit_idx must be valid in [0, bitarray_length(bitarray_ptr)).
 * @return true if the bit is set, false otherwise.
 */
bool bitarray_check(BitArray const* bitarray_ptr, size_t bit_idx);

/**
 * Checks if all the bits in the bitarray are set.
 * @param bitarray_ptr a pointer to the bitarray.
 * @return true if all the bits are set, false otherwise.
 */
bool bitarray_all(BitArray const* bitarray_ptr);

/**
 * Checks if any bit in the bitarray is set.
 * @param bitarray_ptr a pointer to the bitarray.
 * @return true if any bit is set, false otherwise.
 */
bool bitarray_any(BitArray const* bitarray_ptr);

/**
 * Checks if all the bits in the bitarray are unset.
 * @param bitarray_ptr a pointer to the bitarray.
 * @return true if all the bits are unset, false otherwise.
 */
bool bitarray_none(BitArray const* bitarray_ptr);

/**
 * Returns the number of set bits.
 * @param bitarray_ptr a pointer to the bitarray.
 * @return the number of set bits.
 */
size_t bitarray_popcount(BitArray const* bitarray_ptr);

/**
 * Returns the ammount of bits in the bitarray.
 * @param bitarray_ptr a pointer to the bitarray.
 * @return the length of the bitarray.
 */
size_t bitarray_length(BitArray const* bitarray_ptr);

/**
 * Returns the maximum ammount of bits the bitarray can store.
 * @param bitarray_ptr a pointer to the bitarray.
 * @return the capacity of the bitarray.
 */
size_t bitarray_capacity(BitArray const* bitarray_ptr);

/**
 * Sets the bit at the index bit_idx.
 * Does not check whether bit_idx is a valid index in the bitarray.
 * @param bitarray_ptr a pointer to the bitarray.
 * @param bit_idx the index of the bit to be set.
 * bit_idx must be valid in 0 <= bit_idx < bitarray_length(bitarray_ptr).
 */
void bitarray_set(BitArray* bitarray_ptr, size_t bit_idx);
/**
 * Unsets the bit at the index bit_idx.
 * Does not check whether bit_idx is a valid index in the bitarray.
 * @param bitarray_ptr a pointer to the bitarray.
 * @param bit_idx the index of the bit to be unset.
 * bit_idx must be valid in 0 <= bit_idx < bitarray_length(bitarray_ptr).
 */
void bitarray_unset(BitArray* bitarray_ptr, size_t bit_idx);

/**
 * Sets every bit.
 * @param bitarray_ptr a pointer to the bitarray.
 */
void bitarray_fill(BitArray* bitarray_ptr);

/**
 * Unsets every bit.
 * @param bitarray_ptr a pointer to the bitarray.
 */
void bitarray_clear(BitArray* bitarray_ptr);

/**
 * Flips the bit at the index bit_idx.
 * If the bit is set, it's unset. If the bit is unset, it's set.
 * Does not check whether bit_idx is a valid index in the bitarray.
 * @param bitarray_ptr a pointer to the bitarray.
 * @param bit_idx the index of the bit to be flipped.
 * bit_idx must be valid in 0 <= bit_idx < bitarray_length(bitarray_ptr).
 */
void bitarray_flip(BitArray* bitarray_ptr, size_t bit_idx);

#endif  // BIT_ARRAY_H
