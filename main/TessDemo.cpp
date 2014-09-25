#include "TessDemo.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"
#include "tess_demo/tessData.h"
#include "AxisData.h"

TessDemo::TessDemo(std::string name, int w, int h, int vpp, Home* home_ptr) {
    Example::InitVariables(name, w, h, vpp);
    this->home = home_ptr;
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";
}

void TessDemo::DrawScene() {

    if (this->currentDemo == 0) { //0 es triangulos
        switch (this->spacingMode) {
        case 0:
            this->currentShader = &this->shadersTriangleEqual;
            break;
        case 1:
            this->currentShader = &this->shadersTriangleEven;
            break;
        case 2:
            this->currentShader = &this->shadersTriangleOdd;
            break;
        }
        //Dibujado del triangulo
        this->currentShader->Bind();
        this->currentShader->SetUniform("MVPMatrix", Example::MVPMatrix);
        this->currentShader->SetUniform("TessLevels", this->TessLevelsTriangle);
        this->currentShader->SetUniform("TessDefault", this->TessDefault);
        this->currentShader->SetUniform("Tessellate",      this->tessellate);

        this->vaoTriangle->Render(GL_PATCHES, sizeof(TD::TriangleIndices)/sizeof(unsigned int));
        this->currentShader->Unbind();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        float sx = 2.0 / float(this->WINDOW_WIDTH);
        float sy = 2.0 / float(this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("OL0 = "+utils::XToStr(this->TessLevelsTriangle[0])).c_str(), glm::vec4(this->colorFps, 1.0), 25, 0.5, -0.0, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("OL1 = "+utils::XToStr(this->TessLevelsTriangle[1])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.65, -0.0, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("OL2 = "+utils::XToStr(this->TessLevelsTriangle[2])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.1, -0.95, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("IL0 = "+utils::XToStr(this->TessLevelsTriangle[3])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.10, -0.0, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render("v0", glm::vec4(this->colorFps, 1.0), 25, -0.9, -0.85, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render("v1", glm::vec4(this->colorFps, 1.0), 25, 0.85,  -0.85, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render("v2", glm::vec4(this->colorFps, 1.0), 25, -0.03, 0.9, sx, sy, this->WINDOW_HEIGHT);
        if (not Example::fillPolygon) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (this->currentDemo == 1) { //1 es Quads
        switch (this->spacingMode) {
        case 0:
            this->currentShader = &this->shadersQuadEqual;
            break;
        case 1:
            this->currentShader = &this->shadersQuadEven;
            break;
        case 2:
            this->currentShader = &this->shadersQuadOdd;
            break;
        }
        //Dibujado del cuadrilatero
        this->currentShader->Bind();
        this->currentShader->SetUniform("MVPMatrix", Example::MVPMatrix);
        this->currentShader->SetUniform("TessLevelsOuter", this->TessLevelsQuadOuter);
        this->currentShader->SetUniform("TessLevelsInner", this->TessLevelsQuadInner);
        this->currentShader->SetUniform("TessDefault", this->TessDefault);
        this->currentShader->SetUniform("Tessellate",      this->tessellate);

        this->vaoQuad->Render(GL_PATCHES, sizeof(TD::QuadIndices)/sizeof(unsigned int));
        this->currentShader->Unbind();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        float sx = 2.0 / float(this->WINDOW_WIDTH);
        float sy = 2.0 / float(this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("OL0 = "+utils::XToStr(this->TessLevelsQuadOuter[0])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.9, -0.0, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("OL1 = "+utils::XToStr(this->TessLevelsQuadOuter[1])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.10, -0.95, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("OL2 = "+utils::XToStr(this->TessLevelsQuadOuter[2])).c_str(), glm::vec4(this->colorFps, 1.0), 25,  0.7, -0.0, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("OL3 = "+utils::XToStr(this->TessLevelsQuadOuter[3])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.10, 0.9, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("IL0 = "+utils::XToStr(this->TessLevelsQuadInner[0])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.10, -0.3, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render(std::string("IL1 = "+utils::XToStr(this->TessLevelsQuadInner[1])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.3, -0.0, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render("v0", glm::vec4(this->colorFps, 1.0), 25, -0.75, -0.9, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render("v1", glm::vec4(this->colorFps, 1.0), 25, -0.75, 0.85, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render("v2", glm::vec4(this->colorFps, 1.0), 25, 0.7, 0.85, sx, sy, this->WINDOW_HEIGHT);
        Example::textRenderer->Render("v3", glm::vec4(this->colorFps, 1.0), 25, 0.7, -0.9, sx, sy, this->WINDOW_HEIGHT);
        if (not Example::fillPolygon) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (this->currentDemo == 2) { //2 es Isoline
        switch (this->spacingMode) {
            case 0: 
                this->currentShader = &this->shadersLineEqual;
                this->currentShaderPoints = &this->shadersLinePointsEqual;
                break;
            case 1:
                this->currentShader = &this->shadersLineEven;
                this->currentShaderPoints = &this->shadersLinePointsEven;
                break;
            case 2:
                this->currentShader = &this->shadersLineOdd;
                this->currentShaderPoints = &this->shadersLinePointsOdd;
                break;
            }
            //Dibujado de la isolinea
            this->currentShader->Bind();
            this->currentShader->SetUniform("MVPMatrix", Example::MVPMatrix);
            this->currentShader->SetUniform("TessLevelsOuter", this->TessLevelsLine);
            this->currentShader->SetUniform("TessDefault", this->TessDefault);
            this->currentShader->SetUniform("Tessellate",      this->tessellate);
            this->currentShader->SetUniform("LineSpiral", this->lineSpiral);

            this->vaoQuad->Render(GL_PATCHES, sizeof(TD::LineIndices)/sizeof(unsigned int));
            this->currentShader->Unbind();

            if (not this->lineSpiral) { //Dibujado de los puntos que se utilizan para definir las posiciones de las poligonales
                glPointSize(10.0);
                //Dibujado de los puntos fantasma
                this->shadersAxis.Bind(); 
                this->shadersAxis.SetUniform("MVPMatrix", Example::MVPMatrix);
                this->vaoPoint->Render(GL_POINTS, sizeof(TD::points_indices)/sizeof(unsigned int));
                this->shadersAxis.Unbind();
            }

            //Dibujado de los puntos de las isolines
            glPointSize(5.0);
            this->currentShaderPoints->Bind();
            this->currentShaderPoints->SetUniform("MVPMatrix", Example::MVPMatrix);
            this->currentShaderPoints->SetUniform("TessLevelsOuter", this->TessLevelsLine);
            this->currentShaderPoints->SetUniform("TessDefault", this->TessDefault);
            this->currentShaderPoints->SetUniform("Tessellate",      this->tessellate);
            this->currentShaderPoints->SetUniform("LineSpiral", this->lineSpiral);

            this->vaoQuad->Render(GL_PATCHES, sizeof(TD::LineIndices)/sizeof(unsigned int));
            this->currentShaderPoints->Unbind();

            
 
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            float sx = 2.0 / float(this->WINDOW_WIDTH);
            float sy = 2.0 / float(this->WINDOW_HEIGHT);
            Example::textRenderer->Render(std::string("OL0 = "+utils::XToStr(this->TessLevelsLine[0])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.8, -0.0, sx, sy, this->WINDOW_HEIGHT);
            Example::textRenderer->Render(std::string("OL1 = "+utils::XToStr(this->TessLevelsLine[1])).c_str(), glm::vec4(this->colorFps, 1.0), 25, -0.1, -0.8, sx, sy, this->WINDOW_HEIGHT);
            if (not Example::fillPolygon) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }    

    //Ahora se dibujan los ejes
    this->shadersAxis.Bind(); 
    this->shadersAxis.SetUniform("MVPMatrix", Example::MVPMatrix);
    //Dibujado de los ejes
    this->vaoAxis->Render(GL_LINES, sizeof(AxisIndices)/sizeof(unsigned int));
    this->shadersAxis.Unbind();
}

void TessDemo::CreateScene() {
    //Crear los datos para triangle 
    this->vaoTriangle = new VAO(2);
    this->vaoTriangle->AddBuffer(GL_ARRAY_BUFFER, &TD::TriangleVertices[0][0], sizeof(TD::TriangleVertices), 3, GL_STATIC_DRAW);
    this->vaoTriangle->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(TD::TriangleIndices[0][0]), sizeof(TD::TriangleIndices));
    
    //Crear los datos para quads 
    this->vaoQuad = new VAO(2);
    this->vaoQuad->AddBuffer(GL_ARRAY_BUFFER, &TD::QuadVertices[0][0], sizeof(TD::QuadVertices), 3, GL_STATIC_DRAW);
    this->vaoQuad->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(TD::QuadIndices[0][0]), sizeof(TD::QuadIndices));
    
    //Crear los datos para isolines 
    this->vaoLine = new VAO(2);
    this->vaoLine->AddBuffer(GL_ARRAY_BUFFER, &TD::LineVertices[0][0], sizeof(TD::LineVertices), 3, GL_STATIC_DRAW);
    this->vaoLine->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(TD::LineIndices[0][0]), sizeof(TD::LineIndices));
  
    this->vaoAxis = new VAO(3);  
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisVertices[0][0], sizeof(AxisVertices), 3, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ARRAY_BUFFER, &AxisColors[0][0], sizeof(AxisColors), 4, GL_STATIC_DRAW);
    this->vaoAxis->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &AxisIndices[0][0], sizeof(AxisIndices));

    this->vaoPoint = new VAO(2);
    this->vaoPoint->AddBuffer(GL_ARRAY_BUFFER, &TD::points[0][0], sizeof(TD::points), 3, GL_STATIC_DRAW);
    this->vaoPoint->AddBuffer(GL_ELEMENT_ARRAY_BUFFER, &(TD::points_indices[0][0]), sizeof(TD::points_indices));

    //Crear los distintos shaders para triangle
    this->shadersTriangleEqual.CreateProgram("shaders/tess_demo/tri_equal.vert", "shaders/tess_demo/tri_equal.tcs", "shaders/tess_demo/tri_equal.tes", "", "shaders/tess_demo/tri_equal.frag");
    this->shadersTriangleEven.CreateProgram ("shaders/tess_demo/tri_even.vert" , "shaders/tess_demo/tri_even.tcs" , "shaders/tess_demo/tri_even.tes" , "", "shaders/tess_demo/tri_even.frag" );
    this->shadersTriangleOdd.CreateProgram  ("shaders/tess_demo/tri_odd.vert"  , "shaders/tess_demo/tri_odd.tcs"  , "shaders/tess_demo/tri_odd.tes"  , "", "shaders/tess_demo/tri_odd.frag"  );
    //Crear los distintos shaders para quads
    this->shadersQuadEqual.CreateProgram("shaders/tess_demo/quad_equal.vert", "shaders/tess_demo/quad_equal.tcs", "shaders/tess_demo/quad_equal.tes", "", "shaders/tess_demo/quad_equal.frag");
    this->shadersQuadEven.CreateProgram ("shaders/tess_demo/quad_even.vert" , "shaders/tess_demo/quad_even.tcs" , "shaders/tess_demo/quad_even.tes" , "", "shaders/tess_demo/quad_even.frag" );
    this->shadersQuadOdd.CreateProgram  ("shaders/tess_demo/quad_odd.vert"  , "shaders/tess_demo/quad_odd.tcs"  , "shaders/tess_demo/quad_odd.tes"  , "", "shaders/tess_demo/quad_odd.frag"  );
    //Crear los distintos shaders para isolines
    this->shadersLineEqual.CreateProgram("shaders/tess_demo/line_equal.vert", "shaders/tess_demo/line_equal.tcs", "shaders/tess_demo/line_equal.tes", "", "shaders/tess_demo/line_equal.frag");
    this->shadersLineEven.CreateProgram ("shaders/tess_demo/line_even.vert" , "shaders/tess_demo/line_even.tcs" , "shaders/tess_demo/line_even.tes" , "", "shaders/tess_demo/line_even.frag" );
    this->shadersLineOdd.CreateProgram  ("shaders/tess_demo/line_odd.vert"  , "shaders/tess_demo/line_odd.tcs"  , "shaders/tess_demo/line_odd.tes"  , "", "shaders/tess_demo/line_odd.frag"  );
    //Crear los distintos shaders para los puntos de las isolines
    this->shadersLinePointsEqual.CreateProgram("shaders/tess_demo/line_equal.vert", "shaders/tess_demo/line_equal.tcs", "shaders/tess_demo/line_equal_points.tes", "", "shaders/tess_demo/line_equal.frag");
    this->shadersLinePointsEven.CreateProgram ("shaders/tess_demo/line_even.vert" , "shaders/tess_demo/line_even.tcs" , "shaders/tess_demo/line_even_points.tes" , "", "shaders/tess_demo/line_even.frag" );
    this->shadersLinePointsOdd.CreateProgram  ("shaders/tess_demo/line_odd.vert"  , "shaders/tess_demo/line_odd.tcs"  , "shaders/tess_demo/line_odd_points.tes"  , "", "shaders/tess_demo/line_odd.frag"  );

    this->shadersAxis.CreateProgram("shaders/ejes.vert", "", "", "", "shaders/ejes.frag"); 
    
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
}

void TessDemo::DestroyScene() {
    delete this->vaoTriangle;
    delete this->vaoAxis;
    this->shadersAxis.DeleteProgram();
    this->shadersTriangleEqual.DeleteProgram();
    this->shadersTriangleOdd.DeleteProgram();
    this->shadersTriangleEven.DeleteProgram();
    this->shadersQuadEqual.DeleteProgram();
    this->shadersQuadOdd.DeleteProgram();
    this->shadersQuadEven.DeleteProgram();
    this->shadersLineEqual.DeleteProgram();
    this->shadersLineOdd.DeleteProgram();
    this->shadersLineEven.DeleteProgram();
    this->shadersLinePointsEqual.DeleteProgram();
    this->shadersLinePointsOdd.DeleteProgram();
    this->shadersLinePointsEven.DeleteProgram();
 
    this->home->Reset();
}

void TessDemo::SetScene() {
    Example::zNear = 0.1f;
    Example::zFar = 20.0;
    Example::camStep = 0.1f;
    this->kDisplacement = 1.0; //Velocidad de movimiento 
    Example::camPos = glm::vec3(0.5, 0.5, 0.4);
    Example::camCenter  = glm::vec3(0.5, 0.5, 0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    this->RecalcMatrices();

    this->tessellate = true;
    this->TessDefault = 64.0;
    Example::fillPolygon = false;
    Example::renderText = false;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    this->TessLevelsTriangle = glm::vec4(1, 1, 1, 1);
    this->TessLevelsQuadOuter = glm::vec4(1,1,1,1);
    this->TessLevelsQuadInner = glm::vec2(1,1);
    this->TessLevelsLine = glm::vec2(1,1);
    this->currentShader = &this->shadersTriangleEqual;
    this->currentShaderPoints = &this->shadersLinePointsEqual;
    this->spacingMode = 0;
    this->currentDemo = 0;
    this->selectedLevel = 0;

    this->lineSpiral = false;

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
}

void TessDemo::cb_KeyboardExtended(unsigned char key, int x, int y) {
    std::string spacingString = "";
    std::string currentString = "";
    switch(key) {
    case 27: //escape
        this->DestroyScene();
        break;
    case 'T': 
    case 't':
        this->tessellate = not this->tessellate;
        if (this->tessellate) Example::lastMessage = "Teselacion adaptativa activada.\n"; 
        else Example::lastMessage = "Teselacion adaptativa desactivada. Valor por defecto = "+utils::XToStr(this->TessDefault)+".\n";
        break;
    case '+':
        if (this->currentDemo == 0) { //Triangulo, 4 parametros
            this->TessLevelsTriangle[this->selectedLevel] = std::min(64.0, this->TessLevelsTriangle[this->selectedLevel]+1.0);
            Example::lastMessage = "Niveles de teselacion = " + utils::XToStr(this->TessLevelsTriangle[0]) + ", "  + utils::XToStr(this->TessLevelsTriangle[1]) + ", " + utils::XToStr(this->TessLevelsTriangle[2]) + ", " + utils::XToStr(this->TessLevelsTriangle[3]) + ".\n";
        }
        if (this->currentDemo == 1) { //Cuadrilatero, 6 parametros
            if (this->selectedLevel < 4) this->TessLevelsQuadOuter[this->selectedLevel] = std::min(64.0, this->TessLevelsQuadOuter[this->selectedLevel]+1.0);
            else                         this->TessLevelsQuadInner[this->selectedLevel-4] = std::min(64.0, this->TessLevelsQuadInner[this->selectedLevel-4]+1.0);
            Example::lastMessage = "Niveles de teselacion = Outer:" + utils::XToStr(this->TessLevelsQuadOuter[0]) + ", " + utils::XToStr(this->TessLevelsQuadOuter[1]) + ", " 
                                    + utils::XToStr(this->TessLevelsQuadOuter[2]) + ", " + utils::XToStr(this->TessLevelsQuadOuter[3]) + "; Inner: " 
                                    + utils::XToStr(this->TessLevelsQuadInner[0]) + ", " + utils::XToStr(this->TessLevelsQuadInner[1]) + ".\n";
        }
        if (this->currentDemo == 2) { //Linea, 2 parametros
            this->TessLevelsLine[this->selectedLevel] = std::min(64.0, this->TessLevelsLine[this->selectedLevel]+1.0);
            Example::lastMessage = "Niveles de teselacion = " + utils::XToStr(this->TessLevelsLine[0]) + ", "  + utils::XToStr(this->TessLevelsLine[1]) + ".\n";
        }
        break;
    case '-':
        if (this->currentDemo == 0) { //Triangulo, 4 parametros
            this->TessLevelsTriangle[this->selectedLevel] = std::max(0.0, this->TessLevelsTriangle[this->selectedLevel]-1.0);
            Example::lastMessage = "Niveles de teselacion = " + utils::XToStr(this->TessLevelsTriangle[0]) + ", "  + utils::XToStr(this->TessLevelsTriangle[1]) + ", " + utils::XToStr(this->TessLevelsTriangle[2]) + ", " + utils::XToStr(this->TessLevelsTriangle[3]) + ".\n";
        }
        if (this->currentDemo == 1) { //Cuadrilatero, 6 parametros
            if (this->selectedLevel < 4) this->TessLevelsQuadOuter[this->selectedLevel] = std::max(0.0, this->TessLevelsQuadOuter[this->selectedLevel]-1.0);
            else                         this->TessLevelsQuadInner[this->selectedLevel-4] = std::max(0.0, this->TessLevelsQuadInner[this->selectedLevel-4]-1.0);
            Example::lastMessage = "Niveles de teselacion = Outer:" + utils::XToStr(this->TessLevelsQuadOuter[0]) + ", " + utils::XToStr(this->TessLevelsQuadOuter[1]) + ", " 
                                    + utils::XToStr(this->TessLevelsQuadOuter[2]) + ", " + utils::XToStr(this->TessLevelsQuadOuter[3]) + "; Inner: " 
                                    + utils::XToStr(this->TessLevelsQuadInner[0]) + ", " + utils::XToStr(this->TessLevelsQuadInner[1]) + ".\n";
        }
        if (this->currentDemo == 2) { //Linea, 2 parametros
            this->TessLevelsLine[this->selectedLevel] = std::max(1.0, this->TessLevelsLine[this->selectedLevel]-1.0);
            Example::lastMessage = "Niveles de teselacion = " + utils::XToStr(this->TessLevelsLine[0]) + ", "  + utils::XToStr(this->TessLevelsLine[1]) + ".\n";
        }
        break;
    case 'z':
    case 'Z':
        if (this->currentDemo == 0) { //Triangulo, 4 parametros
            this->selectedLevel = (this->selectedLevel+1)%4;
        }
        if (this->currentDemo == 1) { //Quad, 6 parametros
            this->selectedLevel = (this->selectedLevel+1)%6;
        }
        if (this->currentDemo == 2) { //Linea, 2 parametros
            this->selectedLevel = (this->selectedLevel+1)%2;
        }
        Example::lastMessage = "Parametro actual seleccionado = " + utils::XToStr(this->selectedLevel) + ".\n";
        break;
    case 'x':
    case 'X':
        if (this->currentDemo == 0) { //Triangulo, 4 parametros
            this->selectedLevel = (this->selectedLevel+4-1)%4;
        }
        if (this->currentDemo == 1) { //Quad, 6 parametros
            this->selectedLevel = (this->selectedLevel+6-1)%6;
        }
        if (this->currentDemo == 2) { //Quad, 6 parametros
            this->selectedLevel = (this->selectedLevel+2-1)%2;
        }
        Example::lastMessage = "Parametro actual seleccionado = " + utils::XToStr(this->selectedLevel) + ".\n";
        break;
    case 'c':
    case 'C':
        if (key == 'c') this->spacingMode = (this->spacingMode+1)%3;
        else this->spacingMode = (this->spacingMode+3-1)%3;
        switch(this->spacingMode) {
        case 0: 
            spacingString = " Simetrico.\n"; break;
        case 1: 
            spacingString = " Par.\n"; break;
        case 2: 
            spacingString = " Impar.\n"; break;
        }
        Example::lastMessage = "Metodo de espaciado = " + spacingString;
        break;
    case 'v':
    case 'V':
        this->currentDemo = (this->currentDemo+1)%3;
        this->selectedLevel = 0; //para evitar SIGSEGV en lineas
        switch(this->currentDemo) {
        case 0: glFrontFace(GL_CCW);glPatchParameteri(GL_PATCH_VERTICES, 3); currentString = " Triangulos.\n"; break;
        case 1: glFrontFace(GL_CW); glPatchParameteri(GL_PATCH_VERTICES, 4); currentString = " Cuadrilateros.\n"; break;
        case 2: glPatchParameteri(GL_PATCH_VERTICES, 4); currentString = " Isolineas.\n"; break;
        }
        Example::lastMessage = "Demostracion de teselacion de " + currentString;
        break;
    case 'f':
    case 'F':
        this->lineSpiral = not this->lineSpiral;
        if (this->lineSpiral) Example::lastMessage = "Dibujado de espiral.\n";
        else Example::lastMessage = "Dibujado de lineas paralelas.\n";
        break;
    case 'h':
    case 'H':
        if (this->debugMode) { 
            std::cout<<"\tT: Activa o desactiva teselacion por hardware.\n";
            std::cout<<"\tL: Intercambia entre poligono rellenos o no.\n";
            std::cout<<"\tH: Imprime este texto.\n";
        }
        const char* added_text = 
        "    T: Activa o desactiva teselacion por hardware.\n"
        "    L: Intercambia entre poligono rellenos o no.\n"
        "    V: Cambia la demostracion entre Triangulos, Cuadrilateros o Isolineas.\n"
        "    C: Cambia el metodo de espaciado entre simetrico, par o impar.\n"
        "    +: Aumenta el valor del nivel de teselacion seleccionado.\n"
        "    -: Decrece el valor del nivel de teselacion seleccionado.\n"
        "    Z: Cambia hacia adelante el nivel de teselacion seleccionado para modificar.\n"
        "    X: Cambia hacia atras el nivel de teselacion seleccionado para modificar.\n" 
        "    F: Activa o desactiva el dibujado de la espiral en teselacion de isolineas.\n" 
        "    Escape: Vuelve al menu principal.\n"
        "    H: Imprime este texto.\n";
        Example::lastMessage += std::string(added_text);
        break;
    }
}

void TessDemo::cb_SpecialExtended(int key, int x, int y) {
}

void TessDemo::cb_MouseExtended(int x, int y) {
}
