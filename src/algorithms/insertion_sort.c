/*
 * insertion_sort.c: A simple permute function implementation
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
 * A little exercise I'm working on going through Jon Bentley's
 * Programming Pearls.
 *
 * To compile on my mac:
 * gcc -DUSEMAIN -Werror -std=c99 -pedantic -o isort insertion_sort.c 
 * clang -DUSEMAIN insertion_sort.c
 */
#include <stdio.h>
#include <stdlib.h>

// Basic implementation.
void isort1(int elements, int* array)
{
    for (int i = 1; i < elements; ++i) {
        for (int j = i; (j > 0) && (array[j - 1] > array[j]); --j) {
            // Swap elements around
            int tmp = array[j - 1];
            array[j - 1] = array[j];
            array[j] = tmp;
        }
    }
}

// More nuanced implementation. Slightly faster than isort1
// because we don't do a swap.
void isort2(int elements, int* array)
{
    for (int i = 1; i < elements; ++i) {
        int t = array[i];
        int j;
        for (j = i; (j > 0) && (array[j - 1] > t); --j) {
            array[j] = array[j - 1];
        }
        array[j] = t;
    }
}

void print_array(int elements, int* array) 
{
    for (int i = 0; i < elements; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

#ifdef USEMAIN
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

        isort2(elements, array);

        printf("After Sorting\n");
        print_array(elements, array);
    }

    return 0;
}
#endif // USEMAIN

// vim: sts=4 sw=4 ts=4 et ft=c
