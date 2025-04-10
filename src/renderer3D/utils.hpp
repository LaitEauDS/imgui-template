#pragma once
#include <glm/glm.hpp>
#include "chess2D/Piece.hpp"

struct ModelData{
    int index_board;
    glm::mat4 model_matrix;
    Color color;
};

//fonction qui conv un index en position 2D
glm::vec2 from_index_to_2D_pos(int index) ;

//fonction qui conv une position 2D en position 3D (dans le monde)
glm::vec3 from_2D_pos_to_3D_pos(glm::vec2 position);

//fonction qui conv une "Color" en "glm::vec3"
glm::vec3 color_to_vec3(Color color);
