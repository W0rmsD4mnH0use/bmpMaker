#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#pragma pack(push, 1)
typedef struct { //14 bytes
        unsigned char bmtype[2];
        int32_t filesize;
	int32_t reserved;
        int32_t dataOffset;
} bmp_fh;

typedef struct{ //40 bytes
        int32_t bihSize;
        int32_t width;
        int32_t height;
        int16_t planes;
        int16_t bpp; //bits per pixel (dpi)
        int32_t compression;
        int32_t imageSize;
        int32_t xPerM;
        int32_t yPerM;
        int32_t colorsUsed;
        int32_t impColors;
} bmp_ih;

typedef struct{
	int8_t r,g,b;
} rgb_data;
#pragma pack(pop)

void saveBMP(const char* filename, int width, int height, int dpi, rgb_data* pixels){
	FILE* image;
	int image_size = width*height;
	int file_size = 54+4*image_size;

	bmp_fh* fileHed = (bmp_fh*)malloc(sizeof(bmp_fh));
	bmp_ih* infoHed = (bmp_ih*)malloc(sizeof(bmp_ih));

	strcpy(fileHed->bmtype, "BM");
	fileHed->filesize = file_size;
	fileHed->reserved = 0;
	fileHed->dataOffset = 0;

	infoHed->bihSize = 40;

	infoHed->width = width;
	infoHed->height = height;
	infoHed->planes = 1;
	infoHed->bpp = dpi;
	infoHed->compression = 0;
	infoHed->imageSize = 0;
	infoHed->xPerM = 1;
	infoHed->yPerM = 1;
	infoHed->colorsUsed = 0;
	infoHed->impColors = 0;

	image = fopen(filename, "wb");

	fwrite(fileHed, 1, sizeof(fileHed), image);
	fwrite(infoHed, 1, sizeof(infoHed), image);

	for(int i=0;i<image_size;i++){
		rgb_data RGB = pixels[i];
		int r = RGB.r;
		int g = RGB.g;
		int b = RGB.b;

		unsigned char pixel[3] = {r,g,b};
		fwrite(pixel, 1, sizeof(pixel), image);
	}
}

int main(){
	int width = 400;
	int height = 400;
	int dpi = 24;

	rgb_data imageData[width*height];

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if((i>50&&i<350)&&(j>50&&j<350)){
				imageData[(j*width)+i].r=55;
				imageData[(j*width)+i].g=55;
				imageData[(j*width)+i].b=55;
			}else{
				imageData[(j*width)+i].r=0;
				imageData[(j*width)+i].g=0;
				imageData[(j*width)+i].b=0;
			}
		}
	}
	
	saveBMP("Test.bmp", width, height, dpi, imageData);
}

