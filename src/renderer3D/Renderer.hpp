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
    void update(std::array<std::unique_ptr<Piece>, 64>& board, std::optional<Move> &move);
    void render();
    // callbacks
    void cursor_position_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);
    void key_callback(int key, int scancode, int action, int mods);

private:
    // renderer3D
    Model3DManager model_manager;
    glmax::Camera  camera{true};
    Skybox         skybox{};
    glmax::Shader  skybox_shader;
    glmax::Shader  classic_shader;
    double start_animation_time = 0.0f;
    double end_animation_time   = 1.0f;
};