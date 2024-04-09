#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include "./init.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* args[]){
	
	App app;
	Player player = {128, 128, 128, 128};
	player.angle = 0;

	initSDL(&app, &player);

	SDL_Event event;	while(1){
	while(SDL_PollEvent(&event)){
	switch (event.type) {
		case SDL_QUIT:
			SDL_Quit();			
			exit(0);
			break;
		case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					movePlayerForward(&player);
					if(detectCollision(&app, &player) == 1){
						player.x = player.oldX;
						player.y = player.oldY;
						break;
					}
					break;
				case SDLK_DOWN:
					movePlayerBackward(&player);
					if(detectCollision(&app, &player) == 1){
						player.x = player.oldX;
						player.y = player.oldY;
						break;
					}
					break;
				case SDLK_LEFT:
					player.angle -= PLAYER_ANGLE;
					if(player.angle == 360){
						player.angle = 0;
					}
					break;
				case SDLK_RIGHT:	
					player.angle += PLAYER_ANGLE;
					if(player.angle == -360){
						player.angle = 0;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
		}
	}
	
	updateMap(&app, &player);	
	SDL_Delay(16);
}

cleanupSDL(&app);

}
