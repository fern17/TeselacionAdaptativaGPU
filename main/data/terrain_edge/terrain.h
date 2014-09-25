const float terrain_positions[][2] = {
  {0, 0}, 
  {0.25, 0}, 
  {0.5, 0}, 
  {0.75, 0}, 
  {1, 0}, 
  {0, 0.25}, 
  {0.25, 0.25},
  {0.5, 0.25}, 
  {0.75, 0.25}, 
  {1, 0.25}, 
  {0, 0.5}, 
  {0.25, 0.5}, 
  {0.5, 0.5}, 
  {0.75, 0.5}, 
  {1, 0.5}, 
  {0, 0.75}, 
  {0.25, 0.75}, 
  {0.5, 0.75}, 
  {0.75, 0.75}, 
  {1, 0.75}, 
  {0, 1}, 
  {0.25, 1}, 
  {0.5, 1}, 
  {0.75, 1}, 
  {1, 1}
};
const unsigned int terrain_elements[][4] = {
  {0, 5, 6, 1}, 
  {1, 6, 7, 2}, 
  {2, 7, 8, 3}, 
  {3, 8, 9, 4}, 
  {5, 10, 11, 6}, 
  {6, 11, 12, 7}, 
  {7, 12, 13, 8}, 
  {8, 13, 14, 9}, 
  {10, 15, 16, 11}, 
  {11, 16, 17, 12}, 
  {12, 17, 18, 13}, 
  {13, 18, 19, 14}, 
  {15, 20, 21, 16}, 
  {16, 21, 22, 17}, 
  {17, 22, 23, 18}, 
  {18, 23, 24, 19}
};
unsigned int terrain_cant_elementos = 16;
