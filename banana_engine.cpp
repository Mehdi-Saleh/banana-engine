#ifndef BANANA_ENGINE
#define BANANA_ENGINE


#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include "shader.h"


class BananaEngine
{
    private: GLFWwindow* window = nullptr;
    private: std::string currentExecutablePath = "\0";

    private: float time = 0.0;

    private: bool x = false;
    private: bool z = false;

    private: Shader* shader;
    private: Shader* shader2;

    private: unsigned int triangleVBO;
    private: unsigned int triangleVAO;
    private: unsigned int rectangleVBO;
    private: unsigned int rectangleVAO;
    private: unsigned int rectangleEBO;


    public: void Start()
    {
        if ( Init() != 0 )
        {
            std::cout << "Failed to start engine. Terminating proccess!" << std::endl;
            return;
        }

        LoadShaders();
        LoadTriangle();
        LoadRectangle();

        while( !glfwWindowShouldClose( window ) )
        {
            time = glfwGetTime();
            HandleInput();
            Render();
            glfwSwapBuffers( window );
            glfwPollEvents();
        }
        
        UnloadShaders();
        glfwTerminate();
    }


    private: int Init()
    {
        glfwInit();
        glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        // UNCOMMENT NEXT LINE IF ON MAC
        // glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
        
        window = glfwCreateWindow( 800, 600, "LearnOpenGL", NULL, NULL );
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent( window );
        
        
        if (!gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress ) )
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }  
        
        glViewport( 0, 0, 800, 600 );
        // glfwSetFramebufferSizeCallback( window, (( GLFWwindow* window, int width, int height ) => OnWindowResized( width, height )) );
        
        return 0;
    }


    private: void HandleInput()
    {
        if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
            glfwSetWindowShouldClose( window, true );
        x = glfwGetKey( window, GLFW_KEY_X ) == GLFW_PRESS;
        z = glfwGetKey( window, GLFW_KEY_Z ) == GLFW_PRESS;
    }


    private: void Render()
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        if ( z ) 
            shader->SetFloat4( "renderColor", sin( time*2.0+M_PI )*0.5+0.5, sin( time*2.0 )*0.5+0.5, 0.0, 1.0 );
        
        // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        if ( x )
            DrawRectangle();
        else
            DrawTriangle();
    }
    
    
    private: void LoadTriangle()
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        };
        glGenVertexArrays( 1, &triangleVAO );
        glBindVertexArray( triangleVAO );
        glGenBuffers( 1, &triangleVBO );
        glBindBuffer( GL_ARRAY_BUFFER, triangleVBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6*sizeof( float ), (void*)0 );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6*sizeof( float ), (void*)( 3 * sizeof( float ) ) );
        glEnableVertexAttribArray( 1 );

        glBindVertexArray( 0 );
    }


    private: void LoadRectangle()
    {
        float vertices[] = {
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.8f,
            0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,  0.8f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        };
        unsigned int indices[] = {
            0,  1,  2,
            2,  3,  0,
        };

        glGenVertexArrays( 1, &rectangleVAO );
        glBindVertexArray( rectangleVAO );
        glGenBuffers( 1, &rectangleVBO );
        glBindBuffer( GL_ARRAY_BUFFER, rectangleVBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

        glGenBuffers( 1, &rectangleEBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, rectangleEBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6*sizeof( float ), (void*)0 );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6*sizeof( float ), (void*)( 3 * sizeof( float ) ) );
        glEnableVertexAttribArray( 1 );

        glBindVertexArray( 0 );
    }


    private: void LoadShaders()
    {
        shader = new Shader( "./Shaders/shader.vertex", "./Shaders/shader.frag" );
        shader2 = new Shader( "./Shaders/shader.vertex", "./Shaders/shader2.frag" );
    }


    private: void UnloadShaders()
    {
        delete shader;
        delete shader2;
    }


    private: void DrawTriangle()
    {
        if ( z )
            shader->Use();
        else
            shader2->Use();

        glBindVertexArray( triangleVAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );
    }


    private: void DrawRectangle()
    {
        if ( z )
            shader->Use();
        else
            shader2->Use();

        glBindVertexArray( rectangleVAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );
    }


    private: void OnWindowResized( int width, int height )
    {
        glViewport(0, 0, width, height);
    }


    // private: std::string GetAbsolutePathFromRelative( std::string relativePath )
    // {
    //     if ( currentExecutablePath == "\0" )
    //         currentExecutablePath =
    // }


    // private: std::string GetCurrentExecutablePath()
    // {

    // }
};


#endif