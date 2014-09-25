#ifndef _VAO_H_
#define _VAO_H_
#include <GL/glew.h>    
#include <GL/freeglut.h>
#include <vector>
class VAO {
    typedef struct {
        GLuint id;
        GLenum type;
        size_t size;
        GLenum usageHint;
        unsigned int pointSize;
        const float *data;
    }buffer;
    std::vector<buffer> buffers;
    GLuint vaoId;
    GLuint *vboId;
    unsigned int cantidadBuffer;
    unsigned int newBufferId;
    unsigned int elementArrayIdx; //id del ELEMENT_ARRAY en vbo_id
    unsigned int vertexArrayIdx; //id del GL_ARRAY_BUFFER en vbo_id
    public:
    VAO();
    void Init(unsigned int cantidad_buffer);
    VAO(unsigned int cantidad_buffer);
    ~VAO();
    void AddBuffer(GLenum type, const float *data, size_t size, unsigned int point_size, GLenum usage_hint);
    void AddBuffer(GLenum type, const unsigned int *data, size_t size);
    void UpdateBuffer(GLenum type, float *data, size_t size);
    void Render(GLenum type, unsigned int size);
    void RenderArray(GLenum type, unsigned int size);
    void BindAttribs (std::vector<unsigned int> lista);
    void UnbindAttribs (std::vector<unsigned int> lista);
    GLuint GetVAO();
    GLuint GetVBO(unsigned int idx);
};
#endif
