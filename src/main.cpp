#include <imgui.h>
#include "quick_imgui/quick_imgui.hpp"
#include "ChessBoard.hpp"


int main()
{
    ChessBoard chessboard{};

    quick_imgui::loop(
        "ChessGame",
        /* init: */ [&]() {
            ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);
        },
        /* loop: */
        [&]() {
            ImGui::Begin("Lait-Eau's ChessGame");
            chessboard.display_board();
            ImGui::End();
        }
    );
}