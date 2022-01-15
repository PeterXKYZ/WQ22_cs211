#pragma once

#include <stdbool.h>

// Find the first instance of c in s and return a pointer to that position in
// s. Return NULL if no instance exists.
const char* str_chr(const char* s, char c);

// Determine if needle is the prefix of haystack. The characters of needle
// must exactly match the initial characters of haystack. Return true or false.
bool is_prefix_of(const char* haystack, const char* needle);

// Find the first instance of needle in haystack and return a pointer to that
// position in haystack. Return NULL if no instance exists.
const char* str_str(const char *haystack, const char* needle);

