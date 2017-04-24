run: cg_proj1.h cg_proj1.c
	gcc cg_proj1.c -lGLU -lGL -lglut -o run
clean:
	rm run;
