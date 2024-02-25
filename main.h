#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
// #include <emmintrin.h>
// #include <immintrin.h>
#include <x86intrin.h>
#include <stdbool.h>
// #include <nmmintrin.h>

#define MAX_CITIES 101
#define MAX_PRODUCTS 100

#define MAX_CITY_LENGTH 18 // 17 characters + null terminator
#define MAX_PRODUCT_LENGTH 17 // 16 characters + null terminator
#define MAX_LINE_LENGTH (MAX_CITY_LENGTH + MAX_PRODUCT_LENGTH + 6 + 3) // +3 for commas and newline

struct ProductEntry {
	const char	*name;
	int			productIndex;
};

struct CityEntry {
    const char *name;
    int			cityIndex;  // This index can be used to access a City object in a global array.
};

struct Product {
	double 		price;
	char		*name;
};

struct City {
	double			total;
	char		    *name;
	int				numProducts;
	struct Product	products[MAX_PRODUCTS];
};


const struct CityEntry *get_city_index_by_name(const char *str, unsigned int len);
const struct ProductEntry *get_product_index_by_name(const char *str, size_t len);