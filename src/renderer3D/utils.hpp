#pragma once
#include <glm/glm.hpp>

//fonction qui conv un index en position 2D
glm::vec2 from_index_to_2D_pos(int index) ;

//fonction qui conv une position 2D en position 3D (dans le monde)
glm::vec3 from_2D_pos_to_3D_pos(glm::vec2 position);
