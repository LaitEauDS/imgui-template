#include <imgui.h>
#include "quick_imgui/quick_imgui.hpp"
#include "ChessBoard.hpp"


int main()
{
    ChessBoard chessboard{};

    quick_imgui::loop(
        "ChessGame",
        /* init: */ [&]() {
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.Fonts->AddFontDefault();
            ImFont* chessFont = io.Fonts->AddFontFromFileTTF("/Users/leode/Desktop/Dossier cours/IMAC2/imgui-template/src/fonts/MVALFONT.ttf", 48.0f);
            ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);

            chessboard.setFont(chessFont);
        },
        /* loop: */
        [&]() {
            ImGui::Begin("Lait-Eau's ChessGame");
            chessboard.display_board();
            ImGui::End();
        }
    );
}