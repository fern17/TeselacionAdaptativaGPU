#ifndef _ZFIGHT_H_
#define _ZFIGHT_H_
#include "Example.h"
#include "VAO.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "../Home.h"

class ZFight : public Example {
    protected:
    Home* home;
    VAO *vaoT1;
    VAO *vaoT2;
    ShaderProgram shaderTriangles;
    bool tessellate;
    double TessDefault;
    double delta_z;

    public:
    ZFight(std::string name, int w, int h, int vpp, Home* home_ptr);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~ZFight() {};
};
#endif
