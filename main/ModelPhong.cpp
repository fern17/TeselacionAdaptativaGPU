#include "ModelPhong.h"
#include "model_phong/LightData.h"
#include "AxisData.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"

ModelPhong::ModelPhong(std::string name, int w, int h, int vpp, bool extendedData, Home* home_ptr, std::string modelname) {
    if (extendedData)
        Example::InitVariables(name, w, h, vpp*2);
    else 
        Example::InitVariables(name, w, h, vpp);
    
    this->home = home_ptr;
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";

    std::string filename;
    if (modelname.length() > 0) filename = "../mesh/" + modelname;
    else filename = "../mesh/alien.obj";
    Example::lastMessage = "Modelo cargado: " + filename + ".\n";
    
    this->model = new Model(filename, vpp, extendedData);
    this->model->GenExtendedData(); //Genera vecindarios de vertices
}

void ModelPhong::DrawScene() {
    this->shadersModel.Bind();  
    this->shadersModel.SetUniform("ModelViewMatrix", Example::ModelViewMatrix);
    this->shadersModel.SetUniform("MVPMatrix",       Example::MVPMatrix);
    this->shadersModel.SetUniform("ViewportMatrix",  Example::ViewportMatrix);
    if (Example::useVirtualCamera) { this->shadersModel.SetUniform("CamPos", Example::virtualCamPos); this->shadersModel.SetUniform("CamCenter", Example::virtualCamCenter); }
    else                           { this->shadersModel.SetUniform("CamPos", Example::camPos);        this->shadersModel.SetUniform("CamCenter", Example::camCenter); }
    this->shadersModel.SetUniform("MaxTess",         this->maxTess);
    this->shadersModel.SetUniform("Tessellate",      this->tessellate);
    this->shadersModel.SetUniform("TessDefault",     this->tessDefault);
    this->shadersModel.SetUniform("viewPortSize",    this->viewPortSize);
    this->shadersModel.SetUniform("Beta",            this->beta);
    this->shadersModel.SetUniform("LightPosition", 
                                  glm::vec3(MP::lightVertices[0][0], MP::lightVertices[0][1], MP::lightVertices[0][2]));
    this->shadersModel.SetUniform("DrawWire",         this->drawWire);
    this->shadersModel.SetUniform("UseIllumination",  this->useIllumination);
    this->shadersModel.SetUniform("UseTessColoration",this->useTessColoration);
    this->shadersModel.SetUniform("Alpha",            this->alpha);
    this->shadersModel.SetUniformTex("TexColorMap", 8);
    this->vaoModel->Render(GL_PATCHES, this->model->GetNumIndices());
    this->shadersModel.Unbind();

    this->shadersAxis.Bind(); 
    this->shadersAxis.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->vaoAxis->Render(GL_LINES, sizeof(AxisIndices)/sizeof(unsigned int));
    this->shadersAxis.Unbind();

    glPointSize(10.0);
    this->shadersLight.Bind();
    this->shadersLight.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shadersLight.SetUniform("UseIllumination", this->useIllumination);
    this->vaoLight->UpdateBuffer(GL_ARRAY_BUFFER, &MP::lightVertices[0][0], sizeof(MP::lightVertices));
    this->vaoLight->Render(GL_POINTS, sizeof(MP::lightIndices)/sizeof(unsigned int));
    this->shadersLight.Unbind();

    if (this->drawNormals) {
        this->shadersNormals.Bind();
        this->shadersNormals.SetUniform("MVPMatrix", Example::MVPMatrix);
        this->shadersNormals.SetUniform("NormScale", this->normScale);
        this->vaoNormals->RenderArray(GL_POINTS, this->model->normals.size());
        this->shadersNormals.Unbind();
    }
}

void ModelPhong::CreateScene() {
    this->vaoModel = new VAO(3);
    this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &(this->model->vertices[0]), sizeof(float)*this->model->vertices.size(), 3, GL_STATIC_DRAW);
    this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &(this->model->normals[0]), sizeof(float)*this->model->normals.size(), 3, GL_STATIC_DRAW);
    this->vaoModel->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(this->model->indicesExtended[0]), sizeof(unsigned int)*this->model->numFaces*3*2); //tiene el doble de indices porque hay el doble de vertices por elemento
    
    this->vaoAxis = new VAO(3);  
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisVertices[0][0], sizeof(AxisVertices), 3, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisColors[0][0], sizeof(AxisColors), 4, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &AxisIndices[0][0], sizeof(AxisIndices));
    
    this->vaoLight = new VAO(2);  
    this->vaoLight->AddBuffer(GL_ARRAY_BUFFER, &MP::lightVertices[0][0], sizeof(MP::lightVertices), 3, GL_STREAM_DRAW); //Este se modifica
    this->vaoLight->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &MP::lightIndices[0][0], sizeof(MP::lightIndices));

    this->vaoNormals = new VAO(2);
    this->vaoNormals->AddBuffer(GL_ARRAY_BUFFER, &(this->model->vertices[0]), sizeof(float)*this->model->vertices.size(), 3, GL_STATIC_DRAW);
    this->vaoNormals->AddBuffer(GL_ARRAY_BUFFER, &(this->model->normals[0]), sizeof(float)*this->model->normals.size(), 3, GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE8);
    this->texColorMap = utils::LoadImageTex(texColorName.c_str());

    if (this->shadersModel.CreateProgram("shaders/model_phong/vertex.vert", "shaders/model_phong/tess_control.tcs", "shaders/model_phong/tess_evaluation.tes", "shaders/model_phong/geometry.geom", "shaders/model_phong/fragment.frag")) {
        if (this->shadersAxis.CreateProgram("shaders/ejes.vert", "", "", "", "shaders/ejes.frag")) {
            if (shadersNormals.CreateProgram("shaders/model_phong/normals.vert", "", "", "shaders/model_phong/normals.geom", "shaders/model_phong/normals.frag")) {
                if (not shadersLight.CreateProgram("shaders/light.vert", "", "", "", "shaders/light.frag")) { 
                    std::cout<<"Ocurrio un error al crear los shaders de las luces.\n";
                }
            } else std::cout<<"Ocurrio un error al crear los shaders de las normales.\n";
        } else std::cout<<"Ocurrio un error al crear los shaders de los ejes.\n";
    } else std::cout<<"Ocurrio un error al crear los shaders del modelo.\n";
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void ModelPhong::DestroyScene() {
    delete vaoModel;
    delete vaoAxis;
    delete vaoNormals;
    delete vaoLight;
    delete model;

    this->shadersAxis.DeleteProgram();
    this->shadersModel.DeleteProgram();
    this->shadersLight.DeleteProgram();
    this->shadersNormals.DeleteProgram();

    this->home->Reset();
}

void ModelPhong::SetScene() {
    Example::zNear = 0.1f;
    Example::zFar = 40.0;
    Example::camStep = 0.1f;
    this->kDisplacement = 1.0; //Velocidad de movimiento 
    Example::camPos = glm::vec3(1, 1, 3);
  //Example::camPos = glm::vec3(1, 4, 1);
  //Example::camCenter  = glm::vec3(-1, 4, 0);
    Example::camCenter  = glm::vec3(1, 1, 0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(camCenter - camPos);
    Example::virtualCamPos = glm::vec3(2,4,1);
    Example::virtualCamCenter = glm::vec3(0,3,0);
    Example::useVirtualCamera = false;
    this->RecalcMatrices();

    this->tessellate = true;
    this->drawWire = true;
    this->useIllumination = true;
    this->useTessColoration = false;
    this->drawNormals = false;
    this->normScale = 0.03;
    this->maxTess = 8.0;
    this->tessDefault = 1.0;
    this->alpha = 0.75;
    this->beta = 0.25;

    this->texColorName = "../resources/colormap.png";

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glDisable(GL_CULL_FACE);
    
    Example::renderText = true;
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
}

void ModelPhong::cb_KeyboardExtended(unsigned char key, int x, int y) {
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
    case 'y': 
    case 'Y':
        if (this->maxTess < 1.01) this->maxTess = 4.0f;
        else if (this->maxTess < 64.0) this->maxTess += 4.0f;
        Example::lastMessage = "Nivel de teselacion maxima = " + utils::XToStr(this->maxTess) + ".\n";
        break;
    case 'u': 
    case 'U':
        if (this->maxTess <= 4.0) this->maxTess = 1.0;
        else  this->maxTess -= 4.0f;
        Example::lastMessage = "Nivel de teselacion maxima = " + utils::XToStr(this->maxTess) + ".\n";
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
    case 'z':
    case 'Z':
        this->alpha -= 0.05f;
        this->alpha = std::max(this->alpha, 0.0f);
        Example::lastMessage = "Alpha = " + utils::XToStr(this->alpha) + ".\n";
        break;
    case 'x':
    case 'X':
        this->alpha += 0.05f;
        this->alpha = std::min(alpha, 1.0f);
        Example::lastMessage = "Alpha = " + utils::XToStr(this->alpha) + ".\n";
        break;
    case '+':
        this->tessDefault = std::min(64.0, tessDefault+1.0);        
        Example::lastMessage = "Niveles de teselacion = " + utils::XToStr(this->tessDefault) + ".\n";
        break;
    case '-':
        this->tessDefault = std::max(1.0, tessDefault-1.0);        
        Example::lastMessage = "Niveles de teselacion = " + utils::XToStr(this->tessDefault) + ".\n";
        break;
    case 'f':
        this->beta = std::min(this->beta+0.05, 1.0);
        Example::lastMessage = "Constante Beta = " + utils::XToStr(this->beta) + ".\n";
        break;
    case 'F':
        this->beta = std::max(this->beta-0.05, 0.0);
        Example::lastMessage = "Constante Beta = " + utils::XToStr(this->beta) + ".\n";
        break;
    case 'n':
    case 'N':
        this->drawNormals = not this->drawNormals;
        if (this->drawNormals) Example::lastMessage = "Dibujar normales.\n";
        else Example::lastMessage = "No dibujar normales.\n";
        break;
    case ',':
        this->normScale -= 0.01f;
        this->normScale = std::max(this->normScale, 0.01f);
        Example::lastMessage = "Longitud de normales = " + utils::XToStr(this->normScale) + ".\n";
        break;
    case '.':
        this->normScale += 0.01f;
        Example::lastMessage = "Longitud de normales = " + utils::XToStr(this->normScale) + ".\n";
        break;
    case 'h':
    case 'H':
        /*
        std::cout<<"\tT: Activa o desactiva teselacion por hardware.\n";
        std::cout<<"\tL: Intercambia entre poligono rellenos o no.\n";
        std::cout<<"\tK: Intercambia entre dibujar lineas o no.\n";
        std::cout<<"\tI: Intercambia entre usar iluminacion o no.\n";
        std::cout<<"\tN: Intercambia entre dibujar normales o no.\n";
        std::cout<<"\t,: Disminuye el tamano de normales.\n";
        std::cout<<"\t.: Aumenta el tamano de normales.\n";
        std::cout<<"\tY: Aumenta el nivel maximo de teselacion.\n";
        std::cout<<"\tU: Disminuye el nivel maximo de teselacion.\n";
        std::cout<<"\tFlechas y Av/RePag: Cambia la posicion de la luz.\n";
        std::cout<<"\tH: Imprime este texto.\n";
        */
        const char *added_text = 
        "    T: Activa o desactiva teselacion por hardware.\n"
        "    K: Intercambia entre dibujar lineas o no.\n"
        "    I: Intercambia entre usar iluminacion o no.\n"
        "    O: Intercambia entre usar coloracion de niveles de teselacion o no.\n"
        "    N: Intercambia entre dibujar normales o no.\n"
        "    ,: Disminuye el tamano de normales.\n"
        "    .: Aumenta el tamano de normales.\n"
        "    Y: Aumenta el nivel maximo de teselacion.\n"
        "    U: Disminuye el nivel maximo de teselacion.\n"
        "    Flechas y Av/RePag: Cambia la posicion de la luz.\n"
        "    Escape: Vuelve al menu principal.\n"
        "    H: Imprime este texto.\n";
        Example::lastMessage += std::string(added_text);

        break;
    }
}

void ModelPhong::cb_SpecialExtended(int key, int x, int y) {
    switch(key){
    case GLUT_KEY_UP:
        MP::lightVertices[0][2] += 1.0;
        break;
    case GLUT_KEY_DOWN: 
        MP::lightVertices[0][2] -= 1.0;
        break;
    case GLUT_KEY_LEFT: 
        MP::lightVertices[0][0] -= 1.0;
        break;
    case GLUT_KEY_RIGHT: 
        MP::lightVertices[0][0] += 1.0;
        break;
    case GLUT_KEY_PAGE_DOWN: 
        MP::lightVertices[0][1] += 1.0;
        break;
    case GLUT_KEY_PAGE_UP: 
        MP::lightVertices[0][1] -= 1.0;
        break;
    }
}

void ModelPhong::cb_MouseExtended(int x, int y) {}
