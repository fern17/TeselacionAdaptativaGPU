#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_
//Graficos
#include <GL/glew.h>        //glew para facilitar la carga de extensiones y crear aplicaciones portables
#include <GL/freeglut.h>    //GLUT
#include <glm/glm.hpp>      //glm
#include <string>
#include <fstream>
#include "TextRenderer.h"
class Example;
static Example* g_currentInstance; //Puntero a una instancia de la clase. Sirve para poder hacer openGL OOP
class Example {
    private:
    //"truco" para hacer opengl OOP: Los callback no aceptan funciones que dependan de una instancia, asi que se
    //lo "engaña" (en tiempo de compilacion) pasandole una funcion estatica que en realidad llama a una funcion de instancia (en tiempo de ejecucion)
    void SetupCallbacks() {
        g_currentInstance = this;
        glutDisplayFunc (Example::display_cb);
        glutIdleFunc    (Example::idle_cb);
        glutKeyboardFunc(Example::key_cb);
        glutMotionFunc  (Example::motion_cb);
        //glutPassiveMotionFunc(Example::mouse_cb);
        //glutMouseFunc(Example::mouse_cb);
        glutReshapeFunc (Example::reshape_cb);
        glutSpecialFunc (Example::special_cb);
        glutCloseFunc   (Example::close_cb);
    }
    //Callback static que llaman a los callback de instancia una vez creada
    static void display_cb() { g_currentInstance->cb_Display(); }
    static void idle_cb()    { g_currentInstance->cb_Idle(); }
    static void key_cb(unsigned char key, int x, int y)     { g_currentInstance->cb_Keyboard(key, x, y); }
    static void motion_cb(int x, int y)  { g_currentInstance->cb_Mouse(x, y); }
    static void reshape_cb(int x, int y) { g_currentInstance->cb_Reshape(x, y); }
    static void special_cb(int key, int x, int y) { g_currentInstance->cb_Special(key, x, y); }
    static void close_cb()   { g_currentInstance->DestroyScene(); }
    
    public:
    static TextRenderer *textRenderer;
    float maxTess;

    protected:
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    std::string WINDOW_NAME;
    //int g_window; 
    unsigned int VERTICES_PER_PATCH;
    unsigned int CONTEXT_MAJOR;
    unsigned int CONTEXT_MINOR;
    glm::vec2 viewPortSize;

    //Camara
    static glm::vec3 camPos;
    static glm::vec3 camCenter;
    static glm::vec3 camUp;
    static glm::vec3 camEyeTarget;
    static glm::vec3 virtualCamPos;
    static glm::vec3 virtualCamCenter;
    static float zNear;
    static float zFar;
    static float fov;
    static bool fillPolygon;

    glm::vec3 lastTranslation;
    glm::vec3 lastRotation;
    glm::vec3 lastScalation;

    float deltaMaxTess;
    unsigned int secondsSinceBeginning;
    unsigned int timeToChangeMaxTess;

    bool hasMouseExtended;
    //Utilidades para el movimiento
    int xPrev;
    int yPrev;
    float kDisplacement; 
    float camStep; 
    static bool useVirtualCamera;

    //Parametros para contar frames
    static double clockLast;
    double clockNow;
    double clockRot;
    static unsigned int frames;
    static unsigned int fps;
    static double deltaToMeasureFPS;
    static double frameTime;
    static std::vector<unsigned int> historyFps;

    static glm::mat4 ModelMatrix;
    static glm::mat4 ViewMatrix;
    static glm::mat4 ModelViewMatrix;
    static glm::mat4 ProjectionMatrix;
    static glm::mat4 MVPMatrix;
    static glm::mat4 ViewportMatrix;
    static glm::mat3 NormalMatrix;
   
    bool debugMode;
    static bool renderText;

    static std::string lastMessage;
    static double currentMessageTime;
    double messageTime;
    glm::vec3 colorFps;
    glm::vec3 colorHelp;
    glm::vec3 colorStatus;
    public:
    static std::ofstream fileToLog;
    Example() {}
    Example(std::string name, int w, int h, int vpp, int ctx_major = 4, int ctx_minor = 0);
    void InitVariables(std::string name, int w, int h, int vpp, int ctx_major = 4, int ctx_minor = 2);
    void Initialize();
    void cb_Display();
    void cb_Reshape(int x, int y);
    void cb_Mouse(int x, int y);
    void cb_Idle();
    void cb_Keyboard(unsigned char key, int x, int y);
    void cb_Special(int key, int x, int y);
    virtual ~Example() { }

    void Translate(glm::vec3 direction);
    void RevertTranslation();
    void RecalcMatrices();

    void CalcStatistics(unsigned int values_to_ignore = 3);
    
    virtual void SetScene() = 0;
    virtual void DrawScene() = 0;
    virtual void CreateScene() = 0;
    virtual void DestroyScene() = 0;
    virtual void cb_KeyboardExtended(unsigned char key, int x, int y) = 0;
    virtual void cb_SpecialExtended(int key, int x, int y) = 0;
    virtual void cb_MouseExtended(int x, int y) = 0;
};
#endif
