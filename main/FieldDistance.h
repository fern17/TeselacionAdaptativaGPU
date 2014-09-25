#ifndef _FIELDDISTANCE_H_
#define _FIELDDISTANCE_H_
#include "Example.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Home.h"

#include <string>
class FieldDistance : public Example {
    protected:
    Home *home;
    std::vector<std::string> varyings;
    ShaderProgram shadersTexture;
    ShaderProgram shadersFeedback;
    //ShaderProgram shadersTessellate;
    ShaderProgram shadersDraw;
    GLuint query;
    float stepH;
    float dx;
    float dy;
   
    GLuint tfo;
    GLint slotPosition;
    GLint slotField;
    GLint slotFieldR;
    GLint slotFieldRB;
    GLint slotFieldB;
    GLint slotPositionOriginal;
    //Datos para Teselacion
    //float maxTess;
    float tessDefault;
    float scaleX;
    float scaleY;

    GLuint framebuffer;
    GLuint outTexture;
    GLuint accumTexture;
    GLenum drawBuffers[2];
    GLuint vaoQuad;
    GLuint vboQuad;

    GLuint noiseTexture;

    //Estados del dibujado
    bool fillPolygon;
    bool tessellate;
    bool drawWire;

    GLuint meshA;
    GLuint meshB;
    GLuint meshOriginal;
    unsigned int countToReset;
    unsigned int currentCountToReset;
    int currentField;
    unsigned int maxField;
    float  (*data);
    unsigned int sizeOfData;
    unsigned int backgroundColor;//color del fondo, en escala 0,255

    public:
    FieldDistance(std::string name, int w, int h, int vpp, Home *home_ptr);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    unsigned int ReloadData(unsigned int field_id = 0, bool reset = true);
    void Reset(unsigned int valor_por_defecto = 0);
    ~FieldDistance() {};
};
#endif
