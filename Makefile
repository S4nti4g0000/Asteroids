all:
	g++ -Isrc/include -Lsrc/lib -o AYYmain main.cpp -lmingw32 -lSDL2main -lSDL2