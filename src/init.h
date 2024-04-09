#ifndef _INITS_H
#define _INITS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

#define WALL_SIZE 32
#define MAP_BOUNDS SCREEN_WIDTH/WALL_SIZE

#define PLAYER_SPEED 4
#define PLAYER_ANGLE (M_PI_4)

typedef struct {
	
	SDL_Window *window;
	SDL_Renderer *renderer;

}App;

typedef struct{
	
	float x, y, angle;
	float oldX, oldY;

}Player;

typedef struct{
	float camX, camY;
} cameraPlane;

typedef struct{
	
	float length, angle;


}ray;

typedef struct{
	float x, y;
}nextSquare;

void initSDL(App *, Player *);
void cleanupSDL(App *);
void drawMap(App *);
void drawPlayer(App *, Player *);
void updateMap(App *, Player *);
bool detectCollision(App *, Player *);
void movePlayerForward(Player *);
void movePlayerBackward(Player *);
#endif
