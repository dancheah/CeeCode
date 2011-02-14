/*
 * permute.c: A simple permute function implementation
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
 * gcc -DUSEMAIN -Werror -std=c99 -pedantic -o permute permute.c 
 * clang -DUSEMAIN permute.c
 */
#include <stdio.h>
#include <string.h>

/**
 * A function that prints out the permutations
 * of a string.
 *
 * It follows pretty naturally from the defintion
 * of a permutation. First we swap elements of the
 * array with the first element. Then we recurse
 * onto a smaller part of the array.
 *
 * The base case is when we can no longer recurse
 * onto a smaller part of the array because we only
 * have 1 element left. At this point, we print
 * the value out.
 *
 * This function has side effects. It mutates
 * the array while permuting it. We reverse the
 * order of operations after the permute step
 * so once the permutation is done the array is
 * mutated back into its original state.
 */
void permute(char str[], int start, int length)
{
    // Base Case
    if (start == (length - 1)) {
        printf("%s\n", str);
        return;
    }

    // For each element of the array, we'll
    // fix one element by swapping it to the
    // front and then recurse on the remainder
    // of the array.
    for (int i = start; i < length; ++i) {
        // Swap 0th and ith position
        char value = str[start];
        str[start] = str[i];
        str[i] = value;

        // Permute recursive step
        permute(str, start + 1, length);

        // Swap ith and 0th position back
        str[i] = str[start];
        str[start] = value;
    }
}

#ifdef USEMAIN
int main(int argc, char** argv)
{
    if (argc > 1) {
        char *str = argv[1];

        printf("Before - Original String: %s\n", str); 
        permute(str, 0, strlen(str));
        printf("After - Original String: %s\n", str); 
    }

    return 0;
}
#endif // USEMAIN
