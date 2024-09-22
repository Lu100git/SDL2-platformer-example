#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>


class Rect{
    public:
        Rect(int x, int y, int w, int h);
        void draw(SDL_Renderer*&);
        void update();
        void applyGravity();
        void handleEvent(SDL_Event& event);
        bool collidesWithBlock(struct block& block);
        void handleHorizontalBlocksCollision(size_t amount, struct block*& blocks);
        void handleVerticalBlocksCollision(size_t amount, struct block*& blocks);
        void handleCamera(size_t amount, struct block*& blocks);
        void setRectPosition();
        virtual ~Rect();
    private:
        struct{
            int x = 0;
            float y = 0;
        }velocity;

        int x_pos;
        int y_pos;
        int width;
        int height;
        bool grounded = false;

        SDL_Rect pos_rect;
        SDL_Rect camera_rect;
};

#endif // RECT_H
