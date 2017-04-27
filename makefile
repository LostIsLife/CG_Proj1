bmp: bmp_loader.h bmp_loader.c
	gcc -c bmp_loader.c -o bmp_loader.o
run: cg_proj1.h cg_proj1.c bmp
	gcc cg_proj1.c bmp_loader.o -lGLU -lGL -lglut -lGLEW -o run
clean:
	rm run; rm bmp_loader.o;
