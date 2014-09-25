#ifndef _TESSDEMO_H_
#define _TESSDEMO_H_
#include "Example.h"
#include "VAO.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Home.h"

class TessDemo : public Example {
    protected:
    Home* home;
    VAO *vaoTriangle;
    VAO *vaoQuad;
    VAO *vaoLine;
    VAO *vaoAxis;
    VAO *vaoPoint;
    ShaderProgram* currentShader;
    ShaderProgram* currentShaderPoints;
    ShaderProgram shadersTriangleOdd;
    ShaderProgram shadersTriangleEven;
    ShaderProgram shadersTriangleEqual;
    ShaderProgram shadersQuadEqual;
    ShaderProgram shadersQuadOdd;
    ShaderProgram shadersQuadEven;
    ShaderProgram shadersLineEqual;
    ShaderProgram shadersLineOdd;
    ShaderProgram shadersLineEven;
    ShaderProgram shadersLinePointsEqual;
    ShaderProgram shadersLinePointsOdd;
    ShaderProgram shadersLinePointsEven;
    ShaderProgram shadersAxis;
    bool tessellate;
    double TessDefault;
    glm::vec4 TessLevelsTriangle;
    glm::vec2 TessLevelsQuadInner;
    glm::vec4 TessLevelsQuadOuter;
    glm::vec2 TessLevelsLine;
    unsigned int currentDemo;
    unsigned int spacingMode;
    unsigned int selectedLevel;
    bool lineSpiral;

    public:
    TessDemo(std::string name, int w, int h, int vpp, Home* home_ptr);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~TessDemo() {};
};
#endif
