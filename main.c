#include "main.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


struct City cities[MAX_CITIES] = {0};

#define NUM_CHILDREN 35



void update_city_and_product_totals(const char *cityName, size_t cityNameLength, const char *productName, size_t productNameLength, uint32_t price)
{
	const struct CityEntry *cityEntry = get_city_index_by_name(cityName, cityNameLength);
	if (!cityEntry)
	{
		printf("City not found: %s\n", cityName);
		exit(EXIT_FAILURE);
	}

	struct City *city = &cities[cityEntry->cityIndex];
	if (city->name == NULL)
	{
		city->name = (char *)cityEntry->name;
	}

	const struct ProductEntry *productEntry = get_product_index_by_name(productName, productNameLength);
	if (!productEntry)
	{
		perror("Product not found");
		exit(EXIT_FAILURE);
	}

	struct Product *product = &(city->products[productEntry->productIndex]);
	if (product->name == NULL)
	{
		product->name = (char *)productEntry->name;
		product->price = price;
		city->numProducts++;
	}
	else if (product->price > price)
	{
		product->price = price;
	}
	city->total += price;
}

void	serialize_city(FILE *file, const struct City *city)
{
	size_t cityNameLength = strlen(city->name);
	fwrite(&cityNameLength, sizeof(size_t), 1, file);
	fwrite(city->name, sizeof(char), cityNameLength, file);
	fwrite(&city->total, sizeof(uint64_t), 1, file);

	fwrite(&city->numProducts, sizeof(int), 1, file);

	for (int i = 0; i < MAX_PRODUCTS; i++)
	{
		if (city->products[i].name != NULL)
		{
			size_t productNameLength = strlen(city->products[i].name);
			fwrite(&productNameLength, sizeof(size_t), 1, file);
			fwrite(city->products[i].name, sizeof(char), productNameLength, file);
			fwrite(&city->products[i].price, sizeof(uint32_t), 1, file);
		}
	}
}

void child_process_task() {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "results_%d.bin", getpid());

    FILE* file = fopen(filePath, "wb");
    if (file) {
        for (int i = 0; i < MAX_CITIES; i++) {
			if (cities[i].name != NULL) {
				serialize_city(file, &cities[i]);
			}
        }
        fclose(file);
    }
}

static inline uint32_t parse_price_component(char *component_str, uint32_t component_len) {
  // Predefined values for subtracting ASCII zero ('0') based on the component length
  static uint32_t ascii_zero_offset[4] = {0, '0', 11 * '0', 111 * '0'};
  
  // Multipliers for each digit position, depending on the component length
  static uint32_t digit_multipliers[3][4] = {
    {0, 1, 10, 100},   // Multipliers for the first digit
    {0, 0, 1,  10},    // Multipliers for the second digit
    {0, 0, 0,  1},     // Multipliers for the third digit
  };
  
  // Calculate and return the integer value of the price component
  uint32_t result = (
    digit_multipliers[0][component_len] * component_str[0] + 
    digit_multipliers[1][component_len] * component_str[1] + 
    digit_multipliers[2][component_len] * component_str[2] -
    ascii_zero_offset[component_len]
  );
  return result;
}

void process_segment(const char *segment, size_t length) {
    const char *end = segment + length;
    const char *line_start = segment;

    while (line_start < end) {
        const char *line_end = (const char *)memchr(line_start, '\n', end - line_start);
        if (!line_end) {
            line_end = end; // Handle the case where the last line doesn't end with a newline
        }

        const char *first_comma = (const char *)memchr(line_start, ',', line_end - line_start);
        const char *second_comma = first_comma ? (const char *)memchr(first_comma + 1, ',', line_end - (first_comma + 1)) : NULL;

        if (first_comma && second_comma) {
            // Extract cityName
            char cityName[MAX_CITY_LENGTH] = {0};
            size_t cityNameLength = first_comma - line_start;
            memcpy(cityName, line_start, cityNameLength);
            cityName[cityNameLength] = '\0';

            // Extract productName
            char productName[MAX_PRODUCT_LENGTH] = {0};
            size_t productNameLength = second_comma - first_comma - 1;
            memcpy(productName, first_comma + 1, productNameLength);
            productName[productNameLength] = '\0';

            // Extract price
            // double price = atof(second_comma + 1);
			char* price_d = (char *)second_comma + 1;
   			size_t price_d_len = 0;
			while (price_d[price_d_len] != '.' && &price_d[price_d_len] < line_end)
				price_d_len++;
			uint32_t price_decimal = parse_price_component(price_d, price_d_len);

			char *price_f = price_d + price_d_len + 1;
			size_t price_f_len = line_end - price_f;
			uint32_t price_fractional = parse_price_component(price_f, price_f_len);
			price_fractional *= (price_f_len < 2) ? 10 : 1;

			uint32_t price = price_decimal * 100 + price_fractional;

			// Process the line
			update_city_and_product_totals(cityName, cityNameLength, productName, productNameLength, price);
        }
        // Move to the start of the next line
        line_start = line_end + 1;
    }
	child_process_task();
}


int deserialize_city(FILE* file, struct City *city)
{
	size_t cityNameLength;
	if (fread(&cityNameLength, sizeof(size_t), 1, file) < 1) return -1;
	city->name = (char *)malloc(cityNameLength + 1);
	fread(city->name, sizeof(char), cityNameLength, file);
	city->name[cityNameLength] = '\0';
	fread(&city->total, sizeof(uint64_t), 1, file);
	fread(&city->numProducts, sizeof(int), 1, file);

	for (int i = 0; i < city->numProducts; i++)
	{
		uint32_t price;
		size_t productNameLength;
		char productName[MAX_PRODUCT_LENGTH] = {0};

		fread(&productNameLength, sizeof(size_t), 1, file);
		fread(productName, sizeof(char), productNameLength, file);
		productName[productNameLength] = '\0';
		fread(&price, sizeof(uint32_t), 1, file);

		const struct ProductEntry *productEntry = get_product_index_by_name(productName, productNameLength);
		if (!productEntry)
		{
			perror("Product not found");
			exit(EXIT_FAILURE);
		}
		city->products[productEntry->productIndex].name = (char *)productEntry->name;
		city->products[productEntry->productIndex].price = price;
	}
	return (0);
}

void aggregate_city(struct City aggregatedCities[MAX_CITIES], struct City* newCity)
{
	const struct CityEntry *cityEntry = get_city_index_by_name(newCity->name, strlen(newCity->name));
	if (!cityEntry)
	{
		perror("City not found");
		exit(EXIT_FAILURE);
	}

	if (aggregatedCities[cityEntry->cityIndex].name == NULL)
	{
		aggregatedCities[cityEntry->cityIndex].name = newCity->name;
		aggregatedCities[cityEntry->cityIndex].total = newCity->total;
		aggregatedCities[cityEntry->cityIndex].numProducts = newCity->numProducts;
	}
	else
		aggregatedCities[cityEntry->cityIndex].total += newCity->total;

	for (int i = 0; i < MAX_PRODUCTS; i++)
	{
		if (newCity->products[i].name)
		{
			if (aggregatedCities[cityEntry->cityIndex].products[i].name == NULL)
			{
				aggregatedCities[cityEntry->cityIndex].products[i].name = newCity->products[i].name;
				aggregatedCities[cityEntry->cityIndex].products[i].price = newCity->products[i].price;
			}
			else if (aggregatedCities[cityEntry->cityIndex].products[i].price > newCity->products[i].price)
			{
				aggregatedCities[cityEntry->cityIndex].products[i].price = newCity->products[i].price;
			}
		}
	}
}

int compareProducts(const void *a, const void *b)
{
	const struct Product *productA = (const struct Product *)a;
	const struct Product *productB = (const struct Product *)b;

	if (productA->name == NULL) return (productB->name) ? 1 : 0;
	if (productB->name == NULL) return -1;

	if (productA->price < productB->price) return -1;
	if (productA->price > productB->price) return 1;

	return strcmp(productA->name, productB->name);
}


void	parent_process_task(pid_t pids[NUM_CHILDREN])
{
	char filePaths[NUM_CHILDREN][256];
	struct City aggregatedCities[MAX_CITIES] = {0};

	for (int i = 0; i < NUM_CHILDREN; i++)
	{
		snprintf(filePaths[i], sizeof(filePaths[i]), "results_%d.bin", pids[i]);
		FILE *file = fopen(filePaths[i], "rb");
		if (file)
		{
			while (!feof(file))
			{
				struct City newCity = {0};
				if (deserialize_city(file, &newCity) == -1) break;

				aggregate_city(aggregatedCities, &newCity);
			}
		}
		fclose(file);
	}

	uint64_t minTotal = UINT64_MAX;
	int minCityIndex = -1; // -1 indicates no city found yet
	for (int i = 0; i < MAX_CITIES; ++i) 
	{
		if (aggregatedCities[i].name && aggregatedCities[i].total < minTotal) {
			minTotal = aggregatedCities[i].total;
			minCityIndex = i;
		}
	}

	if (minCityIndex != -1) {
		qsort(aggregatedCities[minCityIndex].products, MAX_PRODUCTS, sizeof(struct Product), compareProducts);
		FILE *outputFile = fopen("output.txt", "w");
		if (outputFile)
		{
			fprintf(outputFile, "%s %lu.%02lu\n", aggregatedCities[minCityIndex].name, minTotal / 100, minTotal % 100);
			for (int i = 0; i < 5; i++)
			{
				if (aggregatedCities[minCityIndex].products[i].name != NULL)
				{
					uint32_t price = aggregatedCities[minCityIndex].products[i].price;
					fprintf(outputFile, "%s %u.%02u\n", aggregatedCities[minCityIndex].products[i].name, price / 100, price % 100);
				}
			}
			fclose(outputFile);
		}
	}
	else
		printf("No cities processed.\n");

	for (int i = 0; i < NUM_CHILDREN; i++)
		remove(filePaths[i]);
}




int main() {

	pid_t pids[NUM_CHILDREN];

    // int fd = open("input.txt", O_RDONLY);
    int fd = open("/Users/aajaanan/goinfre/input.txt", O_RDONLY);
    struct stat sb;
    if (fd == -1 || fstat(fd, &sb) == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char *file_in_memory = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (file_in_memory == MAP_FAILED) {
        perror("Error mmapping the file");
        return EXIT_FAILURE;
    }

	const off_t initial_segment_size = sb.st_size / NUM_CHILDREN;
	off_t current_offset = 0;

	for (int i = 0; i < NUM_CHILDREN; i++) {
		off_t offset = current_offset; // Start of the current segment
		off_t size = (i == NUM_CHILDREN - 1) ? (sb.st_size - offset) : initial_segment_size;

		if (i != 0) { // Adjust start for all but the first segment
			while (file_in_memory[offset] != '\n' && offset < sb.st_size) {
				offset++;
				size--;
			}
			offset++; // Skip the newline character
			size--; // Adjust size after skipping
		}

		if (i != NUM_CHILDREN - 1) { // Adjust end for all but the last segment
			off_t end = offset + size; // Initial end
			while (file_in_memory[end] != '\n' && end < sb.st_size) {
				end++;
			}
			size = end - offset + 1; // Include the newline character
		}

		pids[i] = fork();
		if (pids[i] == 0) { // Child
			printf("Child %d processing segment starting at %lld, size %lld\n", i, offset, size);
			process_segment(file_in_memory + offset, size);
			munmap(file_in_memory, sb.st_size);
			close(fd);
			exit(EXIT_SUCCESS);
		} else if (pids[i] < 0) {
			perror("fork failed");
			exit(EXIT_FAILURE);
		}

		current_offset = offset + size; // Prepare offset for the next segment
	}

    // Parent waits for all children to complete
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    munmap(file_in_memory, sb.st_size);
    close(fd);



	parent_process_task(pids);

    return EXIT_SUCCESS;
}