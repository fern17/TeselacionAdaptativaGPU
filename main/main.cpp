//Graficos
#include <GL/glew.h>    //glew para facilitar la carga de extensiones y crear aplicaciones portables
#include <GL/freeglut.h>    //GLUT

//DeViL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

//Source
#include "utils.h"
#include "Home.h"
#include "Example.h"

//Algunos define que prenden o apagan ciertas funcionalidades
//#define ERRORCHECK //si esta activo, se hacen las llamadas a glGetError
#define LOG //si esta activo, se guarda la salida a un archivo

//Inicializacion de variables static
TextRenderer* Example::textRenderer;
glm::vec3 Example::virtualCamPos = glm::vec3(0.0);
glm::vec3 Example::virtualCamCenter = glm::vec3(0.0);
glm::vec3 Example::camPos = glm::vec3(0.0);
glm::vec3 Example::camCenter = glm::vec3(0.0);
glm::vec3 Example::camUp = glm::vec3(0.0);
glm::vec3 Example::camEyeTarget = glm::vec3(0.0);
float Example::zNear = 1.0;
float Example::zFar = 100.0;
float Example::fov = 60;
double       Example::clockLast = 0.0;
unsigned int Example::frames = 0;
unsigned int Example::fps = 0;
double       Example::frameTime = 0.0;
glm::mat4 Example::ModelMatrix = glm::mat4(0.0);
glm::mat4 Example::ViewMatrix = glm::mat4(0.0);
glm::mat4 Example::ModelViewMatrix = glm::mat4(0.0);
glm::mat4 Example::ProjectionMatrix = glm::mat4(0.0);
glm::mat4 Example::MVPMatrix = glm::mat4(0.0);
glm::mat4 Example::ViewportMatrix = glm::mat4(0.0);
glm::mat3 Example::NormalMatrix = glm::mat3(0.0);
std::string Example::lastMessage = ""; 
double       Example::currentMessageTime = 0.0;
bool Example::renderText = true;
bool Example::fillPolygon = true;
double Example::deltaToMeasureFPS = 1.0;
std::ofstream Example::fileToLog;
bool Example::useVirtualCamera = false;
std::vector<unsigned int> Example::historyFps;

unsigned int StrToInt(std::string s) {
    std::stringstream ss;
    ss<<s;
    unsigned int x;
    ss>>x;
    return x;
}

int main(int argc, char** argv) {
    //Inicializacion de GLUT
	glutInit(&argc, argv);
    //  ----- Initialise DevIL -----
    ilutRenderer(ILUT_OPENGL);
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    Home *home;
    home = new Home("Ejemplos de uso de teselacion adaptativa en GPU", 800, 600);
    home->Initialize();
    Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
    home->SetScene();
    if (argc > 2) {
        std::string model_to_read(argv[2]);
        home->SetModel(model_to_read);
    }if (argc > 1) {
        unsigned int exampleToStart = StrToInt(std::string(argv[1])); 
        std::cout<<"Iniciando desde el ejemplo "<<exampleToStart<<"\n";

        home->SetExample(exampleToStart);
    }
    
   
#ifdef LOG
    Example::fileToLog.open("logfile.txt", std::ios::trunc);
    Example::fileToLog<<"Log ejecutado el "<<utils::GetCurrentDateTime()<<"\n";
    Example::fileToLog<<"Tiempo\t\t\t\t\t\tFPS\n";
#endif
    glutMainLoop();
#ifdef LOG
    Example::fileToLog.close();
#endif
    
    delete home;
	return 0;
}

