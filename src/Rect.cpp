#include <iostream>
#include "../include/Rect.h"
#include "../data/settings.h"

Rect::Rect(int x, int y, int w, int h){
    x_pos = x;
    y_pos = y;
    width = w * SCALE;
    height = h * SCALE;
    camera_rect.x = x_pos;
    camera_rect.y = y_pos;
    camera_rect.w = (w * SCALE) + 200;
    camera_rect.h = (h * SCALE) + 200;
}

void Rect::draw(SDL_Renderer*& renderer){
    setRectPosition();

    if(testing_camera){
        SDL_SetRenderDrawColor(renderer, 0,0,255,0);
        SDL_RenderFillRect(renderer, &camera_rect);
    }

    SDL_SetRenderDrawColor(renderer, 255,0,0,0);
    SDL_RenderFillRect(renderer, &pos_rect);
}

void Rect::update(){
    x_pos += velocity.x;

    if (y_pos + width > WINDOW_HEIGHT){
        y_pos = WINDOW_HEIGHT - width;
    }

    else if(x_pos < 0){
        x_pos += player_speed;
    }

    else if(x_pos + width > WINDOW_WIDTH){
        x_pos -= player_speed;
    }
}

void Rect::applyGravity(){
    velocity.y += gravity;
    y_pos += velocity.y;
}


void Rect::handleEvent(SDL_Event& event){
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
        switch(event.key.keysym.sym){
            case SDLK_SPACE:
                if (grounded){
                    velocity.y = jump_limit;
                    grounded = false;
                }
            break;

            case SDLK_LEFT: velocity.x -= player_speed; break;
            case SDLK_RIGHT: velocity.x += player_speed; break;
        }
    }

    else if(event.type == SDL_KEYUP && event.key.repeat == 0){
        switch(event.key.keysym.sym){
            case SDLK_LEFT: velocity.x += player_speed; break;
            case SDLK_RIGHT: velocity.x -= player_speed; break;
        }
    }
}


bool Rect::collidesWithBlock(struct block& block){
    int topA = y_pos;
    int leftA = x_pos;
    int rightA = x_pos + width;
    int bottomA = y_pos + height;

    int topB = block.y;
    int leftB = block.x;
    int rightB = block.x + TILE_SIZE * SCALE;
    int bottomB = block.y + TILE_SIZE * SCALE;

    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    return true;

}

void Rect::handleHorizontalBlocksCollision(size_t amount, struct block*& blocks){
    for(size_t i = 0; i < amount; ++i){
        block currentBlock = blocks[i];
        if(collidesWithBlock(currentBlock)){
            if(velocity.x > 0 && x_pos < currentBlock.x){
                x_pos = currentBlock.x - width;
            }

            if(velocity.x < 0 && currentBlock.x < x_pos){
                x_pos = currentBlock.x + TILE_SIZE * SCALE;
            }
        }
    }
}

void Rect::handleVerticalBlocksCollision(size_t amount, struct block*& blocks){
    for(size_t i = 0; i < amount; ++i){
        block currentBlock = blocks[i];
        if(collidesWithBlock(currentBlock)){
            if(velocity.y > 0 && y_pos < currentBlock.y){
                y_pos = blocks[i].y - width;
                velocity.y = 0;
                grounded = true;
            }
            
            if(velocity.y < 0 && currentBlock.y < y_pos){
                velocity.y = 0;
                y_pos = currentBlock.y + TILE_SIZE * SCALE;
            }
        }
    }
}


void Rect::handleCamera(size_t amount, struct block*& blocks){
    if (camera_rect.y + camera_rect.h > WINDOW_HEIGHT){
        y_pos -= velocity.y;
        for(size_t i = 0; i < amount; ++i){
            blocks[i].y -= (int) velocity.y;
        }
    }

    else if (camera_rect.y < 0){
        y_pos += player_speed + gravity;
        for(size_t i = 0; i < amount; ++i){
            blocks[i].y += player_speed;
        }
    }

    else if (camera_rect.x < 0){
        x_pos += player_speed;
        for(size_t i = 0; i < amount; ++i){
            blocks[i].x += player_speed;
        }
    }

    else if (camera_rect.x + camera_rect.w > WINDOW_WIDTH && velocity.x > 0){
        x_pos -= player_speed;
        for(size_t i = 0; i < amount; ++i){
            blocks[i].x -= player_speed;
        }
    }
}

void Rect::setRectPosition(){
    pos_rect.x = x_pos;
    pos_rect.y = y_pos;
    pos_rect.w = width;
    pos_rect.h = height;
    camera_rect.x = x_pos - (camera_rect.w / 2) + (width / 2);
    camera_rect.y = y_pos - (camera_rect.h / 2) + (height / 2);
}

Rect::~Rect(){}
