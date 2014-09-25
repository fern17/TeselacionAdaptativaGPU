#ifndef _TERRAINDISTANCE_H_
#define _TERRAINDISTANCE_H_
#include "Example.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include <string>
#include "Home.h"
class TerrainDistance : public Example {
    protected:
    Home* home;
    VAO *vaoModel;
    VAO *vaoAxis;
    VAO *vaoLight;
    ShaderProgram shadersModel;
    ShaderProgram shadersAxis;
    ShaderProgram shadersLight;
    GLuint texHeight;
    GLuint texRock;
    GLuint texGrass;
    GLuint texColorMap;

    //Archivos de Texturas
    std::string texHeightMapName;
    std::string texRockName;
    std::string texGrassName;
    std::string texColorName;

    //Datos de la malla
    glm::vec2 meshSize;
    float horizScale;
    float vertScale;

    //Datos para Teselacion
    float minDist;
    float maxDist;
    //float maxTess;
    float tessDefault;
    bool useTessLinear;

    //Estados del dibujado
    bool fillPolygon;
    bool tessellate;
    bool drawWire;
    bool useIllumination;
    bool useTexture;
    bool useFog;
    bool useTessColoration;
    
    public:
    TerrainDistance(std::string name, int w, int h, int vpp, Home* home_ptr);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    ~TerrainDistance() {};
};
#endif
