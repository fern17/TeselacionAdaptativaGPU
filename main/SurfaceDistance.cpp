#include "SurfaceDistance.h"
#include "NewellTeasetData.h"
#include "AxisData.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"
#include <algorithm>

SurfaceDistance::SurfaceDistance(std::string name, int w, int h, int vpp, Home *home_ptr) { 
    this->home = home_ptr;
    Example::InitVariables(name, w, h, vpp); 
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";
}

void SurfaceDistance::DrawScene() {
    //Dibujado de la superficie
        double displacement = -15;
    this->shadersModel.Bind(); 
 
    this->shadersModel.SetUniform("MaxDist", this->maxDist);
    this->shadersModel.SetUniform("MinDist", this->minDist);
    this->shadersModel.SetUniform("UseTessLinear", this->useTessLinear);
    this->shadersModel.SetUniform("Tessellate", this->tessellate);

    this->shadersModel.SetUniform("MaxTess", this->maxTess);
    if (Example::useVirtualCamera) this->shadersModel.SetUniform("CamPos", Example::virtualCamPos);
    else                           this->shadersModel.SetUniform("CamPos", Example::camPos);
    this->shadersModel.SetUniform("UseIllumination", this->useIllumination);
    this->shadersModel.SetUniform("UseTessColoration", this->useTessColoration);
    this->shadersModel.SetUniformTex("TexColorMap", 8);

    
    for (int i = 0; i < 3; i++) {
        //Primero se calcula la rotacion del modelo
        Example::ModelMatrix = glm::mat4(1.0);
        Example::ModelMatrix = glm::rotate(Example::ModelMatrix, -90.0f, glm::vec3(1,0,0));
        this->RecalcMatrices(); //recalcular todas las matrices
        glm::vec3 delta = glm::vec3(displacement/2*i, displacement*i, 0.0); //desplazamiento a imponer al modelo
        this->Translate(delta); //trasladar el modelo
        this->shadersModel.SetUniform("delta", delta);  //enviar la posicion nueva y la matriz nueva
        this->shadersModel.SetUniform("ModelViewMatrix", Example::ModelViewMatrix);
        this->shadersModel.SetUniform("MVPMatrix", Example::MVPMatrix);
        this->shadersModel.SetUniform("NormalMatrix", Example::NormalMatrix);
        this->shadersModel.SetUniform("ViewportMatrix", this->ViewportMatrix);

        this->vaoModel->Render(GL_PATCHES, sizeof(newellTeapotPatch)/sizeof(unsigned int)); 
        this->RevertTranslation(); //restaurar e iterar
    }
    this->shadersModel.Unbind();




  ////Dibujado de los ejes
  //this->Translate(glm::vec3(3.0, 0.0, 0.0));
  //this->shadersAxis.Bind(); 
  //this->shadersAxis.SetUniform("MVPMatrix", MVPMatrix);
  //this->vaoAxis->Render(GL_LINES, sizeof(AxisIndices)/sizeof(unsigned int));
  //this->shadersAxis.Unbind();
  //this->RevertTranslation();
}

void SurfaceDistance::CreateScene() {
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
    if (this->shadersModel.CreateProgram("shaders/surface_distance/vertex.vert", "shaders/surface_distance/tess_control.tcs", "shaders/surface_distance/tess_evaluation.tes", "shaders/surface_distance/geometry.geom", "shaders/surface_distance/fragment.frag", true)) {
        if (not this->shadersAxis.CreateProgram("shaders/ejes.vert", "", "", "", "shaders/ejes.frag", true)) std::cout<<"Ocurrio un error al crear los shaders de los ejes.\n";
    } else std::cout<<"Ocurrio un error al crear los shaders del modelo.\n";
    
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void SurfaceDistance::DestroyScene() {
    //Limpieza
    delete vaoModel;
    delete vaoAxis;
    this->shadersAxis.DeleteProgram();
    this->shadersModel.DeleteProgram();
    this->home->Reset();
}


void SurfaceDistance::SetScene() {
	glClearColor (0.6f, 0.6f, 0.6f, 1.0f);
    Example::zNear = 1.0;
    Example::zFar = 100.0;
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
    this->maxDist = 10.0;
    this->minDist = Example::zNear;
    this->useTessLinear = true;
    this->useIllumination = true;
    this->useTessColoration = false;
    this->maxTess = 64.0;
    this->tessellate = true;
    
    this->texColorName = "../resources/colormap.png";
    //Configuramos la cantidad de vertices por patch
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
}

void SurfaceDistance::cb_KeyboardExtended(unsigned char key, int x, int y) {
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
            if (this->maxDist > 1.0f) this->maxDist -= 1.0f;
            Example::lastMessage = "Distancia Maxima de teselacion = " + utils::XToStr(this->maxDist) + ".\n"; 
            break;
        case 'y':
        case 'Y':
            this->maxDist += 1.0f;
            Example::lastMessage = "Distancia Maxima de teselacion = " + utils::XToStr(this->maxDist) + ".\n"; 
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
        case 'v':
        case 'V':
            this->useTessLinear = not this->useTessLinear;
            if (this->useTessLinear) Example::lastMessage = "Se utiliza teselacion lineal.\n";
            else Example::lastMessage = "Se utiliza teselacion lineal inversa.\n";
            break;
        case 't':
        case 'T':
            this->tessellate = not this->tessellate;
            if (this->tessellate) Example::lastMessage = "Teselacion activada.\n";
            else Example::lastMessage = "Teselacion desactivada.\n";
            break;
        case 'h':
        case 'H':
            if (this->debugMode) {
                std::cout<<"\tY: Aumenta la distancia maxima para teselacion.\n";
                std::cout<<"\tU: Disminuye la distancia maxima para teselacion.\n";
                std::cout<<"\tI: Activa o desactiva la iluminacion.\n";
                std::cout<<"\tH: Imprime este texto.\n";
            }
            Example::lastMessage += "    Y: Aumenta la distancia maxima para teselacion.\n    U: Disminuye la distancia maxima para teselacion.\n    V: Intercambia entre teselacion lineal y lineal inversa.\n    I: Activa o desactiva la iluminacion.\n    H: Imprime este texto.\n    Escape: Vuelve al menu principal.\n";
            break;
    }
}

void SurfaceDistance::cb_SpecialExtended(int key, int x, int y) {}

void SurfaceDistance::cb_MouseExtended(int x, int y) {};

