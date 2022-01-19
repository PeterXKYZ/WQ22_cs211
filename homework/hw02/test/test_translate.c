#include "../src/translate.h"

#include <211.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>


/////
///// TEST HELPER SIGNATURES
/////

/*
 * The purpose of these helper functions is to make your test cases
 * easier to read and write. You should use them, but also be sure to go
 * check out their definitions at the bottom of this file. Try to
 * understand what they're doing for you, because you will very likely
 * want to design testing helpers of your own for future assignments.
 */

// Runs an expand_charseq() test case. Asserts that
// `expand_charseq(input)` will return `expected`.
static void
check_expand(const char* input, const char* expected);

// Runs a translate() test case. Asserts that `translate(input,
// from0, to0)` changes `input` to `expected`. (But uses a copy of
// `input`, since `input` might be a string literal, and changing those
// is UB.)
static void
check_tr(const char* input,
         const char* from0,
         const char* to0,
         const char* expected);

// Clones a string into fresh, `malloc`ed memory. Some C implementations
// provide a function `strdup` to do this, but it's non-standard.
static char*
clone_string(const char* src);


/////
///// TEST CASES FOR charseq_length
/////

static void test_charseq_length(void)
{
    CHECK_SIZE( charseq_length("abc"), 3 );
    CHECK_SIZE( charseq_length("a-z"), 26 );

    CHECK_SIZE( charseq_length("a-a"), 1);
    CHECK_SIZE( charseq_length("a-cd-f"), 6); // two ranges
    CHECK_SIZE( charseq_length("a-c-f"), 5);
    CHECK_SIZE( charseq_length("-abc"), 4);
    CHECK_SIZE( charseq_length("abc-"), 4);
    CHECK_SIZE( charseq_length("z-a"), 0);
    CHECK_SIZE( charseq_length("-abc-"), 5);
    CHECK_SIZE( charseq_length("hello\n"), 6);
    CHECK_SIZE( charseq_length("hello\\n"), 6);
    CHECK_SIZE( charseq_length("hello\\\n"), 6);
    CHECK_SIZE( charseq_length("hello\\\\n"), 7);
    CHECK_SIZE( charseq_length("     "), 5); // spaces
}


/////
///// TEST CASES FOR expand_charseq
/////

static void test_expand_charseq(void)
{
    check_expand( "abc", "abc" );
    check_expand( "a-e", "abcde" );

    check_expand( "a-a", "a"); // single char range
    check_expand( "a-cd-f", "abcdef"); // double range
    check_expand( "a-c-f", "abc-f"); // first range expanded
    check_expand( "---", "-"); // single dash range
    check_expand( "abc-", "abc-"); // ending dash as literal
    check_expand( "-abc", "-abc"); // starting dash as literal
    check_expand( "z-a", ""); // empty range
    check_expand( "-abc-", "-abc-"); // starting and ending dash
    check_expand( "\\t", "\t"); // escape sequence
    check_expand( "\\q", "q"); // invalid escape sequence
    check_expand( "\\\\", "\\"); // escape backslash
    check_expand( "\\-\\", "\\"); // dash range
    check_expand( "\\\n", "\n"); // literally not possible to input
    check_expand( "\\\\n", "\\n"); // escape backslash
    check_expand( "\na-e", "\nabcde"); // escape next to range
    check_expand( " -#", " !\"#"); // space range?
    check_expand( " - ", " "); // let the emptiness swallow you
    check_expand( "\xA-\xF", "\xA\xB\xC\xD\xE\xF"); // hex ranges
}


/////
///// TEST CASES FOR translate_char
/////

static void test_translate_char(void)
{
    CHECK_CHAR( translate_char('a', "xyz", "XYZ"), 'a' );
    CHECK_CHAR( translate_char('y', "xyz", "XYZ"), 'Y' );

    CHECK_CHAR( translate_char('\n', "hello\n", "abcdef"), 'f'); // find escape characters
    CHECK_CHAR( translate_char('\n', "helloo", "abcdef"), '\n'); // return escape characters
    CHECK_CHAR( translate_char(' ', "what the", "WHATQTHE"), 'Q'); // find space
    CHECK_CHAR( translate_char(' ', "whatqthe", "WHATQTHE"), ' '); // return space
    CHECK_CHAR( translate_char('\0', "hello", "HELLO"), '\0'); // don't find string terminator
    CHECK_CHAR( translate_char('a', "baaaa", "ABCDE"), 'B'); // return first instance
    CHECK_CHAR( translate_char('a', "", ""), 'a'); // empty string
    CHECK_CHAR( translate_char('\x4C', "Lol", "FOO"), 'F'); // hexadecimal char: \x4C -> L
    CHECK_CHAR( translate_char('L', "abc\x4C def", "abcqpdef"), 'q'); // hexadecimal string
    CHECK_CHAR( translate_char('L', "abcLGdef", "abc\x5D def"), ']'); // hexadecimal string
    CHECK_CHAR( translate_char('\x4C', "aaa", "AAA"), 'L'); // hexadecimal char 
}


/////
///// TEST CASES FOR translate
/////

static void test_translate(void)
{
    check_tr( "Hello, world!", ",! ",    "___",    "Hello__world_" );
    check_tr( "hELLO, WORLD!", "a-zA-Z", "A-Za-z", "Hello, world!" );

    check_tr( "wafting zephyrs quickly vexed jumbo.", "a-o", "A-O",
                "wAFtING zEpHyrs quICKLy vExED JuMBO."); // partial alphabet capitalization
    check_tr( "hello\n", "\n", "!", "hello!"); // escape characters
    check_tr( "hello\n", "\no", "O\t", "hell\tO"); // escape characters
    check_tr( "hello!", "lll", "abc", "heaao!"); // use the first mapping
    check_tr( "hello!", "l-l", "a", "heaao!"); // single character range
    check_tr( "hello!", "z-ao", "Q", "hellQ!"); // empty range
    check_tr( "[\\]^_`", "Z-a", "iiiiiiii", "iiiiii"); // non alphabet range
    check_tr( "[\\]^_`", "Z-\\", "aaa", "aa]^_`"); // weird ranges
    check_tr( "[\\]^_`", "\\-`", "aaaaa", "[aaaaa"); // weird ranges 
    check_tr( "hello", "", "", "hello"); // empty strings
    check_tr( "", "a", "b", ""); // empty strings
    check_tr( "", "", "", ""); // empty strings
    check_tr( "the-thing", "-e", "!!", "th!!thing"); // literal -
    check_tr( "the-thing", "e-", "!!", "th!!thing"); // literal -
    check_tr( "the-thing", "e-e", "!", "th!-thing"); // no - replacement
    check_tr( "4-9", "--6", "a-j", "ha9"); // dash ranges
    check_tr( "()", "&--", "D-K", "FG"); // dash ranges
    check_tr( "hello\n", "\na-e", "A-E\t", "h\tlloA"); // escape + ranges 
    check_tr( "'hello world'", " -'", "f-m", "mhellofworldm"); // space range
    check_tr( "\xE", "\xE-\x10", "abc", "a"); // unprintable hex characters 
}


/////
///// main
/////

int main(void)
{
    test_expand_charseq();
    test_translate_char();
    test_translate();
    test_charseq_length();

    return 0;
}


/////
///// HELPER FUNCTION DEFINITIONS
/////

static void check_expand(const char* input, const char* expected)
{
    char* actual = expand_charseq(input);
    CHECK_STRING( actual, expected );
    free(actual);
}

static void check_tr(const char* input,
                     const char* from0,
                     const char* to0,
                     const char* expected)
{
    char* from   = expand_charseq(from0);
    char* to     = expand_charseq(to0);

    // This is a more standard use of `assert` than we saw last week:
    // stopping the program if something is wrong. These assertions will
    // crash our test program if memory allocation fails, rather than
    // keep going and perform a bogus test.
    assert(from);
    assert(to);

    // We need to clone `input` because it probably came from a string
    // literal, and C forbids modifying string literals.
    char* actual = clone_string(input);

    // The actual operation and check:
    translate(actual, from, to);
    CHECK_STRING( actual, expected );

    // Deallocate the memory, since this function allocated it and now
    // we're done with it.
    free(from);
    free(to);
    free(actual);
}

static char* clone_string(const char* src)
{
    char* dst = malloc(strlen(src) + 1);
    assert( dst ); // avoids UB in case of OOM
    strcpy(dst, src);
    return dst;
}
