#include "translate.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> // remove

// Helper function for interpreting escapes. Given the character that
// follows a backslash, returns the character that the combination
// should be replaced with. Recognizes the seven standard C escapes, and
// maps every other character to itself.
char interpret_escape(char c)
{
    switch (c) {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    default:  return c;
    }
}

size_t charseq_length(const char* src)
{
    size_t result = 0;
    
    while (*src != '\0') { // if the current char is not '\0', do loop

        // if the next char is '-', it is a range
        // if the current char is '-', it is the literal character
        // if '\0' follows '-', then treat '-' as a literal character
        if (*(src + 1) == '-' && *(src + 2) != '\0') { 
            int start = *src;      // start char of the range 
            int end = *(src + 2);  // end char of the range  

            if (start <= end) { // valid range, otherwise empty range
                result += end - start + 1;  // range length
            }
            src += 3;   // skip to char after end char of the range
            continue;   // go back to the beginning of the loop
        }

        /* if the current char is '\\' (single backslash) 
        and the next char is not '\0', then we found an escape sequence */
        if (*src == '\\' && *(src + 1) != '\0') {
            ++ result; // an escape sequence such as '\n' count as length one
            src += 2; // skip to char after escape sequence
            continue;
        }
    
        ++result; // if none of the conditions are met, add one to count
        ++src; // go to the next position
    }

    return result;
}

/*
char* expand_charseq(const char* src)
{
    char* const dst = malloc(charseq_length(src) + 1);
    if (!dst) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    (void)i;  // Marks variable `i` as "used" to avoid a compiler warning.
              // (Delete it once you've written code that uses `i`.)

    //
    // TODO: Your code goes here
    //

    dst[j] = 0;

    return dst;
} */

// The starter code for expand_charseq above is written in
// *array-indexing style*, whereas the commented-out expand_charseq
// below uses *pointer arithmetic style*. If you prefer pointer
// arithmetic to array indexing, you may comment out the expand_charseq
// above and uncomment the one right here:

char* expand_charseq(const char* src)
{
    // allocate memory based on length of the expanded src + null terminator \0
    char* result = malloc(charseq_length(src) + 1);
    if (!result) {
        return NULL;
    }

    char* dst = result; // pointer to beginning of the result array

    while(*src != '\0') { // if current char is not \0, do loop

        // if the next char is '-', it is a range
        // if the current char is '-', it is the literal character
        // if '\0' follows '-', then treat '-' as a literal character
        if (*(src + 1) == '-' && *(src + 2) != '\0') { 
            int start = *src;      // start char of the range 
            int end = *(src + 2);  // end char of the range  

            if (start <= end) { // valid range, otherwise empty range
                while (start <= end) {  // expand range as a list of chars
                    *dst = (char)start; // set start as a char as the value of *dst
                    ++dst;      // go to next location
                    ++start;    // next char
                }
            }
            src += 3;   // skip to char after range
            continue;
        }

        if (*src == '\\' && *(src + 1) != '\0') {
            *dst = interpret_escape(*(src + 1));    // returns the correct escape character
            ++dst;      // go to next location (escape characters have length 1)
            src += 2;   // skip to char after escape sequence
            continue;
        }

        *dst = *src;    // copies char from *src to *dst
        ++dst;          // next location
        ++src;          // next location
    }

    *dst = '\0';        // set the last char as null terminator

    return result;
}


char translate_char(char c, const char* from, const char* to)
{
    int i = 0;

    for ( ; from[i] != c; ++i) {    // if current char of from does not match c, do loop
        if (from[i] == '\0') {      // if current char of from is \0,
            return c;               // found no match, return c as is
        }
    }

    return to[i];   // if current char of from does match c, return current char of to
}

void translate(char* s, const char* from, const char* to) 
{
    for (int i = 0; s[i] != '\0'; ++i) {    // calls translate_char for every char of s
        s[i] = translate_char(s[i], from, to);
    }
}
