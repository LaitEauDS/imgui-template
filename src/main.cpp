#include <imgui.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Camera.hpp"
#include "chess2D/ChessBoard.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "renderer3D/Model3DManager.hpp"

int main()
{
    int           window_width  = 1280;
    int           window_height = 720;
    //renderer3D
    glmax::Shader shader;
    glmax::Camera camera{true};
    //


    //chess2D
    ChessBoard chessboard{};
    //renderer3D
    Model3DManager model_manager;

    

    quick_imgui::loop(
        "Quick ImGui",
        {
            .init                     = [&]() { 
            std::cout << "Init\n";
            //Chess2D
                            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.Fonts->AddFontDefault();
            ImFont* chessFont = io.Fonts->AddFontFromFileTTF("../../assets/fonts/MVALFONT.ttf", 48.0f);
            ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);                  
            chessboard.setFont(chessFont);

            //Renderer3D
            shader.load_shader("model.vs.glsl", "model.fs.glsl");
            model_manager.init_chessboard();
            model_manager.init_pieces_positions_in_board(chessboard.get_board());
            model_manager.load_all_meshes();  
        },
        .loop                     = [&]() {  
            model_manager.init_pieces_positions_in_board(chessboard.get_board());
                //chess2D

            ImGui::Begin("Lait-Eau's ChessGame");
            chessboard.display_board();
            ImGui::End();



                //renderer3D
                glClearColor(0.847f, 0.82f, 0.929f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                //
                glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                shader.use();
                
                //VP
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);

                //LIGHT SETTINGS
                shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                
                //CAMERA SETTINGS
                shader.set_uniform_3fv("viewPos", camera.get_position());
                //UPDATE POSITIONS

                //MODEL RENDER
                model_manager.render(shader);
               
        },
            .key_callback             = [&](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .mouse_button_callback    = [&](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            .cursor_position_callback = [&](double xpos, double ypos) { camera.track_ball_move_callback(xpos, ypos); },
            .scroll_callback          = [&](double xoffset, double yoffset) { camera.process_scroll(yoffset); },
            .window_size_callback     = [&](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}