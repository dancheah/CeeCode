/*
 * array.c: Dynamic array implementation
 * Copyright (C) 2011 Daniel Cheah
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

/*
 * To compile on my mac:
 * gcc -DUSEMAIN -Werror -std=c99 -pedantic -o arraytest arraytest.c (works on Ubuntu)
 * clang -DUSEMAIN array.c
 *
 * TODO: Run valgrind.
 * TODO: More error checking
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Don't like typing unsigned long long everywhere.
 */
typedef unsigned long long ull;

/**
 * Data was currently unsigned int for the
 * experiments I was trying.
 */
typedef unsigned int data_t;

/**
 * Array structure containing  various meta data. It contains
 * enough meta data to implement a  deque but is really just a
 * dynamic array implementation at this point.
 */
typedef struct array 
{
    /**
     * Index of the head element
     */
    ull head; // not used

    /**
     * Index of the tail element
     */
    ull tail;

    /**
     * How much of the internal data
     * array has been used.
     */
    ull used;

    /**
     * How many data elements we can hold in the 
     * internal data array. To calculate bytes,
     * it would be sizeof(data_t) * size.
     */
    ull size;

    /**
     * How many resizes do we need to do.
     */
    unsigned int resizes;

    /**
     * Pointer to the data. This is where
     * the array data is stored.
     */
    data_t* data;
} array_t;

/**
 * This allocates a new array.
 */
array_t* new_array(void) 
{
    array_t* a = (array_t *)malloc(sizeof(array_t));

    a->resizes = 0;
    a->used = 0;
    a->size = 1024;
    a->head = 0;
    a->tail = 0;
    a->data = (data_t *)malloc(sizeof(data_t) * a->size);

    return a;
}

/**
 * This cleans up the memory associated
 * with the array.
 */
void delete_array(array_t* a)
{
    free(a->data);
    free(a);
}

/**
 * Prints out information about the array.
 */
void print_array_info(array_t* a)
{
    printf("Head: %llu Tail: %llu\n", a->head, a->tail);
    printf("Used: %llu Size: %llu\n", a->used, a->size);
    printf("Resizes: %u\n", a->resizes);
}

/**
 * Prints a data element. 
 */
void print_data(data_t* d)
{
    printf("%u\n", *d);
}

/**
 * Append a data element to the end of the array.
 * If the internal array does not have sufficient space,
 * it will double the size of the internal array. This
 * was done to conduct an experiment in amortized analysis.
 */
void append(array_t* a, data_t d) 
{
    if (a->used == a->size) {
        // Need to do a resize
        a->resizes++;
        // Double the amount of memory we need
        unsigned int new_size = a->size * 2;
        // Allocate new memory. TODO: As an optimization can play
        // with realloc later
        data_t* tmp = (data_t*)malloc(sizeof(data_t) * new_size);
        // Copy old buffer to new buffer. Memory shouldn't be
        // overlapping so memcpy is fine.
        memcpy(tmp, a->data, sizeof(data_t) * a->size);
        
        // Update to the new size
        a->size = new_size;
        // Free old buffer
        free(a->data);
        // Point to new buffer
        a->data = tmp;
    }

    // The tail is where we need to insert the new element
    (a->data)[a->tail] = d;

    // Setup the tail for the next insert
    a->tail++;

    // We used another element
    a->used++;
}

/**
 * Get a data element from the array.
 */
data_t* get(array_t* a, unsigned int pos)
{
    // TODO: bounds check
    return &((a->data)[pos]);
}

#ifdef USEMAIN
void test1()
{
    array_t* a = new_array();

    for (int i = 0; i < 1024; i++) {
        append(a, i);
    }

    printf("Test Resize 1\n");
    for (int i = 1024; i < 2048; i++) {
        append(a, i);
    }
    print_array_info(a);

    printf("Test Resize 2\n");
    for (int i = 2048; i < 4096; i++) {
        append(a, i);
    }
    print_array_info(a);

    data_t* tmp = get(a, 0);
    print_data(tmp); 

    tmp = get(a, 4095);
    print_data(tmp); 
}

void run_experiment(ull testsize)
{
    array_t* a = new_array();

    for (ull i = 0; i < testsize; i++) {
        append(a, i);        
    }

    //print_array_info(a); 

    destroy_array(a);
}

int main(int argc, char** argv)
{
    if (argc > 1) {
        printf("Arg 0: %s\n", argv[0]);

        ull testsize = atoll(argv[1]);
        printf("Arg 1: %llu\n", testsize);

        time_t t0 = time(NULL);
        for (int i = 0; i < 1000; i++) {
            run_experiment(testsize);
        }
        time_t t1 = time(NULL);
        double time_delta = difftime(t1, t0);

        printf("Time Delta: %.2lf\n", time_delta);


    } else {
        test1();
    }

    return 0;
}
#endif // USEMAIN

// vim: sts=4 sw=4 ts=4 et ft=c

