#include "Home.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include <glm/gtc/type_ptr.hpp> //value_ptr
#include "utils.h"
#include <algorithm>
#include "SurfaceDistance.h"
#include "SurfaceCurvature.h"
#include "TerrainDistance.h"
#include "TerrainEdge.h"
#include "ModelPhong.h"
//#include "ModelSilhouette.h"
#include "CurveCurvature.h"
#include "FieldDistance.h"
#include "TessDemo.h"
#include "other/ZFight.h"

Home::Home(std::string name, int w, int h) { Example::InitVariables(name, w, h, 1); }
#define RENDERTEXT0 //si esta activo, dibuja el menu principal
#define RENDERTEXT1 //si esta activo, dibuja texto en pantalla (mas lento)

void Home::DrawScene() {
    if (this->currentExample != 0) {
         //double clockNow = utils::GetUnixTime();
         //double dt_fps = clockNow - Example::clockLast;
         //if (dt_fps > Example::deltaToMeasureFPS) { 
         //    if (this->secondsSinceBeginning > this->timeToChangeMaxTess) {
         //        this->loadedExample->maxTess = std::min(64.0f, this->loadedExample->maxTess+this->deltaMaxTess);
         //        std::cerr<<"MaxTess = "<<this->loadedExample->maxTess<<"\n";
         //        this->secondsSinceBeginning = 0;

         //        if (Example::fileToLog.is_open())
         //            Example::fileToLog<<utils::GetCurrentDateTime()<<"\t\t\tMaxTess\t"<<this->loadedExample->maxTess;
         //        this->CalcStatistics(0);
         //        Example::historyFps.clear(); 
         //        Example::historyFps.reserve(this->timeToChangeMaxTess+10);
         //        } else  this->secondsSinceBeginning++;       
         //}
        
        this->loadedExample->DrawScene();
        if (Example::useVirtualCamera) {
                
            glPointSize(10.0);
            this->shadersVirtualCamera.Bind(); 
            this->shadersVirtualCamera.SetUniform("MVPMatrix", Example::MVPMatrix);
            this->vaoVirtualCamera->UpdateBuffer(GL_ARRAY_BUFFER, (glm::value_ptr(Example::virtualCamPos)), sizeof(double)*3);
            this->vaoVirtualCamera->Render(GL_POINTS, 1);
            this->shadersVirtualCamera.Unbind();
        }
#ifdef RENDERTEXT1
        if (Example::renderText) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            float sx = 2.0 / float(this->WINDOW_WIDTH);
            float sy = 2.0 / float(this->WINDOW_HEIGHT);
            unsigned int text_size = float(this->WINDOW_HEIGHT)/50.0;
            Example::textRenderer->Render((utils::IntToStr(this->fps)+" fps").c_str(), glm::vec4(this->colorFps, 1.0), 15, -1.0, 0.95, sx, sy, this->WINDOW_HEIGHT);
            Example::textRenderer->Render((utils::XToStr(Example::frameTime)+" ms per frame").c_str(), glm::vec4(this->colorFps, 1.0), 15, 0.65, 0.95, sx, sy, this->WINDOW_HEIGHT);
            //Example::textRenderer->Render(std::string("Ayuda (h)").c_str(), glm::vec4(this->colorHelp, 1.0), 15, 0.85, 0.95, sx, sy, this->WINDOW_HEIGHT);
            Example::textRenderer->Render(Example::lastMessage.c_str(), glm::vec4(this->colorStatus, 1.0), text_size+1, -1.0, -1.0 + (std::count(Example::lastMessage.begin(), Example::lastMessage.end(), '\n'))/25.0, sx, sy, this->WINDOW_HEIGHT);
            if (not Example::fillPolygon) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }    
#endif
    } else {
#ifdef RENDERTEXT0
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        float sx = 2.0 / float(this->WINDOW_WIDTH);
        float sy = 2.0 / float(this->WINDOW_HEIGHT);
        unsigned int text_size = float(this->WINDOW_HEIGHT)/15.0;

        Example::textRenderer->Render(this->menuTitle.c_str(), glm::vec4(1.0, 1.0, 1.0, 1.0), text_size+1, -1.0, 0.8, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(this->menuInstructions.c_str(), glm::vec4(0.2, 0.2, 0.2, 1.0), text_size-3, -1.0, 0.4, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(this->menuList.c_str(), glm::vec4(this->colorStatus, 1.0), text_size-5, -1.0, 1.75 - (std::count(this->menuList.begin(), this->menuList.end(), '\n'))/5.0, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(this->menuAuthor.c_str(), glm::vec4(0.2, 0.2, 0.2, 1.0), text_size-15, -1.0, -0.75, sx, sy, this->WINDOW_HEIGHT);
        if (not this->fillPolygon) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#else
    static bool show_once = false;
    if (not show_once) {
        std::cout<<this->menuTitle<<this->menuInstructions<<this->menuList<<this->menuAuthor<<"\n\n\n";
        show_once = true;
    }
#endif
    }
}

void Home::CreateScene() {
    this->menuTitle = "TESELACION ADAPTATIVA EN GPU\nEjemplos de uso\n";
    this->menuInstructions = "  Seleccione con el teclado\n  el ejemplo que desea ejecutar";
    this->menuList = "";
    this->menuList += "    F1 - Demostraciones de primitivas teseladas\n";
    this->menuList += "    F2 - Superficie por Distancia\n";
    this->menuList += "    F3 - Terreno por Distancia\n";
    this->menuList += "    F4 - Campo Vectorial por Distancia\n";
    this->menuList += "    F5 - Curva por Curvatura\n";
    this->menuList += "    F6 - Superficie por Curvatura\n";
    this->menuList += "    F7 - Terreno por Longitud de Arista\n";
    //this->menuList += "    F8 - Modelo por Silueta\n";
    this->menuList += "    F8 - Modelo por Silueta (con Phong Tessellation)\n";
    //this->menuAuthor = "Alumno: Fernando Nellmeldin\nDirector: Dr. Nestor Calvo\nUNL-FICH\n2013-2014";
    this->menuAuthor = "Fernando Nellmeldin\nUNL-FICH\n2013-2014";

    
    this->vaoVirtualCamera = new VAO(2);  
    this->vaoVirtualCamera->AddBuffer(GL_ARRAY_BUFFER, glm::value_ptr(Example::virtualCamPos), sizeof(double)*3, 3, GL_STREAM_DRAW); //Este se modifica
    const unsigned int virtualCameraIndices[][1] = { {0} };
    this->vaoVirtualCamera->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &virtualCameraIndices[0][0], sizeof(virtualCameraIndices));
    shadersVirtualCamera.CreateProgram("shaders/virtualcamera.vert", "", "", "", "shaders/virtualcamera.frag");
}

void Home::DestroyScene() {
    delete this->vaoVirtualCamera;
    this->shadersVirtualCamera.DeleteProgram();
    delete Example::textRenderer;
}

void Home::SetScene() {
    glClearColor(0.6,0.6,0.6,1.0);
    this->currentExample = 0;
    Example::zFar = 40.0;
    this->camStep = 0.25f;
    this->kDisplacement = 1.0; //Velocidad de movimiento 
    Example::camPos = glm::vec3(0, 4, -6);
    Example::camCenter  = glm::vec3(0, 0, 0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    Example::ModelMatrix = glm::mat4(1.0);
    this->RecalcMatrices();
    //Parametros para los poligonos de este modelo en particular
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
  //glFrontFace(GL_CW);
  //
    Example::renderText = true;
    this->VERTICES_PER_PATCH = 1;
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (this->modelToRead.size() == 0) //si no estaba seteando desde antes
        this->modelToRead = "alien.obj";
#if defined(RENDERTEXT0) || defined(RENDERTEXT1) 
    Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
#endif
}

void Home::cb_KeyboardExtended(unsigned char key, int x, int y) {
    if (this->currentExample == 0) { //si no hay ninguno cargado, corremos el keyboard de este
        switch(key) {
            case 27: //escape
                glutLeaveMainLoop();
                break;
            default:
            //Example::lastMessage += "    Y: Aumenta la distancia maxima para teselacion.\n    U: Disminuye la distancia maxima para teselacion.\n    I: Activa o desactiva la iluminacion.\n    H: Imprime este texto.\n";
                break;
        }
    } else { //si hay un ejemplo cargado, llamamos el keyboard de el
        this->loadedExample->cb_KeyboardExtended(key, x, y);
    }
}

void Home::PrepareExample() {
    if (this->currentExample == 0) return;
    switch (this->currentExample) {
    case 1:
        this->loadedExample = new TessDemo("Demostracion Basica de Teselacion", 800, 600, 3, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
    case 2:
        this->loadedExample = new SurfaceDistance("Teselacion de superficie de Bezier por distancia", 800, 600, 16, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
    case 3:
        this->loadedExample = new TerrainDistance("Teselacion de terreno por distancia a la camara", 800, 600, 4, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
    case 4:
        this->loadedExample = new FieldDistance("Campo vectorial por distancia", 800, 600, 1, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
    case 5:
        this->loadedExample = new CurveCurvature("Curva por curvatura", 800, 600, 4, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
    case 6:
        this->loadedExample = new SurfaceCurvature("Teselacion de superficie de Bezier por curvatura", 800, 600, 16, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
    case 7:
        this->loadedExample = new TerrainEdge("Teselacion de terreno por longitud de arista", 800, 600, 4, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
  //case 8:
  //    this->loadedExample = new ModelSilhouette("Teselacion de modelo por silueta", 800, 600, 3, true, this, this->modelToRead);
  //    this->loadedExample->SetScene();
  //    this->loadedExample->CreateScene();
  //    break;
    case 8:
        this->loadedExample = new ModelPhong("Phong Tessellation", 800, 600, 3, true, this, this->modelToRead);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
        break;
    case 9:
        this->loadedExample = new ZFight("Z Fighting Demo", 800, 600, 3, this);
        this->loadedExample->SetScene();
        this->loadedExample->CreateScene();
    default:
        break;
    }
}

void Home::cb_SpecialExtended(int key, int x, int y) {
    if (this->currentExample != 0)
        this->loadedExample->cb_SpecialExtended(key, x, y);
    else {
        switch(key) {
            case GLUT_KEY_F1:
                //dibujar superficie por distancia
                this->currentExample = 1;
                this->PrepareExample();
                break;
            case GLUT_KEY_F2:
                //dibujar superficie por curvatura
                this->currentExample = 2;
                this->PrepareExample();
                break;
            case GLUT_KEY_F3:
                //dibujar terreno distancia
                this->currentExample = 3;
                this->PrepareExample();
                break;
            case GLUT_KEY_F4:
                //dibujar terreno arista
                this->currentExample = 4;
                this->PrepareExample();
                break;
            case GLUT_KEY_F5:
                //dibujar teselacion por silueta
                this->currentExample = 5;
                this->PrepareExample();
                break;
            case GLUT_KEY_F6:
                //dibujar phong tessellation
                this->currentExample = 6;
                this->PrepareExample();
                break;
            case GLUT_KEY_F7:
                //dibujar curva por curvatura
                this->currentExample = 7;
                this->PrepareExample();
                break;
            case GLUT_KEY_F8:
                //dibujar campo por distancia 
                this->currentExample = 8;
                this->PrepareExample();
                break;
            case GLUT_KEY_F9:
                //dibujar Z-Fighting demo 
                this->currentExample = 9;
                this->PrepareExample();
                break;
        }
    }
}

void Home::cb_MouseExtended(int x, int y) {
    if (this->currentExample != 0)
        this->loadedExample->cb_MouseExtended(x, y);
}

void Home::Reset() {
    delete this->loadedExample;
    //Cheat que reinicia el text renderer
    delete Example::textRenderer;
    Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
    //this->CalcStatistics(3);
    //Example::historyFps.clear(); Example::historyFps.reserve(120);
    
    this->SetScene();
}

void Home::SetExample(unsigned int ExampleNum) {
    this->currentExample = ExampleNum;
    this->PrepareExample();
}

void Home::SetModel(std::string model) {
    this->modelToRead = model;
}
