#include "Example.h"
#include "utils.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include <algorithm>
Example::Example(std::string name, int w, int h, int vpp, int ctx_major, int ctx_minor) {
    this->InitVariables(name, w, h, vpp, ctx_major, ctx_minor);
}

void Example::InitVariables(std::string name, int w, int h, int vpp, int ctx_major, int ctx_minor) {
    this->WINDOW_NAME = name;
    this->WINDOW_WIDTH = w;
    this->WINDOW_HEIGHT = h;
    this->VERTICES_PER_PATCH = vpp; 
    this->CONTEXT_MAJOR = ctx_major;
    this->CONTEXT_MINOR = ctx_minor;
    this->viewPortSize = glm::vec2(WINDOW_WIDTH,WINDOW_HEIGHT);
    Example::camPos = glm::vec3(1.0, 3.0, 1.0);
    Example::camCenter  = glm::vec3(0.0, 3.0, 0.0);
    Example::camUp      = glm::vec3(0.0, 1.0, 0.0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    Example::virtualCamPos = Example::camPos;
    Example::zNear = 0.01f;
    Example::zFar = 100.0f;
    Example::fov = 60.0f;
    this->xPrev = w/2.0;
    this->yPrev = h/2.0;
    this->kDisplacement = 0.1; 
    this->camStep = 1.0; 
    Example::frames = 0;
    Example::fps = 0;
    Example::fillPolygon = true;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Example::deltaToMeasureFPS = 1.0;
    this->lastTranslation = glm::vec3(0.0, 0.0, 0.0);
    this->lastRotation = glm::vec3(0.0, 0.0, 0.0);
    this->lastScalation = glm::vec3(1.0, 1.0, 1.0);
    this->hasMouseExtended = false;
    this->debugMode = false;
    Example::lastMessage = "";
    Example::currentMessageTime = 0.0;
    this->messageTime = 1000.0;
    this->colorFps = glm::vec3(0.0, 0.0, 0.0);
    this->colorStatus = glm::vec3(0.0, 0.0, 0.0);
    this->colorHelp = glm::vec3(0.0, 0.0, 0.0);
    Example::renderText = true;
    Example::clockLast = utils::GetUnixTime();
    this->secondsSinceBeginning = 0;
    this->maxTess = 1.0f;
    this->deltaMaxTess = 1.0f;
    this->timeToChangeMaxTess = 10;
    Example::historyFps.clear();
    Example::historyFps.reserve(120);

}

void Example::cb_Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->DrawScene();

    //Calculo de los fps
    ++Example::frames;
    double clockNow = utils::GetUnixTime();
    double dt_fps = clockNow - Example::clockLast;
   
    Example::currentMessageTime += dt_fps;
    if (Example::currentMessageTime > this->messageTime) {
        Example::lastMessage = "";
        Example::currentMessageTime = 0.0;
    }
    if (dt_fps > Example::deltaToMeasureFPS) {
        static const float weightFrames = 0.9;
        Example::fps = Example::fps*(1.0-weightFrames) + Example::frames*weightFrames;
        std::cout<<Example::fps<<" fps"; std::cout.flush(); std::cout<<"\r";
        Example::historyFps.push_back(Example::fps);
      //if (Example::fileToLog.is_open() ) {
      //    Example::fileToLog<<utils::GetCurrentDateTime()<<"\t\t\t"<<Example::fps<<"\n";
      //}
        Example::frames = 0;
        Example::clockLast = clockNow;
        Example::frameTime = (Example::deltaToMeasureFPS*1000)/Example::fps;
      //if (this->secondsSinceBeginning > this->timeToChangeMaxTess) {
      //    this->maxTess = std::min(64.0f, this->maxTess+this->deltaMaxTess);
      //    std::cerr<<"MaxTess = "<<this->maxTess<<"\n";
      //    this->secondsSinceBeginning = 0;
      //    this->CalcStatistics(2);
      //} else  this->secondsSinceBeginning++;
    }    
    
    //Llama a redibujado
    glutSwapBuffers(); glutPostRedisplay();
}
 
void Example::cb_Reshape(int new_w, int new_h) {
    //Setea el nuevo Viewport
    this->WINDOW_WIDTH = new_w;
    this->WINDOW_HEIGHT = new_h;
    glViewport(0, 0, (GLsizei) new_w, (GLsizei) new_h);
   
    float w2 = this->WINDOW_WIDTH / 2.0f;
    float h2 = this->WINDOW_HEIGHT / 2.0f;
    Example::ViewportMatrix =  glm::mat4(glm::vec4(w2,0.0f,0.0f,0.0f),
                                glm::vec4(0.0f,h2,0.0f,0.0f),
                                glm::vec4(0.0f,0.0f,1.0f,0.0f),
                                glm::vec4(w2+0, h2+0, 0.0f, 1.0f));
   
    //Actualizacion de matrices
    this->viewPortSize = glm::vec2(new_w, new_h);
    Example::ProjectionMatrix = glm::perspective(Example::fov, float(this->WINDOW_WIDTH)/float(this->WINDOW_HEIGHT), Example::zNear, Example::zFar); 
    Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;
}

void Example::cb_Idle() { glutPostRedisplay(); }


void Example::cb_Mouse(int x, int y) {
    if (this->hasMouseExtended) {
        this->cb_MouseExtended(x, y);
    } else {
        y = this->WINDOW_HEIGHT - y;
        int dx = x - this->xPrev;
        int dy = y - this->yPrev;
        if (dx == 0 and dy == 0) return; //No hay cambios
        Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
        glm::vec3 delta (dx, dy, 0.0);
        delta *= 1.0/50.0;
        Example::camCenter = Example::camCenter + glm::vec3(delta[0], delta[1], delta[2]);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 

        this->xPrev = x;  this->yPrev = y;
    }
}

void Example::cb_Keyboard(unsigned char key, int x, int y) {
    glm::vec3 crs, upp, virtualCET;
    int mod;
    float modi, dist;
    switch (key) {
  //case 27: //escape
  //    glutLeaveMainLoop();
  //    return;
    case 8: //backspace
        Example::lastMessage = ""; break;
    case 'l': 
        Example::fillPolygon = not Example::fillPolygon;
        if (Example::fillPolygon) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
            Example::lastMessage = "Poligono relleno.\n";
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
            Example::lastMessage = "Poligono con lineas.\n";
        }
        break;
    case 'r':
    case 'R':
        Example::virtualCamPos = Example::camPos;
        Example::virtualCamCenter = Example::camCenter;
        Example::lastMessage = "Se retorna la posicion virtual de la camara a la real = (" + utils::XToStr(Example::virtualCamPos[0]) + ", " + utils::XToStr(Example::virtualCamPos[1]) + ", "+ utils::XToStr(Example::virtualCamPos[2]) + ")\n.";
        break;
    //Controla la posicion de la camara
    case 'w':
        mod = glutGetModifiers();
        modi = this->camStep;
        if (mod & GLUT_ACTIVE_ALT and Example::useVirtualCamera) {
            Example::virtualCamPos    = Example::virtualCamPos    + Example::camUp*this->kDisplacement*modi; 
            Example::virtualCamCenter = Example::virtualCamCenter + Example::camUp*this->kDisplacement*modi;
            Example::lastMessage = "Posicion virtual de la camara = (" + utils::XToStr(Example::virtualCamPos[0]) + ", " + utils::XToStr(Example::virtualCamPos[1]) + ", "+ utils::XToStr(Example::virtualCamPos[2]) + ")\n.";
        } else {
            Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
            Example::camPos = Example::camPos + Example::camUp*this->kDisplacement*modi;
            Example::camCenter = Example::camCenter + Example::camUp*this->kDisplacement*modi;
            Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
            Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
            Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;
        }
        break;
    case 'W':
        mod = glutGetModifiers();
        modi = this->camStep;
        if (mod & GLUT_ACTIVE_ALT and Example::useVirtualCamera) {
            virtualCET = glm::normalize(Example::virtualCamCenter - Example::virtualCamPos);
            Example::virtualCamPos =    Example::virtualCamPos    + virtualCET*this->kDisplacement*modi; 
            Example::virtualCamCenter = Example::virtualCamCenter + virtualCET*this->kDisplacement*modi;
            Example::lastMessage = "Posicion virtual de la camara = (" + utils::XToStr(Example::virtualCamPos[0]) + ", " + utils::XToStr(Example::virtualCamPos[1]) + ", "+ utils::XToStr(Example::virtualCamPos[2]) + ")\n.";
        } else {
            Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
            Example::camPos = Example::camPos + Example::camEyeTarget*this->kDisplacement*modi;
            Example::camCenter = Example::camCenter + Example::camEyeTarget*this->kDisplacement*modi;
            Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
            Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
            Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;
        }
        break;
    case 's':
        mod = glutGetModifiers();
        modi = this->camStep;
        if (mod & GLUT_ACTIVE_ALT and Example::useVirtualCamera) {
            Example::virtualCamPos    = Example::virtualCamPos    - Example::camUp*this->kDisplacement*modi;
            Example::virtualCamCenter = Example::virtualCamCenter - Example::camUp*this->kDisplacement*modi; 
            Example::lastMessage = "Posicion virtual de la camara = (" + utils::XToStr(Example::virtualCamPos[0]) + ", " + utils::XToStr(Example::virtualCamPos[1]) + ", "+ utils::XToStr(Example::virtualCamPos[2]) + ")\n.";
        } else {
            Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
            Example::camPos = Example::camPos - Example::camUp*this->kDisplacement*modi;
            Example::camCenter = Example::camCenter - Example::camUp*this->kDisplacement*modi;
            Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
            Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
            Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;
        }
        break;
    case 'S':
        mod = glutGetModifiers();
        modi = this->camStep;
        if (mod & GLUT_ACTIVE_ALT and Example::useVirtualCamera) {
            virtualCET = glm::normalize(Example::virtualCamCenter - Example::virtualCamPos);
            Example::virtualCamPos =    Example::virtualCamPos    - virtualCET*this->kDisplacement*modi; 
            Example::virtualCamCenter = Example::virtualCamCenter - virtualCET*this->kDisplacement*modi;
            Example::lastMessage = "Posicion virtual de la camara = (" + utils::XToStr(Example::virtualCamPos[0]) + ", " + utils::XToStr(Example::virtualCamPos[1]) + ", "+ utils::XToStr(Example::virtualCamPos[2]) + ")\n.";
        } else {
            Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
            Example::camPos = Example::camPos - Example::camEyeTarget*this->kDisplacement*modi;
            Example::camCenter = Example::camCenter - Example::camEyeTarget*this->kDisplacement*modi;
            Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
            Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
            Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;
        }
        break;
    case 'a':
    case 'A':
        mod = glutGetModifiers();
        upp =  glm::normalize(Example::camUp);
        modi = this->camStep;
        if (mod & GLUT_ACTIVE_ALT and Example::useVirtualCamera) {
            crs = glm::cross(glm::normalize(Example::virtualCamCenter - Example::virtualCamPos), upp);
            Example::virtualCamPos    = Example::virtualCamPos    - crs*this->kDisplacement*modi;
            Example::virtualCamCenter = Example::virtualCamCenter - crs*this->kDisplacement*modi; 
            Example::lastMessage = "Posicion virtual de la camara = (" + utils::XToStr(Example::virtualCamPos[0]) + ", " + utils::XToStr(Example::virtualCamPos[1]) + ", "+ utils::XToStr(Example::virtualCamPos[2]) + ")\n.";
        } else {
            if (mod == GLUT_ACTIVE_SHIFT) modi *= 3.0;
            Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
            crs = glm::cross(Example::camEyeTarget, upp);
            Example::camCenter = Example::camCenter - crs*this->kDisplacement*modi;
            Example::camPos = Example::camPos - crs*this->kDisplacement*modi;
            Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
            Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
            Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;
        }
        break;
    case 'd':
    case 'D':
        mod = glutGetModifiers();
        upp =  glm::normalize(Example::camUp);
        modi = this->camStep;
        if (mod & GLUT_ACTIVE_ALT) {
            crs = glm::cross(glm::normalize(Example::virtualCamCenter - Example::virtualCamPos), upp);
            Example::virtualCamPos    = Example::virtualCamPos    + crs*this->kDisplacement*modi;
            Example::virtualCamCenter = Example::virtualCamCenter + crs*this->kDisplacement*modi; 
            Example::lastMessage = "Posicion virtual de la camara = (" + utils::XToStr(Example::virtualCamPos[0]) + ", " + utils::XToStr(Example::virtualCamPos[1]) + ", "+ utils::XToStr(Example::virtualCamPos[2]) + ")\n.";
        } else {
            if (mod == GLUT_ACTIVE_SHIFT) modi *= 3.0;
            Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
            crs = glm::cross(Example::camEyeTarget, upp);
            Example::camCenter = Example::camCenter + crs*this->kDisplacement*modi;
            Example::camPos = Example::camPos + crs*this->kDisplacement*modi;
            Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
            Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
            Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        }
        break;
    case 'b':
    case 'B':
        Example::useVirtualCamera = not Example::useVirtualCamera;
        if (Example::useVirtualCamera) {
            Example::lastMessage = "Activado el uso de la posicion virtual de camara.\n";
        } else {
            Example::lastMessage = "Desactivado el uso de la posicion virtual de camara.\n";
        }
        break;
    case 'q':
    case 'Q':
        Example::camEyeTarget = (Example::camCenter - Example::camPos);
        dist = glm::l2Norm(Example::camEyeTarget);
        Example::camEyeTarget = glm::normalize(Example::camEyeTarget);
        upp = glm::normalize(Example::camUp);
        crs = glm::normalize(glm::cross(Example::camEyeTarget, upp));
        Example::camCenter = Example::camCenter - crs*dist;
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case 'e':
    case 'E':
        Example::camEyeTarget = (Example::camCenter - Example::camPos);
        dist = glm::l2Norm(Example::camEyeTarget);
        Example::camEyeTarget = glm::normalize(Example::camEyeTarget);
        upp = glm::normalize(Example::camUp);
        crs = glm::normalize(glm::cross(Example::camEyeTarget, upp));
        Example::camCenter = Example::camCenter + crs*dist;
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '1':
        Example::camCenter = glm::vec3(0.0, 2.75, 0.0);
        Example::camPos = glm::vec3(0.0, 2.75, 2.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '2':
        Example::camCenter = glm::vec3(0.0, 2.75, 0.0);
        Example::camPos = glm::vec3(0.0, 2.75, -2.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '3':
        Example::camCenter = glm::vec3(0.0, 2.75, 0.0);
        Example::camPos = glm::vec3(2.0, 2.75, 0.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '4':
        Example::camCenter = glm::vec3(0.0, 2.75, 0.0);
        Example::camPos = glm::vec3(-2.0, 2.75, 0.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '5':
        Example::camCenter = glm::vec3(0.0, 2.0, 0.0);
        Example::camPos = glm::vec3(0.0, 5.0, 1.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '6':
        Example::camCenter = glm::vec3(0.0, 3.0, 0.0);
        Example::camPos = glm::vec3(0.0, -1.0, -1.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '7':
        Example::camCenter = glm::vec3(0.0, 3.0, 0.0);
        Example::camPos = glm::vec3(1.0, 3.0, 1.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '8':
        Example::camCenter = glm::vec3(0.0, 3.0, 0.0);
        Example::camPos = glm::vec3(1.0, 3.0, -1.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '9':
        Example::camCenter = glm::vec3(0.0, 3.0, 0.0);
        Example::camPos = glm::vec3(-1.0, 3.0, -1.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '0':
        Example::camCenter = glm::vec3(0.0, 3.0, 0.0);
        Example::camPos = glm::vec3(-1.0, 3.0, 1.0);
        Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
        Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
        Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix; 
        break;
    case '_':
        this->debugMode = not this->debugMode;
        if (this->debugMode) Example::lastMessage = "Modo debug activado.\n"; 
        else Example::lastMessage = "Modo debug desactivado.\n"; 
        break;
    case 'g':
    case 'G':
        Example::renderText = not Example::renderText;
        if (Example::renderText) Example::lastMessage = "Dibujado de texto activado.\n";
        else Example::lastMessage = "Dibujado de texto desactivado.\n";
        break;
    case 'h':
    case 'H':
        if (this->debugMode) {
            std::cout<<"Texto de ayuda:\n";
            std::cout<<"\tW: Mueve la camara hacia adelante.\n";
            std::cout<<"\tS: Mueve la camara hacia atras.\n";
            std::cout<<"\tw: Mueve la camara hacia arriba.\n";
            std::cout<<"\ts: Mueve la camara hacia abajo.\n";
            std::cout<<"\tA: Mueve la camara hacia la izquierda.\n";
            std::cout<<"\tD: Mueva la camara hacia la derecha.\n";
            std::cout<<"\tE: Rota la camara 45 grados hacia la derecha.\n";
            std::cout<<"\tQ: Rota la camara 45 grados hacia la Izquierda.\n";
            std::cout<<"\t0-9: Cambia la posicion de la vista a alineada con los ejes.\n";
            //std::cout<<"\tT: Activa o desactiva teselacion por hardware.\n";
            std::cout<<"\tL: Intercambia entre poligono rellenos o no.\n";
        }
        const char *added_text = "Texto de ayuda: \n"
                              "    W: Mueve la camara hacia adelante.\n"
                              "    S: Mueve la camara hacia atras.\n"
                              "    w: Mueve la camara hacia arriba.\n"
                              "    s: Mueve la camara hacia abajo.\n"
                              "    A: Mueve la camara hacia la izquierda.\n"
                              "    D: Mueva la camara hacia la derecha.\n"
                              "    R: Mueve la posicion de la camara virtual a la real.\n"
                              "    B: Intercambia entre usar o no posicion de camara virtual (se mueve mantienendo ALT y WSwasd).\n"
                              "    E: Rota la camara 45 grados hacia la derecha.\n"
                              "    Q: Rota la camara 45 grados hacia la izquierda.\n"
                              "    0-9: Cambia la posicion de la vista a alineada con los ejes.\n"
                              //"    T: Activa o desactiva teselacion por hardware.\n"
                              "    L: Intercambia entre poligono rellenos o no.\n"
                              "    G: Intercambia entre dibujar texto o no.\n";
        Example::lastMessage.assign(added_text); 
        break;
    }
    cb_KeyboardExtended(key, x, y);
    if (key == 'h' or key == 'H') { 
        Example::lastMessage += "    _: Activa o desactiva el modo debug (desactivado por defecto).\n    backspace: Esconder este texto.\n";
    }
    if (Example::lastMessage.length() > 100.0) this->currentMessageTime = 800.0;
    else if (Example::lastMessage.length() > 0.0) this->currentMessageTime = 0.0;
    if (this->debugMode) std::cout<<Example::lastMessage;
}


void Example::cb_Special(int key, int x, int y) {
    cb_SpecialExtended(key, x, y);
    //do nothing
}

void Example::Initialize() {
    //Init Context
    glutInitContextVersion(this->CONTEXT_MAJOR, this->CONTEXT_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    //Init Window
    //Al cerrar la ventana, no cierra el programa si no que sigue ejecutando el main
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    
    //Modo de la ventana
	unsigned int displayMode = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
	glutInitDisplayMode(displayMode);
	
    //Creacion de una ventana
	glutInitWindowSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
	glutInitWindowPosition (0, 500);
    //this->g_window = glutCreateWindow (this->WINDOW_NAME.c_str());
    glutCreateWindow (this->WINDOW_NAME.c_str());

    SetupCallbacks(); //setea el callback para la instancia actual

    //Inicializacion de Glew y verificacion de que sea correcto
    glewExperimental = GL_TRUE; 
    GLenum glew_result = glewInit();
    if (GLEW_OK != glew_result) {
        std::cerr<<"Error: "<<glewGetErrorString(glew_result)<<std::endl;   exit(EXIT_FAILURE);
    }
    //Limpia el buffer de error
    glGetError();

    //Init Draw Parameters
    //Parametros de OpenGL iniciales
	glClearColor (0.6f, 0.6f, 0.6f, 1.0f);
	glClearDepth (1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    if (Example::fillPolygon) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Incializa la matriz de proyeccion
    Example::ProjectionMatrix = glm::perspective(Example::fov, float(this->WINDOW_WIDTH)/float(this->WINDOW_HEIGHT), Example::zNear, Example::zFar); 
    //Inicializa la matriz de vista
    Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 

    Example::ViewportMatrix = glm::mat4(1.0);
    float w2 = this->WINDOW_WIDTH / 2.0f;
    float h2 = this->WINDOW_HEIGHT / 2.0f;
    ViewportMatrix[0][0] = w2;
    ViewportMatrix[1][1] = h2;
    ViewportMatrix[3][0] = w2;
    ViewportMatrix[3][1] = h2;
 
    //Inicializa la matriz de modelo
    Example::ModelMatrix = glm::mat4(1.0);
    
    //Inicializa la matriz de modelo-vista
    Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
    Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;

    //Construye la matriz normal
    this->NormalMatrix = glm::transpose(glm::inverse(glm::mat3(glm::vec3(Example::ModelViewMatrix[0]), glm::vec3(Example::ModelViewMatrix[1]), glm::vec3(Example::ModelViewMatrix[2]))));

    //Configuramos la cantidad de vertices por patch
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);

    clockRot = Example::clockLast;

    this->CreateScene();
}

void Example::Translate(glm::vec3 direction) {
    Example::ModelMatrix = glm::translate(Example::ModelMatrix, direction);
    Example::ViewMatrix = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
    Example::ModelViewMatrix = Example::ViewMatrix * Example::ModelMatrix;
    Example::MVPMatrix = Example::ProjectionMatrix * Example::ModelViewMatrix;
    this->lastTranslation = direction;
}

void Example::RevertTranslation() {
    this->Translate(-this->lastTranslation);
}

void Example::RecalcMatrices() {
    //Se asume que la matriz del modelo se setea antes
    Example::ViewMatrix  = glm::lookAt(Example::camPos, Example::camCenter, Example::camUp); 
    Example::ModelViewMatrix  = Example::ViewMatrix * Example::ModelMatrix;
    Example::ProjectionMatrix = glm::perspective(Example::fov, float(this->WINDOW_WIDTH)/float(this->WINDOW_HEIGHT), Example::zNear, Example::zFar); 
    Example::MVPMatrix        = Example::ProjectionMatrix * Example::ModelViewMatrix;
    Example::NormalMatrix = glm::transpose(glm::inverse(glm::mat3(glm::vec3(Example::ModelViewMatrix[0]), glm::vec3(Example::ModelViewMatrix[1]), glm::vec3(Example::ModelViewMatrix[2]))));
    float w2 = this->WINDOW_WIDTH / 2.0f;
    float h2 = this->WINDOW_HEIGHT / 2.0f;
    Example::ViewportMatrix =  glm::mat4(glm::vec4(w2,0.0f,0.0f,0.0f),
                                glm::vec4(0.0f,h2,0.0f,0.0f),
                                glm::vec4(0.0f,0.0f,1.0f,0.0f),
                                glm::vec4(w2+0, h2+0, 0.0f, 1.0f));
   
}

void Example::CalcStatistics(unsigned int values_to_ignore) {
    if (Example::historyFps.size() == 0) return;
    Example::historyFps.erase(Example::historyFps.begin(), Example::historyFps.begin()+values_to_ignore);
    unsigned int sum = 0;
    for (unsigned int i = 0; i < Example::historyFps.size(); ++i) {
        sum += Example::historyFps[i];
    }
    unsigned int value_mean = (unsigned int) (float(sum)/float(Example::historyFps.size()));
    unsigned int value_max = *std::max_element(Example::historyFps.begin(), Example::historyFps.end());
    unsigned int value_min = *std::min_element(Example::historyFps.begin(), Example::historyFps.end());
    if (Example::fileToLog.is_open()) {
        //Example::fileToLog<<utils::GetCurrentDateTime()<<"\t\t\tmaxTess\t"<<this->maxTess<<"\tmean\t"<<value_mean<<"\tmax\t"<<value_max<<"\tmin\t"<<value_min<<"\n";
        Example::fileToLog<<"\tmean\t"<<value_mean<<"\tmax\t"<<value_max<<"\tmin\t"<<value_min<<"\n";
    }
}
