#include "FieldDistance.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> //lookat
#include <glm/gtx/norm.hpp> //l2norm
#include "utils.h"
//#include "data_small.h"
//#include "data_long.h"
//#include "mesh.h"  //contiene la malla de cuadrilateros y los elementos
//#include "campo.h" //contiene el campo vectorial aplicado a la mesh
//#include "campo_unsentido.h" //contiene el campo vectorial aplicado a la mesh
//#include "field_distance/triangles.h"
#include <utility>
#include <fstream>
#include <cmath>
FieldDistance::FieldDistance(std::string name, int w, int h, int vpp, Home *home_ptr) {
    this->home = home_ptr;
    Example::InitVariables(name, w, h, vpp); 
    glutSetWindowTitle(this->WINDOW_NAME.c_str());
    if (Example::fileToLog.is_open() ) Example::fileToLog<<utils::GetCurrentDateTime()<<"\tCambiando a "<<this->WINDOW_NAME<<".\n";
}

void FieldDistance::DrawScene() {
    //Antes de hacer nada, verificar si no hay que reiniciar el ciclo
    this->currentCountToReset++;
    if (this->currentCountToReset > this->countToReset) this->Reset(this->backgroundColor);

    //PASO 1: Mover vertices
    this->shadersFeedback.Bind(); 
    this->shadersFeedback.SetUniform("MVPMatrix", Example::MVPMatrix); 
    this->shadersFeedback.SetUniform("StepH", this->stepH);
    this->shadersFeedback.SetUniform("FieldId", this->currentField);
    
    glEnable(GL_RASTERIZER_DISCARD); //Este shader no va a dibujar nada, no se llama al fragment shader
    
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, this->tfo);
    //glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, this->meshB);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->meshA); //Entrada
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, this->meshB); //Salida

    this->slotPosition = this->shadersFeedback.GetAttribLocation("in_Position"); this->slotField = this->shadersFeedback.GetAttribLocation("in_Field");
    this->slotFieldR = this->shadersFeedback.GetAttribLocation("in_FieldRight"); this->slotFieldRB = this->shadersFeedback.GetAttribLocation("in_FieldRightBottom");
    this->slotFieldB = this->shadersFeedback.GetAttribLocation("in_FieldBottom");
    glEnableVertexAttribArray(this->slotPosition); glEnableVertexAttribArray(this->slotField);
    glEnableVertexAttribArray(this->slotFieldR); glEnableVertexAttribArray(this->slotFieldRB); glEnableVertexAttribArray(this->slotFieldB); 
    char *pOffset = 0;
    size_t step = 2*sizeof(float);
    glVertexAttribPointer(this->slotPosition, 2, GL_FLOAT, GL_FALSE, step*5, pOffset);        glVertexAttribPointer(this->slotField,   2, GL_FLOAT, GL_FALSE, step*5, pOffset+step); 
    glVertexAttribPointer(this->slotFieldR,   2, GL_FLOAT, GL_FALSE, step*5, pOffset+2*step); glVertexAttribPointer(this->slotFieldRB, 2, GL_FLOAT, GL_FALSE, step*5, pOffset+3*step); 
    glVertexAttribPointer(this->slotFieldB,   2, GL_FLOAT, GL_FALSE, step*5, pOffset+4*step); 
    glBeginTransformFeedback(GL_POINTS); //el parametro se tiene que corresponder con el que tiene el geometry shader (si se usa)
    {
        glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, this->query);
        //glDrawArrays(GL_POINTS, 0, sizeof(data)/(4*sizeof(float)));
        //glDrawArrays(GL_POINTS, 0, this->sizeofdata/(4*sizeof(float)));
        glDrawArrays(GL_POINTS, 0, this->sizeOfData/(10*sizeof(float)));
        glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    }
    glEndTransformFeedback();
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
    glDisableVertexAttribArray(this->slotPosition); glDisableVertexAttribArray(this->slotField);
    glDisableVertexAttribArray(this->slotFieldR); glDisableVertexAttribArray(this->slotFieldRB); glDisableVertexAttribArray(this->slotFieldB); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
    this->shadersFeedback.Unbind();

    glDisable(GL_RASTERIZER_DISCARD); //Se vuelve a activar el rasterizado

    GLuint primitives_written;
    glGetQueryObjectuiv(this->query, GL_QUERY_RESULT, &primitives_written);
   
    std::swap(meshA, meshB); //Ahora la salida va a ser A y la entrada B
  
    ////////////////////////////////
    
    ///PASO 2: Teselar y dibujar a textura los vertices movidos, esto sirve para la acumulacion
    this->shadersTexture.Bind(); 
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->framebuffer); //se dibuja al framebuffer, a la textura outtexture
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->outTexture, 0); 

    glViewport(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT);

    //Ahora dibujamos el buffer
    
    //Cargamos el buffer con las posiciones iniciales. Estas posiciones son las que se utilizaran en el fragment shader para calcular el color de un fragmento
    //Este color debe ser constante en toda la ejecucion, por lo que se necesita tener la informacion original (en la ejecucion la posicion inicial se pierde una vez se mueven los vertices)
    glBindBuffer(GL_ARRAY_BUFFER, this->meshOriginal);
    this->slotPositionOriginal = this->shadersTexture.GetAttribLocation("in_PositionOriginal");
    glEnableVertexAttribArray(this->slotPositionOriginal);
    glVertexAttribPointer(this->slotPositionOriginal, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    //Ahora se cargan los datos de la malla de salida del paso anterior
    glBindBuffer(GL_ARRAY_BUFFER, meshA); //se dibuja la malla de salida a un framebuffer

    this->slotPosition = this->shadersTexture.GetAttribLocation("in_Position"); this->slotField = this->shadersTexture.GetAttribLocation("in_Field");
    this->slotFieldR = this->shadersTexture.GetAttribLocation("in_FieldRight"); this->slotFieldRB = this->shadersTexture.GetAttribLocation("in_FieldRightBottom");
    this->slotFieldB = this->shadersTexture.GetAttribLocation("in_FieldBottom");
    glEnableVertexAttribArray(this->slotPosition); glVertexAttribPointer(this->slotPosition, 2, GL_FLOAT, GL_FALSE, step*5, pOffset); 
    glEnableVertexAttribArray(this->slotField);    glVertexAttribPointer(this->slotField,    2, GL_FLOAT, GL_FALSE, step*5, pOffset+step); 
    glEnableVertexAttribArray(this->slotFieldR);   glVertexAttribPointer(this->slotFieldR,   2, GL_FLOAT, GL_FALSE, step*5, pOffset+step*2); 
    glEnableVertexAttribArray(this->slotFieldRB);  glVertexAttribPointer(this->slotFieldRB,  2, GL_FLOAT, GL_FALSE, step*5, pOffset+step*3); 
    glEnableVertexAttribArray(this->slotFieldB);   glVertexAttribPointer(this->slotFieldB,   2, GL_FLOAT, GL_FALSE, step*5, pOffset+step*4); 

    this->shadersTexture.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shadersTexture.SetUniform("StepH", this->stepH);
    this->shadersTexture.SetUniform("Tessellate", this->tessellate);   
    this->shadersTexture.SetUniform("MaxTess", this->maxTess);
    this->shadersTexture.SetUniform("dx", this->dx);  this->shadersTexture.SetUniform("dy", this->dy);
    this->shadersTexture.SetUniform("TessDefault", this->tessDefault);  
    this->shadersTexture.SetUniform("CurrentField", this->currentField);  
    this->shadersTexture.SetUniform("ScaleX", this->scaleX);  
    this->shadersTexture.SetUniform("ScaleY", this->scaleY);  
    if (Example::useVirtualCamera) this->shadersTexture.SetUniform("CamPos", Example::virtualCamPos);
    else                           this->shadersTexture.SetUniform("CamPos", Example::camPos);
    this->shadersTexture.SetUniform("CurrentField", this->currentField);  
    this->shadersTexture.SetUniformTex("noisetexture", 2);

    glDrawTransformFeedback(GL_PATCHES, this->tfo);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout<<"Error en el framebuffer\n";

    //glDisableVertexAttribArray(this->slotPositionOriginal);
    glDisableVertexAttribArray(this->slotPosition);  glDisableVertexAttribArray(this->slotField);
    glDisableVertexAttribArray(this->slotFieldR); glDisableVertexAttribArray(this->slotFieldRB); glDisableVertexAttribArray(this->slotFieldB); 

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // No se necesita mas este framebuffer
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glViewport(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT);

    this->shadersTexture.Unbind();

    ///PASO 3: Dibujar en la ventana
    this->shadersDraw.Bind(); 
    glBindBuffer(GL_ARRAY_BUFFER, this->vboQuad);
    glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,  (GLubyte*) NULL); 
   
    this->shadersDraw.SetUniform("MVPMatrix", Example::MVPMatrix);
    this->shadersDraw.SetUniformTex("outtexture", 0);
    this->shadersDraw.SetUniformTex("accumtexture", 1);
        glDrawArrays(GL_TRIANGLES, 0, 6); 
    
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    this->shadersDraw.Unbind();

    //Copiado de outtexture a prevtexture
    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

    glBindTexture(GL_TEXTURE_2D, 0);
    //Lee desde el color0
    //glReadBuffer(GL_COLOR_ATTACHMENT0);
    //glDrawBuffer(GL_COLOR_ATTACHMENT1); //glDrawBuffers(2, this->drawBuffers);
    //Escribe al color1
    //glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outtexture, 0); 
    
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->accumTexture, 0);

    //glFramebufferTexture2D(GL_TEXTURE_2D, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->accumTexture, 0); 
    //En la linea anterior queda la duda de poner GL_TEXTURE_2D o GL_DRAW_FRAMEBUFFER
    glBlitFramebuffer(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0); glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0); glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FieldDistance::CreateScene() {
    unsigned int sizei = this->ReloadData(0, false);
    //unsigned int sizei = sizeof(data_inicial)/(sizeof(float));
  //this->data = new float[sizei];
  //this->data = data_inicial;
    this->sizeOfData = sizei*sizeof(float);
    //Generacion de los buffers. Un buffer para entrada y otro para salida. Luego se intercambian. 
    glGenBuffers(1, &this->meshA);
    glBindBuffer(GL_ARRAY_BUFFER, this->meshA);
    glBufferData(GL_ARRAY_BUFFER, this->sizeOfData, &*this->data, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(1, &this->meshB);
    glBindBuffer(GL_ARRAY_BUFFER, this->meshB);
    glBufferData(GL_ARRAY_BUFFER, this->sizeOfData, 0, GL_STREAM_DRAW);
    glBindBufferRange(GL_ARRAY_BUFFER, 0, this->meshB, 0, this->sizeOfData); //WTF
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Copia de la malla original, para los colores en la textura de ruido
    glGenBuffers(1, &this->meshOriginal);
    glBindBuffer(GL_ARRAY_BUFFER, this->meshOriginal);
    glBufferData(GL_ARRAY_BUFFER, this->sizeOfData, &*this->data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Esta es la construccion del shader de lic
    bool ok = this->shadersFeedback.CreateProgram("shaders/field_distance/feedback.vert", "", "", "shaders/field_distance/feedback.geom", "shaders/field_distance/feedback.frag", false);
    if (not ok) { std::cout<<"Ocurrio un error al crear los shaders de la LIC.\n"; }
    else {
        this->varyings.push_back("Position"); this->varyings.push_back("Field");
        this->varyings.push_back("FieldR"); this->varyings.push_back("FieldRB"); this->varyings.push_back("FieldB");
        //ok = this->shadersFeedback.SetTransformFeedback(this->varyings, GL_SEPARATE_ATTRIBS);
        ok = this->shadersFeedback.SetTransformFeedback(this->varyings, GL_INTERLEAVED_ATTRIBS);
        if (not ok) { std::cout<<"Ocurrio un error al configurar el transform feedback.\n"; }
    }

    //Creacion del Transform Feedback object
    glGenTransformFeedbacks(1, &this->tfo);

    //No tiene geometry shader
    if (not this->shadersTexture.CreateProgram("shaders/field_distance/texture.vert", "shaders/field_distance/texture.tcs", "shaders/field_distance/texture.tes", "", "shaders/field_distance/texture.frag")) std::cout<<"Ocurrio un error al crear los shaders de la textura.\n";
    if (not this->shadersDraw.CreateProgram("shaders/field_distance/draw.vert", "", "", "", "shaders/field_distance/draw.frag")) std::cout<<"Ocurrio un error al crear los shaders de dibujado.\n";
    
    std::vector<GLubyte> empty_data(this->WINDOW_WIDTH * this->WINDOW_HEIGHT * 10, 0.6); //vector de ceros para inicializar las texturas a cero
    //El buffer de salida del shader
    glGenFramebuffers(1, &this->framebuffer);

    //La textura donde se guarda todo
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &this->outTexture);
    glBindTexture(GL_TEXTURE_2D, this->outTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &empty_data[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    
    //La textura acumulada
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &this->accumTexture);
    glBindTexture(GL_TEXTURE_2D, this->accumTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &empty_data[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    this->drawBuffers[0] = GL_COLOR_ATTACHMENT0; this->drawBuffers[1] = GL_COLOR_ATTACHMENT1;

    glGenQueries(1, &this->query);  //Para la query de cuantos vertices se dibujaron en el primer shader
 
    //Esto es donde se va a dibujar la textura
    glGenVertexArrays(1, &this->vaoQuad); glBindVertexArray(this->vaoQuad);
     
    static const GLfloat quad[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f,  1.0f, 0.0f, -1.0f,  1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f  };
    glGenBuffers(1, &this->vboQuad);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboQuad);  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW); glBindBuffer(GL_ARRAY_BUFFER, 0);
  
    //Textura de ruido
    glActiveTexture(GL_TEXTURE2); 
    std::string texNoiseName = "../resources/noise_image.png";
    this->noiseTexture = utils::LoadImageTex(texNoiseName.c_str());
 
    delete Example::textRenderer; Example::textRenderer = new TextRenderer("../resources/LiberationSerif-Regular.ttf");
    this->Reset(this->backgroundColor);
};

void FieldDistance::DestroyScene() {
    this->shadersFeedback.DeleteProgram();
    this->shadersTexture.DeleteProgram();
    this->shadersDraw.DeleteProgram();

    glDeleteBuffers(1, &this->meshA);
    glDeleteBuffers(1, &this->meshB);
    glDeleteBuffers(1, &this->meshOriginal);

    glDeleteBuffers(1, &vboQuad);
    glDeleteTextures(1, &outTexture);
    glDeleteTextures(1, &accumTexture);
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteVertexArrays(1, &vaoQuad);
    glDeleteQueries(1, &query);

    this->home->Reset();
}

void FieldDistance::SetScene() {
    Example::zNear = 0.1;
    Example::zFar = 10.0;
    this->kDisplacement = 0.5; //Velocidad de movimiento 
    Example::camPos = glm::vec3(0.1, 0.1, 2);
    Example::camCenter  = glm::vec3(0.1, 0.1, 0.0);
    Example::camUp      = glm::vec3(0, 1, 0);
    Example::camEyeTarget = glm::normalize(Example::camCenter - Example::camPos);
    //Esto se pone aca de nuevo porque la camara cambio desde la inicializacion en Example::initialize()
    this->RecalcMatrices();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    
    this->maxTess = 16.0;
    this->tessDefault = 4.0;
    this->fillPolygon = true; 
    this->tessellate = true;
    this->drawWire = true;
   
    this->stepH = 0.0005;
    //this->stepH = 0.001;
    this->dx = 0.125;
    this->dy = 0.125;
    glPointSize(1.0);
    
    this->colorFps = glm::vec3(1.0, 1.0, 1.0);
    this->colorHelp = glm::vec3(1.0, 1.0, 1.0);
    this->colorStatus = glm::vec3(1.0, 1.0, 1.0);
   
    this->currentCountToReset = 0;
    this->countToReset = 2000;

    this->maxField = 3;
    this->currentField = 0;
    this->scaleX = 0.05;
    this->scaleY = 0.05;
    this->kDisplacement = 0.1;
    this->backgroundColor = 255; //color del fondo, en escala 0,255
    
    glPatchParameteri(GL_PATCH_VERTICES, this->VERTICES_PER_PATCH);
}

void FieldDistance::cb_KeyboardExtended(unsigned char key, int x, int y) {
    switch(key) {
    case 27: //escape
        this->DestroyScene();
        break;
    case 'T': 
    case 't':
        this->tessellate = not this->tessellate;
        if (this->tessellate) Example::lastMessage = "Teselacion adaptativa activada.\n";
        else  Example::lastMessage = "Teselacion adaptativa desactivada. Valor por defecto = " + utils::XToStr(this->tessDefault) + ".\n";
        this->Reset(this->backgroundColor);
        break;
    case 'k':
    case 'K':
        this->drawWire = not this->drawWire;
        if (this->drawWire) Example::lastMessage = "Dibujar lineas.\n";
        else Example::lastMessage = "No dibujar lineas.\n";
        break;
    case 'y': 
    case 'Y':
        if (this->maxTess < 1.01) this->maxTess = 2.0f;
        else if (this->maxTess < 64.0) this->maxTess += 2.0f;
        Example::lastMessage = "maxTess = " + utils::XToStr(this->maxTess) + ".\n";
        this->Reset(this->backgroundColor);
        break;
    case 'u': 
    case 'U':
        if (this->maxTess <= 2.0)  this->maxTess = 1.0;
        else this->maxTess -= 2.0f;
        Example::lastMessage = "maxTess = " + utils::XToStr(this->maxTess) + ".\n";
        this->Reset(this->backgroundColor);
        break;
    case 'c':
    case 'C':
        this->currentField = (this->currentField+1)%this->maxField;
        this->ReloadData(this->currentField);
        std::cout<<"Cargado el campo "<<this->currentField<<".\n";
        break;
    case 'r':
    case 'R':
        this->Reset(this->backgroundColor);
        std::cout<<"Reiniciado.\n";
        break;
    case 'w':
    case 'W':
    case 's':
    case 'S':
    case 'a':
    case 'A':
    case 'd':
    case 'D':
        this->Reset(this->backgroundColor);
        break;
    case 'h':
    case 'H':
        std::cout<<"\tK: Intercambia entre dibujar lineas o no.\n";
        std::cout<<"\tY: Aumenta el nivel maximo de teselacion.\n";
        std::cout<<"\tU: Disminuye el nivel maximo de teselacion.\n";
        std::cout<<"\tR: Reinicia el proceso de dibujado.\n";
        std::cout<<"\tT: Activa o desactiva la teselacion por hardware.\n";
        std::cout<<"\tH: Imprime este texto\n";
        const char* added_text = 
        "    K: Intercambia entre dibujar lineas o no.\n"
        "    Y: Aumenta el nivel maximo de teselacion.\n"
        "    U: Disminuye el nivel maximo de teselacion.\n"
        "    R: Reinicia el proceso de dibujado.\n"
        "    T: Activa o desactiva la teselacion por hardware.\n"
        "    Escape: Vuelve al menu principal.\n"
        "    H: Imprime este texto.\n";
        Example::lastMessage += std::string(added_text);
        break;
    }
}

void FieldDistance::Reset(unsigned int valor_por_defecto) {
    glBindBuffer(GL_ARRAY_BUFFER, this->meshA);
    glBufferData(GL_ARRAY_BUFFER, this->sizeOfData, &*data, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, this->meshB);
    glBufferData(GL_ARRAY_BUFFER, this->sizeOfData, 0, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::vector<GLubyte> empty_data(this->WINDOW_WIDTH * this->WINDOW_HEIGHT * 4, valor_por_defecto); //vector de ceros para inicializar las texturas a cero
    //La textura donde se guarda todo
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->outTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &empty_data[0]);
        
    //La textura acumulada
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->accumTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &empty_data[0]);
    this->currentCountToReset = 0;
}

void FieldDistance::cb_SpecialExtended(int key, int x, int y) {}
void FieldDistance::cb_MouseExtended(int x, int y) {}


unsigned int FieldDistance::ReloadData(unsigned int field_id, bool reset) {
    unsigned int xdiv = 16; 
    unsigned int zdiv = 16;
    float positions[(xdiv+1)*(zdiv+1)*4]; //(16+1)*(16+1)*4
    this->scaleX = 0.05;
    this->scaleY = 0.05;
    float dx = 1.0/((double) xdiv);
    float dz = 1.0/((double) zdiv);

    unsigned int idx = 0;
    for (unsigned int j = 0; j <= 2*zdiv; j += 2) {
        float z = ((double) j)*dz*0.5;
        z = 2*z - 1.0;//mapea en [-1,1] en lugar de [0, 1]
        for (unsigned int i = 0; i <= 2*xdiv; i+= 2) {
            float x = ((double) i)*dx*0.5;
            //unsigned int idx = xdiv*j+i; //revisar
            
            x = 2*x - 1.0; //mapea en [-1,1] en lugar de [0, 1]
          
            std::pair<float, float> local_field;
            //Si se cambia esto, cambiar las derivadas en el shader texture.tcs
            if (field_id == 0) {
                local_field.first = std::cos(x)*scaleX;
                local_field.second = (z)*scaleY;
            }
            if (field_id == 1) {
                local_field.first =  (x)*scaleX;
                local_field.second = (z)*scaleY;
            }
            if (field_id == 2) {
                local_field.first =  std::sin(x)*scaleX;
                local_field.second = std::cos(z)*scaleY;
            }
            positions[idx] = x;
            positions[idx+1] = z;
            positions[idx+2] = local_field.first;
            positions[idx+3] = local_field.second;
          //data_inicial[idx] = x;
          //data_inicial[idx+1] = z;
          //data_inicial[idx+2] = local_field.first;
          //data_inicial[idx+3] = local_field.second;
            idx += 4;
        }
    }
    //Regeneracion del puntero data
    unsigned int sizei = (xdiv+1)*(zdiv+1)*10;
    unsigned int quant = (xdiv+1)*(zdiv+1)*4;
    //if (this->data) delete this->data;
    this->data = new float[sizei];
    
    for (unsigned int i = 0; i < sizei; i++) this->data[i] = 0.0f; //relleno con ceros para los datos ausentes

    unsigned int posi = 0; //posi direcciona las posiciones en positions
    for (unsigned int i = 0; i < sizei; ) { //notar que el contador aqui no se aumenta
        for (unsigned int j = 0; j < 4; j++) { //copia de la posicion y el campo de este punto
            this->data[i+j] = positions[posi+j];
        }
        //Copia del campo de los otros 3 puntos
        //Derecha
        short cond = 0;
        if (((posi+4)/4)%(xdiv+1) != 0) {
            this->data[i+4] = positions[posi+4+2];
            this->data[i+5] = positions[posi+4+3];
            cond++;
        }
        //Abajo
        if ((posi + (xdiv+1)*4) < quant) {
            this->data[i+8] = positions[posi+(xdiv+1)*4+2];
            this->data[i+9] = positions[posi+(xdiv+1)*4+3];
            cond++;
        }
        //Abajo Derecha
        //if ((posi < sizei - (zdiv+1)*10) and ((posi+4)%((xdiv+1)*10) != 0) {
        if (cond == 2) { //si cumplio las otras dos condiciones
            this->data[i+6] = positions[posi+(xdiv+1)*4+4+2];
            this->data[i+7] = positions[posi+(xdiv+1)*4+4+3];
        }
        posi += 4; //posi avanza 4
        i += 10; //i avanza 10 (10 datos por vector)
    }

  //std::string filename = "data_dump.h";
  //std::ofstream file (filename.c_str(), std::ios::trunc|std::ios::out);
  //if (file.is_open()) {
  //    file<<"float data[] = {\n";
  //    file<<"//\t\t{Posicion}\t{Campo}\t{CampoDerecha}\t{CampoAbajoDerecha}\t{CampoAbajo}\n";
  //    
  //    for (unsigned int i = 0; i < sizei; i += 10) {
  //        file<<"\t{ {"<<data[i]<<", "<<data[i+1]<<"}, {"<<data[i+2]<<", "<<data[i+3]<<"}, { "<<data[i+4]<<", "<<data[i+5]<<"}, {"<<data[i+6]<<", "<<data[i+7]<<"}, {"<<data[i+8]<<", "<<data[i+9]<<"}";
  //        if (i < sizei-10) file<<"},\n";
  //        else file<<"}\n";
  //    }
  //    file<<"};\n";
  //    file.close();
  //}

        
    if (reset) this->Reset(this->backgroundColor);

    return sizei;
}
