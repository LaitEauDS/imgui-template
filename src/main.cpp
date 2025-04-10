#include <imgui.h>
#include <glm/glm.hpp>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"
#include "renderer3D/Renderer.hpp"

int main()
{
    // renderer3D
    Renderer renderer{};
    // chessgame2D
    ChessBoard chessboard{};
    //
    quick_imgui::loop(
        "Quick ImGui",
        {
            .init = [&]() { 
            // chess2D
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.Fonts->AddFontDefault();
            ImFont* chessFont = io.Fonts->AddFontFromFileTTF("../../assets/fonts/MVALFONT.ttf", 48.0f);
            ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);
            chessboard.setFont(chessFont);
            // renderer3D
            renderer.init(chessboard.get_board()); },
            .loop = [&]() {
                 // chess2D
                ImGui::Begin("Lait-Eau's ChessGame");
                chessboard.display_board();
                ImGui::End();
                // renderer3D
                renderer.update(chessboard.get_board());
                renderer.render();
            },
            .key_callback             = [&](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .mouse_button_callback    = [&](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            .cursor_position_callback = [&](double xpos, double ypos) { renderer.cursor_position_callback(xpos, ypos); },
            .scroll_callback          = [&](double xoffset, double yoffset) { renderer.scroll_callback(xoffset, yoffset); },
            .window_size_callback     = [&](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}