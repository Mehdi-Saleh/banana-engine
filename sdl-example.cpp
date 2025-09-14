#ifndef SDL_EXAMPLE
#define SDL_EXAMPLE

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include "include/glad/glad.h"

class Renderer
{
    private: SDL_Window* window = nullptr;
    private: SDL_Renderer* sdlRenderer = nullptr;

    private: std::string windowName = "Window";
    private: int windowWidth = 10;
    private: int windowHeight = 10;



    public: Renderer()
    {
    }


    ~Renderer()
    {
        SDL_DestroyRenderer( sdlRenderer );
        SDL_DestroyWindow( window );
        SDL_Quit();
    }


    public: int Init( std::string windowName, int width, int height )
    {
        this->windowName = windowName;
        windowWidth = width;
        windowHeight = height;
        
        int exitCode = 0;
        exitCode = InitSDL();
        return exitCode;
    }


    private: int InitSDL()
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow( windowName.c_str(),windowWidth, windowHeight, 0 );
        if (window == nullptr) 
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }
        sdlRenderer = SDL_CreateRenderer(window, NULL);
        if (sdlRenderer == nullptr) 
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow( window );
            SDL_Quit();
            return 1;
        }

        return 0;
    }

    public: void Render()
    {
        SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( sdlRenderer );

        SDL_RenderPresent( sdlRenderer ); // Render the screen
    }
};

#endif