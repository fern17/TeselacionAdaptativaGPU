#include "SurfaceCurvature.h"
#include "NewellTeasetData.h"
#include "AxisData.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"
#include <algorithm>

SurfaceCurvature::SurfaceCurvature(std::string name, int w, int h, int vpp, Home *home_ptr) { 
    this->home = home_ptr;
    Example::InitVariables(name, w, h, vpp); 
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";
}

void SurfaceCurvature::DrawScene() {
    //Dibujado de la superficie
    this->shadersModel.Bind(); 
 
    //this->shadersModel.SetUniform("MaxCurvature", this->maxCurvature);
    this->shadersModel.SetUniform("MaxTess", this->maxTess);
    this->shadersModel.SetUniform("CurvFactor", this->curvFactor);
    if (Example::useVirtualCamera) this->shadersModel.SetUniform("CamPos", Example::virtualCamPos);
    else                           this->shadersModel.SetUniform("CamPos", Example::camPos);
    this->shadersModel.SetUniform("UseIllumination", this->useIllumination);
    this->shadersModel.SetUniform("UseTessColoration", this->useTessColoration);

    //this->shadersModel.SetUniform("ModelViewMatrix", Example::ModelViewMatrix);
    this->shadersModel.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shadersModel.SetUniform("NormalMatrix", Example::NormalMatrix);
    this->shadersModel.SetUniform("ViewportMatrix", this->ViewportMatrix);
    this->shadersModel.SetUniformTex("TexColorMap", 8);

  //glBeginQuery(GL_PRIMITIVES_GENERATED, this->query);
    this->vaoModel->Render(GL_PATCHES, sizeof(newellTeapotPatch)/sizeof(unsigned int)); 
  //glEndQuery(GL_PRIMITIVES_GENERATED);
  //unsigned int value;
  //glGetQueryObjectuiv(this->query, GL_QUERY_RESULT, &value);
  //if (value == GL_TRUE) {
  //    glGetQueryObjectuiv(this->query, GL_QUERY_RESULT, &value);
 //     std::cerr<<value<<"\n\n";
  //}
    this->shadersModel.Unbind();

    //Dibujado de los ejes
    this->Translate(glm::vec3(3.0, 0.0, 0.0));
    this->shadersAxis.Bind(); 
    this->shadersAxis.SetUniform("MVPMatrix", MVPMatrix);
    this->vaoAxis->Render(GL_LINES, sizeof(AxisIndices)/sizeof(unsigned int));
    this->shadersAxis.Unbind();
    this->RevertTranslation();
}

void SurfaceCurvature::CreateScene() {
    glGenQueries(1, &this->query);  
    this->vaoModel = new VAO(2);
    //Superficie
    this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &newellTeapotVertices[0][0], sizeof(newellTeapotVertices), 3, GL_STATIC_DRAW);
    this->vaoModel->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &newellTeapotPatch[0][0], sizeof(newellTeapotPatch));
    
    //Ejes
    this->vaoAxis = new VAO(3);  
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisVertices[0][0], sizeof(AxisVertices), 3, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisColors[0][0], sizeof(AxisColors), 4, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &AxisIndices[0][0], sizeof(AxisIndices));

    glActiveTexture(GL_TEXTURE8);
    this->texColorMap = utils::LoadImageTex(texColorName.c_str());

    //Creacion de los shaders
    if (this->shadersModel.CreateProgram("shaders/surface_curvature/vertex.vert", "shaders/surface_curvature/tess_control.tcs", "shaders/surface_curvature/tess_evaluation.tes", "shaders/surface_curvature/geometry.geom", "shaders/surface_curvature/fragment.frag", true)) {
        if (not this->shadersAxis.CreateProgram("shaders/ejes.vert", "", "", "", "shaders/ejes.frag", true)) std::cout<<"Ocurrio un error al crear los shaders de los ejes.\n";
    } else std::cout<<"Ocurrio un error al crear los shaders del modelo.\n";
    
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void SurfaceCurvature::DestroyScene() {
    //Limpieza
    delete vaoModel;
    delete vaoAxis;
    this->shadersAxis.DeleteProgram();
    this->shadersModel.DeleteProgram();
    this->home->Reset();
}


void SurfaceCurvature::SetScene() {
    Example::zNear = 1.0;
    Example::zFar = 40.0;
    Example::camStep = 0.25f;
    this->kDisplacement = 1.0; //Velocidad de movimiento 
    Example::camPos = glm::vec3(0, 4, -6);
    Example::camCenter  = glm::vec3(0, 0, 0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    Example::ModelMatrix = glm::mat4(1.0);
    Example::ModelMatrix = glm::rotate(Example::ModelMatrix, -90.0f, glm::vec3(1,0,0));
    this->RecalcMatrices();
    //Parametros para los poligonos de este modelo en particular
    glDisable(GL_CULL_FACE); //se deshabilita porque se ve la parte interior de elementos opuestos
    //glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    this->maxCurvature = 2.0;
    this->curvFactor = 20.0;
    this->useIllumination = true;
    this->useTessColoration = false;
    this->maxTess = 64.0;
    
    this->texColorName = "../resources/colormap.png";
    
    //Configuramos la cantidad de vertices por patch
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
}

void SurfaceCurvature::cb_KeyboardExtended(unsigned char key, int x, int y) {
    switch(key) {
        case 27: //escape
            this->DestroyScene();
            break;
        case '+':
            this->maxTess = std::min(this->maxTess+1.0, 64.0);
            Example::lastMessage = "Nivel maximo de teselacion = " + utils::XToStr(this->maxTess) + ".\n";
            break;
        case '-':
            this->maxTess = std::max(this->maxTess-1.0, 0.0);
            Example::lastMessage = "Nivel maximo de teselacion = " + utils::XToStr(this->maxTess) + ".\n";
            break;
        case 'u':
        case 'U':
            this->maxCurvature = std::max(0.0f, this->maxCurvature-0.1f);
            Example::lastMessage = "Curvatura maxima de teselacion = " + utils::XToStr(this->maxCurvature) + ".\n"; 
            break;
        case 'y':
        case 'Y':
            this->maxCurvature += 0.1f;
            Example::lastMessage = "Curvatura maxima de teselacion = " + utils::XToStr(this->maxCurvature) + ".\n"; 
            break;
        case 'i':
        case 'I':
            this->useIllumination = not this->useIllumination;
            if (this->useIllumination) Example::lastMessage = "Iluminacion activada.\n";
            else Example::lastMessage = "Iluminacion desactivada.\n";
            break;
        case 'o':
        case 'O':
            this->useTessColoration = not this->useTessColoration;
            if (this->useTessColoration) Example::lastMessage = "Coloracion de niveles de teselacion activada.\n";
            else Example::lastMessage = "Coloracion de niveles de teselacion desactivada.\n";
            break;
        case 'h':
        case 'H':
            if (this->debugMode) {
                std::cout<<"\tY: Aumenta la distancia maxima para teselacion.\n";
                std::cout<<"\tU: Disminuye la distancia maxima para teselacion.\n";
                std::cout<<"\tI: Activa o desactiva la iluminacion.\n";
                std::cout<<"\tH: Imprime este texto.\n";
            }
            Example::lastMessage += "    Y: Aumenta la curvatura maxima para teselacion.\n    U: Disminuye la curvatura maxima para teselacion.\n    I: Activa o desactiva la iluminacion.\n    H: Imprime este texto.\n    Escape: Vuelve al menu principal.\n";
            break;
    }
}

void SurfaceCurvature::cb_SpecialExtended(int key, int x, int y) {}

void SurfaceCurvature::cb_MouseExtended(int x, int y) {};

