#include "ShaderProgram.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> //value_ptr

ShaderProgram::ShaderProgram() {
    this->programId = 0;
    this->vsId = 0;
    this->tcsId = 0;
    this->tesId = 0;
    this->gsId = 0;
    this->fsId = 0;
}

void ShaderProgram::PrintLog(std::string filename, GLuint shader_id) {
    int len;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
	if (len){
	    char * infoLog = (char *)malloc(sizeof(char)*(len+1));
	    glGetShaderInfoLog(shader_id,len+1, NULL, infoLog);
		std::cout<<"Archivo = "<<filename<<"\n";
	    std::cerr << infoLog << std::endl;
	    free(infoLog);
	}
}

bool ShaderProgram::CreateProgram(std::string vs, std::string tcs, 
                                  std::string tes, std::string gs, std::string fs, bool link) {
    this->programId = glCreateProgram();
    if (programId == 0){ 
        std::cout<<"Ocurrio un error al crear el programa\n";
        return false;
    }

    if (vs.length() > 0) {
        this->vsId = this->LoadShader(vs, GL_VERTEX_SHADER);
        if (IsCompiled(this->vsId)) 
            glAttachShader(this->programId, this->vsId);
        else { 
            std::cout<<"Error al compilar el Vertex Shader\n";
            return false;
        }
    }
    
    if (tcs.length() > 0) {
        this->tcsId = this->LoadShader(tcs, GL_TESS_CONTROL_SHADER);
        if (IsCompiled(this->tcsId))
            glAttachShader(this->programId, this->tcsId);
        else { 
            std::cout<<"Error al compilar el Tessellation Control Shader\n";
            return false;
        }
    }
    
    if (tes.length() > 0) {
        this->tesId = this->LoadShader(tes, GL_TESS_EVALUATION_SHADER);
        if (IsCompiled(this->tesId)) 
            glAttachShader(this->programId, this->tesId);
        else { 
            std::cout<<"Error al compilar el Tessellation Evaluation Shader\n";
            return false;
        }
    }
    
    if (gs.length() > 0) {
        this->gsId = this->LoadShader(gs, GL_GEOMETRY_SHADER);
        if (IsCompiled(this->gsId)) 
            glAttachShader(this->programId, this->gsId);
        else { 
            std::cout<<"Error al compilar el Geometry Shader\n";
            return false;
        }
    }
    
    if (fs.length() > 0) {
        this->fsId = this->LoadShader(fs, GL_FRAGMENT_SHADER);
        if (IsCompiled(this->fsId))
            glAttachShader(this->programId, this->fsId);
        else { 
            std::cout<<"Error al compilar el Fragment Shader\n";
            return false;
        }
    }

    if (not link) return true; //No se hace el linkeo para dejar otras actividades
    else return this->LinkProgram();
}

bool ShaderProgram::LinkProgram() {
    glLinkProgram(this->programId);
    
    char errbuf[4096];
    GLsizei len;
    GLint link_ok;

    glGetProgramInfoLog(this->programId, sizeof(errbuf), &len, errbuf);
    glGetProgramiv(this->programId, GL_LINK_STATUS, &link_ok);

    if (not link_ok)  {
        std::cout << errbuf << std::endl;
        std::cout << "Error al linkear los shaders." << std::endl;
        return false;
    }

    return true;
}

bool ShaderProgram::SetTransformFeedback(std::vector<std::string> varyings, GLenum mode) {
    unsigned int count = varyings.size();
    const char **var = new const char*[count];
    unsigned int real_count = 0; //no tiene en cuenta los gl_NextBuffer que separan entre buffers
    for (unsigned int i = 0; i < count; i++) {
        var[i] = varyings[i].c_str();
        if (strcmp(varyings[i].c_str(), "gl_NextBuffer") != 0) real_count++;
    }
    glTransformFeedbackVaryings(this->programId, real_count, var, mode);

    return this->LinkProgram();
}

GLuint ShaderProgram::GetUniformLocation(std::string name) {
    return glGetUniformLocation(this->programId, name.c_str());
}

void ShaderProgram::SetUniform(std::string name, double value) {
    glUniform1f(this->GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(std::string name, float value) {
    glUniform1f(this->GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(std::string name, unsigned int value) {
    glUniform1i(this->GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(std::string name, int value) {
    glUniform1i(this->GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(std::string name, bool value) {
    glUniform1i(this->GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(std::string name, glm::vec2 value) {
    glUniform2fv(this->GetUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(std::string name, glm::vec3 value) {
    glUniform3fv(this->GetUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(std::string name, glm::vec4 value) {
    glUniform4fv(this->GetUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(std::string name, glm::mat3 value) {
    glUniformMatrix3fv(this->GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(std::string name, glm::mat4 value) {
    glUniformMatrix4fv(this->GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
//Para Texturas
//name es el nombre del Sampler2D
//tex_num es 0 en GL_TEXTURE0, 1 para GL_TEXTURE1, etc
void ShaderProgram::SetUniformTex(std::string name, int tex_num) {
    glUniform1i(this->GetUniformLocation(name), tex_num);
}

void ShaderProgram::Bind() {
    glUseProgram(this->programId);
}

void ShaderProgram::Unbind() {
    glUseProgram(0);
}

GLuint ShaderProgram::LoadShader(std::string filename, GLenum type) {
    GLuint shader_id = 0;
    FILE* file;
    long file_size = -1;
    char* glsl_source;

    if (NULL != (file = fopen(filename.c_str(), "rb")) &&
            0 == fseek(file, 0, SEEK_END) &&
            -1 != (file_size = ftell(file))) {
        rewind(file);
        
        if (NULL != (glsl_source = (char*)malloc(file_size + 1))) {
            if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file)) {
                glsl_source[file_size] = '\0';

                if (0 != (shader_id = glCreateShader(type))) {
                    const GLchar* source = glsl_source;
                    glShaderSource(shader_id, 1, &source, NULL);
                    glCompileShader(shader_id);
        			this->PrintLog(filename, shader_id);
                }
                else
                    fprintf(stderr, "ERROR: Could not create a shader.\n");
            }
            else
                fprintf(stderr, "ERROR: Could not read file %s\n", filename.c_str());
            free(glsl_source);
        }
        else
            fprintf(stderr, "ERROR: Could not allocate %li bytes.\n", file_size);
        fclose(file);
    }
    else
        fprintf(stderr, "ERROR: Could not open file %s\n", filename.c_str());

    return shader_id;
}

bool ShaderProgram::IsCompiled(GLuint id) {
    GLint CompileStatus;
    glGetShaderiv(id, GL_COMPILE_STATUS, &CompileStatus);
    if (not CompileStatus)
        return false;
    else  
        return true;
}

void ShaderProgram::DeleteProgram() {
    if (this->fsId != 0) {
        glDetachShader(this->programId, this->fsId);
        glDeleteShader(this->fsId);
    }
    if (this->gsId != 0) {
        glDetachShader(this->programId, this->gsId);
        glDeleteShader(this->gsId);
    }
    if (this->tesId != 0) {
        glDetachShader(this->programId, this->tesId);
        glDeleteShader(this->tesId);
    }
    if (this->tcsId != 0) {
        glDetachShader(this->programId, this->tcsId);
        glDeleteShader(this->tcsId);
    }
    if (this->vsId != 0) {
        glDetachShader(this->programId, this->vsId);
        glDeleteShader(this->vsId);
    }
    glDeleteProgram(this->programId);
}

GLint ShaderProgram::GetAttribLocation(std::string name) {
    return glGetAttribLocation(this->programId, name.c_str());
}

void ShaderProgram::EnableVAA(GLint location, GLint cant_coord, GLenum tipo_coord, GLboolean normalizar, GLsizei stride, const GLvoid* data) {
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, cant_coord, tipo_coord, normalizar, stride, data);
}

void ShaderProgram::DisableVAA(GLint location) {
    glDisableVertexAttribArray(location);
}

