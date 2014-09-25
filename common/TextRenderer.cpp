#include "TextRenderer.h"
#include <iostream>
#include "utils.h"
#include <vector>

TextRenderer::TextRenderer(std::string facename) {
    //Inicializacion de la fuente
    if(FT_Init_FreeType(&this->ft)) {
        std::cerr<<"Error: No se pudo inicializar la biblioteca FreeType\n";    
    } 
    if(FT_New_Face(this->ft, facename.c_str(), 0, &this->face)) {
        std::cerr<<"Error: No se pudo leer la face :"<<facename<<"\n";
    }
    //FT_Set_Pixel_Sizes(this->face, 0, facesize);

    //Inicializacion del shader
    if (not this->shaders.CreateProgram("../common/TextRenderer.vert", "", "", "", "../common/TextRenderer.frag", true)) {
#ifdef ERRORCHECK
        utils::ExitOnGLError("ERROR: no se pudo crear el shader para dibujar texto.\n");
#else
        std::cout<<"ERROR: no se pu do crear el shader para dibujar texto.\n";
#endif
    }

    //Inicializacion de la textura
    glActiveTexture(GL_TEXTURE9); //notar que se usa el slot 9
    glGenTextures(1, &this->texId);
    glBindTexture(GL_TEXTURE_2D, this->texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifdef ERRORCHECK
    utils::ExitOnGLError("ERROR: no se pudo cargar la textura para dibujar texto.\n");
#endif

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //esta linea sirve para evitar restricciones de alineamiento

    //Inicializacion de un Vertex Buffer Object para mandar al shader
  //this->attributeLocation = this->shaders.GetAttribLocation("coord");
  //glGenBuffers(1, &this->vbo);
  //glEnableVertexAttribArray(this->attributeLocation);
  //glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  //utils::ExitOnGLError("ERROR: No se puede bindear el array buffer para dibujar texto.\n");
  //glVertexAttribPointer(this->attributeLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);
  //utils::ExitOnGLError("ERROR: No se pueden definir el vertexattribpointer para dibujar texto.\n");
  //glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->attributeLocation = this->shaders.GetAttribLocation("coord");
    glGenVertexArrays(1, &this->vaoId);
    glBindVertexArray(this->vaoId);
    glGenBuffers(1, &this->vbo);
    glBindVertexArray(this->vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    float x2, y2, w, h; x2 = y2 = h = w = 0.0;
    GLfloat box[4][4] = { //dummy data
            {x2,     -y2    , 0, 0},
            {x2 + w, -y2    , 1, 0},
            {x2,     -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };

    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW); 

#ifdef ERRORCHECK
    utils::ExitOnGLError("ERROR: No se puede bindear el array buffer para dibujar texto.\n");
#endif
    glEnableVertexAttribArray(this->attributeLocation);
    glVertexAttribPointer(this->attributeLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);
#ifdef ERRORCHECK
    utils::ExitOnGLError("ERROR: No se pueden definir el vertexattribpointer para dibujar texto.\n");
#endif
    glBindVertexArray(0);
}

TextRenderer::~TextRenderer() {
    this->shaders.DeleteProgram();
    glDeleteBuffers(1, &this->vbo);
    glDeleteTextures(1, &this->texId);
}

void TextRenderer::Render(const char *text, glm::vec4 text_color, unsigned int text_size, float x, float y, float sx, float sy, unsigned int window_height) {
    std::vector<std::string> los;
    std::string str(text);
    std::string s;
    std::size_t posi = 0, newpos = 0;
    GLint front_value;
    glGetIntegerv(GL_FRONT_FACE, &front_value);
    glFrontFace(GL_CW);
    while(true) {
        newpos = str.find('\n', posi);
        if (newpos == std::string::npos) {
            s = str.substr(posi); //hasta el final
            los.push_back(s);
            break;
        } else {
            s = str.substr(posi, newpos-posi+1);
            los.push_back(s);
        }
        posi = newpos+1;
        if (posi >= str.size()) break;
    }
    float position = 1.5*float(text_size+3)/float(window_height);
    
    for (unsigned int i = 0; i < los.size(); i++) {
        this->Render2(los[i].c_str(), text_color, text_size, x, y-i*position, sx, sy);
    }
    glFrontFace(front_value);
}

void TextRenderer::Render2(const char *text, glm::vec4 text_color, unsigned int text_size, float x, float y, float sx, float sy) {
    GLboolean blend_activated;
    glGetBooleanv(GL_BLEND, &blend_activated);
    GLint blend_mode;
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &blend_mode);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(this->vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    this->shaders.Bind(); 
    this->shaders.SetUniformTex("tex", 9); //se usa el slot 9 para esta textura
    this->shaders.SetUniform("color", text_color); 
    
    FT_Set_Pixel_Sizes(this->face, 0, text_size);
    FT_GlyphSlot g = this->face->glyph; //shortcut

    const char *p;
    for(p = text; *p; p++) {
        if (*p == '\n') continue;
        if(FT_Load_Char(this->face, *p, FT_LOAD_RENDER)) continue;
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            g->bitmap.buffer
        );
    
        float x2 = x + g->bitmap_left * sx;
        float y2 = -y - g->bitmap_top * sy;
        float w = g->bitmap.width * sx;
        float h = g->bitmap.rows * sy;
        
        GLfloat box[4][4] = {
            {x2,     -y2    , 0, 0},
            {x2 + w, -y2    , 1, 0},
            {x2,     -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW); 
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 
    
        x += (g->advance.x >> 6) * sx;
        y += (g->advance.y >> 6) * sy;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    this->shaders.Unbind();
    if (not blend_activated) glDisable(GL_BLEND); 
    else glBlendFunc(GL_SRC_ALPHA, blend_mode);
}
