#pragma once

#include "Camera.hpp"
#include "Shader.hpp"
#include "chess2D/ChessBoard.hpp"
#include "renderer3D/Model3DManager.hpp"
#include "renderer3D/Skybox.hpp"
class Renderer {
public:
    Renderer() = default;
    void init(std::array<std::unique_ptr<Piece>, 64>& board);
    void update(std::array<std::unique_ptr<Piece>, 64>& board);
    void render();
    // callbacks
    void cursor_position_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);

private:
    // renderer3D
    Model3DManager model_manager;
    glmax::Camera  camera{true};
    Skybox         skybox{};
    glmax::Shader  skybox_shader;
    glmax::Shader  classic_shader;
};