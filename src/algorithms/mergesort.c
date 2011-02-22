/*
 * mergesort.c: A merge sort implementation
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
 * Working through a merge sort exercise. Merge sort turns out to 
 * be the most complicated sort to implement so far in C because
 * of the extra memory needed to be allocated.
 *
 * To compile on my mac:
 * gcc -DUSEMAIN -Werror -std=c99 -pedantic -o msort mergesort.c 
 * clang -DUSEMAIN mergesort.c
 */
#include <stdio.h>
#include <stdlib.h>

void msort(int elems, int* array)
{
    // termination condition. we are done
    if (elems <= 1) {
        return;
    }

    // split array into left and right sub array
    int middle = elems / 2;

    int lsize = elems - middle;
    int* larray = (int*)malloc(sizeof(int) * lsize);
    int o = 0;
    for (int i = 0; o < lsize; ++i, ++o) {
        larray[i] = array[i];
    }

    int rsize = elems - lsize;  
    int* rarray = (int*)malloc(sizeof(int) * rsize);
    for (int i = 0; o < elems; ++i, ++o) {
        rarray[i] = array[o];
    }

    // merge sort left side
    msort(lsize, larray); 
    // merge sort right side
    msort(rsize, rarray); 

    // merge the two lists
    int l = 0;
    int r = 0;
    o = 0;
    while ((l < lsize) && (r < rsize)) {
        if (larray[l] < rarray[r]) {
            array[o] = larray[l];
            ++o;
            ++l;
        } else {
            array[o] = rarray[r];
            ++o;
            ++r;
        }
    }
    
    // check if the right side is empty
    if (l < lsize) {
        for (; l < lsize; ++l, ++o) {
            array[o] = larray[l];
        }
    }

    // check if the left side is empty
    if (r < rsize) {
        for (; r < rsize; ++r, ++o) {
            array[o] = rarray[r];
        }
    }

    // free up the memory we allocated when split the 
    // array into two pieces.
    free(larray);
    free(rarray);
}

#ifdef USEMAIN
void print_array(int elements, int* array) 
{
    for (int i = 0; i < elements; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    if (argc > 1) {
        int elements = argc - 1;

        printf("Elements: %d\n", elements);

        // Allocate memory for array and initialize
        // elements.
        int *array = (int *)malloc(sizeof(int) * elements);
        for (int i = 0; i < elements; ++i) {
            array[i] = atoi(argv[i + 1]);
        }

        printf("Before Sorting\n");
        print_array(elements, array);

        msort(elements, array);

        printf("After Sorting\n");
        print_array(elements, array);
    }
}
#endif // USEMAIN

// vim: sts=4 sw=4 ts=4 et ft=c
