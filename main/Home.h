#ifndef _HOME_H_
#define _HOME_H_
#include "Example.h"
#include "VAO.h"
#include "ShaderProgram.h"

class Home : public Example {
    protected:
    std::string menuTitle;
    std::string menuList;
    std::string menuInstructions;
    std::string menuAuthor;
    Example* loadedExample;
    unsigned int currentExample;
    VAO *vaoVirtualCamera;
    ShaderProgram shadersVirtualCamera;
    std::string modelToRead;
    public:
    Home(std::string name, int w, int h);
    void cb_KeyboardExtended(unsigned char key, int x, int y);
    void cb_SpecialExtended(int key, int x, int y);
    void cb_MouseExtended(int x, int y);
    void SetScene();
    void DrawScene();
    void CreateScene();
    void DestroyScene();
    void Reset();
    void PrepareExample();
    void SetExample(unsigned int exampleNum);
    void SetModel(std::string model);
    ~Home() {};
};

#endif
