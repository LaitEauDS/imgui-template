#include "utils.hpp"

glm::vec2 from_index_to_2D_pos(int index) 
{
    return {index % 8, index / 8};
}

glm::vec3 from_2D_pos_to_3D_pos(glm::vec2 position)
{
    return {position.x - 3.5, 0.0f, position.y - 3.5f};
}