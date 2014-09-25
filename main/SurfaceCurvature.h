#ifndef _SURFACECURVATURE_H_
#define _SURFACECURVATURE_H_
#include "Example.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Home.h"

class SurfaceCurvature : public Example {
    protected:
    Home* home;
    VAO *vaoModel;
    VAO *vaoAxis;
    ShaderProgram shadersModel;
    ShaderProgram shadersAxis;
    float maxCurvature; //sin uso
    float curvFactor;
    //float maxTess;
    bool useIllumination;
    bool useTessColoration;
    GLenum query;
    GLuint texColorMap; 
    std::string texColorName;
    public:
    SurfaceCurvature(std::string name, int w, int h, int vpp, Home* home_ptr);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~SurfaceCurvature() {};
};

#endif
