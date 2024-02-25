#include "main.h"



// #===================================== City Hash Table =====================================#

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
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH_ 17
#define MIN_HASH_VALUE 6
#define MAX_HASH_VALUE_ 306
/* maximum key range = 301, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
// static unsigned int hash_(const char *str, unsigned int len)
unsigned int hash_(const char *str, unsigned int len)
{
  unsigned short asso_values[] =
    {
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 105,  50, 307,  25,
      307, 307, 307,  65, 307,  35,   5,   0,   5, 307,
      307, 307, 307,  25, 307,  25, 307, 307, 307, 307,
      307, 307, 307, 307, 307,  65,   0,   0,  40,  95,
       30,   5,  25, 120,   0,   5,  55,  70,  60,  30,
       10,  15,   5,  10,   0,  20,  30,   0,  60, 307,
      307,  10,  20,   0, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307,   0,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307,  15, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
      307, 307, 307, 307, 307, 307, 307
    };
    unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]+1];
      /*FALLTHROUGH*/
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
        break;
    }
  return hval;
}


// static inline const struct CityEntry *get_city_index_by_name(const char *str, unsigned int len)
const struct CityEntry *get_city_index_by_name(const char *str, unsigned int len) // update it to static
{
  static struct CityEntry wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""},
#line 110 "cities.gperf"
      {"Drarga", 99},
      {""},
#line 95 "cities.gperf"
      {"Ouazzane", 84},
      {""},
#line 73 "cities.gperf"
      {"Ouarzazate", 62},
      {""}, {""},
#line 30 "cities.gperf"
      {"Laayoune", 19},
      {""},
#line 103 "cities.gperf"
      {"Guerguerat", 92},
#line 66 "cities.gperf"
      {"Jerada", 55},
      {""},
#line 46 "cities.gperf"
      {"Guelta_Zemmur", 35},
#line 41 "cities.gperf"
      {"Chichaoua", 30},
#line 33 "cities.gperf"
      {"Bir_Lehlou", 22},
      {""},
#line 19 "cities.gperf"
      {"Kenitra", 8},
#line 74 "cities.gperf"
      {"Inezgane", 63},
#line 25 "cities.gperf"
      {"Taza", 14},
#line 72 "cities.gperf"
      {"Ben_guerir", 61},
#line 23 "cities.gperf"
      {"Beni_Mellal", 12},
#line 28 "cities.gperf"
      {"Guelmim", 17},
#line 14 "cities.gperf"
      {"Fes", 3},
#line 21 "cities.gperf"
      {"Safi", 10},
      {""},
#line 56 "cities.gperf"
      {"Souk_Larbaa", 45},
#line 50 "cities.gperf"
      {"Tinghir", 39},
      {""}, {""}, {""}, {""},
#line 59 "cities.gperf"
      {"Larache", 48},
#line 62 "cities.gperf"
      {"Goulmima", 51},
#line 68 "cities.gperf"
      {"Ksar_es_Seghir", 57},
#line 24 "cities.gperf"
      {"Errachidia", 13},
#line 76 "cities.gperf"
      {"Sefrou", 65},
#line 60 "cities.gperf"
      {"Tan-Tan", 49},
#line 93 "cities.gperf"
      {"Boujdour", 82},
#line 91 "cities.gperf"
      {"Assa", 80},
#line 12 "cities.gperf"
      {"Rabat", 1},
#line 42 "cities.gperf"
      {"Chefchaouen", 31},
#line 82 "cities.gperf"
      {"Guercif", 71},
#line 44 "cities.gperf"
      {"Taourirt", 33},
#line 27 "cities.gperf"
      {"Khouribga", 16},
#line 85 "cities.gperf"
      {"Ahfir", 74},
#line 51 "cities.gperf"
      {"Ifrane", 40},
#line 108 "cities.gperf"
      {"Zemamra", 97},
#line 29 "cities.gperf"
      {"Jorf_El_Melha", 18},
#line 26 "cities.gperf"
      {"Essaouira", 15},
#line 39 "cities.gperf"
      {"Nador", 28},
#line 70 "cities.gperf"
      {"Ait_Melloul", 59},
#line 94 "cities.gperf"
      {"Tarfaya", 83},
#line 31 "cities.gperf"
      {"Ksar_El_Kebir", 20},
#line 48 "cities.gperf"
      {"La\303\242youne", 37},
#line 100 "cities.gperf"
      {"Midar", 89},
#line 35 "cities.gperf"
      {"Temara", 24},
#line 86 "cities.gperf"
      {"Berkane", 75},
      {""},
#line 32 "cities.gperf"
      {"Sale", 21},
#line 36 "cities.gperf"
      {"Mohammedia", 25},
#line 98 "cities.gperf"
      {"Saidia", 87},
#line 83 "cities.gperf"
      {"Bouarfa", 72},
      {""}, {""},
#line 67 "cities.gperf"
      {"Youssoufia", 56},
#line 104 "cities.gperf"
      {"Asilah", 93},
#line 55 "cities.gperf"
      {"Sidi_Slimane", 44},
#line 53 "cities.gperf"
      {"Bab_Taza", 42},
      {""},
#line 92 "cities.gperf"
      {"Smara", 81},
#line 77 "cities.gperf"
      {"Aourir", 66},
#line 15 "cities.gperf"
      {"Tangier", 4},
      {""},
#line 88 "cities.gperf"
      {"Boulemane", 77},
#line 109 "cities.gperf"
      {"Sidi_Kacem", 98},
      {""},
#line 101 "cities.gperf"
      {"Moulay_Bousselham", 90},
      {""}, {""},
#line 52 "cities.gperf"
      {"Azrou", 41},
#line 97 "cities.gperf"
      {"had_soualem", 86},
#line 71 "cities.gperf"
      {"Layoune", 60},
#line 106 "cities.gperf"
      {"Tafraout", 95},
#line 102 "cities.gperf"
      {"Khemisset", 91},
#line 80 "cities.gperf"
      {"Bni_Hadifa", 69},
#line 57 "cities.gperf"
      {"Tiflet", 46},
      {""},
#line 89 "cities.gperf"
      {"Khenifra", 78},
      {""},
#line 81 "cities.gperf"
      {"Fquih_Ben_Salah", 70},
      {""}, {""},
#line 111 "cities.gperf"
      {"Skhirate", 100},
#line 45 "cities.gperf"
      {"Taroudant", 34},
#line 18 "cities.gperf"
      {"Oujda", 7},
#line 63 "cities.gperf"
      {"Midelt", 52},
#line 20 "cities.gperf"
      {"Tetouan", 9},
      {""}, {""},
#line 99 "cities.gperf"
      {"Bab_Berred", 88},
#line 47 "cities.gperf"
      {"Dakhla", 36},
      {""}, {""},
#line 61 "cities.gperf"
      {"Sidi_Ifni", 50},
      {""},
#line 37 "cities.gperf"
      {"Settat", 26},
#line 84 "cities.gperf"
      {"Demnate", 73},
#line 87 "cities.gperf"
      {"Akhfenir", 76},
      {""}, {""},
#line 49 "cities.gperf"
      {"Tiznit", 38},
      {""},
#line 107 "cities.gperf"
      {"Imzouren", 96},
#line 13 "cities.gperf"
      {"Marrakech", 2},
      {""},
#line 34 "cities.gperf"
      {"Arfoud", 23},
      {""}, {""}, {""}, {""},
#line 17 "cities.gperf"
      {"Meknes", 6},
      {""}, {""}, {""}, {""},
#line 65 "cities.gperf"
      {"Azilal", 54},
#line 90 "cities.gperf"
      {"Bir_Anzerane", 79},
      {""},
#line 54 "cities.gperf"
      {"Berrechid", 43},
      {""},
#line 79 "cities.gperf"
      {"Tichla", 68},
      {""}, {""}, {""}, {""},
#line 78 "cities.gperf"
      {"Oulad_Teima", 67},
      {""},
#line 40 "cities.gperf"
      {"Kalaat_MGouna", 29},
      {""}, {""},
#line 96 "cities.gperf"
      {"Zagora", 85},
#line 38 "cities.gperf"
      {"B\303\251ni_Mellal", 27},
      {""}, {""}, {""},
#line 105 "cities.gperf"
      {"Sidi_Bouzid", 94},
#line 58 "cities.gperf"
      {"Sidi_Bennour", 47},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 69 "cities.gperf"
      {"Tichka", 58},
      {""}, {""}, {""}, {""},
#line 75 "cities.gperf"
      {"Oujda_Angad", 64},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 16 "cities.gperf"
      {"Agadir", 5},
      {""}, {""}, {""},
#line 11 "cities.gperf"
      {"Casablanca", 0},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 22 "cities.gperf"
      {"El_Jadida", 11},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""},
#line 43 "cities.gperf"
      {"Al_Hoceima", 32},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 64 "cities.gperf"
      {"Figuig", 53}
    };

	if (len <= MAX_WORD_LENGTH_ && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash_(str, len);

      if (key <= MAX_HASH_VALUE_)
        {
          const char *s = wordlist[key].name;

        //   if (*str == *s && !strcmp (str + 1, s + 1))
        //     return &wordlist[key];
			if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
				return &wordlist[key];
        }
    }
  return 0;
}

// #===================================== End of City Hash Table =====================================#
