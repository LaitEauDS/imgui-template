#include "ChessBoard.hpp"
#include "Pawn.hpp"
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include <string>

ChessBoard::ChessBoard()
{
    //placement temporaire des pions
    for (int i = 8; i < 16; i++)
        m_board[i] = std::make_unique<Pawn>(Color::White);
    for (int i = 48; i < 56; i++)
        m_board[i] = std::make_unique<Pawn>(Color::Black);
}

void ChessBoard::display_board()
{
    ImVec4 whiteColor = ImVec4(234.0f / 255.0f, 233.0f / 255.0f, 210.0f / 255.0f, 1.0f); // #EAE9D2
    ImVec4 blackColor = ImVec4(75.0f / 255.0f, 115.0f / 255.0f, 153.0f / 255.0f, 1.0f);  // #4B7399
    ImVec4 hoverColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            int index = x * 8 + y;
            ImGui::PushID(index);

            ImVec4 backgroundColor = ((x + y) % 2 == 0) ? whiteColor : blackColor;
            ImGui::PushStyleColor(ImGuiCol_Button, backgroundColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);

            if (m_board[index])
            {
                std::string label = "P";
                if (ImGui::Button(label.c_str(), ImVec2{70.f, 70.f})) // à remplacer par un switch case sur le type
                {
                    std::cout << "Position : " << index << "\n";
                }
            }
            else
            {
                ImGui::Button(" ", ImVec2{70.f, 70.f});
            }

            ImGui::PopStyleColor(2);
            if (y != 7)
                ImGui::SameLine();
            ImGui::PopID();
        }
    }
}