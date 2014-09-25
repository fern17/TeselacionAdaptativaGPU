#ifndef _MODELPHONG_H_
#define _MODELPHONG_H_
#include "Example.h"
#include "VAO.h"
#include "Model.h"
#include "Home.h"
#include "ShaderProgram.h"
#include <vector>
class ModelPhong : public Example {
    protected:
    Home* home;
    VAO *vaoModel;
    VAO *vaoAxis;
    VAO *vaoNormals;
    VAO *vaoLight;
    ShaderProgram shadersModel;
    ShaderProgram shadersAxis;
    ShaderProgram shadersNormals;
    ShaderProgram shadersLight;
    bool tessellate;
    bool drawWire;
    bool useIllumination;
    bool useTessColoration;
    bool drawNormals;
    float beta;
    //float maxTess;
    float tessDefault;
    float alpha;
    float zoom;
    float normScale;
    Model *model;
    GLuint texColorMap; 
    std::string texColorName;

    public:
    ModelPhong(std::string name, int w, int h, int vpp, bool extendedData, Home* home_ptr, std::string modelname);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~ModelPhong() {};
};
#endif
