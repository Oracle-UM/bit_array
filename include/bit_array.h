#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

/**
 * If set to @p true, performs runtime bounds-checking on bitarray length and
 * index function arguments, as well as null checking on memory allocations.
 * Otherwise, assumes these are always valid. 
 */
#define BIT_ARRAY_ASSERTS false

/**
 * If set to @p true, uses compiler builtins to compute byte popcount.
 * Otherwise, uses custom implementation.
 */
#define BIT_ARRAY_USE_BUILTIN_POPCOUNT false

/**
 * A compact, fixed size heap array of bit values.
 */
typedef struct BitArray BitArray;

/**
 * Constructs a bitarray with all bits unset.
 * @param length the length, in bits, of the bitarray. <b>Must not be zero</b>.
 * If @p BIT_ARRAY_ASSERTS is set to @p true, checks if <tt>length > 0</tt>, and
 * if the memory allocation was successful.
 * @return a pointer to the constructed bitarray.
 * If an error occurs allocating memory, @p NULL may be returned.
 */
BitArray* bitarray_with_capacity(size_t length);

/**
 * Deallocates the memory used by the bitarray.
 * Any pointer to the bitarray becomes invalid.
 * @param ba a pointer to the bitarray.
 */
void bitarray_delete(BitArray* ba);

/**
 * Checks if the bit at the index @p bit_idx is set.
 * Does not check whether @p bit_idx is a valid index in the bitarray.
 * @param ba a pointer to the bitarray.
 * @param bit_idx the index of the bit to be checked. Must belong in the
 * interval <tt>[ 0, bitarray_length(ba) )</tt>. If @p BIT_ARRAY_ASSERTS is set
 * to @p true, checks if @p bit_idx is in this interval.
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
 * <tt>[ 0, bitarray_length(ba) )</tt>. If @p BIT_ARRAY_ASSERTS is set to
 * @p true, checks if @p bit_idx is in this interval.
 */
void bitarray_set(BitArray* ba, size_t bit_idx);

/**
 * Unsets the bit at the index @p bit_idx.
 * Does not check whether @p bit_idx is a valid index in the bitarray.
 * @param ba a pointer to the bitarray.
 * @param bit_idx the index of the bit to be unset. Must belong in the interval
 * <tt>[ 0, bitarray_length(ba) )</tt>. If @p BIT_ARRAY_ASSERTS is set to
 * @p true, checks if @p bit_idx is in this interval.
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
 * interval <tt>[ 0, bitarray_length(ba) )</tt>. If @p BIT_ARRAY_ASSERTS is set
 * to @p true, checks if @p bit_idx is in this interval.
 */
void bitarray_flip(BitArray* ba, size_t bit_idx);

#endif  // BIT_ARRAY_H
