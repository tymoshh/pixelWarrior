compile:
	cls
	g++ -Iinclude -Ilib -Iinclude/SDL2 -Isrc -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


# mingw32-make -f Makefile