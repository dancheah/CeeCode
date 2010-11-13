/*
 * bit_vector.c: Bit vector implementation
 * Copyright (C) 2010 Daniel Cheah
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

/**
 * On my mac, compile single file like this:
 * clang -DUSEMAIN bit_vector.c
 * gcc -DUSEMAIN bit_vector.c
 *
 * Making shared object:
 * gcc -fPIC -c test.c 
 * gcc -shared -Wl,-soname,libmystuff.so.1 -o libmystuff.so.1.0.1 test.o
 * To use clang, substitute gcc with clang. Seems to work without any 
 * change.
 *
 * TODO: Run this through valgrind. I don't think I'm leaking memory
 * TODO: This implementation could probably do more error checking. It
 * does'nt validate the values being passed in.
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * bit_vector data structure.
 */
typedef struct bit_vector {
    // Bits for the bit vector
    unsigned char* bits;

    // Number of bits in the vector
    unsigned int size;
} bit_vector_t;

/**
 * Helper function to calculate how many bytes I need
 * to allocate.
 */
static unsigned int calc_bytes(unsigned int num_of_bits) {
    unsigned int size = sizeof(unsigned char);

    if ((num_of_bits % size) == 0) {
        return num_of_bits / size;
    } else {
        return (num_of_bits / size) + 1;
    }
}

/**
 * Calculate the offset into the array of
 * bytes.
 */
static unsigned int calc_offset(unsigned int pos) {
    unsigned int size = sizeof(unsigned char);

    return pos / size;
}

static unsigned char get_off_mask(unsigned int pos) {
    unsigned char array[] = { 0xFE, 0xFC, 0xFA, 0xF7, 0xEF, 0xCF, 0xAF, 0x7F };
    return array[pos];
}

static unsigned char get_on_mask(unsigned int pos) {
    unsigned char array[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
    return array[pos];
}

/**
 * Create a new bit_vector with the specified number of bits.
 * TODO: Need to check return value of malloc
 */
bit_vector_t* new_bit_vector(unsigned int num_of_bits) {
    // Allocate the structure
    bit_vector_t *vec = (bit_vector_t *) malloc(sizeof(bit_vector_t));

    // Store number of bits
    vec->size = num_of_bits;

    // Allocate the bits
    vec->bits = (unsigned char *) malloc(calc_bytes(num_of_bits));

    return vec;
}

/** 
 * Clean up memory allocated to this bit vector.
 */
void delete_bit_vector(bit_vector_t *vec) {
    free(vec->bits);
    free(vec);
}

/**
 * Set a bit at a particular location
 */
void set_bit(bit_vector_t *vec, unsigned int pos, unsigned char val) {
    unsigned int offset = calc_offset(pos);
    unsigned int bitpos = pos - (offset * sizeof(unsigned char));

    if (val) {
        unsigned char mask = get_on_mask(bitpos);
        vec->bits[offset] = vec->bits[offset] | mask;
    } else {
        unsigned char mask = get_off_mask(bitpos);
        vec->bits[offset] = vec->bits[offset] & mask;
    }

    return;
}

/**
 * Get a bit at a particular location
 */
unsigned char get_bit(bit_vector_t *vec, unsigned int pos) {
    unsigned int offset = calc_offset(pos);
    unsigned int bitpos = pos - (offset * sizeof(unsigned char));

    unsigned char mask = get_on_mask(bitpos);
    return vec->bits[offset] & mask;
}

#ifdef USEMAIN
int main(void) {
    bit_vector_t *vec = new_bit_vector(32);

    for (int i = 0; i < 32; i++) {
        set_bit(vec, i, 1);
        unsigned char v = get_bit(vec, i);
        printf("test on %d: %u\n", i, v);

        set_bit(vec, i, 0);
        v = get_bit(vec, i);
        printf("test off %d: %u\n", i, v);
    }

    delete_bit_vector(vec);

    return 0;
}
#endif

