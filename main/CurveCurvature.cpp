#include "CurveCurvature.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"
#include "curve_curvature/curveData.h"
#include "AxisData.h"

CurveCurvature::CurveCurvature(std::string name, int w, int h, int vpp, Home* home_ptr) {
    Example::InitVariables(name, w, h, vpp);
    this->home = home_ptr;
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";
}

void CurveCurvature::DrawScene() {
    this->Translate(glm::vec3(1, 1, 0));

    this->shadersModel.Bind();  
    this->shadersModel.SetUniform("MVPMatrix",       Example::MVPMatrix);
    this->shadersModel.SetUniform("Tessellate",      this->tessellate);
    this->shadersModel.SetUniform("NumLines",        int(std::floor(this->numLines)));
    this->shadersModel.SetUniform("TessDefault",     this->tessDefault);
    this->shadersModel.SetUniform("MaxTess",         this->maxTess);
    this->shadersModel.SetUniform("CurvFactor",         this->curvFactor);
    
    this->vaoModel->UpdateBuffer(GL_ARRAY_BUFFER, &CC::CurveVertices[0][0], sizeof(CC::CurveVertices));
    //Dibujado de la curva
    this->vaoModel->Render(GL_PATCHES, sizeof(CC::CurveIndices)/sizeof(unsigned int));
    this->shadersModel.Unbind();

    this->shadersAxis.Bind(); 
    this->shadersAxis.SetUniform("MVPMatrix", Example::MVPMatrix);
    //Actualizacion del poligono de control de la curva
    this->vaoPoly->UpdateBuffer(GL_ARRAY_BUFFER, &CC::CurveVertices[0][0], sizeof(CC::CurveVertices));
    //Dibujado del poligono de control
    this->vaoPoly->Render(GL_LINES, sizeof(CC::PolyIndices)/sizeof(unsigned int));

    glPointSize(5.0);
    //Actualizado de los puntos de control de la curva
    this->vaoPoint->UpdateBuffer(GL_ARRAY_BUFFER, &CC::CurveVertices[0][0], sizeof(CC::CurveVertices));
    //Dibujado de los puntos de control de la curva
    this->vaoPoint->Render(GL_POINTS, sizeof(CC::PointIndices)/sizeof(unsigned int));
    this->shadersAxis.Unbind();

    this->RevertTranslation();

    //Ahora se dibujan los ejes
    this->shadersAxis.Bind(); 
    this->shadersAxis.SetUniform("MVPMatrix", Example::MVPMatrix);

    //Dibujado de los ejes
    this->vaoAxis->Render(GL_LINES, sizeof(AxisIndices)/sizeof(unsigned int));
    this->shadersAxis.Unbind();
}

void CurveCurvature::CreateScene() {
    this->vaoModel = new VAO(2);
    this->vaoModel->AddBuffer(GL_ARRAY_BUFFER, &CC::CurveVertices[0][0], sizeof(CC::CurveVertices), 3, GL_STREAM_DRAW);
    this->vaoModel->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(CC::CurveIndices[0][0]), sizeof(CC::CurveIndices));
  
    this->vaoPoly = new VAO(2);
    this->vaoPoly->AddBuffer(GL_ARRAY_BUFFER, &CC::CurveVertices[0][0], sizeof(CC::CurveVertices), 3, GL_STREAM_DRAW);
    this->vaoPoly->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(CC::PolyIndices[0][0]), sizeof(CC::PolyIndices));

    this->vaoPoint = new VAO(2);
    this->vaoPoint->AddBuffer(GL_ARRAY_BUFFER, &CC::CurveVertices[0][0], sizeof(CC::CurveVertices), 3, GL_STREAM_DRAW);
    this->vaoPoint->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(CC::PointIndices[0][0]), sizeof(CC::PointIndices));

    this->vaoAxis = new VAO(3);  
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisVertices[0][0], sizeof(AxisVertices), 3, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisColors[0][0], sizeof(AxisColors), 4, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &AxisIndices[0][0], sizeof(AxisIndices));

    if (this->shadersModel.CreateProgram("shaders/curve_curvature/vertex.vert", "shaders/curve_curvature/tess_control.tcs", "shaders/curve_curvature/tess_evaluation.tes", "", "shaders/curve_curvature/fragment.frag")) {
        if (not this->shadersAxis.CreateProgram("shaders/ejes.vert", "", "", "", "shaders/ejes.frag")) std::cout<<"Ocurrio un error al crear los shaders de los ejes.\n";
    } else std::cout<<"Ocurrio un error al crear los shaders del modelo.\n";
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void CurveCurvature::DestroyScene() {
    delete this->vaoModel;
    delete this->vaoAxis;
    delete this->vaoPoly;
    delete this->vaoPoint;
    this->shadersAxis.DeleteProgram();
    this->shadersModel.DeleteProgram();
    this->home->Reset();
}

void CurveCurvature::SetScene() {
    Example::zNear = 0.1f;
    Example::zFar = 20.0;
    Example::camStep = 0.1f;
    this->kDisplacement = 1.0; //Velocidad de movimiento 
    Example::camPos = glm::vec3(1.5, 1.5, 2);
    Example::camCenter  = glm::vec3(1.5, 1.5, 0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    this->RecalcMatrices();

    this->tessellate = true;
    this->maxTess = 32.0;
    this->tessDefault = 32.0;
    this->hasMouseExtended = false;
    this->selectedPoint = 0;
    this->numLines = 2.0;
    this->curvFactor = 10.0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
}

void CurveCurvature::cb_KeyboardExtended(unsigned char key, int x, int y) {
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
    case 'y': 
    case 'Y':
        this->maxTess = std::min(this->maxTess+1.0, 64.0);
        Example::lastMessage = "Nivel de teselacion maxima = " + utils::XToStr(this->maxTess) + ".\n";
        break;
    case 'u': 
    case 'U':
        this->maxTess = std::max(this->maxTess-1.0, 1.0);
        Example::lastMessage = "Nivel de teselacion maxima = " + utils::XToStr(this->maxTess) + ".\n";
        break;
    case 'z':
    case 'Z':
        this->numLines = std::max(1.0f, this->numLines-1);
        Example::lastMessage = "Cantidad de lineas a dibujar = " + utils::XToStr(this->numLines) + ".\n";
        break;
    case 'x':
    case 'X':
        this->numLines = std::min(this->maxTess, this->numLines+1);
        Example::lastMessage = "Cantidad de lineas a dibujar = " + utils::XToStr(this->numLines) + ".\n";
        break;
    case 'h':
    case 'H':
        if (this->debugMode) { 
            std::cout<<"\tT: Activa o desactiva teselacion por hardware.\n";
            std::cout<<"\tL: Intercambia entre poligono rellenos o no.\n";
            std::cout<<"\tY: Disminuye el nivel maximo de teselacion.\n";
            std::cout<<"\tU: Aumenta el nivel maximo de teselacion.\n";
            std::cout<<"\tZ: Disminuye la cantidad de lineas a dibujar.\n";
            std::cout<<"\tX: Aumenta la cantidad de lineas a dibujar.\n";
            std::cout<<"\tF1-F4: Selecciona el punto 1-4.\n";
            std::cout<<"\tFlechas y Av/Re Pag: Mueve el punto seleccionado.\n";
            std::cout<<"\tH: Imprime este texto.\n";
        }
        const char* added_text = 
        "    T: Activa o desactiva teselacion por hardware.\n"
        "    L: Intercambia entre poligono rellenos o no.\n"
        "    Y: Disminuye el nivel maximo de teselacion.\n"
        "    U: Aumenta el nivel maximo de teselacion.\n"
        "    Z: Disminuye la cantidad de lineas a dibujar.\n"
        "    X: Aumenta la cantidad de lineas a dibujar.\n"
        "    F1-F4: Selecciona el punto 1-4.\n"
        "    Flechas y Av/Re Pag: Mueve el punto seleccionado.\n"
        "    Escape: Vuelve al menu principal.\n"
        "    H: Imprime este texto.\n";
        Example::lastMessage += std::string(added_text);
        break;
    }
}

void CurveCurvature::cb_SpecialExtended(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1: 
        Example::lastMessage = "Punto seleccionado = 1.\n";
        this->selectedPoint = 0;
        break;
    case GLUT_KEY_F2: 
        Example::lastMessage = "Punto seleccionado = 2.\n";
        this->selectedPoint = 1;
        break;
    
    case GLUT_KEY_F3: 
        Example::lastMessage = "Punto seleccionado = 3.\n";
        this->selectedPoint = 2;
        break;
    
    case GLUT_KEY_F4: 
        Example::lastMessage = "Punto seleccionado = 4.\n";
        this->selectedPoint = 3;
        break;
    case GLUT_KEY_UP:
        CC::CurveVertices[this->selectedPoint][1] += 0.2f;
        break;
    case GLUT_KEY_DOWN:
        CC::CurveVertices[this->selectedPoint][1] -= 0.2f;
        break;
    case GLUT_KEY_LEFT:
        CC::CurveVertices[this->selectedPoint][0] -= 0.2f;
        break;
    case GLUT_KEY_RIGHT:
        CC::CurveVertices[this->selectedPoint][0] += 0.2f;
        break;
    case GLUT_KEY_PAGE_DOWN:
        CC::CurveVertices[this->selectedPoint][2] += 0.2f;
        break;
    case GLUT_KEY_PAGE_UP:
        CC::CurveVertices[this->selectedPoint][2] -= 0.2f;
        break;
    }
}

void CurveCurvature::cb_MouseExtended(int x, int y) {
}
