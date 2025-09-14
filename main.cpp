#include <iostream>
#include <SDL3/SDL.h>
#include "opengl-example.cpp"

int main( int argc, char* argv[] )
{
    Renderer renderer;
    renderer.Init( "Test Window", 800, 600 );

    std::cout << "Hell-Oh!" << std::endl;

    bool running = true;
    // while ( running )
    // {
    //     SDL_Event event;
    //     while ( SDL_PollEvent( &event ) ) 
    //     {
    //         if ( event.type == SDL_EVENT_QUIT ) 
    //         {
    //             running = false;
    //         }
    //     }
        
        renderer.Render();
    // }

    return 0;
}
