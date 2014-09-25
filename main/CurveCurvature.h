#ifndef _CURVECURVATURE_H_
#define _CURVECURVATURE_H_
#include "Example.h"
#include "VAO.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Home.h"

class CurveCurvature : public Example {
    protected:
    Home* home;
    VAO *vaoModel;
    VAO *vaoAxis;
    VAO *vaoPoly;
    VAO *vaoPoint;
    ShaderProgram shadersModel;
    ShaderProgram shadersAxis;
    bool tessellate;
    float numLines;
    float maxTess;
    double tessDefault;
    unsigned int selectedPoint;
    float curvFactor;

    public:
    CurveCurvature(std::string name, int w, int h, int vpp, Home* home_ptr);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~CurveCurvature() {};
};
#endif
