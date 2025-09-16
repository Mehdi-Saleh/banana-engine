#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "banana_engine.cpp"


int main( int argc, char* argv[] )
{
    BananaEngine engine = BananaEngine();
    engine.Start();
    return 0;
}

