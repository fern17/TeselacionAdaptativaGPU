#include "VAO.h"
#include <GL/glew.h>    
#include <GL/freeglut.h>
#include "utils.h"

VAO::VAO() { //constructor vacio
}

void VAO::Init(unsigned int cantidad_buffer) {
    glGenVertexArrays(1, &this->vaoId);
    glBindVertexArray(this->vaoId);

    this->newBufferId = 0;
    this->cantidadBuffer = cantidad_buffer;
    this->vboId = new GLuint[cantidad_buffer];
  
    //Creamos los objetos de buffer
    glGenBuffers(this->cantidadBuffer, this->vboId);
}

VAO::VAO(unsigned int cantidad_buffer) {
    this->Init(cantidad_buffer);
}


//Vertices, Normales, Texturas
void VAO::AddBuffer(GLenum type, const float *data, size_t size, unsigned int point_size, GLenum usage_hint) {
    glBindVertexArray(this->vaoId);
    utils::ExitOnGLError("Error: no se pudo bindear el VAO");
    
    glBindBuffer(type, this->vboId[this->newBufferId]);
    utils::ExitOnGLError("Error: no se pudo bindear el VBO");
    
    glBufferData(type, size, data, usage_hint);
    utils::ExitOnGLError("Error: no se pudo cargar el buffer");
    
    glEnableVertexAttribArray(this->newBufferId); 
    utils::ExitOnGLError("Error: no se pudo activar el vertex attribute");

    //glVertexAttribPointer(this->newBufferId, point_size, GL_FLOAT, GL_FALSE, sizeof(data[0]), 0);
    //glVertexAttribPointer(this->newBufferId, point_size, GL_FLOAT, GL_FALSE, sizeof(data[0])*point_size, (GLvoid*) 0);
    //glVertexAttribPointer(this->newBufferId, point_size, GL_FLOAT, GL_FALSE, point_size*sizeof(float), 0);
    glVertexAttribPointer(this->newBufferId, point_size, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);
    utils::ExitOnGLError("Error: no se pudo definir el vertex attribute");
 
    this->vertexArrayIdx = this->newBufferId;

    VAO::buffer buf;
    buf.id = this->vboId[newBufferId];
    buf.type = type;
    buf.size = size;
    buf.data = data;
    buf.usageHint = usage_hint;
    buf.pointSize = point_size;
    this->buffers.push_back(buf);

    this->newBufferId++;
    glBindVertexArray(0);
}

//Actualiza el buffer de posiciones
void VAO::UpdateBuffer(GLenum type, float *data, size_t size) {
    glBindBuffer(type, this->vboId[this->vertexArrayIdx]);
    glBufferSubData(type, 0, size, data);
    glBindBuffer(type, 0);
}

//Indices
void VAO::AddBuffer(GLenum type, const unsigned int *data, size_t size) {
    glBindVertexArray(this->vaoId);
    
    glBindBuffer(type, this->vboId[this->newBufferId]);
    //glBufferData(type, sizeof(data[0]), data, GL_STATIC_DRAW);
    glBufferData(type, size, data, GL_STATIC_DRAW);
    
    //glVertexAttribPointer(this->newBufferId, point_size, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

    this->elementArrayIdx = this->newBufferId;
    this->newBufferId++;
    glBindVertexArray(0);
}

//void VAO::Render(GLenum type, unsigned int size, unsigned int components) {
void VAO::Render(GLenum type, unsigned int size) {
    glBindVertexArray(this->vaoId);

    //glVertexAttribPointer(0, components, GL_FLOAT, GL_FALSE, 0, 0);
    //Dibuja la malla
  //GLenum query;
  //unsigned int value;
  //glGenQueries(1, &query);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vboId[this->elementArrayIdx]);
  //glBeginQuery(GL_PRIMITIVES_GENERATED, query);
    glDrawElements(type, size, GL_UNSIGNED_INT, (GLvoid*)0);
  //glEndQuery(GL_PRIMITIVES_GENERATED);
  //glGetQueryObjectuiv(query, GL_QUERY_RESULT_AVAILABLE, &value);
  //if (value == GL_TRUE) {
  //    glGetQueryObjectuiv(query, GL_QUERY_RESULT, &value);
  //    std::cerr<<value<<"\n\n";
  //}
    
    glBindVertexArray(0);
}

void VAO::RenderArray(GLenum type, unsigned int size) {
    glBindVertexArray(this->vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboId[0]);
    glDrawArrays(type, 0, size);
    glBindVertexArray(0);
}

//Esta funcion no sirve
void VAO::BindAttribs(std::vector<unsigned int> lista) {
    glBindVertexArray(this->vaoId);

    for (unsigned int i = 0; i < lista.size(); i++) {
        if (lista[i] >= this->buffers.size()) continue; //fuera de rango
        glBindBuffer(this->buffers[lista[i] ].type, this->buffers[lista[i] ].id);
        //glEnableVertexAttribArray(this->buffers[lista[i] ].id);
        glVertexAttribPointer(this->buffers[lista[i] ].id, this->buffers[lista [i] ].pointSize, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);
    }
}

void VAO::UnbindAttribs(std::vector<unsigned int> lista) {
    glBindVertexArray(this->vaoId);
    for (unsigned int i = 0; i < lista.size(); i++) {
        if (lista[i] >= this->buffers.size()) continue; //fuera de rango
        glBindBuffer(this->buffers[lista[i] ].type, 0);
        glDisableVertexAttribArray(this->buffers[lista[i] ].id);
    }
    glBindVertexArray(0);
}

VAO::~VAO() {
    glDeleteBuffers(this->cantidadBuffer, this->vboId);
    glDeleteVertexArrays(1, &this->vaoId);
}

GLuint VAO::GetVAO() {
    return this->vaoId;
}

GLuint VAO::GetVBO(unsigned int idx) {
    if (idx >= this->cantidadBuffer) return 0;
    else return this->buffers[idx].id;
}
