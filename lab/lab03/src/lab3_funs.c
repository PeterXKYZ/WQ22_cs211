#include "lab3_funs.h"

#include <stddef.h>

const char* str_chr(const char* s, char c) {
    int i = 0;
    
    for ( ; s[i] != c; ++i) {
        if (s[i] == '\0') {
            return NULL;
        }
    }

    return s+i;  // FIX ME!
}

bool is_prefix_of(const char* haystack, const char* needle) {
    for (int i = 0; needle[i] != '\0'; ++i) {
        if (haystack[i] != needle[i]) {
            return false;
        }
    }

    return true;  // FIX ME!
}

const char* str_str(const char* haystack, const char* needle) {
    for (int i = 0; haystack[i] != '\0'; ++i) {
        if (is_prefix_of(haystack + i, needle)) {
            return haystack + i;
        }
    }

    return NULL;  // FIX ME!
}


