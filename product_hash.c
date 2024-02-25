#include "main.h"

// #===================================== Product Hash Table =====================================#

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error
#endif

#line 1 "products.gperf"
#line 6 "products.gperf"


// #define TOTAL_KEYWORDS 100
#ifndef TOTAL_KEYWORDS
#define TOTAL_KEYWORDS 100
#endif
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 16
#define MIN_HASH_VALUE 6
#define MAX_HASH_VALUE 139
/* maximum key range = 134, duplicates = 6 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif

// static unsigned int hash(  const char *str,   size_t len)
unsigned int hash(const char *str, size_t len)
{
 	unsigned char asso_values[] =
    {
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140,  40,  40,   0,  75,   0,
        0,  15,  20, 140,  55,  50,  20,  30,  35,  95,
        0, 140,  10,  25,  65, 140, 140,  20, 140,   5,
        5, 140, 140, 140, 140, 140, 140,   0,   0,  65,
       60,   0, 140,  65,  40,   5,  10,   0,  30,  50,
        5,   0,  30, 140,   5,  20,   0,   0, 140,  55,
      140,  20, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
      140, 140, 140, 140, 140, 140
    };
  return len + asso_values[(unsigned char)str[2]] + asso_values[(unsigned char)str[0]] + asso_values[(unsigned char)str[len - 1]];
}


// static inline const struct ProductEntry *get_product_index_by_name(const char *str, size_t len)
const struct ProductEntry *get_product_index_by_name(const char *str, size_t len)
{
  static struct ProductEntry wordlist[] =
    {
#line 63 "products.gperf"
      {"Potato", 52},
#line 51 "products.gperf"
      {"Cabbage", 40},
#line 23 "products.gperf"
      {"Pear", 12},
#line 73 "products.gperf"
      {"Clementine", 62},
#line 42 "products.gperf"
      {"Carrot", 31},
#line 71 "products.gperf"
      {"Currant", 60},
#line 101 "products.gperf"
      {"Plantain", 90},
#line 17 "products.gperf"
      {"Pineapple", 6},
#line 27 "products.gperf"
      {"Cantaloupe", 16},
#line 87 "products.gperf"
      {"Cantaloupe", 76},
#line 52 "products.gperf"
      {"Cauliflower", 41},
#line 75 "products.gperf"
      {"Rhubarb", 64},
#line 107 "products.gperf"
      {"Rutabaga", 96},
#line 93 "products.gperf"
      {"Persimmon", 82},
#line 36 "products.gperf"
      {"Guava", 25},
#line 59 "products.gperf"
      {"Peas", 48},
#line 33 "products.gperf"
      {"Grapefruit", 22},
#line 22 "products.gperf"
      {"Cherry", 11},
#line 46 "products.gperf"
      {"Lettuce", 35},
#line 69 "products.gperf"
      {"Cranberry", 58},
#line 74 "products.gperf"
      {"Cranberry", 63},
#line 94 "products.gperf"
      {"Ginger", 83},
#line 78 "products.gperf"
      {"Parsley", 67},
#line 38 "products.gperf"
      {"Passion_Fruit", 27},
#line 92 "products.gperf"
      {"Starfruit", 81},
#line 16 "products.gperf"
      {"Watermelon", 5},
#line 35 "products.gperf"
      {"Papaya", 24},
#line 64 "products.gperf"
      {"Sweet_Potato", 53},
#line 79 "products.gperf"
      {"Cilantro", 68},
#line 80 "products.gperf"
      {"Mint", 69},
#line 18 "products.gperf"
      {"Mango", 7},
#line 15 "products.gperf"
      {"Grapes", 4},
#line 106 "products.gperf"
      {"Parsnip", 95},
#line 55 "products.gperf"
      {"Beet", 44},
#line 20 "products.gperf"
      {"Peach", 9},
#line 58 "products.gperf"
      {"Green_Beans", 47},
#line 34 "products.gperf"
      {"Avocado", 23},
#line 57 "products.gperf"
      {"Artichoke", 46},
#line 100 "products.gperf"
      {"Artichoke", 89},
#line 98 "products.gperf"
      {"Watercress", 87},
#line 12 "products.gperf"
      {"Banana", 1},
#line 39 "products.gperf"
      {"Apricot", 28},
#line 43 "products.gperf"
      {"Broccoli", 32},
#line 21 "products.gperf"
      {"Plum", 10},
#line 70 "products.gperf"
      {"Goji_Berry", 59},
#line 60 "products.gperf"
      {"Celery", 49},
#line 83 "products.gperf"
      {"Rosemary", 72},
#line 25 "products.gperf"
      {"Raspberry", 14},
#line 14 "products.gperf"
      {"Strawberry", 3},
#line 30 "products.gperf"
      {"Pomegranate", 19},
#line 90 "products.gperf"
      {"Pomegranate", 79},
#line 68 "products.gperf"
      {"Pumpkin", 57},
#line 77 "products.gperf"
      {"Collard_Greens", 66},
#line 76 "products.gperf"
      {"Chard", 65},
#line 110 "products.gperf"
      {"Endive", 99},
#line 109 "products.gperf"
      {"Bok_Choy", 98},
#line 24 "products.gperf"
      {"Blueberry", 13},
#line 26 "products.gperf"
      {"Blackberry", 15},
#line 29 "products.gperf"
      {"Coconut", 18},
#line 89 "products.gperf"
      {"Coconut", 78},
#line 50 "products.gperf"
      {"Eggplant", 39},
#line 32 "products.gperf"
      {"Lime", 21},
#line 11 "products.gperf"
      {"Apple", 0},
#line 53 "products.gperf"
      {"Brussels_Sprouts", 42},
#line 44 "products.gperf"
      {"Spinach", 33},
#line 41 "products.gperf"
      {"Cucumber", 30},
#line 72 "products.gperf"
      {"Date", 61},
#line 31 "products.gperf"
      {"Lemon", 20},
#line 102 "products.gperf"
      {"Cactus_Pear", 91},
#line 108 "products.gperf"
      {"Salsify", 97},
#line 49 "products.gperf"
      {"Zucchini", 38},
#line 45 "products.gperf"
      {"Kale", 34},
#line 48 "products.gperf"
      {"Bell_Pepper", 37},
#line 105 "products.gperf"
      {"Dragon_Fruit", 94},
#line 28 "products.gperf"
      {"Honeydew", 17},
#line 88 "products.gperf"
      {"Honeydew", 77},
#line 104 "products.gperf"
      {"Squash_Blossom", 93},
#line 82 "products.gperf"
      {"Thyme", 71},
#line 62 "products.gperf"
      {"Garlic", 51},
#line 67 "products.gperf"
      {"Acorn_Squash", 56},
#line 84 "products.gperf"
      {"Sage", 73},
#line 81 "products.gperf"
      {"Basil", 70},
#line 66 "products.gperf"
      {"Butternut_Squash", 55},
#line 56 "products.gperf"
      {"Asparagus", 45},
#line 13 "products.gperf"
      {"Orange", 2},
#line 86 "products.gperf"
      {"Oregano", 75},
#line 97 "products.gperf"
      {"Kohlrabi", 86},
#line 99 "products.gperf"
      {"Okra", 88},
#line 95 "products.gperf"
      {"Turnip", 84},
#line 65 "products.gperf"
      {"Yam", 54},
#line 40 "products.gperf"
      {"Nectarine", 29},
#line 61 "products.gperf"
      {"Onion", 50},
#line 103 "products.gperf"
      {"Kiwano", 92},
#line 19 "products.gperf"
      {"Kiwi", 8},
#line 54 "products.gperf"
      {"Radish", 43},
#line 47 "products.gperf"
      {"Tomato", 36},
#line 96 "products.gperf"
      {"Jicama", 85},
#line 91 "products.gperf"
      {"Jackfruit", 80},
#line 37 "products.gperf"
      {"Fig", 26},
#line 85 "products.gperf"
      {"Dill", 74}
    };

  static short lookup[] =
    {
        -1,   -1,   -1,   -1,   -1,   -1,    0,    1,
        -1,    2,    3,    4,    5,    6,    7, -122,
        10,   11,   12,   13,   14,  -92,   -2,   -1,
        15,   16,   17,   18,   -1, -223,   -1,   21,
        22,   23,   24,   25,   26,   27,   28,   29,
        30,   31,   32,   -1,   33,   34,   35,   36,
        -1, -220,   39,   40,   41,   42,   43,   44,
        45,   -1,   46,   47,   48, -218,   51,   -1,
        52,   53,   54,   -1,   55,   56,   57,   -1,
      -213,   60,   61,   62,   63,   64,   65,   66,
        67,   68,   69,   70,   71,   -1,   72,   73,
      -198,   76,   77,   78,   79,   -1,   80,   81,
        82,  -26,   -2,   83,   -1,   84,   85,   86,
        87,   -1,   88,   -1,   89,   90,   91,   92,
       -42,   -2,   93,   -1,   94,  -51,   -2,  -63,
        -2,   95,  -81,   -2,   -1,   -1,   96,   -1,
        -1,   97,   -1,   -1,   -1,   98,   -1,   -1,
        -1,   -1,   -1,   99
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
        unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
            int index = lookup[key];

          if (index >= 0)
            {
                const char *s = wordlist[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
          else if (index < -TOTAL_KEYWORDS)
            {
                int offset = - 1 - TOTAL_KEYWORDS - index;
                struct ProductEntry *wordptr = &wordlist[TOTAL_KEYWORDS + lookup[offset]];
                struct ProductEntry *wordendptr = wordptr + -lookup[offset + 1];

              while (wordptr < wordendptr)
                {
                    const char *s = wordptr->name;

                  if (*str == *s && !strcmp (str + 1, s + 1))
                    return wordptr;
                  wordptr++;
                }
            }
        }
    }
  return 0;
}

// #===================================== End of Product Hash =====================================