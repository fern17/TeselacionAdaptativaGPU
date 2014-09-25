#include "ZFight.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"
#include "../data/z_fight/zFightData.h"
#include "AxisData.h"

ZFight::ZFight(std::string name, int w, int h, int vpp, Home* home_ptr) {
    Example::InitVariables(name, w, h, vpp);
    this->home = home_ptr;
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";
}

void ZFight::DrawScene() {

    //Dibujado de los triangulos
    this->shaderTriangles.Bind();
    this->shaderTriangles.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shaderTriangles.SetUniform("TessDefault", this->TessDefault);
    this->shaderTriangles.SetUniform("Tessellate",      this->tessellate);

    this->shaderTriangles.SetUniform("Color", glm::vec4(1.0, 0.0, 0.0, 1.0));
    this->vaoT1->UpdateBuffer(GL_ARRAY_BUFFER, &ZF::Triangle1Vertices[0][0], sizeof(ZF::Triangle1Vertices));
    this->vaoT1->Render(GL_PATCHES, sizeof(ZF::Triangle1Indices)/sizeof(unsigned int));

    this->shaderTriangles.Unbind();
    
    this->shaderTriangles.Bind();
    this->shaderTriangles.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shaderTriangles.SetUniform("TessDefault", this->TessDefault);
    this->shaderTriangles.SetUniform("Tessellate",      this->tessellate);

    this->shaderTriangles.SetUniform("Color", glm::vec4(0.0, 0.0, 1.0, 1.0));
    this->vaoT2->UpdateBuffer(GL_ARRAY_BUFFER, &ZF::Triangle2Vertices[0][0], sizeof(ZF::Triangle2Vertices));
    this->vaoT2->Render(GL_PATCHES, sizeof(ZF::Triangle2Indices)/sizeof(unsigned int));

    this->shaderTriangles.Unbind();
}

void ZFight::CreateScene() {
    //Crear los datos para triangles 
    this->vaoT1 = new VAO(2);
    this->vaoT1->AddBuffer(GL_ARRAY_BUFFER, &ZF::Triangle1Vertices[0][0], sizeof(ZF::Triangle1Vertices), 3, GL_STREAM_DRAW);
    this->vaoT1->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(ZF::Triangle1Indices[0][0]), sizeof(ZF::Triangle1Indices));
    this->vaoT2 = new VAO(2);
    this->vaoT2->AddBuffer(GL_ARRAY_BUFFER, &ZF::Triangle2Vertices[0][0], sizeof(ZF::Triangle2Vertices), 3, GL_STREAM_DRAW);
    this->vaoT2->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(ZF::Triangle2Indices[0][0]), sizeof(ZF::Triangle2Indices));
    
    this->shaderTriangles.CreateProgram("shaders/z_fight/vertex.vert", "shaders/z_fight/tess_control.tcs", "shaders/z_fight/tess_evaluation.tes", "", "shaders/z_fight/fragment.frag");
    
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void ZFight::DestroyScene() {
    delete this->vaoT1;
    delete this->vaoT2;
    this->shaderTriangles.DeleteProgram();
    this->home->Reset();
}

void ZFight::SetScene() {
    Example::zNear = 0.1f;
    Example::zFar = 20.0;
    Example::camStep = 0.1f;
    this->kDisplacement = 1.0; //Velocidad de movimiento 
    Example::camPos = glm::vec3(0.0, 0.5, 2.0);
    Example::camCenter  = glm::vec3(0.5, 0.5, 0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    this->RecalcMatrices();

    this->tessellate = true;
    this->TessDefault = 64.0;
    Example::fillPolygon = true;
    Example::renderText = true;
    this->delta_z = 0.005;

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
	//glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
}

void ZFight::cb_KeyboardExtended(unsigned char key, int x, int y) {
    std::string spacingString = "";
    std::string currentString = "";
    switch(key) {
    case 27: //escape
        this->DestroyScene();
        break;
    case 'z':
        Example::zFar -= 1;
        Example::lastMessage = "zFar = " + utils::XToStr(Example::zFar) + ".\n";
        this->RecalcMatrices();
        break;
    case 'x':
        Example::zFar += 1;
        Example::lastMessage = "zFar = " + utils::XToStr(Example::zFar) + ".\n";
        this->RecalcMatrices();
        break;
    case 'c':
        Example::zNear -= 1;
        Example::lastMessage = "zNear = " + utils::XToStr(Example::zNear) + ".\n";
        this->RecalcMatrices();
        break;
    case 'v':
        Example::zNear += 1;
        Example::lastMessage = "zNear = " + utils::XToStr(Example::zNear) + ".\n";
        this->RecalcMatrices();
        break;
    case '+':
        ZF::Triangle1Vertices[1][2] += this->delta_z;
        Example::lastMessage = "T1 z = " + utils::XToStr(ZF::Triangle1Vertices[1][2]) + ".\n";
        ZF::Triangle2Vertices[0][2] += this->delta_z;
        Example::lastMessage += "T2 z = " + utils::XToStr(ZF::Triangle2Vertices[0][2]) + ".\n";
break;
    case '-':
        ZF::Triangle1Vertices[1][2] -= this->delta_z;
        Example::lastMessage = "T1 z = " + utils::XToStr(ZF::Triangle1Vertices[1][2]) + ".\n";
        ZF::Triangle2Vertices[0][2] -= this->delta_z;
        Example::lastMessage += "T2 z = " + utils::XToStr(ZF::Triangle2Vertices[0][2]) + ".\n";
        break;
    case 'm':
        ZF::Triangle2Vertices[0][2] += this->delta_z;
        ZF::Triangle2Vertices[1][2] += this->delta_z;
        ZF::Triangle2Vertices[2][2] += this->delta_z;
        Example::lastMessage = "T2 z = " + utils::XToStr(ZF::Triangle2Vertices[0][2]) + ".\n";
        break;
    case 'n':
        ZF::Triangle2Vertices[0][2] -= this->delta_z;
        ZF::Triangle2Vertices[1][2] -= this->delta_z;
        ZF::Triangle2Vertices[2][2] -= this->delta_z;
        Example::lastMessage = "T2 z = " + utils::XToStr(ZF::Triangle2Vertices[0][2]) + ".\n";
        break;
    case 'T': 
    case 't':
        this->tessellate = not this->tessellate;
        if (this->tessellate) Example::lastMessage = "Teselacion activada TL = " + utils::XToStr(this->TessDefault) + ".\n"; 
        else Example::lastMessage = "Teselacion desactivada.\n";
        break;
    case 'h':
    case 'H':
        if (this->debugMode) { 
            std::cout<<"\tT: Activa o desactiva teselacion por hardware.\n";
            std::cout<<"\tL: Intercambia entre poligono rellenos o no.\n";
            std::cout<<"\tH: Imprime este texto.\n";
        }
        const char* added_text = 
        "    Escape: Vuelve al menu principal.\n"
        "    H: Imprime este texto.\n";
        Example::lastMessage += std::string(added_text);
        break;
    }
}

void ZFight::cb_SpecialExtended(int key, int x, int y) {
}

void ZFight::cb_MouseExtended(int x, int y) {
}
