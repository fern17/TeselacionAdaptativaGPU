#ifndef _MODEL_H_
#define _MODEL_H_
#include <vector>
#include <string>
#include <glm/glm.hpp>

//Assimp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

//Estructura auxiliar para usar en ListOfEdges
//Contiene la informacion referente a una arista: los nodos que la componen y los elementos que separa
//Dos aristas son iguales si tienen los mismos nodos (aunque en distinto orden)
struct Edge {
    int node1; //Primer nodo de la arista
    int node2; //Segundo nodo de la arista
    int elm1;  //Primer elemento de la arista
    int elm2;  //Segundo elemento de la arista
    Edge() : node1(-1), node2(-1), elm1(-1), elm2(-1) {} 
    Edge(int n1, int n2) : node1(n1), node2(n2), elm1(-1), elm2(-1) {}
    bool operator == (const Edge &other) { //iguales si tienen los mismos nodos o en el orden invertido
        return ((this->node1 == other.node1 and this->node2 == other.node2) or 
                (this->node1 == other.node2 and this->node2 == other.node1));
    }
    bool AddElement(int elm) { //Se asume que el elemento elm tiene a esta arista como arista
        if (elm == -1) return false;
        if (elm1 == elm or elm2 == elm) return false; //si ya lo tiene
        if (elm1 == -1 and elm2 != elm) { elm1 = elm; return true; } //si el slot1 esta sin usar y el 2do no coincide
        if (elm1 != elm and elm2 == -1) { elm2 = elm; return true; } //si el slot2 esta sin usar y el 1ro no coincide
        return false;
    }
    //True si node1==n1 y node2==n2 y elm1==elm (si la arista tiene los nodos pasados en el mismo orden y elm1 es igual al elemento por parametro)
    //Notar que aqui SI importa el orden de las aristas y los parametros
    bool EqualityByElement(int n1, int n2, int elm) {
        return ((this->node1 == n1 and this->node2 == n2) and (this->elm1 == elm or this->elm2 == elm));
    }
};

//Lista de aristas del modelo. Para cada arista tiene los nodos que la componen y los elementos que esta arista separa. 
struct ListOfEdges { 
    std::vector<Edge> edges; 
    unsigned int edgesCount; //cantidad de aristas reales
    ListOfEdges() : edgesCount(0) {}
   
    //True si la arista ya estaba. Si estaba, intenta agregar el elemento.
    bool HasEdge(Edge &eg, int elm) {
        for (unsigned int i = 0; i < this->edgesCount; i++) {
            if (this->edges[i] == eg) { 
                //Si lo tenia, aun podemos actualizar la informacion de elementos
                this->edges[i].AddElement(elm); //Notar que no se esta usando el retval de AddElement
                return true;
            }
        }
        return false;
    }

    //Inserta una arista con un elemento. Si la arista no estaba, le agrega el elemento. 
    bool Insert(Edge &eg, int elm = -1) {
        if (not this->HasEdge(eg, elm)) {
            eg.AddElement(elm); //Notar que no se esta usando el retval de AddElement
            this->edges.push_back(eg);
            this->edgesCount++;
            return true;
        } else return false;
    }

    void Init(unsigned int spaceToReserve) {
        this->edges.clear();
        this->edgesCount = 0;
        this->edges.reserve(spaceToReserve); //se reserva el espacio para evitar redimensionado
    }

    //Devuelve el vecino de un elemento por una arista en particular
    void GetOther(int n1, int n2, int elm, int &other) {
        for (unsigned int i = 0; i < this->edgesCount; ++i) {
             if (this->edges[i].EqualityByElement(n1, n2, elm) ) {
                other = this->edges[i].elm2;
                return;
             }
             if (this->edges[i].EqualityByElement(n2, n1, elm) ) {
                other = this->edges[i].elm1;
                return;
             } 
        }
    }

    //Devuelve los vecinos del elemento elm, buscando la informacion de aristas
    void GetNeighborsOfElement(int elm, int neighbors_of_elm[3]) {
        unsigned int current = 0;
        neighbors_of_elm[0] = neighbors_of_elm[1] = neighbors_of_elm[2] = -1;
        for (unsigned int i = 0; i < this->edgesCount; ++i) {
            Edge &eg = this->edges[i];
            if (eg.elm1 == elm) {
                neighbors_of_elm[current] = eg.elm2;
                ++current;
            } else if (eg.elm2 == elm) {
                neighbors_of_elm[current] = eg.elm1;
                ++current;
            }
            if (current == 3 ) return; //ya se encontraron los 3 vecinos
        }
    }
};

class Model {
    public:
    std::string file;

    //Informacion del modelo
    struct aiMesh* mesh;
    unsigned int numFaces; 
    unsigned int numIndices;
    unsigned int numVertices;
    unsigned int numVerticesPerFace;        //Se supone que son todos iguales
    unsigned int maxNeighborsPerNode;       

    //Informacion de estado
    bool hasNeighborsPerNode;               //True si se construyo la informacion de vecindad de nodos (neighborsPerNode)
    bool hasNeighborsNormalsPerNode;        //True si se construyo neighborsNormalsPerNode
    bool hasNeighborsPerElement;            //True se construyo neighborsPerElement
    bool hasNeighborsNormalsPerElement;     //True si se construyo neighborsNormalsPerElement
    bool hasBoundingBox;                    //True si la bounding box esta calculada
    bool hasAdjacencies;                    //True si se tiene informacion de los vecinos por arista (listOfEdges)
    bool hasExtended;                       //True si tiene data extendida (vecinos de cada triangulo)
 
    //Informacion sobre la Bounding Box (alineada con el eje: Axis Aligned Bounding Box)
    std::vector<float> bb;                  //Coordenadas de la bounding box
    std::vector<unsigned int> bbIndices;    //Indices para dibujar la bounding box
    glm::vec3 bbMin;                        //Extremo menor (minimo en x,y,z)
    glm::vec3 bbMax;                        //Extremo mayor (maximo en x,y,z)

    std::vector<float> vertices;
    std::vector<unsigned int> indices;      //Indices de los elementos
    std::vector<unsigned int> indicesExtended;//Indices de los elementos con los vecinos
    std::vector<float> normals;             //Normales por nodo
    std::vector<float> texCoords;           //Coordenada de textura por nodo
    std::vector<std::vector<unsigned int> > neighborsPerNode;   //Lista (indices de nodos) de vecinos por nodo
    std::vector<float> neighborsNormalsPerNode;                 //Lista (valores) de las normales vecinas de cada nodo
    std::vector<float> neighborsNormalsPerElement[3];           //Lista (valores) de las normales vecinas de cada elemento (son 3 vectores, uno para cada vecino:0, 1 y 2)
    int (*neighborsPerElement)[3]; //Lista (indices de elementos) de los vecinos de cada elemento por cada cara (-1 si no esta el vecino)

    ListOfEdges edges; //lista de aristas


    Model();
    void Init(std::string filename, unsigned int numverticesface); 
    Model (std::string filename, unsigned int numverticesface, bool extended = false);
    ~Model();
    bool ImportModel( std::string filename);
   
    //Utilidades para el calculo de informacion de vecindario por nodos
    std::vector<unsigned int> GetNeighborsOfNode(unsigned int nodi);
    void GenNeighborsPerNode();
    void PrintNeighborsPerNode();
    bool LoadNeighborsPerNode(std::string filename);

    //Utilidades para el calculo de informacion de vecindario por elementos
    void GenAdjacencies();
    void GenNeighborsOfElements();

    bool BuildNeighborsNormalsPerNode();
    bool BuildNeighborsNormalsPerElement();

    //Utilidades para el calculo de la bounding box
    float GetMaximumCoord(unsigned int coord);
    float GetMinimumCoord(unsigned int coord);
    void CalculateBoundingBox();
    void GetBoundingBox(std::vector<float> &bb);

    void GenExtendedData();
    unsigned int GetNumIndices();
};
#endif
