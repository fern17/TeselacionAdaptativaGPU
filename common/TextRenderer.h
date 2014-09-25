#ifndef _TEXTRENDERER_H_
#define _TEXTRENDER_H_
#include "ShaderProgram.h"
#include <string>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <ft2build.h>
#include FT_FREETYPE_H
class TextRenderer {
    private:
    ShaderProgram shaders;
    FT_Library ft;
    FT_Face face;

    GLuint texId;
    GLuint vaoId;
    GLuint vbo;
    GLint attributeLocation;
    public:
    TextRenderer(std::string facename);
    void Render(const char *text, glm::vec4 text_color, unsigned int text_size, float x, float y, float sx = 1.0, float sy = 1.0, unsigned int window_height = 300);
    void Render2(const char *text, glm::vec4 text_color, unsigned int text_size, float x, float y, float sx = 1.0, float sy = 1.0);
    ~TextRenderer();
};

#endif
