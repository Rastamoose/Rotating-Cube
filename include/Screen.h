#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector> 

class Screen{
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;

    public:
    Screen(){
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(640*2, 480*2, 0, &window, &renderer);
        SDL_RenderSetScale(renderer,2,2);
    }

    void pixel(float x, float y){       //add to points vector and creats pixels that we want to draw
        points.emplace_back(x,y);       //creats a new point and adds it to the vector
    }

    void show(){        //draws the pixels
        SDL_SetRenderDrawColor(renderer,0,0,0,255);     //set draw colour to black 
        SDL_RenderClear(renderer);                       //and then clear screen (so screen basically turns black)

        SDL_SetRenderDrawColor(renderer,255,255,255,255);   //sets draw colour to white so we can see it on black screen
        for(auto& point : points){
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }

        SDL_RenderPresent(renderer);
    }

    void clear(){
        points.clear();
    }

    void input(){       //get input for exiting window
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                SDL_Quit();
                exit(0);
            }
        }
    }
};

#endif