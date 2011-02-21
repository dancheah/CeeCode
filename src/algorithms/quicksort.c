/*
 * quicksort.c: A quick sort implementation
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
 * Working through a quick sort exercise
 *
 * To compile on my mac:
 * gcc -DUSEMAIN -Werror -std=c99 -pedantic -o qsort quicksort.c 
 * clang -DUSEMAIN quicksort.c
 */
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * qsort1 from programming pearls.
 */
void qsort1(int* array, int l, int u)
{
    if (l >= u) {
        return;
    }

    int m = l;

    for (int i = l + 1; i <= u; i++) {
        if (array[i] < array[l]) {
            ++m;
            swap(&array[m], &array[i]);
        }
    }
    swap(&array[m], &array[l]);

    qsort1(array, l, m - 1);
    qsort1(array, m + 1, u);
}

/**
 * qsort3 from programming pearls.
 */
void qsort3(int* array, int l, int u)
{
    if (l >= u) {
        return;
    }

    int t = array[l];
    int i = l;
    int j = u + 1;

    while (1) {
        do { ++i; } while ((i <= u) && (array[i] < t));
        do { --j; } while (array[j] > t);
        if (i > j) {
            break;
        }
        swap(&array[i], &array[j]);
    }
    swap(&array[l], &array[j]);

    qsort3(array, l, j - 1);
    qsort3(array, j + 1, u);
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

        qsort3(array, 0, elements - 1);

        printf("After Sorting\n");
        print_array(elements, array);
    }

    return 0;
}
#endif // USEMAIN
