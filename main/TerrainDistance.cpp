#include "TerrainDistance.h"
//#include "terrain_big.h"
//#include "terrain_bigga.h"
#include "terrain_distance/terrain_small.h"
#include "terrain_distance/lights.h"
#include "AxisData.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"

TerrainDistance::TerrainDistance(std::string name, int w, int h, int vpp, Home *home_ptr) {
    this->home = home_ptr;
    Example::InitVariables(name, w, h, vpp);
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";
}

void TerrainDistance::DrawScene() {
    //Carga el shader
    this->shadersModel.Bind();
 
    this->shadersModel.SetUniform("ModelViewMatrix", Example::ModelViewMatrix);
    this->shadersModel.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shadersModel.SetUniform("ViewportMatrix", Example::ViewportMatrix);
    if (Example::useVirtualCamera) this->shadersModel.SetUniform("CamPos", Example::virtualCamPos);
    else                           this->shadersModel.SetUniform("CamPos", Example::camPos);
    this->shadersModel.SetUniform("HorizScale", this->horizScale);
    this->shadersModel.SetUniform("VertScale", this->vertScale);
    this->shadersModel.SetUniform("MeshSize", this->meshSize);
    this->shadersModel.SetUniform("MaxDist", this->maxDist);
    this->shadersModel.SetUniform("MinDist", this->minDist);
    this->shadersModel.SetUniform("UseTessLinear", this->useTessLinear);
    this->shadersModel.SetUniform("MaxTess", this->maxTess);
    this->shadersModel.SetUniform("Tessellate", this->tessellate);
    this->shadersModel.SetUniform("TessDefault", this->tessDefault);
    this->shadersModel.SetUniform("ViewPortSize", this->viewPortSize);
    this->shadersModel.SetUniform("LightPosition", glm::vec4(
                TD::lightVertices[0][0],
                TD::lightVertices[0][1],
                TD::lightVertices[0][2],
                1.0));
    this->shadersModel.SetUniform("DrawWire", this->drawWire);
    this->shadersModel.SetUniform("UseIllumination", this->useIllumination);
    this->shadersModel.SetUniform("UseTexture", this->useTexture);
    this->shadersModel.SetUniform("UseTessColoration", this->useTessColoration);
    this->shadersModel.SetUniform("UseFog", this->useFog);
    this->shadersModel.SetUniformTex("HeightMap", 0);
    this->shadersModel.SetUniformTex("TexRock", 1);
    this->shadersModel.SetUniformTex("TexGrass", 2);
    this->shadersModel.SetUniformTex("TexColorMap", 8);

    this->vaoModel->Render(GL_PATCHES, sizeof(TD::terrain_elements)/sizeof(unsigned int));
    this->shadersModel.Unbind();

    this->shadersAxis.Bind(); 
    this->shadersAxis.SetUniform("MVPMatrix", MVPMatrix);
    this->vaoAxis->Render(GL_LINES, sizeof(AxisIndices)/sizeof(unsigned int));
    this->shadersAxis.Unbind();

    glPointSize(10.0);
    this->shadersLight.Bind(); 
    this->shadersLight.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shadersLight.SetUniform("UseIllumination", this->useIllumination);
    this->vaoLight->UpdateBuffer(GL_ARRAY_BUFFER, &TD::lightVertices[0][0], sizeof(TD::lightVertices));
    this->vaoLight->Render(GL_POINTS, sizeof(TD::lightIndices)/sizeof(unsigned int));
    this->shadersLight.Unbind();
}

void TerrainDistance::CreateScene() {
    this->vaoModel = new VAO(2);
    this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &TD::terrain_positions[0][0], sizeof(TD::terrain_positions), 2, GL_STATIC_DRAW);
    this->vaoModel->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &TD::terrain_elements[0][0], sizeof(TD::terrain_elements));
    glActiveTexture(GL_TEXTURE0); 
    this->texHeight = utils::LoadImageTex(texHeightMapName.c_str());
    glActiveTexture(GL_TEXTURE1); 
    this->texRock = utils::LoadImageTex(texRockName.c_str());
    glActiveTexture(GL_TEXTURE2); 
    this->texGrass = utils::LoadImageTex(texGrassName.c_str());

    glActiveTexture(GL_TEXTURE8);
    this->texColorMap = utils::LoadImageTex(texColorName.c_str());
 
    this->vaoAxis = new VAO(3);  
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisVertices[0][0], sizeof(AxisVertices), 3, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisColors[0][0], sizeof(AxisColors), 4, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &AxisIndices[0][0], sizeof(AxisIndices));
        
    this->vaoLight = new VAO(2);  
    this->vaoLight->AddBuffer(GL_ARRAY_BUFFER, &TD::lightVertices[0][0], sizeof(TD::lightVertices), 3, GL_STREAM_DRAW); //Este se modifica
    this->vaoLight->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &TD::lightIndices[0][0], sizeof(TD::lightIndices));
    
    if (this->shadersModel.CreateProgram("shaders/terrain_distance/vertex.vert", "shaders/terrain_distance/tess_control.tcs", "shaders/terrain_distance/tess_evaluation.tes", "shaders/terrain_distance/geometry.geom", "shaders/terrain_distance/fragment.frag", true))
        if (this->shadersAxis.CreateProgram("shaders/ejes.vert", "", "", "", "shaders/ejes.frag", true))
            if (shadersLight.CreateProgram("shaders/light.vert", "", "", "", "shaders/light.frag", true)) {}//std::cout<<"Shaders creados con exito.\n";
            else std::cout<<"Ocurrio un error al crear los shaders de las normales.\n";
        else std::cout<<"Ocurrio un error al crear los shaders de los ejes.\n";
    else std::cout<<"Ocurrio un error al crear los shaders del modelo.\n";
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void TerrainDistance::DestroyScene() {
    delete vaoModel;
    delete vaoAxis;
    delete vaoLight;
    this->shadersLight.DeleteProgram();
    this->shadersAxis.DeleteProgram();
    this->shadersModel.DeleteProgram();
    this->home->Reset();
}

void TerrainDistance::SetScene() {
    this->texHeightMapName = "../resources/heightmap.png";
    this->texRockName = "../resources/rock.png";
    this->texGrassName = "../resources/grass.png";
    this->texColorName = "../resources/colormap.png";
    
    Example::zFar = 150.0;
    Example::zNear = 1.0;
    this->kDisplacement = 0.75; //Velocidad de movimiento 
    Example::camPos = glm::vec3(0, 10.0, 0);
    Example::camCenter  = glm::vec3(50.0, 0, 50.0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    this->RecalcMatrices();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    this->meshSize = glm::vec2(trunc(sqrt(TD::terrain_cant_elementos)));
    this->horizScale = 100.0;
    this->vertScale = this->horizScale/10.0;
    this->maxTess = 64.0;
    this->useTessLinear = true;
    this->tessDefault = 32.0;
    Example::fillPolygon = true;
    this->tessellate = true;
    this->drawWire = true;
    this->useIllumination = false;
    this->useTessColoration = false;
    this->useTexture = true;
    this->useFog = false;
    this->maxDist = 50.0;
    this->minDist = Example::zNear;
    Example::renderText = true;
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
    
}

void TerrainDistance::cb_KeyboardExtended(unsigned char key, int x, int y) {
    switch(key) {
    case 27: //escape
        this->DestroyScene();
        break;
    case 'T': 
    case 't':
        this->tessellate = not this->tessellate;
        if (this->tessellate) Example::lastMessage = "Teselacion adaptativa activada.\n"; 
        else Example::lastMessage = "Teselacion adaptativa desactivada. Valor por defecto = "+utils::XToStr(this->tessDefault)+".\n";
        break;
    case 'k':
    case 'K':
        this->drawWire = not this->drawWire;
        if (this->drawWire) Example::lastMessage = "Dibujar lineas.\n";
        else Example::lastMessage = "No dibujar lineas.\n";
        break;
    case '+':
        this->maxDist += 5.f; Example::lastMessage = "maxDist = " + utils::XToStr(this->maxDist) + ".\n";
        break;
    case '-':
        this->maxDist = std::max(1.0, this->maxDist-5.0); Example::lastMessage = "maxDist = " + utils::XToStr(this->maxDist) + ".\n";
        break;
    case 'y': 
    case 'Y':
        if (this->maxTess < 1.01) this->maxTess = 4.0f;
        else if (this->maxTess < 64.0) this->maxTess += 4.0f;
        Example::lastMessage = "maxTess = " + utils::XToStr(this->maxTess) + ".\n";
        break;
    case 'u': 
    case 'U':
        if (this->maxTess <= 4.0) this->maxTess = 1.0;
        else this->maxTess -= 4.0f;
        Example::lastMessage = "maxTess = " + utils::XToStr(this->maxTess) + ".\n";
        break;
    case 'i':
    case 'I':
        this->useIllumination = not this->useIllumination;
        if (this->useIllumination) Example::lastMessage = "Iluminacion activada.\n";
        else Example::lastMessage = "Iluminacion desactivada.\n";
        break;
    case 'p':
    case 'P':
        this->useTexture = not this->useTexture;
        if (this->useTexture) Example::lastMessage = "Textura activada.\n";
        else Example::lastMessage = "Textura desactivada.\n";
        break;
    case 'f':
    case 'F':
        this->useFog = not this->useFog;
        if (this->useFog) Example::lastMessage = "Niebla activada.\n";
        else Example::lastMessage = "Niebla desactivada.\n";
        break;  
    case 'o':
    case 'O':
        this->useTessColoration = not this->useTessColoration;
        if (this->useTessColoration) Example::lastMessage = "Coloracion de niveles de teselacion activada.\n";
        else Example::lastMessage = "Coloracion de niveles de teselacion desactivada.\n";
        break;
    case 'v':
    case 'V':
        this->useTessLinear = not this->useTessLinear;
        if (this->useTessLinear) Example::lastMessage = "Se utiliza teselacion lineal.\n";
        else Example::lastMessage = "Se utiliza teselacion lineal inversa.\n";
        break;
    case 'h':
    case 'H':
        const char *added_text = 
        "    T: Activa o desactiva teselacion por hardware.\n"
        "    K: Intercambia entre dibujar lineas o no.\n"
        "    I: Intercambia entre usar iluminacion o no.\n"
        "    P: Intercambia entre usar texturas o no.\n"
        "    O: Intercambia entre usar coloracion de teselacion o no.\n"
        "    F: Intercambia entre usar niebla o no.\n"
        "    Y: Aumenta el nivel maximo de teselacion.\n"
        "    U: Disminuye el nivel maximo de teselacion.\n"
        "    +: Aumenta la distancia minima para teselacion.\n"
        "    -: Disminuye la distancia minima para teselacion.\n"
        "    V: Intercambia entre teselacion lineal y lineal inversa.\n"
        "    Flechas y Av/RePag: Cambia la posicion de la luz.\n"
        "    Escape: Vuelve al menu principal.\n"
        "    H: Imprime este texto.\n";
        Example::lastMessage += std::string(added_text); 
        break;
    }
}

void TerrainDistance::cb_SpecialExtended(int key, int x, int y) {
    switch(key){
    case GLUT_KEY_UP:
        TD::lightVertices[0][2] += 1.0;
        break;
    case GLUT_KEY_DOWN: 
        TD::lightVertices[0][2] -= 1.0;
        break;
    case GLUT_KEY_LEFT: 
        TD::lightVertices[0][0] -= 1.0;
        break;
    case GLUT_KEY_RIGHT: 
        TD::lightVertices[0][0] += 1.0;
        break;
    case GLUT_KEY_PAGE_DOWN: 
        TD::lightVertices[0][1] += 1.0;
        break;
    case GLUT_KEY_PAGE_UP: 
        TD::lightVertices[0][1] -= 1.0;
        break;
    }
}
void TerrainDistance::cb_MouseExtended(int x, int y) {}
