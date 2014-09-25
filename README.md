TeselacionAdaptativaGPU
=======================
INSTALACION y USO DEL REPOSITORIO:
Nota: Estas intrucciones fueron probadas en Kubuntu 13.10 64 bits.
Para poder compilar el proyecto, es necesario tener un conjunto de bibliotecas instaladas en el sistema. Estas bibliotecas tienen diversas funciones en el código, según como se indica a continuación:

-- Bibliotecas necesarias:
* OpenGL 4.2: biblioteca principal del software
* freeglut 3: creación de ventanas e interacción con el software
* Glew 1.8.0: lectura de shaders 
* GLM 0.9.4.6: vectores y matrices
* Boost: necesaria para compilar ASSIMP
* ASSIMP 3.0.1270: lectura de modelos .obj
* DEVIL 1.7.8: lectura de imágenes (texturas)
* libpng: necesaria para compilar FreeType
* FreeType 2.5.2: renderizado de texto en pantalla

A continuación se detalla las instrucciones para instalar cada una de estas bibliotecas. En sistemas donde no se posee el comando apt-get, se deberá utilizar el gestor de paquetes propio de la distribución. 

Instalación freeglut:
$ sudo apt-get install freeglut3

Instalación Glew:
$ sudo apt-get install libglew-dev glew-utils

Instalación GLM:
Descargar GLM desde el sitio web y copiar la carpeta glm/glm a /usr/include/glm

Instalación Boost:
$ sudo apt-get install libboost-all-dev

Instalación ASSIMP:
Descargar ASSIMP desde el sitio web, extraer y luego realizar los siguientes comandos en consola (necesita libboost):
$ cmake -G 'Unix Makefiles'
$ make
$ sudo make install

Instalación DEVIL:
$ sudo apt-get install libdevil-dev

Instalación libpng:
$ sudo apt-get install libpng12-dev

Instalación FreeType:
Descargar y extraer (necesita libpng)
$ ./configure
$ make
$ sudo make install

Modificación de PATH para que se encuentren todas las bibliotecas:
Agregar al .bashrc el path /usr/local/lib
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib


Parámetros para los makefiles:
Linking:
- Glut: -lglut 
- OpenGL: -lGL -lGLU 
- Glew: -lGLEW 
- Devil: -lIL -lILU -lILUT 
- Assimp: -lm -lpthread -lassimp 
- FreeType: -lfreetype -lz -lpng12

Includes: 
- FreeType (en compilación): 
  -I/usr/include/freetype2 -I/usr/local/include/freetype2
- FreeType (en código):
  #include <ft2buildh>
  #include FT_FREETYPE_H
- Glew (en código): 
  #include <GL/glew.h>      
- freeglut (en código): 
  #include <GL/freeglut.h>
- glm (en código): 
  #include <glm/glm.hpp>      	  //glm
  #include <glm/gtc/matrix_transform.hpp> //lookat
  #include <glm/gtx/norm.hpp> 	  //l2norm
  #include <glm/gtc/type_ptr.hpp> //value_ptr
- Devil (en código):
  #include <IL/il.h>
  #include <IL/ilu.h>
  #include <IL/ilut.h>
- Assimp(en código):
  #include <assimp/Importer.hpp>      // C++ importer interface
  #include <assimp/scene.h>           // Output data structure
  #include <assimp/postprocess.h>     // Post processing flags


