#ifndef _MODELSILHOUETTE_H_
#define _MODELSILHOUETTE_H_
#include "Example.h"
#include "VAO.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Home.h"
class ModelSilhouette : public Example {
    protected:
    Home *home;
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
    bool dyadic;
    float beta;
    float maxTess;
    float tMin;
    float tMax;
    float tessDefault;
    float normScale;
    bool rotate;
    float tessDivisor;
    float rotationSpeed;
    Model *model;
    public:
    ModelSilhouette(std::string name, int w, int h, int vpp, bool extendedData, Home* home_ptr, std::string modelname);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~ModelSilhouette() {};
};
#endif
