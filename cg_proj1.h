#ifndef CG_PROJ1
#define CG_PROJ1

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	double x,y,z;
} vec;

vec* new_vec();
vec* new_vec3d(double, double, double);
void print_vec(vec);

vec* new_vec()
{
	return malloc(sizeof(vec));
}

vec* new_vec3d(double x, double y, double z)
{
	vec* result = malloc(sizeof(vec));
	result->x = x;
	result->y = y;
	result->z = z;
	return result;
}

void print_vec(vec target) { printf ("Vector: (%f, %f, %f)\n", target.x, target.y, target.z); }


#endif
