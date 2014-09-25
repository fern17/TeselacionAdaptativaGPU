namespace TD {
    float TriangleVertices[][3] = { {0.25, 0.3, 0.0}, {0.75, 0.3, 0.0}, {0.5, 0.7, 0.0} };
    unsigned int TriangleIndices[][3] = {{0, 1, 2}};

    float QuadVertices[][3] = { {0.3, 0.3, 0.0},  {0.3, 0.7, 0.0}, {0.7, 0.7, 0.0}, {0.7, 0.3, 0.0},};
    unsigned int QuadIndices[][4] = {{0, 1, 2, 3}};
    
    float LineVertices[][3] = { {0.3, 0.3, 0.0}, {0.7, 0.3, 0.0}, {0.3, 0.7, 0.0}, {0.7, 0.7, 0.0}};
    unsigned int LineIndices[][4] = {{0, 1, 2, 3}};

    float points[][3] = { {0.3,0.3,0}, {0.3, 0.7, 0}, {0.7, 0.3, 0}, {0.7, 0.7, 0} };
    unsigned int points_indices[][1] = { {0}, {1}, {2}, {3} };
}
