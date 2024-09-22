#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "./include/Rect.h"
#include "./data/settings.h"
#include "./data/level.h"

using std::cout;
using std::endl;
using std::cerr;
using std::string;

void sdlInit(SDL_Window*& window, SDL_Renderer*& renderer);
void sdlEnd(SDL_Window*& window, SDL_Renderer*& renderer);
struct block* createCollisionBlocks(size_t& amount);
void setBlocksStartingPosition(int x, int y, size_t amount, struct block*& blocks);
void drawCollisionBlocks(SDL_Renderer*& renderer, SDL_Rect tile, size_t amount, struct block*& blocks);


int main(int argc, char * argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    try{
        sdlInit(window, renderer);
    }
    catch(int e){
        switch(e){
            case 99:
                exit(EXIT_FAILURE);
            break;
            case 98:
                exit(EXIT_FAILURE);
            break;
            case 97:
                exit(EXIT_FAILURE);
            break;
        }
    }

    Rect player(145,100,TILE_SIZE, TILE_SIZE);

    SDL_Rect rect;
    rect.w = TILE_SIZE * SCALE;
    rect.h = TILE_SIZE * SCALE;
    size_t amount = 0;
    struct block* collision_blocks = createCollisionBlocks(amount);
    setBlocksStartingPosition(0, 90, amount, collision_blocks);

    bool running = true;
    while(running){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) running = false;
            player.handleEvent(event);
        }

        player.handleCamera(amount, collision_blocks);
        player.update();
        player.handleHorizontalBlocksCollision(amount, collision_blocks);
        player.applyGravity();
        player.handleVerticalBlocksCollision(amount, collision_blocks);

        SDL_SetRenderDrawColor(renderer, 54,69,79,0);
        SDL_RenderClear(renderer);

        player.draw(renderer);
        drawCollisionBlocks(renderer, rect, amount, collision_blocks);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    sdlEnd(window, renderer);
    delete[] collision_blocks;
    return 0;
}


void sdlInit(SDL_Window*& window, SDL_Renderer*& renderer){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "ERROR 99!...sdl video failed to initialize" << SDL_GetError() << endl;
        throw 99;
    }
    else{
        window = SDL_CreateWindow("SDL2 Platformer template by: Lu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            cerr << "ERROR 98!...sdl window failed to be created..." << SDL_GetError() << endl;
            throw 98;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL){
                cerr << "ERROR 97!...sdl renderer failed to be created" << SDL_GetError() << endl;
                throw 97;
            }
        }
    }
}

void sdlEnd(SDL_Window*& window, SDL_Renderer*& renderer){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

struct block* createCollisionBlocks(size_t& amount){
    for(int i = 0; i < MAP_HEIGHT; ++i){
        for(int j = 0; j < MAP_WIDTH; ++j){
            if(collision_blocks_array[i][j] > -1){
                amount++;
            }
        }
    }

    struct block *blocks = new block[amount];

    int index = 0;
    for(int i = 0; i < MAP_HEIGHT; ++i){
        for(int j = 0; j < MAP_WIDTH; ++j){
            if(collision_blocks_array[i][j] > -1){
                blocks[index].x = j * TILE_SIZE * SCALE;
                blocks[index].y = i * TILE_SIZE * SCALE;
                index++;
            }
        }
    }

    return blocks;
}


void setBlocksStartingPosition(int x, int y, size_t amount, struct block*& blocks){
    for(size_t i = 0; i < amount; ++i){
        blocks[i].x -= (x * player_speed) * SCALE;
        blocks[i].y -= (y * player_speed) * SCALE;
    }
}

void drawCollisionBlocks(SDL_Renderer*& renderer, SDL_Rect tile, size_t amount, struct block*& blocks){
    for(size_t i = 0; i < amount; ++i){
        tile.x = blocks[i].x;
        tile.y = blocks[i].y;
        SDL_SetRenderDrawColor(renderer, 0,255,0,0);
        SDL_RenderFillRect(renderer, &tile);
    }
}


