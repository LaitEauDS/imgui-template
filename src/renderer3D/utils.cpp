#include "utils.hpp"

glm::vec2 from_index_to_2D_pos(int index) 
{
    return {index % 8, index / 8};
}

glm::vec3 from_2D_pos_to_3D_pos(glm::vec2 position)
{
    return {position.x - 3.5, 0.0f, position.y - 3.5f};
}

glm::vec3 color_to_vec3(Color color)
{
    if (color == Color::White)
        return {1.0f, 1.0f, 1.0f};
    else if (color == Color::Black)
        return {0.0f, 0.0f, 0.0f};
    return {1.0f, 1.0f, 1.0f};
}