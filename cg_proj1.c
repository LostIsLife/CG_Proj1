#include "cg_proj1.h"
#include "bmp_loader.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

/*
	GLOBAL VARIABLES
*/
int debug = 1;
vec3d camera;
game_map* game = NULL;
GLuint textureID[3] = {1,2,3};
bmp texture;
GLfloat lightpos[] = {0.5, 1.0, 1.0, 1.0},
	specular[] = {1.0,1.0,1.0,1.0},
	diffuse[] = {1.0,1.0,1.0,1.0};


void load_texture(char* tex_name, int index)
{
	texture = new_bmp(tex_name);
	
	if ( parse_file(&texture,debug) != 0)
	{
		printf ("Error reading texture.\n");
		return;
	}

	glGenTextures(1, &textureID[index]);

	glBindTexture(GL_TEXTURE_2D, textureID[index]);
	glTexImage2D( GL_TEXTURE_2D,0, GL_RGB, texture.width, texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture.data);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//bmp_print(texture);

	glFinish();
}

void draw_cube_color( vec3d max, vec3d min)
{
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	glColor3f (0.0,0.0,1.0);

	glBegin(GL_POLYGON);
		//Face 1
		 glVertex3f(  min.x ,  min.y ,  max.z );
		 glVertex3f(  max.x ,  min.y ,  max.z );
		 glVertex3f(  max.x ,  min.y ,  min.z );
		 glVertex3f(  min.x ,  min.y ,  min.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 2
		 glVertex3f(  min.x ,  min.y ,  max.z );
		 glVertex3f(  max.x ,  min.y ,  max.z );
		 glVertex3f(  max.x ,  max.y ,  max.z );
		 glVertex3f(  min.x ,  max.y ,  max.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 3
		glVertex3f(  max.x ,  min.y ,  min.z );
		glVertex3f(  min.x ,  min.y ,  min.z );
		glVertex3f(  min.x ,  max.y ,  min.z );
		glVertex3f(  max.x ,  max.y ,  min.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 4
		glVertex3f(  min.x ,  min.y ,  max.z );
		glVertex3f(  min.x ,  min.y ,  min.z );
		glVertex3f(  min.x ,  max.y ,  min.z );
		glVertex3f(  min.x ,  max.y ,  max.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 5
		glVertex3f(  max.x ,  min.y ,  max.z );
		glVertex3f(  max.x ,  min.y ,  min.z );
		glVertex3f(  max.x ,  max.y ,  min.z );
		glVertex3f(  max.x ,  max.y ,  max.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 6
		glVertex3f(  min.x ,  max.y ,  max.z );
		glVertex3f(  max.x ,  max.y ,  max.z );
		glVertex3f(  max.x ,  max.y ,  min.z );
		glVertex3f(  min.x ,  max.y ,  min.z );
	glEnd();
}
void draw_cube( vec3d max, vec3d min, int texture_index)
{
	//glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	glBindTexture(GL_TEXTURE_2D, textureID[texture_index]);

	glBegin(GL_POLYGON);
		//Face 1
		glTexCoord2f( 0.0, 1.0); glVertex3f(  min.x ,  min.y ,  max.z );
		glTexCoord2f( 1.0, 1.0); glVertex3f(  max.x ,  min.y ,  max.z );
		glTexCoord2f( 1.0, 0.0); glVertex3f(  max.x ,  min.y ,  min.z );
		glTexCoord2f( 0.0, 0.0); glVertex3f(  min.x ,  min.y ,  min.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 2
		glTexCoord2f(0.0, 0.0); glVertex3f(  min.x ,  min.y ,  max.z );
		glTexCoord2f(1.0, 0.0); glVertex3f(  max.x ,  min.y ,  max.z );
		glTexCoord2f(1.0, 1.0); glVertex3f(  max.x ,  max.y ,  max.z );
		glTexCoord2f(0.0, 1.0); glVertex3f(  min.x ,  max.y ,  max.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 3
		glTexCoord2f(1.0,0.0); glVertex3f(  max.x ,  min.y ,  min.z );
		glTexCoord2f(0.0,0.0); glVertex3f(  min.x ,  min.y ,  min.z );
		glTexCoord2f(0.0,1.0); glVertex3f(  min.x ,  max.y ,  min.z );
		glTexCoord2f(1.0,1.0); glVertex3f(  max.x ,  max.y ,  min.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 4
		glTexCoord2f(0.0,1.0); glVertex3f(  min.x ,  min.y ,  max.z );
		glTexCoord2f(0.0,0.0); glVertex3f(  min.x ,  min.y ,  min.z );
		glTexCoord2f(1.0,0.0); glVertex3f(  min.x ,  max.y ,  min.z );
		glTexCoord2f(1.0,1.0); glVertex3f(  min.x ,  max.y ,  max.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 5
		glTexCoord2f(0.0,1.0); glVertex3f(  max.x ,  min.y ,  max.z );
		glTexCoord2f(0.0,0.0); glVertex3f(  max.x ,  min.y ,  min.z );
		glTexCoord2f(1.0,0.0); glVertex3f(  max.x ,  max.y ,  min.z );
		glTexCoord2f(1.0,1.0); glVertex3f(  max.x ,  max.y ,  max.z );
	glEnd();

	glBegin(GL_POLYGON);
		//Face 6
		glTexCoord2f(1.0,0.0); glVertex3f(  min.x ,  max.y ,  max.z );
		glTexCoord2f(1.0,1.0); glVertex3f(  max.x ,  max.y ,  max.z );
		glTexCoord2f(0.0,1.0); glVertex3f(  max.x ,  max.y ,  min.z );
		glTexCoord2f(0.0,0.0); glVertex3f(  min.x ,  max.y ,  min.z );
	glEnd();
}

void draw_map( matrix map )
{
	if (debug) printf("Drawing Map\n");

	vec3d colors[] = 
	{ 
			create_vec3d(0.0, 0.0, 1.0), 
			create_vec3d(1.0, 0.0, 0.0), 
			create_vec3d(0.0, 1.0, 0.0),
		  	create_vec3d(0.7, 0.7, 0.0),
			create_vec3d(0.3, 0.7, 0.7) 
	};

	vec3d min_point = create_vec(),
			max_point = create_vec();

	for (int cicle = 0; cicle < map.x; cicle++)
		for (int ndcicle = 0; ndcicle < map.y; ndcicle++)
			for (int rdcicle = 0; rdcicle < map.z; rdcicle++)
	{
		min_point = create_vec3d( cicle * map.tam, ndcicle * map.tam, rdcicle * map.tam);
		max_point = create_vec3d( (cicle+1) * map.tam, (ndcicle+1) * map.tam, (rdcicle+1) * map.tam);


		switch( map.el[cicle][ndcicle][rdcicle] )
		{
			//case 0: { draw_cube(min_point, max_point, colors[0]); break; }
			//case 1: { draw_cube(min_point, max_point, 0); break; }
			case 1: { draw_cube(min_point, max_point, 0); break; }
			case 2: { draw_cube(min_point, max_point, 1); break; }
			case 3: { draw_cube(min_point, max_point, 2); break; }
			//case 4: { draw_cube(min_point, max_point, colors[4]); break; }
		}
	}
}

/*

	WALL = RED
	PATH = BLUE
	BEGIN = GREEN
	END = YELLOW

*/

void look_at(double cam_x, double cam_y, double cam_z, double st, double nd, double rd)
{
	camera.x = cam_x;
	camera.y = cam_y;
	camera.z = cam_z;
/*	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(100.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
*/	
	glLoadIdentity();
	gluLookAt( cam_x, cam_y, cam_z, 
		   st,nd,rd,
		   0.0, 0.0, 1.0);

	if (debug) printf("Camera has been moved to (%f, %f, %f) pointing to (%f,%f,%f)\n", cam_x, cam_y, cam_z, st,nd,rd);
}

void display()
{
	int fow = 100;
	printf("Display Callback Function Activated\n");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//glBindTexture(GL_TEXTURE_2D, textureID);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec3d player = gm_get_player_coords(*game);
	
	lightpos[0] = player.x;
	lightpos[1] = player.y;
	lightpos[2] = player.z;
 	
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);	
	

	look_at( player.x, player.y, player.z, player.x * game->orientation.x * fow, player.y * game->orientation.y * fow, player.z * game->orientation.z * fow);

	draw_map(game->map);
	
	//print_vec(player);

	glFlush();
	printf("Done with Display\n");
}

void init_game()
{
	if(debug) printf ("Game Initialized!\n");
	game = malloc(sizeof(game_map));
	*game = gm_init();
	
	//game->map = matrix_test_level_0();
	game->map = create_matrix3i(25,25,1);
	matrix_populate (&game->map, 1);

	gm_gen2dMap(game, 0);	

	gm_simplify_map(game);
}

void keyboard_fun(unsigned char key, int x, int y)
{
	int final = -1;

	if (debug) printf("%c was pressed.\n", key);
	switch(key)
	{
		case 'w': 
		{ 
			final = gm_walk_foward(game); 
			if (final == FINAL_POINT)
			{
				printf ("A WINNER IS YOU!\n");
				getchar();
				exit(0);
			}
			break; 
		}
		case 'a': { gm_turn_character_left(game);   break; }
		case 'd': { gm_turn_character_right(game);  break; }
		case 's': { break; }
	}	  
	
	matrix_print(game->map);

	glutPostRedisplay();
}

void init_gl(int argc, char** argv)
{
	camera.x = 25.0;
	camera.y = 25.0;
	camera.z = 50.0;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition (0,0);
	glutInitWindowSize( 600, 600);
	glutCreateWindow(" Mazé by V1l3l45 & Chr15t1an ");

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//glDepthFunc(GL_LESS);

	GLfloat fogColor[4] = {1.0f,1.0f,1.0f,1.0f};

	//------------------------------------------
	// FOG
	// -----------------------------------------
	glEnable(GL_FOG);
	glFogf(GL_FOG_DENSITY, FOG_DENSITY);
	//glFogf( GL_FOG_START, 0.0);
	//-----------------------------------------
	//-----------------------------------------

	load_texture("./wall.bmp", textureID[0]);
	load_texture("./ceiling.bmp", textureID[1]);
	load_texture("./floor.bmp", textureID[2]);

	glClearColor( 0.0, 0.0, 0.0 ,0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_PROJECTION );
	gluPerspective(100.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	
	gluLookAt( camera.x, camera.y, camera.z,
					25.0, 25.0, 0.0,
					0.0, 1.0, 0.0);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard_fun);
}


int main(int argc, char** argv)
{
	printf(" Starting Main Function \n");
	init_game();
	init_gl(argc, argv);	

	glutMainLoop();
	return 0;
}

