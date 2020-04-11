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
 * @param length the length, in bits, of the bitarray. <b>Must not be zero</b>.
 * @return a pointer to the constructed bitarray.
 * If an error occurs allocating memory, @p NULL may be returned.
 */
BitArray* bitarray_new(size_t length);

/**
 * Deallocates the memory used by the bitarray.
 * @param ba a pointer to the bitarray.
 */
void bitarray_delete(BitArray* ba);

/**
 * Checks if the bit at the index @p bit_idx is set.
 * Does not check whether @p bit_idx is a valid index in the bitarray.
 * @param ba a pointer to the bitarray.
 * @param bit_idx the index of the bit to be checked. Must belong in the
 * interval <tt>[ 0, bitarray_length(ba) )</tt>.
 * @return true if the bit is set, false otherwise.
 */
bool bitarray_check(BitArray const* ba, size_t bit_idx);

/**
 * Checks if all the bits in the bitarray are set.
 * @param ba a pointer to the bitarray.
 * @return true if all the bits are set, false otherwise.
 */
bool bitarray_all(BitArray const* ba);

/**
 * Checks if any bit in the bitarray is set.
 * @param ba a pointer to the bitarray.
 * @return true if any bit is set, false otherwise.
 */
bool bitarray_any(BitArray const* ba);

/**
 * Checks if all the bits in the bitarray are unset.
 * @param ba a pointer to the bitarray.
 * @return true if all the bits are unset, false otherwise.
 */
bool bitarray_none(BitArray const* ba);

/**
 * Returns the number of set bits.
 * @param ba a pointer to the bitarray.
 * @return the number of set bits.
 */
size_t bitarray_popcount(BitArray const* ba);

/**
 * Returns the ammount of bits in the bitarray.
 * @param ba a pointer to the bitarray.
 * @return the length of the bitarray.
 */
size_t bitarray_length(BitArray const* ba);

/**
 * Returns the maximum ammount of bits the bitarray can store.
 * @param ba a pointer to the bitarray.
 * @return the capacity of the bitarray.
 */
size_t bitarray_capacity(BitArray const* ba);

/**
 * Sets the bit at the index @p bit_idx.
 * Does not check whether @p bit_idx is a valid index in the bitarray.
 * @param ba a pointer to the bitarray.
 * @param bit_idx the index of the bit to be set. Must belong in the interval
 * <tt>[ 0, bitarray_length(ba) )</tt>.
 */
void bitarray_set(BitArray* ba, size_t bit_idx);

/**
 * Unsets the bit at the index @p bit_idx.
 * Does not check whether @p bit_idx is a valid index in the bitarray.
 * @param ba a pointer to the bitarray.
 * @param bit_idx the index of the bit to be unset. Must belong in the interval
 * <tt>[ 0, bitarray_length(ba) )</tt>.
 */
void bitarray_unset(BitArray* ba, size_t bit_idx);

/**
 * Sets every bit in the interval <tt>[ 0, bitarray_length(ba) )</tt>.
 * @param ba a pointer to the bitarray.
 */
void bitarray_fill(BitArray* ba);

/**
 * Unsets every bit in the interval <tt>[ 0, bitarray_length(ba) )</tt>.
 * @param ba a pointer to the bitarray.
 */
void bitarray_clear(BitArray* ba);

/**
 * Flips the bit at the index @p bit_idx.
 * If the bit is set, it's unset. If the bit is unset, it's set.
 * Does not check whether @p bit_idx is a valid index in the bitarray.
 * @param ba a pointer to the bitarray.
 * @param bit_idx the index of the bit to be flipped. Must belong in the
 * interval <tt>[ 0, bitarray_length(ba) )</tt>.
 */
void bitarray_flip(BitArray* ba, size_t bit_idx);

#endif  // BIT_ARRAY_H
