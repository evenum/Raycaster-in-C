CC:= gcc


all:
	$(CC) -o game *.c `sdl2-config --cflags --libs` -lm
	
