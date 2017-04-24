/*

	BASIC DOCUMENTATION

	function (param)
	{
		//INIT VARIABLES

		//CALCULATE

		//FREE POINTERS

		//RETURN IF NEEDED
	}



*/


#include "cg_proj1.h"
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void debug1()
{
	vec* st = new_vec3d( 3.0f, 4.0f, 5.0f );
	print_vec( *st );
	free(st);
}

int main(int argc, char** argv)
{
	debug1();

	return 0;
}
