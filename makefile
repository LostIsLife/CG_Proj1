LIBS=-lGLU -lGL -lglut 

all: cg_proj1.h cg_proj1.c bmp
	gcc cg_proj1.c bmp_loader.o $(LIBS) -o run

bmp: bmp_loader.h bmp_loader.c
	gcc -c bmp_loader.c -o bmp_loader.o

debug:
	gcc cg_proj1.c bmp_loader.o $(LIBS) -g3 -o run

clean:
	rm run; rm bmp_loader.o;
