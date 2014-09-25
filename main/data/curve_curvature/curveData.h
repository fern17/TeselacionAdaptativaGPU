namespace CC {
//Puntos de control de la curva
float CurveVertices[][3] = { {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 1.0, 0.0}, {1.0, 1.0, 0.0} };
//Indices para dibujar la curva
unsigned int CurveIndices[][4] = {{0, 1, 2, 3}};
//Indices para dibujar el poligono de control
unsigned int PolyIndices[][2] = {{0, 1}, {1, 2}, {2, 3} };
//Indices para dibujar los puntos de control
unsigned int PointIndices[][1] = {{0}, {1}, {2}, {3}};

//Punto donde esta el parametro actual
float CurrentParameter[][3] = { {0.0, 0.0, 0.0} };
//Color del parametro actual
unsigned int CurrentParameterIndices[][1] = { {0} };
}
