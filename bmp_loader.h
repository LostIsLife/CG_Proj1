#ifndef BMP_LOADER
#define BMP_LOADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BMP_H_SIZE 54

typedef struct
{
	unsigned char filename[50], header[ BMP_H_SIZE ];
  	unsigned int width, height, dataPos, image_size;
	FILE* fl;
	unsigned char* data;
} bmp;

bmp new_bmp( char* n_filename );
int error_check(bmp* target, int verbose);
int parse_file(bmp* target, int verbose);
void bmp_print_data(bmp);
void bmp_print (bmp);

#endif
