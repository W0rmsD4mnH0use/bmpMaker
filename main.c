#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct{
	int8_t r,g,b;
} rgb_data;

void saveBMP(const char* filename, int width, int height, int dpi, rgb_data* pixels){
	FILE* image;
	int image_size = width*height;
	int file_size = 54+4*image_size;
	int ppm = d

}

