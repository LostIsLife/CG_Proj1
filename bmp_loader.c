
#include "bmp_loader.h"

bmp new_bmp( char* n_filename )
{
	bmp result;
	strcpy(result.filename,n_filename);
	result.fl = NULL;
	result.width = 0;
	result.height = 0;
	result.dataPos = 0;
	result.image_size = 0;
	for (int cicle = 0; cicle < BMP_H_SIZE; cicle++)
		result.header[cicle] = '0';
	result.data = NULL;
	return result;
}

int error_check(bmp* target, int verbose)
{
	if (target->fl == NULL)
	{
		if (verbose) printf (" ERROR. Could not find the file.\n");
		return 1;
	}

	if (fread (target->header, 1, 54, target->fl) != 54)
	{
		if (verbose) printf(" ERROR. Header does not have 54 bytes. May not be a real bmp file. Stopping the execution.\n");
		return 2;
	}
	
	if (target->header[0] != 'B' || target->header[1] != 'M')
	{
		if (verbose) printf (" ERROR. File did not start with a BM.\n");
		return 3;
	}
	return 0;
}

int parse_file(bmp* target, int verbose)
{
	int error = -1;
	target->fl = fopen( target->filename, "rb" );

	if ( (error = error_check(target, verbose) ) != 0)
		return error;

	target->dataPos = 		*(int*)&(target->header[0x0A]);
	target->image_size = 	*(int*)&(target->header[0x22]);
	target->width = 		*(int*)&(target->header[0x12]);
	target->height = 		*(int*)&(target->header[0x16]);
	
	if (target->image_size == 0) target->image_size = target->width * target->height * 3;
	if (target->dataPos == 0) 	 target->dataPos = 54;

	if (target->image_size <= 0)
		return 4;

	target->data = malloc(sizeof(unsigned char) * target->image_size );

	fread(target->data, 1, target->image_size, target->fl);
	fclose(target->fl);

	printf ("YES");

	return 0;
}

void bmp_print_data (bmp target) { printf ("%s\n", target.data); }
void bmp_print(bmp target) 
{
	printf ("BMP with file %s\n Header:%s\n Width:%d, Height:%d, DataPos:%d, Image_Size:%d\n", target.filename, target.header, target.width, target.height, target.dataPos);
}
