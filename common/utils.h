#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glew.h>    
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
namespace utils {
static const double PI = 3.14159265358979323846;

float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);

std::string IntToStr(int i);
void PVec3(glm::vec3 v, bool enter = false);
//#define ERRORCHECK
void ExitOnGLError(const char* error_message);
GLuint LoadImageTex(const char* theFileName);

double GetUnixTime();
std::string GetCurrentDateTime();

//Exporta el vector a un archivo
template <typename T>
bool ExportToFile (std::string filename, std::vector<T> data, unsigned int linebreak = 0) {
    unsigned int size = data.size();
    if (size == 0) return false;
    
    std::ofstream file (filename.c_str(), std::ios::out);
    if (not file.is_open()) { std::cout<<"No se pudo abrir el archivo "<<filename<<"\n"; return false; }
    
    file<<size;
    file<<"\n";
    for (unsigned int i = 0; i < size; ++i) {
        file<<data[i];
        if (linebreak != 0 and ((i+1) % linebreak) == 0) file<<'\n';
        else file<<' ';
    }
    file.close();

    return true;
}

//Importa desde un archivo a un vector
template <typename T>
bool ImportFromFile (std::string filename, std::vector<T> &data) {
    std::ifstream file (filename.c_str(), std::ios::in);
    if (not file.is_open()) { std::cout<<"No se pudo abrir el archivo "<<filename<<"\n"; return false; }

    unsigned int size;
    file >> size;
    data.resize(size, 0.0);
    T val;
    unsigned int pos = 0;
    while (file>>val) {
        if (pos >= size) {
            std::cout<<"Error: el tamanio reportado en la cabecera no corresponde con la longitud de datos.\n"; 
            return false;
        }
        data[pos] = val; 
        ++pos;
    }
    file.close();
    return true;
}

template<typename T>
void PrintVector(std::vector<T> v) {
    for (unsigned int i = 0; i < v.size(); i++) {
        if (i != v.size()-1) std::cout<<v[i]<<' ';
        else std::cout<<v[i]<<'\n';
    }
}

template<typename T>
std::string XToStr(T x) {
    std::stringstream ss;
    ss<<x;
    std::string s;
    ss>>s;
    return s;
}

};
#endif
