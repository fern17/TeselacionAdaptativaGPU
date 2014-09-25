#include "ModelSilhouette.h"
#include "model_silhouette/lightData.h"
#include "AxisData.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"

ModelSilhouette::ModelSilhouette(std::string name, int w, int h, int vpp, bool extendedData, Home *home_ptr, std::string modelname) {
    Example::InitVariables(name, w, h, vpp);
    this->home = home_ptr;
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<__TIMESTAMP__<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";

    std::string filename;
    if (modelname.length() > 0) filename = "../mesh/" + modelname;
    else filename = "../mesh/alien.obj";
    Example::lastMessage = "Modelo cargado: " + filename + ".\n";
    this->model = new Model(filename, vpp, extendedData); 
    this->model->GenExtendedData();
}

void ModelSilhouette::DrawScene() {
  //if (this->rotate) {
  //    glm::vec3 upp = glm::normalize(Example::camUp);
  //    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
  //    glm::vec3 crs = glm::cross(Example::camEyeTarget, upp);
  //    Example::camPos = Example::camPos + crs*this->rotationSpeed;
  //    this->RecalcMatrices();
  //}

    this->shadersModel.Bind();  
    this->shadersModel.SetUniform("ModelViewMatrix", Example::ModelViewMatrix);
    this->shadersModel.SetUniform("MVPMatrix",       Example::MVPMatrix);
    this->shadersModel.SetUniform("ViewportMatrix",  Example::ViewportMatrix);
    if (Example::useVirtualCamera) { this->shadersModel.SetUniform("CamPos", Example::virtualCamPos); this->shadersModel.SetUniform("CamCenter", Example::virtualCamCenter); }
    else                           { this->shadersModel.SetUniform("CamPos", Example::camPos);        this->shadersModel.SetUniform("CamCenter", Example::camCenter); }
    this->shadersModel.SetUniform("TMin",            this->tMin);
    this->shadersModel.SetUniform("TMax",            this->tMax);
    this->shadersModel.SetUniform("MaxTess",         this->maxTess);
    this->shadersModel.SetUniform("Tessellate",      this->tessellate);
    this->shadersModel.SetUniform("Beta",            this->beta);
    this->shadersModel.SetUniform("Dyadic",          this->dyadic);
    this->shadersModel.SetUniform("TessDefault",     this->tessDefault);
    this->shadersModel.SetUniform("ViewPortSize",    this->viewPortSize);
    this->shadersModel.SetUniform("DrawWire",        this->drawWire);
    this->shadersModel.SetUniform("UseIllumination", this->useIllumination);
    this->shadersModel.SetUniform("UseTessColoration",this->useTessColoration);
    this->shadersModel.SetUniform("TessDivisor",     this->tessDivisor);
    this->shadersModel.SetUniform("LightPosition", glm::vec3(
                      MS::lightVertices[0][0], MS::lightVertices[0][1], MS::lightVertices[0][2]));

    this->vaoModel->Render(GL_PATCHES, this->model->numIndices);
    this->shadersModel.Unbind();

    this->shadersAxis.Bind(); 
    this->shadersAxis.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->vaoAxis->Render(GL_LINES, sizeof(AxisIndices)/sizeof(unsigned int));
    this->shadersAxis.Unbind();

    glPointSize(5.0);
    this->shadersLight.Bind(); 
    this->shadersLight.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shadersLight.SetUniform("UseIllumination", this->useIllumination);
    this->vaoLight->UpdateBuffer(GL_ARRAY_BUFFER, &MS::lightVertices[0][0], sizeof(MS::lightVertices));
    this->vaoLight->Render(GL_POINTS, sizeof(MS::lightIndices)/sizeof(unsigned int));
    this->shadersLight.Unbind();

    if (this->drawNormals) {
        this->shadersNormals.Bind();
        this->shadersNormals.SetUniform("MVPMatrix", Example::MVPMatrix);
        this->shadersNormals.SetUniform("NormScale", this->normScale);
        this->vaoNormals->RenderArray(GL_POINTS, this->model->normals.size());
        this->shadersNormals.Unbind();
    }
}

void ModelSilhouette::CreateScene() {
    this->vaoModel = new VAO(3);
    this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &(this->model->vertices[0]), sizeof(float)*this->model->vertices.size(), 3, GL_STATIC_DRAW);
    this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &(this->model->normals[0]), sizeof(float)*this->model->normals.size(), 3, GL_STATIC_DRAW);

  //this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &(this->model->neighborsNormalsPerElement[0][0]), sizeof(float)*this->model->neighborsNormalsPerElement[0].size(), 3, GL_STATIC_DRAW);
  //utils::ExitOnGLError("Error: no se pudo bindear el VBO al VAO (model->, normales 0 del elemento)");
  //this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &(this->model->neighborsNormalsPerElement[1][0]), sizeof(float)*this->model->neighborsNormalsPerElement[1].size(), 3, GL_STATIC_DRAW);
  //utils::ExitOnGLError("Error: no se pudo bindear el VBO al VAO (model->, normales 1 del elemento)");
  //this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &(this->model->neighborsNormalsPerElement[2][0]), sizeof(float)*this->model->neighborsNormalsPerElement[2].size(), 3, GL_STATIC_DRAW);
  //utils::ExitOnGLError("Error: no se pudo bindear el VBO al VAO (model->, normales 2 del elemento)");

    //this->vaoModel->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(this->model->indices[0]), sizeof(unsigned int)*this->model->numIndices);
    this->vaoModel->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(this->model->indicesExtended[0]), sizeof(unsigned int)*this->model->numFaces*3*2); //tiene el doble de indices porque hay el doble de vertices por elemento
    
    this->vaoAxis = new VAO(3);  
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisVertices[0][0], sizeof(AxisVertices), 3, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisColors[0][0], sizeof(AxisColors), 4, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &AxisIndices[0][0], sizeof(AxisIndices));
    
    this->vaoLight = new VAO(2);  
    this->vaoLight->AddBuffer(GL_ARRAY_BUFFER, &MS::lightVertices[0][0], sizeof(MS::lightVertices), 3, GL_STREAM_DRAW); //Este se modifica
    this->vaoLight->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &MS::lightIndices[0][0], sizeof(MS::lightIndices));

    this->vaoNormals = new VAO(2);
    this->vaoNormals->AddBuffer(GL_ARRAY_BUFFER, &(this->model->vertices[0]), sizeof(float)*this->model->vertices.size(), 3, GL_STATIC_DRAW);
    this->vaoNormals->AddBuffer(GL_ARRAY_BUFFER, &(this->model->normals[0]), sizeof(float)*this->model->normals.size(), 3, GL_STATIC_DRAW);

    if (this->shadersModel.CreateProgram("shaders/model_silhouette/vertex.vert", "shaders/model_silhouette/tess_control.tcs", "shaders/model_silhouette/tess_evaluation.tes", "shaders/model_silhouette/geometry.geom", "shaders/model_silhouette/fragment.frag")) {
        if (this->shadersAxis.CreateProgram("shaders/ejes.vert", "", "", "", "shaders/ejes.frag")) {
            if (shadersNormals.CreateProgram("shaders/model_silhouette/normals.vert", "", "", "shaders/model_silhouette/normals.geom", "shaders/model_silhouette/normals.frag")) {
                if (not shadersLight.CreateProgram("shaders/light.vert", "", "", "", "shaders/light.frag")) 
                    std::cout<<"Ocurrio un error al crear los shaders de las luces.\n";
            } else std::cout<<"Ocurrio un error al crear los shaders de las normales.\n";
        } else std::cout<<"Ocurrio un error al crear los shaders de los ejes.\n";
    } else  std::cout<<"Ocurrio un error al crear los shaders del modelo.\n";
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void ModelSilhouette::DestroyScene() {
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

void ModelSilhouette::SetScene() {
    Example::zNear = 0.1f;
    Example::zFar = 40.0;
    Example::camStep = 0.1f;
    this->kDisplacement = 1.0; //Velocidad de movimiento 
    Example::camPos = glm::vec3(1, 4, 1);
    Example::camCenter  = glm::vec3(-1, 4, 0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(camCenter - camPos);
    //Este codigo se repite aca porque se modifica el modelo en la linea anterior
   
    this->RecalcMatrices();
    
    this->tessellate = true;
    this->drawWire = false;
    this->useIllumination = false;
    this->useTessColoration = true;
    this->drawNormals = false;
    this->dyadic = true;
    this->beta = 0.25;
    this->maxTess = 8.0;
    this->tessDefault = maxTess;
    this->rotate = false;
    this->normScale = 0.03;
    this->rotationSpeed = 0.05f;
    this->tessDivisor = 10.0f;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    this->tMin = 0.0;
    this->tMax = 100.0;
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
}

void ModelSilhouette::cb_KeyboardExtended(unsigned char key, int x, int y) {
    switch(key) {
    case 27: //escape
        this->DestroyScene();
        break;
    case 'T': 
    case 't':
        this->tessellate = not this->tessellate;
        if (tessellate) Example::lastMessage = "Teselacion adaptativa activada.\n";
        else Example::lastMessage = "Teselacion adaptativa desactivada. Valor por defecto = "+utils::XToStr(tessDefault)+".\n";
        break;
  //case 'r':
  //case 'R':
  //    this->rotate = not this->rotate;
  //    if (rotate) Example::lastMessage = "Rotacion activada.\n";
  //    else Example::lastMessage = "Rotacion desactivada.\n";
  //    break;
    case 'k':
    case 'K':
        this->drawWire = not this->drawWire;
        if (drawWire) Example::lastMessage = "Dibujar lineas.\n";
        else Example::lastMessage = "No dibujar lineas.\n";
        break;
    case 'y': 
        this->dyadic = not this->dyadic;
        if (this->dyadic) Example::lastMessage = "Teselacion diadica activada.\n";
        else Example::lastMessage = "Teselacion diadica desactivada.\n";
        break;
    case '+':
        this->maxTess = std::min(64.0f, this->maxTess+1.0f);
        Example::lastMessage = "maxTess = " + utils::XToStr(maxTess) + ".\n";
        break;
    case '-':
        this->maxTess = std::max(1.0f, this->maxTess-1.0f);
        Example::lastMessage = "maxTess = " + utils::XToStr(maxTess) + ".\n";
        break;
    case 'i':
    case 'I':
        this->useIllumination = not this->useIllumination;
        if (useIllumination) Example::lastMessage = "Iluminacion activada.\n";
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
        this->rotationSpeed -= 0.05f;
        Example::lastMessage = "Velocidad de rotacion = " + utils::XToStr(this->rotationSpeed) + ".\n";
        break;
    case 'x':
    case 'X':
        this->rotationSpeed += 0.05;
        Example::lastMessage = "Velocidad de rotacion = " + utils::XToStr(this->rotationSpeed) + ".\n";
        break;
    case 'c':
    case 'C':
        this->tessDivisor = std::max(this->tessDivisor-1.0, 1.0);
        Example::lastMessage = "Divisor de teselacion = " + utils::XToStr(this->tessDivisor) + ".\n";
        break;
    case 'v':
    case 'V':
        this->tessDivisor += 1.0f;
        Example::lastMessage = "Divisor de teselacion = " + utils::XToStr(this->tessDivisor) + ".\n";
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
        Example::lastMessage = "Longitud de Normales = " + utils::XToStr(this->normScale) + ".\n";
        break;
    case '.':
        this->normScale += 0.01f;
        Example::lastMessage = "Longitud de Normales = " + utils::XToStr(this->normScale) + ".\n";
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
        std::cout<<"\tY: Disminuye el nivel maximo de teselacion.\n";
        std::cout<<"\tU: Aumenta el nivel maximo de teselacion.\n";
        std::cout<<"\tC: Disminuye el divisor para el nivel de teselacion.\n";
        std::cout<<"\tV: Aumenta el divisor para el nivel de teselacion.\n";
        std::cout<<"\tR: Activa o desactiva la rotacion de la camara.\n";
        std::cout<<"\tZ: Disminuye la velocidad de rotacion.\n";
        std::cout<<"\tX: Aumenta la velocidad de rotacion.\n";
        std::cout<<"\tFlechas y Av/RePag: Cambia la posicion de la luz.\n";
        std::cout<<"\tH: Imprime este texto.\n";
        */
        const char* added_text = 
        "    T: Activa o desactiva teselacion por hardware.\n"
        "    L: Intercambia entre poligono rellenos o no.\n"
        "    K: Intercambia entre dibujar lineas o no.\n"
        "    I: Intercambia entre usar iluminacion o no.\n"
        "    O: Intercambia entre usar coloracion de niveles de teselacion o no.\n"
        "    N: Intercambia entre dibujar normales o no.\n"
        "    ,: Disminuye el tamano de normales.\n"
        "    .: Aumenta el tamano de normales.\n"
        "    Y: Disminuye el nivel maximo de teselacion.\n"
        "    U: Aumenta el nivel maximo de teselacion.\n"
        "    C: Disminuye el divisor para el nivel de teselacion.\n"
        "    V: Aumenta el divisor para el nivel de teselacion.\n"
        //"    R: Activa o desactiva la rotacion de la camara.\n"
        "    Z: Disminuye la velocidad de rotacion.\n"
        "    X: Aumenta la velocidad de rotacion.\n"
        "    Flechas y Av/RePag: Cambia la posicion de la luz.\n"
        "    Escape: Vuelve al menu principal.\n"
        "    H: Imprime este texto.\n";
        Example::lastMessage += std::string(added_text);
        break;
    }
}

void ModelSilhouette::cb_SpecialExtended(int key, int x, int y) {
    switch(key){
    case GLUT_KEY_UP: 
        MS::lightVertices[0][2] += 1.0;
        Example::lastMessage = "Posicion de la Luz = " + utils::XToStr(MS::lightVertices[0][0]) + " " + utils::XToStr(MS::lightVertices[0][1]) + " " + utils::XToStr(MS::lightVertices[0][2]) +".\n";
        break;
    case GLUT_KEY_DOWN: 
        MS::lightVertices[0][2] -= 1.0;
        Example::lastMessage = "Posicion de la Luz = " + utils::XToStr(MS::lightVertices[0][0]) + " " + utils::XToStr(MS::lightVertices[0][1]) + " " + utils::XToStr(MS::lightVertices[0][2]) +".\n";
        break;
    case GLUT_KEY_LEFT: 
        MS::lightVertices[0][0] -= 1.0;
        Example::lastMessage = "Posicion de la Luz = " + utils::XToStr(MS::lightVertices[0][0]) + " " + utils::XToStr(MS::lightVertices[0][1]) + " " + utils::XToStr(MS::lightVertices[0][2]) +".\n";
        break;
    case GLUT_KEY_RIGHT: 
        MS::lightVertices[0][0] += 1.0;
        Example::lastMessage = "Posicion de la Luz = " + utils::XToStr(MS::lightVertices[0][0]) + " " + utils::XToStr(MS::lightVertices[0][1]) + " " + utils::XToStr(MS::lightVertices[0][2]) +".\n";
        break;
    case GLUT_KEY_PAGE_DOWN: 
        MS::lightVertices[0][1] += 1.0;
        Example::lastMessage = "Posicion de la Luz = " + utils::XToStr(MS::lightVertices[0][0]) + " " + utils::XToStr(MS::lightVertices[0][1]) + " " + utils::XToStr(MS::lightVertices[0][2]) +".\n";
        break;
    case GLUT_KEY_PAGE_UP: 
        MS::lightVertices[0][1] -= 1.0;
        Example::lastMessage = "Posicion de la Luz = " + utils::XToStr(MS::lightVertices[0][0]) + " " + utils::XToStr(MS::lightVertices[0][1]) + " " + utils::XToStr(MS::lightVertices[0][2]) +".\n";
        break;
    }
}

void ModelSilhouette::cb_MouseExtended(int x, int y) {}
