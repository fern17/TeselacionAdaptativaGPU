#include "Model.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>
#include "utils.h"

Model::Model(std::string filename, unsigned int numverticesface, bool extended) { 
    this->hasExtended = extended;
    this->Init(filename, numverticesface);
}

Model::Model() { //constructor vacio para cuando usamos un puntero a Model
};

Model::~Model() { }

void Model::Init(std::string filename, unsigned int numverticesface) {
    this->numVerticesPerFace = numverticesface;
    this->ImportModel(filename);
    this->hasNeighborsPerNode = false;
    this->hasNeighborsPerElement = false;
    this->hasNeighborsNormalsPerNode = false;
    this->hasNeighborsNormalsPerElement = false;
    this->hasBoundingBox = false;
    this->hasAdjacencies = false;
}

#define AI_CONFIG_PP_PTV_NORMALIZE   "PP_PTV_NORMALIZE" //para normalizar en -1 y 1
bool Model::ImportModel( std::string filename) {
    Assimp::Importer importer;
    //importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.f);//Angulo de tolerancia para GenSmoothNormals
    const aiScene* scene = importer.ReadFile( filename, 
          aiProcess_CalcTangentSpace       | 
          aiProcess_Triangulate            |
          aiProcess_JoinIdenticalVertices  |
          //aiProcess_GenNormals             | //Genera normales para las caras. Un nodo se queda con multiples normales
          aiProcess_GenSmoothNormals             | //Genera normales para los vertices.
          aiProcess_PreTransformVertices   | //normaliza en -1 y 1
          aiProcess_SortByPType);
    
    this->file = filename;
    if( !scene) {
        std::cerr<<"Error "<<importer.GetErrorString();
        return false;
    }
   
    this->mesh = scene->mMeshes[0];
    this->numFaces = mesh->mNumFaces;

    int nvpf = this->numVerticesPerFace;

    this->numIndices = this->numFaces*nvpf; 
    this->indices.resize(this->numIndices);
    
    for (unsigned int i = 0 ; i < this->mesh->mNumFaces ; i++) {
        const aiFace& Face = this->mesh->mFaces[i];
        //assert(Face.mNumIndices == numVerticesPerFace);
        this->indices[i * nvpf + 0]   = Face.mIndices[0];
        this->indices[i * nvpf + 1]   = Face.mIndices[1];
        this->indices[i * nvpf + 2]   = Face.mIndices[2];
    }
    
    this->numVertices = this->mesh->mNumVertices;
    if (this->mesh->HasPositions())       this->vertices.resize ((this->numVertices+1)*3, 0); //se agrega uno virtual al final que va a quedar con todo 0
    if (this->mesh->HasNormals())         this->normals.resize  ((this->numVertices+1)*3, 0);
    if (this->mesh->HasTextureCoords(0))  this->texCoords.resize((this->numVertices+1)*2, 0);

    for (unsigned int i = 0; i < this->mesh->mNumVertices; i++) {
        if (this->mesh->HasPositions()) {
            this->vertices[i*3 + 0] = this->mesh->mVertices[i].x;
            this->vertices[i*3 + 1] = this->mesh->mVertices[i].y;
            this->vertices[i*3 + 2] = this->mesh->mVertices[i].z;
        }
        if (this->mesh->HasNormals()) {
            this->normals[i*3 + 0] = this->mesh->mNormals[i].x;
            this->normals[i*3 + 1] = this->mesh->mNormals[i].y;
            this->normals[i*3 + 2] = this->mesh->mNormals[i].z;
        }
        if (this->mesh->HasTextureCoords(0)) {
            this->texCoords[i*2 + 0] = mesh->mTextureCoords[0][i].x;
            this->texCoords[i*2 + 1] = mesh->mTextureCoords[0][i].y;
        }
    }

    std::cout<<"\nDatos del modelo importado";
    std::cout<<"\nNombre de archivo = "<<this->file;
    std::cout<<"\nCantidad de vertices = "<<this->numVertices;
    std::cout<<"\nCantidad de indices = "<<this->numIndices;
    std::cout<<"\nCantidad de caras = "<<this->numFaces;
    /*
    std::cout<<"\nVertices = \n";
    for (unsigned int i = 0; i < this->numVertices; i++) {
        std::cout<<i<<": "<<
            this->vertices[i*3 + 0]<<' '<<
            this->vertices[i*3 + 1]<<' '<<
            this->vertices[i*3 + 2]<<'\n';
    }
    std::cout<<"\nIndices = \n";
    for (unsigned int i = 0; i < this->numFaces; i++) {
        std::cout<<i<<": "<<
            this->indices[i*3 + 0]<<' '<<
            this->indices[i*3 + 1]<<' '<<
            this->indices[i*3 + 2]<<'\n';
    }
    */
    std::cout<<"\n\n";

    return true;
}

//Retorna la lista de vecinos de un nodo
std::vector<unsigned int> Model::GetNeighborsOfNode(unsigned int nodi) {
    std::vector<unsigned int> ret_val;
    int nvpf = this->numVerticesPerFace;
    for (unsigned int i = 0; i < this->numFaces; i++) {
        //Obtencion de los indices de la cara i
        //std::vector<unsigned int> vv; vv.reserve(this->numVerticesPerFace);
        std::vector<unsigned int>::iterator ini;
        std::vector<unsigned int>::iterator fin;

        //Rango en donde buscar: posicion i*numVerticesPerFace hasta (i+1)*numVerticesPerFace
        if (i+nvpf >= this->numFaces) { //if por si se va fuera de rango
            ini = this->indices.begin()+i*nvpf;
            fin = this->indices.end();
        } else {
            ini = this->indices.begin()+i*nvpf;
            fin = ini+nvpf;
        }
        std::vector<unsigned int> vv(ini, fin);
        std::vector<unsigned int>::iterator posi = std::find(vv.begin(), vv.end(), nodi);
        
        //Si la cara i tiene al nodo nodi, la agrego a ret_val
        if (posi != vv.end()) ret_val.push_back(i);
    }
    return ret_val;
}

//Genera la lista de vecinos por nodo y tambien la guarda a un archivo
void Model::GenNeighborsPerNode() {
    std::ofstream file ("neighbor.txt", std::ios::out);
    if (not file.is_open()) return;
    this->neighborsPerNode.resize(this->numVertices);
    file<<this->numVertices<<"\n";
    for (unsigned int i = 0; i < this->numVertices; i++) {
        std::vector<unsigned int> nei = this->GetNeighborsOfNode(i);
        file<<nei.size()<<' ';
        for (unsigned int j = 0; j < nei.size(); j++) {
            file<<nei[j]<<' ';
        }
        file<<'\n';
        this->neighborsPerNode[i] = nei;
    }
    file.close();
    this->hasNeighborsPerNode = true;
}

//Imprime la lista de vecinos de cada nodo (si esta construida)
void Model::PrintNeighborsPerNode() {
    if (not this->hasNeighborsPerNode) return;
    for (unsigned int i = 0; i < this->neighborsPerNode.size(); i++) {
        std::cout<<"Nodo "<<i<<": ";
        for (unsigned int j = 0; j < this->neighborsPerNode[i].size(); j++) {
            std::cout<<this->neighborsPerNode[i][j]<<' ';
        }
        std::cout<<"\n";
    }
}
//Formato del archivo:
//Primer linea: un solo numero con la cantidad de vertices N
//Luego vienen N lineas con:
//Primer numero con la cantidad de vecinos M. Luego M numeros con los vecinos del nodo N-1
//Todo separados por espacios
bool Model::LoadNeighborsPerNode(std::string filename) {
    std::ifstream file(filename.c_str(), std::ios::in);
    if (not file.is_open()) return false;
    unsigned int cant_vec;
    file>>cant_vec;
    this->neighborsPerNode.resize(cant_vec);
    this->maxNeighborsPerNode = 0;
    for (unsigned int i = 0; i < cant_vec; i++) {
        unsigned int cv;
        file>>cv;
        if (cv > this->maxNeighborsPerNode) {
            this->maxNeighborsPerNode = cv;
        }
        std::vector<unsigned int> vv;
        for (unsigned int j = 0; j < cv; j++) {
            unsigned int v;
            file>>v;
            vv.push_back(v);
        }
        this->neighborsPerNode[i] = vv;
    }
    this->hasNeighborsPerNode = true;
    file.close();
    return true;
}

//A partir del array de vecinos, construye un array que tiene todas las normales de los vecinos de cada nodo
bool Model::BuildNeighborsNormalsPerNode() {
    if (not this->mesh->HasNormals()) return false; //Si no tiene normales, no se pueden calcular
    this->GenNeighborsPerNode();
    
    this->neighborsNormalsPerNode.resize(this->neighborsPerNode.size()*this->maxNeighborsPerNode*3);
    for (unsigned int i = 0; i < this->neighborsPerNode.size(); i++) { //Nodo i
        for (unsigned int j = 0; j < this->neighborsPerNode[i].size(); j++) { //Recorremos todos los vecinos del nodo i
            unsigned int vecij = this->neighborsPerNode[i][j]; //vecino j de i
            std::vector<float>::iterator ini = this->normals.begin()+vecij*3;
            std::vector<float>::iterator fin = ini+3;
            std::copy(ini, fin, this->neighborsNormalsPerNode.begin() + i*this->maxNeighborsPerNode+j*3);
        }
    }
    this->hasNeighborsNormalsPerNode = true;
    return true;
}

//Retorna el minimo valor(posicion de un nodo) en la dimension coord (x=0, y=1, z=2)
float Model::GetMinimumCoord(unsigned int coord) {
    float mini = this->vertices[coord]; 
    for (unsigned int i = 3; i < this->vertices.size(); i += 3) {
        mini = std::min(mini, this->vertices[i+coord]);
    }
    return mini;
}

//Retorna el maximo valor(posicion de un nodo) en la dimension coord (x=0, y=1, z=2)
float Model::GetMaximumCoord(unsigned int coord) {
    float maxi = this->vertices[coord]; 
    for (unsigned int i = 3; i < this->vertices.size(); i += 3) {
        maxi = std::max(maxi, this->vertices[i+coord]);
    }
    return maxi;
}

//Calcula la boundingbox de este modelo, alineada con los ejes (Axis Aligned Bounding Box)
void Model::CalculateBoundingBox() {
    if (this->hasBoundingBox) return;
    //Primero se calculan los extremos en cada eje
    float min_x = this->GetMinimumCoord(0);
    float min_y = this->GetMinimumCoord(1);
    float min_z = this->GetMinimumCoord(2);
    float max_x = this->GetMaximumCoord(0);
    float max_y = this->GetMaximumCoord(1);
    float max_z = this->GetMaximumCoord(2);
    this->bbMin = glm::vec3(min_x, min_y, min_z);
    this->bbMax = glm::vec3(max_x, max_y, max_z);

    //Ahora se crean los 8 puntos que definen la BB
    this->bb.push_back(min_x); this->bb.push_back(min_y); this->bb.push_back(min_z);
    this->bb.push_back(max_x); this->bb.push_back(min_y); this->bb.push_back(min_z);
    this->bb.push_back(max_x); this->bb.push_back(max_y); this->bb.push_back(min_z);
    this->bb.push_back(min_x); this->bb.push_back(max_y); this->bb.push_back(min_z);
    this->bb.push_back(min_x); this->bb.push_back(min_y); this->bb.push_back(max_z);
    this->bb.push_back(max_x); this->bb.push_back(min_y); this->bb.push_back(max_z);
    this->bb.push_back(max_x); this->bb.push_back(max_y); this->bb.push_back(max_z);
    this->bb.push_back(min_x); this->bb.push_back(max_y); this->bb.push_back(max_z);

    //for (unsigned int i = 0; i < this->bb.size(); i += 3) { std::cout<<"("<<bb[i]<<','<<bb[i+1]<<','<<bb[i+2]<<")\n";  }

    unsigned int __ii [12][2] = { 
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 5}, {5, 6}, {6, 2}, {6, 7}, {7, 3}, {0, 4}, {4, 7}, {4, 5}}; 
    for (unsigned int i = 0; i < 12; i++) 
        for (unsigned int j = 0; j < 2; j++) 
            this->bbIndices.push_back(__ii[i][j]);
    this->hasBoundingBox = true;
}

//Devuelve por copia la AABB de este modelo (la calcula si no estaba calculada)
void Model::GetBoundingBox(std::vector<float> &bb) {
    this->CalculateBoundingBox();
    bb = this->bb;
}

//Genera la estructura ListOfEdges que tiene una lista de las aristas, entre que nodos estan conectadas y los elementos en donde esta cada arista
void Model::GenAdjacencies() {
    if (this->hasAdjacencies) return; //si ya esta calculado, salir
   
    std::cout<<"Calculando la estructura de aristas\n";

    unsigned int spaceToReserve = this->numVertices + this->numFaces - 2; //Formula de Euler para grafos planos v-e+f = 2
    int nvpf = this->numVerticesPerFace;
    this->edges.Init(spaceToReserve);
    //Recorrer todas las caras
    for (unsigned int i = 0; i < this->numFaces; ++i) {
        int idx[3]; //vertices de esta cara
        for (unsigned int j = 0; j <= 2; ++j) {
            idx[j] = this->indices[i*nvpf + j];
        }
        for (unsigned int j = 0; j <= 2; ++j) {
            Edge eg(idx[j], idx[(j+1)%3]); //arista j de esta cara
            edges.Insert(eg, i); //Armar una lista de aristas sin repetir
        }
    }

    this->hasAdjacencies = true;
}

void Model::GenNeighborsOfElements() {
    if (this->hasNeighborsPerElement) return; //Ya esta calculado, salir
    if (not this->hasAdjacencies) return; //Si no tengo adyacencias, no puedo calcular

    std::cout<<"Calculando los vecinos por elemento\n";

    int nvpf = this->numVerticesPerFace;
    this->neighborsPerElement = new int[this->numFaces][3];
    for (unsigned int i = 0; i < this->numFaces; ++i) 
        for (unsigned int j = 0; j < 3; ++j) 
            this->neighborsPerElement[i][j] = -1;

    //Por cada elemento i
    for (unsigned int i = 0; i < this->numFaces; ++i) {
        //Recorrer sus aristas j
        for (unsigned int j = 0; j < 3; ++j) {
            //Encontrar la arista j,j+1 en edges
            int p1 = this->indices[i*nvpf + j];
            int p2 = this->indices[i*nvpf + ((j+1)%nvpf)];
            
            //Encontrar el vecino k del elemento i segun lo que dice elm1 o elm2 en edges
            int other = -1;
            this->edges.GetOther(p1, p2, i, other); //Obtenemos el vecino k de i y lo guardamos en other

            //Setear el vecino j del elemento i (puede ser -1 si GetOther no lo encontro)
            this->neighborsPerElement[i][j] = other;
            
            if (other == -1) continue; //si es -1, no hago lo siguiente

            //Tambien actualizar el vecino de other
            for (int k = 0; k < 3; ++k) {
                if ((p1 == this->indices[other*nvpf+k] and p2 == this->indices[other*nvpf+(k+1)%nvpf]) or 
                    (p2 == this->indices[other*nvpf+k] and p1 == this->indices[other*nvpf+(k+1)%nvpf]))
                this->neighborsPerElement[other][k] = i;
            }
        }
    }
    this->hasNeighborsPerElement = true;
}

//Se genera la lista de normales vecinas de un elemento
bool Model::BuildNeighborsNormalsPerElement() {
    if (not this->mesh->HasNormals()) {std::cout<<"No tiene normales\n";  return false; }//Sin normales no se puede construir
    
    //Primero se intenta cargarlo desde un archivo
    if ( not utils::ImportFromFile("NN0.txt", this->neighborsNormalsPerElement[0]) or 
         not utils::ImportFromFile("NN1.txt", this->neighborsNormalsPerElement[1]) or 
         not utils::ImportFromFile("NN2.txt", this->neighborsNormalsPerElement[2]) ) {
        //Si falla, se recalcula todo
        this->GenAdjacencies();
        this->GenNeighborsOfElements();

        std::cout<<"Copiando las normales de cada vecino\n";

        //ERROR, esto debe estar indizado por vertices, no por caras
        for (unsigned int i = 0; i < 3; ++i) 
            //this->neighborsNormalsPerElement[i].resize(this->numFaces*3, 0.0);
            this->neighborsNormalsPerElement[i].resize(this->numVertices*this->numVerticesPerFace, 0.0);

        //neighborsNormalsPerElement tiene la siguiente estructura:
        //Para el nodo i del elemento j, tiene la normal (3 coordenadas) del elemento k, que es vecino de j en la arista que empieza en el nodo i (coord global l)
       
        //PROBLEMA! Los vertices se repiten en varios elemento :S :S

        //Recorrer las caras j
        //Recorrer los nodos i de cada cara j (coordenada global del nodo = l)
        //Conseguir la normal del vecino k de la cara j en la arista i->i+1
        //Guardar esta normal en la posicion: l*3 de neighborsNormalsPerElement[i]
      //for (unsigned int j = 0; j < this->numFaces; ++j) {
      //    for (unsigned int i = 0; i < this->numVerticesPerFace; ++i) {
      //        unsigned int coord_global_nodo = this->indices[j*this->numVerticesPerFace+i];
      //        int k = this->neighborsPerElement[j][i]; //Vecino k
      //        
      //        if (k == -1) continue; //sin vecino
      //        float norm_vec_k[3];
      //        for (unsigned int m = 0; m < 3; ++m) {
      //            norm_vec_k[m] = normales_por_elemento[k];
      //            this->neighborsNormalsPerElement[i][coord_global_nodo*3+m] = norm_vec_k[m];
      //        }
      //    }
      //}
        
       
        ///@TODO: Esta mal construido neighborsNormalsPerElement, porque al final tengo que triplicar la informacion (mismos vecinos para cada nodo de cada triangulo)
      //for (unsigned int i = 0; i < this->numFaces; ++i) { //Por cada elemento
      //    for (unsigned int j = 0; j < this->numVerticesPerFace; ++j) { //Por cada uno de sus vecinos
      //        int vecino = this->neighborsPerElement[i][j]; //Vecino de i en la posicion j
      //        if (vecino == -1) continue;

      //      //Estas normales deben ser normales de ELEMENTO, no de NODO (this->normals son normales de nodo) 
      //        
      //        for (unsigned int k = 0; k < 3; ++k) { //Por cada coordenada del vecino j del elemento i
      //            //this->neighborsNormalsPerElement[i*this->numVerticesPerFace+j*this->numVerticesPerFace+k] = this->normals[vecino*3+k];
      //            this->neighborsNormalsPerElement[j][i*this->numVerticesPerFace+k] = this->normals[vecino*3+k];
      //        }
      //    }
      //}
        this->hasNeighborsNormalsPerElement = true;
        //Lo guardamos para ahorrar trabajo la proxima vez
        utils::ExportToFile("NN0.txt", this->neighborsNormalsPerElement[0], 3);
        utils::ExportToFile("NN1.txt", this->neighborsNormalsPerElement[1], 3);
        utils::ExportToFile("NN2.txt", this->neighborsNormalsPerElement[2], 3);
    }
    return true;
}


//Genera los vecindarios con adyacencias de triangulos
//Indices queda con elementos de 6 vertices: los primeros 3 son los originales {v0, v1, v2}.
//Los otros 3 son los vertices de los elementos vecinos: primero va el vecino por la arista v0-v1, luego v1-v2 y luego v2-v0
void Model::GenExtendedData() {
    if (not this->hasExtended) return; 
    if ( utils::ImportFromFile("indicesExtended.txt", this->indicesExtended)) return;
    
    //ahora tiene el doble de tamaño porque hay el doble de datos
    this->indicesExtended.resize(this->numFaces*this->numVerticesPerFace*2, this->numVertices); //se inicializa con el ultimo. Ver despues que, si se necesita, se reemplaza por el primero de cada vecindario 
    //this->normalsExtended.resize(this->numFaces*this->numVerticesPerFace*3*2, 0.0);
    
    int nvpf = this->numVerticesPerFace; //numero de vertices por cara real
    this->GenAdjacencies();
    this->GenNeighborsOfElements();

    std::cout<<"Generando informacion de vecindario extendido.\n";
    int vecino;
    unsigned int i, j, k, nod_k, idx_nodo_no_compartido, ne0, ne1;
        
    for (i = 0; i < this->numFaces; ++i) { //Recorremos las caras
        
        //los primeros 3 indices de vertices los copiamos sin modificar
        for (j = 0; j <= 2; ++j) this->indicesExtended[i*nvpf*2+j] = this->indices[i*nvpf+j]; 

      ////Las primeras 3 normales son las mismas (9 valores, 3 en j, 3 en k)
      //for (j = 0; j <= 2; ++j) { //este for recorre los indices
      //    idx_nodo = this->indices[i*this->numVerticesPerFace+j]; //idx del vertice j del elemento i

      //    for (k = 0; k <= 2; ++k) { //este for recorre las coordenadas
      //        this->normalsExtended[this->idx_nodo*3*2+k] = this->normals[idx_nodo*3+k]; 
      //    }
      //}
        
        //Pedimos el vecino en cada arista y agregamos su indice
        for (j = 0; j <= 2; ++j) { //por cada arista
            //Encontrar el vecino de esta arista
            vecino = this->neighborsPerElement[i][j];
            if (vecino == -1) continue;

            //Encontrar el indice del nodo que no es igual a j y j+1
            ne0 = this->indices[i*nvpf+j]; //nodo j del elemento actual
            ne1 = this->indices[i*nvpf+((j+1)%3)]; //nodo j+1 circular del elemento actual
            
            idx_nodo_no_compartido = ne0; //para evitar problemas, lo seteamos igual a elm[j]

            for (k = 0; k <= 2; ++k) { //recorrer los 3 nodos del vecino y encontrar uno que no coincida con ne0 y ne1
                nod_k = this->indices[vecino*nvpf+k];
                if (nod_k != ne0 and nod_k != ne1) { //encontrado
                    idx_nodo_no_compartido = nod_k;
                    break;
                }
            }
            //este nodo ponerlo en indicesExtended[i*this->numVerticesPerFace*2+3+j]
            this->indicesExtended[i*nvpf*2+3+j] = idx_nodo_no_compartido; //+3 porque ya seteamos los primeros 3 al principio

          ////Tambien actualizamos las normales
          //idx_nodo = this->indices[vecino*this->numVerticesPerFace];
          //for (k = 0; k <= 2; ++k) {
          //    this->normalsExtended[this->idx_nodo*2*3+k] = this->normals[idx_nodo*3+k];
          //}
        } //fin de cada arista
    }//fin de cada elemento

    //Si algun vecino no se seteo (quedo igul a numVertices), se reemplaza por el primer vertice de la arista de este vecindario
    for (i = 3; i < this->indicesExtended.size(); ++i) {
        //if (i % 6 == 0) { i += 3; continue; } //saltar los primeros 3 de cada 6-upla
        if (this->indicesExtended[i] == this->numVertices) {
            this->indicesExtended[i] = this->indicesExtended[i-3]; //repito el vertice anterior
        }
    }
    utils::ExportToFile("indicesExtended.txt", this->indicesExtended, 6);
    std::cout<<"Generacion de vecindario extendido finalizada.\n";
}

unsigned int Model::GetNumIndices() {
    if (this->hasExtended) return this->numIndices*2;
    else return this->numIndices;
}
