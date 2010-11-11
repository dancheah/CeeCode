#ifndef _BIT_VECTOR_H
#define _BIT_VECTOR_H

typedef struct bit_vector {
    // Bits for the bit vector
    unsigned char* bits;

    // Number of bits in the vector
    unsigned int size;
} bit_vector_t;

bit_vector_t* new_bit_vector(unsigned int num_of_bits);
void delete_bit_vector(bit_vector_t *vec);
void set_bit(bit_vector_t *vec, unsigned int pos, unsigned char val); 
unsigned char get_bit(bit_vector_t *vec, unsigned int pos);

#endif // _BIT_VECTOR_H
