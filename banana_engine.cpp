#ifndef BANANA_ENGINE
#define BANANA_ENGINE
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


class BananaEngine
{
    private: GLFWwindow* window = nullptr;
    private: bool x = false;
    private: bool z = false;
    private: unsigned int vertexShader;
    private: unsigned int fragmentShader;
    private: unsigned int fragmentShader2;
    private: unsigned int shaderProgram;
    private: unsigned int shaderProgram2;
    private: unsigned int triangleVBO;
    private: unsigned int triangleVAO;
    private: unsigned int rectangleVBO;
    private: unsigned int rectangleVAO;
    private: unsigned int rectangleEBO;

    private: const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    private: const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

    private: const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.9f, 0.2f, 1.0f);\n"
    "}\n";


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
            HandleInput();
            Render();
            glfwSwapBuffers( window );
            glfwPollEvents();
        }
        
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
        
        // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        if ( !x )
            DrawRectangle();
        else
            DrawTriangle();
    }


    private: void LoadShaders()
    {
        int success;
        char infoLog[512];

        vertexShader = glCreateShader( GL_VERTEX_SHADER );
        glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
        glCompileShader( vertexShader );
        glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
        glCompileShader( fragmentShader );
        glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        fragmentShader2 = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( fragmentShader2, 1, &fragmentShaderSource2, NULL );
        glCompileShader( fragmentShader2 );
        glGetShaderiv( fragmentShader2, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( fragmentShader2, 512, NULL, infoLog );
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        shaderProgram = glCreateProgram();
        glAttachShader( shaderProgram, vertexShader );
        glAttachShader( shaderProgram, fragmentShader );
        glLinkProgram( shaderProgram );
        glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
        if ( !success )
        {
            glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
            std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        shaderProgram2 = glCreateProgram();
        glAttachShader( shaderProgram2, vertexShader );
        glAttachShader( shaderProgram2, fragmentShader2 );
        glLinkProgram( shaderProgram2 );
        glGetProgramiv( shaderProgram2, GL_LINK_STATUS, &success );
        if ( !success )
        {
            glGetProgramInfoLog( shaderProgram2, 512, NULL, infoLog );
            std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );

        glUseProgram( shaderProgram );
    }
    
    
    private: void LoadTriangle()
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f,
        };
        glGenVertexArrays( 1, &triangleVAO );
        glBindVertexArray( triangleVAO );
        glGenBuffers( 1, &triangleVBO );
        glBindBuffer( GL_ARRAY_BUFFER, triangleVBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof( float ), (void*)0 );
        glEnableVertexAttribArray( 0 );

        glBindVertexArray( 0 );
    }


    private: void LoadRectangle()
    {
        float vertices[] = {
            -0.5f,  0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
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

        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof( float ), (void*)0 );
        glEnableVertexAttribArray( 0 );

        glBindVertexArray( 0 );
    }


    private: void DrawTriangle()
    {
        glUseProgram( z? shaderProgram2 : shaderProgram );
        glBindVertexArray( triangleVAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );
    }


    private: void DrawRectangle()
    {
        glUseProgram( z? shaderProgram2 : shaderProgram );
        glBindVertexArray( rectangleVAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );
    }


    private: void OnWindowResized( int width, int height )
    {
        glViewport(0, 0, width, height);
    }
};


#endif