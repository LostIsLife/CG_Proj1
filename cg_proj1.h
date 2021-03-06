#ifndef CG_PROJ1
#define CG_PROJ1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START_POINT 2
#define FINAL_POINT 3
#define FOG_DENSITY 0.35

/* HEADER PART */

/*

	x = size on the x axis
	y = size on the y axis
	z = size on the z axis
	tam = each square is tam,tam,tam;

*/
typedef struct 
{
	int*** el, x, y, z, tam;
} matrix;

typedef struct
{
	double x,y,z;
} vec3d;

typedef struct
{
	matrix map;
	vec3d orientation;
} game_map;

matrix create_matrix();
matrix create_matrix3i(int new_x, int new_y, int new_z);
void matrix_populate(matrix* target, int a);
void matrix_print ( matrix target );
matrix matrix_test_level_o();

vec3d create_vec();
vec3d create_vec3d(double, double, double);

int rand_to( int);
void gm_gen2dMap( game_map*, int );
void gm_ramifyMap( game_map *, int);
void gm_simplify( game_map*, int );

/* Code Part */



matrix create_matrix()
{
	matrix result;
	result.x = 0;
	result.y = 0;
	result.z = 0;
	result.tam = 1;
	result.el = NULL;

	srand(time(NULL));
}


//CHECK FOR ZEROES, CANT BE ZEROES
matrix create_matrix3i(int new_x, int new_y, int new_z)
{
	matrix result;
	result.x = new_x;
	result.y = new_y;
	result.z = new_z + 2;
	result.tam = 5;

	result.el = malloc(sizeof(int**) * new_x);
	//Check for error

	for (int cicle = 0; cicle < new_x; cicle++)
	{
		result.el[cicle] = malloc(sizeof(int*) * new_y );
		for (int ndcicle = 0; ndcicle < new_y; ndcicle++)
		{
			result.el[cicle][ndcicle] = malloc(sizeof(int) * new_z );
			for (int rdcicle = 0; rdcicle < new_z; rdcicle++)
				result.el[cicle][ndcicle][rdcicle] = 0;
		}
	}

	return result;
}


void matrix_populate(matrix* target, int a)
{
	for (int cicle = 0; cicle < target->z; cicle++)
		for (int ndcicle = 0; ndcicle < target->x; ndcicle++)
			for (int rdcicle = 0; rdcicle < target->y; rdcicle++)
				target->el[ndcicle][rdcicle][cicle] = a;
}

void matrix_print ( matrix target )
{
	for (int cicle = 0; cicle < target.z; cicle++)
	{
		printf("Z=%d\n", cicle);
		for (int ndcicle = 0; ndcicle < target.x; ndcicle++)
		{
			for (int rdcicle = 0; rdcicle < target.y; rdcicle++)
				printf(" %2d ", target.el[ndcicle][rdcicle][cicle]);
			printf("\n");
		}
		printf("\n");
	}
}


matrix matrix_test_level_0()
{
	matrix result = create_matrix3i( 25,25,3 );
	int cicle = 0, ndcicle = 0;

	matrix_populate( &result, 1 );


	for(cicle = 1; cicle < 17; cicle++)
		result.el[cicle][1][1] = 0;

	for (ndcicle = 1; ndcicle < 24; ndcicle++)
		result.el[cicle][ndcicle][1] = 0;

	result.el[1][1][1] = 2;
	result.el[2][1][1] = 4;
	result.el[16][23][1] = 3;

	return result;
}

/*

	VEC3D

*/


vec3d create_vec()
{
	vec3d result;
	result.x = 0.0;
	result.y = 0.0;
	result.z = 0.0;
	return result;
}

vec3d create_vec3d(double a, double b, double c)
{
	vec3d result;
	result.x = a;
	result.y = b;
	result.z = c;
	return result;
}

int vec_equal2v(vec3d st, vec3d nd) { return ( st.x == nd.x && st.y == nd.y && st.z == nd.z ); }
int vec_equal3d(vec3d st, double a, double b, double c) { return ( st.x == a && st.y == b && st.z == c ); }
void vec_assign( vec3d* target, double a, double b, double c) { target->x = a; target->y = b; target->z = c; }

void print_vec( vec3d target ) { printf("(%f, %f, %f)\n", target.x, target.y, target.z); }

/*

	Game_map

*/

game_map gm_init()
{
	game_map result;
	result.orientation = create_vec3d(1.0,0.0,0.0);
	return result;
}

vec3d gm_get_player_coords(game_map target)
{
	for (int cicle = 0; cicle < target.map.z; cicle++)
		for (int ndcicle = 0; ndcicle < target.map.x; ndcicle++)
			for (int rdcicle = 0; rdcicle < target.map.y; rdcicle++)
			/*
				if (target.map.el[ndcicle][rdcicle][cicle] == 4)
					return create_vec3d( (ndcicle+1) * target.map.tam + target.map.tam / 2, (1+rdcicle) * target.map.tam + target.map.tam / 2, (1+cicle) * target.map.tam + target.map.tam / 2);
			*/
				if (target.map.el[ndcicle][rdcicle][cicle] == 4)
					return create_vec3d( (ndcicle) * target.map.tam + target.map.tam / 2, (rdcicle) * target.map.tam + target.map.tam / 2, (cicle) * target.map.tam + target.map.tam / 2);


	return create_vec();
}

vec3d gm_get_player_coords_xyz(game_map target)
{
	for (int cicle = 0; cicle < target.map.z; cicle++)
		for (int ndcicle = 0; ndcicle < target.map.x; ndcicle++)
			for (int rdcicle = 0; rdcicle < target.map.y; rdcicle++)
				if (target.map.el[ndcicle][rdcicle][cicle] == 4)
					return create_vec3d( ndcicle, rdcicle, cicle );
	return create_vec();
}

void gm_turn_character_right( game_map* target )
{
	// Foward to left
	if (vec_equal3d( target->orientation, 1.0, 0.0, 0.0)) 
		vec_assign( &target->orientation, 0.0, -1.0, 0.0);
	//left to back
	else if (vec_equal3d( target->orientation, 0.0, -1.0, 0.0) )
		vec_assign( &target->orientation, -1.0, 0.0, 0.0);
	//back to right
	else if (vec_equal3d( target->orientation, -1.0, 0.0, 0.0) )
		vec_assign( &target->orientation, 0.0, 1.0, 0.0);
	//right to foward
	else if (vec_equal3d( target->orientation, 0.0, 1.0, 0.0) )
		vec_assign( &target->orientation, 1.0, 0.0, 0.0);
	
	else vec_assign( &target->orientation, 1.0, 0.0, 0.0);
}

void gm_turn_character_left( game_map* target )
{
	// Foward to right
	if ( vec_equal3d( target->orientation, 1.0, 0.0, 0.0) )
		vec_assign( &target->orientation, 0.0, 1.0, 0.0);
	//right to back
	else if ( vec_equal3d( target->orientation, 0.0, 1.0, 0.0) )
		vec_assign( &target->orientation, -1.0, 0.0, 0.0);
	//back to left
	else if ( vec_equal3d( target->orientation, -1.0, 0.0, 0.0) )
		vec_assign( &target->orientation, 0.0, -1.0, 0.0);
	//left to foward
	else if ( vec_equal3d( target->orientation, 0.0, -1.0, 0.0) )
		vec_assign( &target->orientation, 1.0, 0.0, 0.0);
	
	else vec_assign( &target->orientation, 1.0, 0.0, 0.0);
}

int gm_walk_foward(game_map *game)
{
	vec3d coords = gm_get_player_coords_xyz(*game);
	int coord_value = game->map.el[(int)(coords.x + game->orientation.x)][(int)(coords.y + game->orientation.y)][(int)(coords.z + game->orientation.z)];

	print_vec(game->orientation);
	printf("Coord: %d\n", coord_value);

	if (coord_value != 1)
	{
		game->map.el[(int)(coords.x + game->orientation.x)][(int)(coords.y + game->orientation.y)][(int)(coords.z + game->orientation.z)] = 4;
		game->map.el[(int)coords.x][(int)coords.y][(int)coords.z] = 0;
	}
	return coord_value;
}

// Simplify turns all the 1 that are not part of a wall (have no 0 next to them) into a -1, to simplify the drawing
void gm_simplify_map ( game_map* target )
{
	for (int cicle = 0; cicle < target->map.x; cicle++)
		for (int ndcicle = 0; ndcicle < target->map.y; ndcicle++)
			for (int rdcicle = 0; rdcicle < target->map.z; rdcicle++)
	{
		if (target->map.el[cicle][ndcicle][rdcicle] != 1)
			continue;

		//Check X axis
		if (cicle > 0 && abs(target->map.el[cicle - 1][ndcicle][rdcicle]) != 1)
			continue;
		if (cicle < (target->map.x - 1) && abs(target->map.el[cicle + 1][ndcicle][rdcicle]) != 1)
			continue;

		//Check Y axis
		if (ndcicle > 0 && abs(target->map.el[cicle][ndcicle - 1][rdcicle]) != 1)
			continue;
		if (ndcicle < (target->map.y - 1) && abs(target->map.el[cicle][ndcicle + 1][rdcicle]) != 1)
			continue;

		//Check Z axis
		if (rdcicle > 0 && abs(target->map.el[cicle][ndcicle][rdcicle - 1]) != 1)
			continue;
		if (rdcicle < (target->map.z - 1) && abs(target->map.el[cicle][ndcicle][rdcicle + 1]) != 1)
			continue;

		target->map.el[cicle][ndcicle][rdcicle] = -1;

	}

}

int rand_to( int limit ) { return rand() % limit; }

void gm_choose_spot(game_map* target, int* x, int* y, int* z, int verbose)
{
	int possible_x, possible_y, possible_z;

	while(1)
	{
		possible_x = rand_to(target->map.x - 2) + 1;
		possible_y = rand_to(target->map.y - 2) + 1;
		possible_z = rand_to(target->map.z - 2) + 1;

		if (verbose) printf ("Possible Spot: %d,%d,%d\n", possible_x, possible_y, possible_z);

		if( 
			target->map.el[possible_x - 1][possible_y][possible_z] == 0 ||
			target->map.el[possible_x + 1][possible_y][possible_z] == 0 ||
			target->map.el[possible_x][possible_y - 1][possible_z] == 0 ||
			target->map.el[possible_x][possible_y + 1][possible_z] == 0 ||
			target->map.el[possible_x][possible_y][possible_z - 1] == 0 ||
			target->map.el[possible_x][possible_y][possible_z + 1] == 0
		  )
			continue;
		
		*x = possible_x;
		*y = possible_y;
		*z = possible_z;

		return;
	}
}

void gm_gen2dMap( game_map* target, int verbose )
{
	srand(time(NULL));

	int history[2] = { 0,0 };
	int x = 0, y = 0, z = 0, 
		 limit = rand_to( target->map.x * target->map.y), 
		 r = 0, inv_r = 0,
		 player_placed = 0,
		 signal = 0;

	gm_choose_spot( target, &x, &y, &z, verbose);
	
	target->map.el[x][y][z] = START_POINT;

	if (verbose) printf ("LIMIT: %d\n", limit);

	for (int cicle = 0; cicle < limit; cicle++)
	{
		if( verbose) printf ("Cicle: %d\n", cicle);

		while(1)
		{
			r = rand_to(4) - 2; 
			inv_r = -1 * r;

			if (verbose) printf ("X,Y,Z = (%d,%d,%d)\n R:%d \n", x,y,z,r);

			// direction can't be 0 and cannot be the inverse of the last two directions
			if(
				r == 0 ||
				history[0] == inv_r ||
				history[1] == inv_r
			) continue;

			//Check if out of boundaries, if yes calculate again, else break the infinite loop

			switch(r)
			{
				case -2: { if ( x < target->map.x - 2){ signal = 1; x++; break; } }
				case -1: { if ( x > 2) { signal = 1; x--; break; } }
				case 1:  { if ( y < target->map.y - 2) { signal = 1; y++; break; } }
				case 2:  { if ( y > 2) { signal = 2; y--; break; } }
				default: continue;
			}
			if (signal == 1)
			{
				signal = 0;
				break;
			}
		}

		history[0] = history[1];
		history[1] = r;

		if (player_placed)
			target->map.el[x][y][z] = 0;
		else 
		{
			target->map.el[x][y][z] = 4;
			player_placed = 1;
		}

	}

		target->map.el[x][y][z] = FINAL_POINT;
}

void gm_ramifyMap( game_map * target, int verbose)
{

}

void gm_simplify( game_map* target, int verbose)
{

}

#endif



/*
	Matrix values:
		0-> Free to walk on
		1-> Wall
		2-> Beginning
		3-> Ending
		4-> Character

	Matrix Specifications:
		x, y must be greater than 0
		z must be greater than 2
	



*/
