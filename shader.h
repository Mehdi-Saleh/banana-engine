#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader
{
public:
    unsigned int id;
    unsigned int vertex;
    unsigned int fragment;


    Shader( const char* vertexPath, const char* fragmentPath )
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        TryLoadCodeFromFile( vertexPath, vertexCode );
        TryLoadCodeFromFile( fragmentPath, fragmentCode );
        CompileShaders( vertexCode, fragmentCode );
        CreateShaderProgram();
        DeleteShaders();
    }


    void Use() 
    { 
        glUseProgram( id ); 
    }


    void SetBool( const std::string &name, bool value ) const
    {         
        glUniform1i( glGetUniformLocation( id, name.c_str() ), (int) value ); 
    }


    void SetInt( const std::string &name, int value ) const
    { 
        glUniform1i( glGetUniformLocation( id, name.c_str() ), value ); 
    }


    void SetFloat( const std::string &name, float value ) const
    { 
        glUniform1f( glGetUniformLocation( id, name.c_str() ), value ); 
    }


    void SetFloat4( const std::string &name, float valueX, float valueY, float valueZ, float valueW ) const
    { 
        glUniform4f( glGetUniformLocation( id, name.c_str() ), valueX, valueY, valueZ, valueW ); 
    }


private:
    bool TryLoadCodeFromFile( std::string filePath, std::string& code )
    {
        try
        {   
            std::ifstream vertexFile( filePath );
            if ( !vertexFile.is_open() ) 
            {
                std::cerr << "Error opening the shader file! " << filePath << std::endl;
            }

            std::stringstream vertexStream;
            vertexStream << vertexFile.rdbuf();
            code = vertexStream.str();

            vertexFile.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << "\n\tfile: " << filePath << std::endl;
            return false;
        }
        return true;
    }


    void CompileShaders( std::string vertexCode, std::string fragmentCode )
    {
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        
        vertex = glCreateShader( GL_VERTEX_SHADER );
        glShaderSource( vertex, 1, &vShaderCode, NULL );
        glCompileShader( vertex );
        CheckCompileErrors( vertex, "VERTEX" );
        
        fragment = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( fragment, 1, &fShaderCode, NULL );
        glCompileShader( fragment );
        CheckCompileErrors( fragment, "FRAGMENT" );
    }


    void CreateShaderProgram()
    {
        id = glCreateProgram();
        glAttachShader( id, vertex );
        glAttachShader( id, fragment );
        glLinkProgram( id );
        CheckCompileErrors( id, "PROGRAM" );
    }


    void DeleteShaders()
    {
        glDeleteShader( vertex );
        glDeleteShader( fragment );
    }


    void CheckCompileErrors( unsigned int shader, std::string type )
    {
        int success;
        char infoLog[1024];
        if ( type != "PROGRAM" )
        {
            glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
            if ( !success )
            {
                glGetShaderInfoLog( shader, 1024, NULL, infoLog );
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv( shader, GL_LINK_STATUS, &success );
            if ( !success )
            {
                glGetProgramInfoLog( shader, 1024, NULL, infoLog );
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
            }
        }
    }
};

#endif