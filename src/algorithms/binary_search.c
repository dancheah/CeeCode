/*
 * binary_search.c: A binary search implementation
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
 * Working through a binary search exercise
 *
 * To compile on my mac:
 * gcc -DUSEMAIN -Werror -std=c99 -pedantic -o bsearch binary_search.c 
 * clang -DUSEMAIN binary_search.c
 */
#include <stdio.h>
#include <stdlib.h>

// Returns the index that it finds within
// the array
int binary_search(int *array, int start, int elements, int key) 
{
    int l = start;
    int u = elements - 1;

    while (l <= u) {
        int m = l + ((u - l)/ 2);
        printf("m: %d\n", m);

        if (key == array[m]) {
            return m;
        } else if (key < array[m]) {
            u = m - 1;
        } else {
            l = m + 1;
        }
    }

    return -1;
}

#ifdef USEMAIN
int main(int argc, char** argv)
{
    if (argc > 1) {
        int key = atoi(argv[1]);

        int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        int idx = binary_search(array, 0, 10, key);

        printf("Searching for %d. Found at Index: %d\n", key, idx);
    }

    return 0;
}
#endif // USEMAIN

// vim: sts=4 sw=4 ts=4 et ft=c
