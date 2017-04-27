
#include <stdio.h>			// Header File For Standard Input / Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <string.h>			// Header File For String Management
#include <stdlib.h>
#include <OpenGL/gl.h>			// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>			// Header File For The GLu32 Library
#include <GLUT/glut.h>			// Header File For The GLUT Library

// Constants -----------------------------------------------------------------

#define kWindowWidth	512
#define kWindowHeight	256

#define false 0
#define true 1

// Structures ----------------------------------------------------------------

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

typedef struct Image Image;

int flag=0;

static unsigned int getint(FILE *fp)
{
  int c, c1, c2, c3;

  /*  get 4 bytes */ 
  c = getc(fp);  
  c1 = getc(fp);  
  c2 = getc(fp);  
  c3 = getc(fp);
  
  return ((unsigned int) c) +   
    (((unsigned int) c1) << 8) + 
    (((unsigned int) c2) << 16) +
    (((unsigned int) c3) << 24);
}

static unsigned int getshort(FILE* fp)
{
  int c, c1;
  
  /* get 2 bytes*/
  c = getc(fp);  
  c1 = getc(fp);

  return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

// Function Prototypes -------------------------------------------------------

GLvoid InitGL(GLvoid);
GLvoid DrawGLScene(GLvoid);
GLvoid ReSizeGLScene(int Width, int Height);
GLvoid Idle(GLvoid);
int LoadBMP(char *filename, Image *texture);
GLvoid LoadTexture(GLvoid);

// Global Variables ----------------------------------------------------------

GLuint texture_id[1];

GLfloat			xrot;			// X Rotation ( NEW )
GLfloat			yrot;			// Y Rotation ( NEW )
GLfloat			zrot;			// Z Rotation ( NEW )

// Keyboard method to allow ESC key to quit 
void keyboard(unsigned char key,int x,int y) 
{        
if(key==27) exit(0); 
if(key==13) {	//Enter
		flag=1;
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}
if(key=='a') glBlendFunc(GL_SRC_COLOR,GL_SRC_COLOR);

glutPostRedisplay();
} 


// Main ----------------------------------------------------------------------

int main(int argc, char** argv)
{
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(kWindowWidth, kWindowHeight); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow("textures - *.bmp"); //(argv[0]);
	
	InitGL();
 
    glutDisplayFunc(DrawGLScene); 
    glutReshapeFunc(ReSizeGLScene);
	glutKeyboardFunc(keyboard);  
    glutIdleFunc(Idle);
	
	xrot = 30;
	yrot = 30;		
	zrot = 30;
	
    glutMainLoop();
  
    return 0;
}

// InitGL --------------------------------------------------------------------

GLvoid InitGL(GLvoid)
{
	
	LoadTexture();				// Load The Texture(s) ( NEW )
	glEnable(GL_TEXTURE_2D);		// Enable Texture Mapping ( NEW )
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// This Will Clear The Background Color To Black
	glClearDepth(1.0);			// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);		// Enables Depth Testing 
	glShadeModel(GL_SMOOTH);		// Enables Smooth Color Shading


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat) kWindowWidth / (GLfloat) kWindowHeight, 0.1f, 100.0f);	
												
	glMatrixMode(GL_MODELVIEW);

}

// Idle ----------------------------------------------------------------------

GLvoid Idle(GLvoid)
{
	xrot += 0.3f;			// X Axis Rotation
	yrot += 0.2f;			// Y Axis Rotation
	zrot += 0.4f;			// Z Axis Rotation
	
	glutPostRedisplay();
}

// DrawGLScene ---------------------------------------------------------------

GLvoid DrawGLScene(GLvoid)
{    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-5.0f);
	
	glRotatef(xrot,1.0f,0.0f,0.0f);		// Rotate On The X Axis
	glRotatef(yrot,0.0f,1.0f,0.0f);		// Rotate On The Y Axis
//	glRotatef(zrot,0.0f,0.0f,1.0f);		// Rotate On The Z Axis

glDisable(GL_BLEND);
	
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);	
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
	glEnd();

if (flag==1){

	glEnable(GL_BLEND);

	glColor4f(0.0f,0.0f,1.0f,0.5f);			// Full Brightness, 50% Alpha ( NEW )
	
	glBegin(GL_QUADS);
		// Front Face
		 glVertex3f(-1.0f, -1.0f,  1.5f);	// Bottom Left Of The Texture and Quad
		 glVertex3f( 1.0f, -1.0f,  1.5f);	// Bottom Right Of The Texture and Quad
		 glVertex3f( 1.0f,  1.0f,  1.5f);	// Top Right Of The Texture and Quad
		 glVertex3f(-1.0f,  1.0f,  1.5f);	// Top Left Of The Texture and Quad
	glEnd();

	glColor4f(0.0f,1.0f,0.0f,1.0f);			// Full Brightness, 0% Alpha ( NEW )

	glDisable(GL_BLEND);

	
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -1.0f,  2.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(0.5f, 0.0f); glVertex3f( .5f, -1.0f,  2.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(0.5f, 0.5f); glVertex3f( .5f,  1.0f,  2.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 0.5f); glVertex3f(-.5f,  1.0f,  2.0f);	// Top Left Of The Texture and Quad
	glEnd();
	
}
	
    glutSwapBuffers();
    glFlush();
}

// ReSizeGLScene ------------------------------------------------------------

GLvoid ReSizeGLScene(int Width, int Height)
{
    glViewport (0, 0, (GLsizei) Width, (GLsizei) Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLfloat) Width / (GLfloat) Height, 0.1, 100.0);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// LoadGLTextures ----------------------------------------------------------


GLvoid LoadTexture(GLvoid)
{	
	Image *TextureImage;
    
	TextureImage = (Image *) malloc(sizeof(Image));
	
	if (TextureImage == NULL) 
	{
		printf("Error allocating space for image");
		exit(1);
	}
	
		
//	LoadBMP("../Logo.bmp", TextureImage);
	LoadBMP("../tex1.bmp", TextureImage);

	glGenTextures(1, &texture_id[0]);
		
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);		// Create The Texture

	free (TextureImage->data);
	free( TextureImage );

}



//--------- loading image BMP

int LoadBMP(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 /*  size of the image in bytes. */
    unsigned long i;                    /*  standard counter. */
    unsigned short int planes;          /*  number of planes in image (must be 1)  */
    unsigned short int bpp;             /*  number of bits per pixel (must be 24) */
    char temp;                          /*  used to convert bgr to rgb color. */

    /*  make sure the file is there. */
    if ((file = fopen(filename, "rb"))==NULL) {
      printf("File Not Found : %s\n",filename);
      return 0;
    }
    
    /*  seek through the bmp header, up to the width height: */
    fseek(file, 18, SEEK_CUR);

    /*  No 100% errorchecking anymore!!! */

    /*  read the width */    image->sizeX = getint (file);
    
    /*  read the height */ 
    image->sizeY = getint (file);
    
    /*  calculate the size (assuming 24 bits or 3 bytes per pixel). */
    size = image->sizeX * image->sizeY * 3;

    /*  read the planes */    
    planes = getshort(file);
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    /*  read the bpp */    
    bpp = getshort(file);
    if (bpp != 24) {
      printf("Bpp from %s is not 24: %u\n", filename, bpp);
      return 0;
    }
	
    /*  seek past the rest of the bitmap header. */
    fseek(file, 24, SEEK_CUR);

    /*  read the data.  */
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { /*  reverse all of the colors. (bgr -> rgb) */
      temp = image->data[i];
      image->data[i] = image->data[i+2];
      image->data[i+2] = temp;
    }

    fclose(file); /* Close the file and release the filedes */

    /*  we're done. */
    return 1;
}

