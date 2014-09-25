#ifndef _SURFACEDISTANCE_H_
#define _SURFACEDISTANCE_H_
#include "Example.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Home.h"

class SurfaceDistance : public Example {
    protected:
    Home* home;
    VAO *vaoModel;
    VAO *vaoAxis;
    ShaderProgram shadersModel;
    ShaderProgram shadersAxis;
    float minDist;
    float maxDist;
    //float maxTess;
    bool useTessLinear;
    bool useIllumination;
    bool useTessColoration;
    bool tessellate;
    GLenum query;
    GLuint texColorMap; 
    std::string texColorName;
    public:
    SurfaceDistance(std::string name, int w, int h, int vpp, Home* home_ptr);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~SurfaceDistance() {};
};

#endif
