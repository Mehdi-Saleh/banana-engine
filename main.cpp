#include <iostream>
#include "sdl-example.cpp"

int main( int argc, char* argv[] )
{
    Renderer renderer;
    renderer.Init( "Test Window", 800, 600 );

    for ( int i = 0; i < 14400; i++ )
        renderer.Render();

    return 0;
}
