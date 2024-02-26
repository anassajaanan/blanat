#include "main.h"
#include <float.h> // For DBL_MAX
#include <stdio.h>


struct City cities[MAX_CITIES] = {0};

#define NUM_CHILDREN 16



void update_city_and_product_totals(const char *cityName, size_t cityNameLength, const char *productName, size_t productNameLength, double price)
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

	// write city name length
	size_t cityNameLength = strlen(city->name);
	fwrite(&cityNameLength, sizeof(size_t), 1, file);
	fwrite(city->name, sizeof(char), cityNameLength, file);
	fwrite(&city->total, sizeof(double), 1, file);

	// write number of products
	fwrite(&city->numProducts, sizeof(int), 1, file);

	for (int i = 0; i < MAX_PRODUCTS; i++)
	{
		if (city->products[i].name != NULL)
		{
			size_t productNameLength = strlen(city->products[i].name);
			fwrite(&productNameLength, sizeof(size_t), 1, file);
			fwrite(city->products[i].name, sizeof(char), productNameLength, file);
			fwrite(&city->products[i].price, sizeof(double), 1, file);
		}
	}

}

void child_process_task() {
    // Prepare file path using PID or another unique identifier
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "results_%d.bin", getpid());

    FILE* file = fopen(filePath, "wb");
    if (file) {
        // Serialize cities array and write to file
        for (int i = 0; i < MAX_CITIES; i++) {
			if (cities[i].name != NULL) {
				serialize_city(file, &cities[i]);
			}
        }
        fclose(file);
    }
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
            if (cityNameLength < sizeof(cityName)) {
                memcpy(cityName, line_start, cityNameLength);
                cityName[cityNameLength] = '\0';
            }

            // Extract productName
            char productName[MAX_PRODUCT_LENGTH] = {0};
            size_t productNameLength = second_comma - first_comma - 1;
            if (productNameLength < sizeof(productName)) {
                memcpy(productName, first_comma + 1, productNameLength);
                productName[productNameLength] = '\0';
            }

            // Extract price
            double price = atof(second_comma + 1);

			// Process the line
			update_city_and_product_totals(cityName, cityNameLength, productName, productNameLength, price);
        }
        // Move to the start of the next line
        line_start = line_end + 1;
    }
	// child_process_task();
}


int deserialize_city(FILE* file, struct City *city)
{
	// read city name length
	size_t cityNameLength;
	char cityName[MAX_CITY_LENGTH] = {0};
	if (fread(&cityNameLength, sizeof(size_t), 1, file) < 1)
	{
		return -1;
	}
	city->name = (char *)malloc(cityNameLength + 1);
	fread(city->name, sizeof(char), cityNameLength, file);
	city->name[cityNameLength] = '\0';


	fread(&city->total, sizeof(double), 1, file);

	// read number of products
	fread(&city->numProducts, sizeof(int), 1, file);

	for (int i = 0; i < city->numProducts; i++)
	{
		size_t productNameLength;
		double price;
		char productName[MAX_PRODUCT_LENGTH] = {0};
		fread(&productNameLength, sizeof(size_t), 1, file);
		fread(productName, sizeof(char), productNameLength, file);
		productName[productNameLength] = '\0';
		fread(&price, sizeof(double), 1, file);

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

// void aggregate_city(struct City* aggregatedCities[], struct City* newCity)
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
	{
		aggregatedCities[cityEntry->cityIndex].total += newCity->total;
	}

	for (int i = 0; i < MAX_PRODUCTS; i++)
	{
		if (newCity->products[i].name)
		{
			if (aggregatedCities[cityEntry->cityIndex].products[i].name == NULL)
			{
				// aggregatedCities[cityEntry->cityIndex].products[i] = newCity->products[i];
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
	// struct City *aggregatedCities[MAX_CITIES] = {0};
	struct City aggregatedCities[MAX_CITIES] = {0};

	for (int i = 0; i < NUM_CHILDREN; i++)
	{
		snprintf(filePaths[i], sizeof(filePaths[i]), "results_%d.bin", pids[i]);
		FILE *file = fopen(filePaths[i], "rb");
		if (file)
		{
			while (!feof(file))
			{
				// struct City newCity = {0};
				struct City newCity = {0};
				if (deserialize_city(file, &newCity) == -1)
				{
					break;
				}

				
				aggregate_city(aggregatedCities, &newCity);
				

			}
		}
		fclose(file);
	}

	// find the city with min total price
	// printf("Aggregated cities\n");
	// find_cheapest_city();
	double minTotal = DBL_MAX;
	int minCityIndex = -1; // -1 indicates no city found yet

	for (int i = 0; i < MAX_CITIES; ++i) 
	{
		if (aggregatedCities[i].name && aggregatedCities[i].total < minTotal) {
			minTotal = aggregatedCities[i].total;
			minCityIndex = i;
		}
	}

	if (minCityIndex != -1) {
		// printf("Cheapest city: %s with total price: %.2f\n", aggregatedCities[minCityIndex].name, minTotal);
		qsort(aggregatedCities[minCityIndex].products, MAX_PRODUCTS, sizeof(struct Product), compareProducts);

		// write the result to output.txt
		FILE *outputFile = fopen("output.txt", "w");
		if (outputFile)
		{
			// fprintf(outputFile, "Cheapest city: %s with total price: %.2f\n", aggregatedCities[minCityIndex].name, minTotal);
			fprintf(outputFile, "%s %.2f\n", aggregatedCities[minCityIndex].name, minTotal);
			for (int i = 0; i < 5; i++)
			{
				if (aggregatedCities[minCityIndex].products[i].name != NULL)
				{
					// fprintf(outputFile, "%s, %.2f\n", aggregatedCities[minCityIndex].products[i].name, aggregatedCities[minCityIndex].products[i].price);
					fprintf(outputFile, "%s %.2f\n", aggregatedCities[minCityIndex].products[i].name, aggregatedCities[minCityIndex].products[i].price);
				}
			}
			fclose(outputFile);
		}
	}
	else
	{
		printf("No cities processed.\n");
	}

	// remove the files
	for (int i = 0; i < NUM_CHILDREN; i++)
	{
		remove(filePaths[i]);
	}
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

	// parent process task
	// parent_process_task(pids);

    return EXIT_SUCCESS;
}