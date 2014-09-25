#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_

#include <GL/glew.h>    //glew para facilitar la carga de extensiones y crear aplicaciones portables
#include <GL/freeglut.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class ShaderProgram {
    GLuint programId;  //Id del programa
    GLuint vsId;       //Id del Vertex Shader
    GLuint tcsId;      //ID del Tessellation Control Shader
    GLuint tesId;      //ID del Tessellation Evaluation Shader
    GLuint gsId;       //ID del Geometry Shader
    GLuint fsId;       //ID del Fragment Shader

    public:
    
    ShaderProgram();    //Inicializa todo en 0
    GLuint GetUniformLocation(std::string name);    //Devuelve la ubicacion de un Uniform
    
    //Setea el valor de un uniform
    void SetUniform(std::string name, float value); 
    void SetUniform(std::string name, double value); 
    void SetUniform(std::string name, int value);
    void SetUniform(std::string name, unsigned int value);
    void SetUniform(std::string name, bool value);
    void SetUniform(std::string name, glm::vec2 value);
    void SetUniform(std::string name, glm::vec3 value);
    void SetUniform(std::string name, glm::vec4 value);
    void SetUniform(std::string name, glm::mat3 value);
    void SetUniform(std::string name, glm::mat4 value);
    void SetUniformTex(std::string name, int tex_num);

    void EnableVAA(GLint location, GLint cant_coord, GLenum tipo_coord, GLboolean normalizar, GLsizei stride, const GLvoid* data);
    void DisableVAA(GLint location);

    GLint GetAttribLocation(std::string name);

    bool CreateProgram(std::string vs, std::string tcs, std::string tes, std::string gs, std::string fs, bool link = true);
    bool SetTransformFeedback(std::vector<std::string> varyings, GLenum mode);
    bool LinkProgram();
    GLuint LoadShader(std::string filename, GLenum type);
    void PrintLog(std::string filename, GLuint shader_id);
    bool IsCompiled(GLuint id);
    void Bind();        //Trae este shader al contexto
    void Unbind();      //Quita este shader del contexto
    void DeleteProgram();
};

#endif
