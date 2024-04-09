#include "./init.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int map[MAP_BOUNDS][MAP_BOUNDS] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,
	1,0,1,1,1,1,0,1,0,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

int mapCord(int x){
	return (x * WALL_SIZE);
}

int unmapCord(int x){
	return (x / WALL_SIZE);
}

void initSDL(App *app, Player *player){
	
	int screenX = 0, screenY = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL_Init Failed!: %s.\n", SDL_GetError());
		exit(-1);
	}

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, 
								SCREEN_HEIGHT,
								SDL_WINDOW_RESIZABLE,
								&app->window,
								&app->renderer);	
	
	if(!app->window){
		printf("Failed to open window: %s\n",SDL_GetError());
	}
	if(!app->renderer){
		printf("Failed to create renderer: %s\n",SDL_GetError());
	}


	SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	SDL_RenderClear(app->renderer);
	drawMap(app);
}

void drawMap(App *app){

	SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	SDL_RenderClear(app->renderer);
	
	for(int y = 0; y < MAP_BOUNDS; y++){
		for(int x = 0; x < MAP_BOUNDS; x++){
			SDL_Rect rect = {mapCord(y), mapCord(x), WALL_SIZE, WALL_SIZE};
			if(map[x][y] == 1){
				SDL_SetRenderDrawColor(app->renderer, 150, 150, 150, 255);
				SDL_RenderFillRect(app->renderer, &rect);
			}
			else{
				SDL_SetRenderDrawColor(app->renderer, 50, 50, 0, 150);
				SDL_RenderDrawRect(app->renderer, &rect);
			}
		}
	}
}

void drawPlayer(App *app, Player *player){

	float startX = player->x;
	float startY = player->y;

	float endX = startX + 8 + (50 * cos(player->angle));
	float endY = startY + 8 + (50 * sin(player->angle));


	SDL_SetRenderDrawColor(app->renderer, 100, 0, 0, 255);
	SDL_Rect rect = {player->x, player->y, WALL_SIZE/2, WALL_SIZE/2};	
	SDL_RenderFillRect(app->renderer, &rect);
	
	SDL_RenderDrawLineF(app->renderer, 
						startX + 8,  startY + 8, 
						endX, endY);
	
	float distance = 32;
	float rayX = (mapCord(unmapCord(startX + distance)));
	float rayY = startY + 8;

	for(;;){
		if(map[unmapCord(rayY)][unmapCord(rayX)] != 1){
			rayX += 32;
		}
		else{break;}
	}
	


	SDL_SetRenderDrawColor(app->renderer, 0, 0, 255, 255);
	SDL_RenderDrawLineF(app->renderer, 
						startX + 8,  startY + 8, 
						rayX, rayY);


}

void updateMap(App *app, Player *player){
		
	if(((player->x == player->oldX) && (player->y == player->oldY))){ return; }	
	drawMap(app);
	drawPlayer(app, player);	
	player->oldX = player->x;
	player->oldY = player->y;
	SDL_RenderPresent(app->renderer);

}

bool detectCollision(App *app, Player *player){
		
	if(map[unmapCord(player->y)][unmapCord(player->x)] == 1 || 
		map[unmapCord(player->y+8)][unmapCord(player->x+8)]){
		return true;
	}
	return false;
}

void movePlayerForward(Player *player){
	player->x += (PLAYER_SPEED * (cos(player->angle)));
	player->y += (PLAYER_SPEED * (sin(player->angle)));
}

void movePlayerBackward(Player *player){
	player->x -= (PLAYER_SPEED * (cos(player->angle )));
	player->y -= (PLAYER_SPEED * (sin(player->angle )));
}


void cleanupSDL(App *app){
	
	SDL_Delay(5000);
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
}

