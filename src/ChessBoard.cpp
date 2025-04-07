#include "ChessBoard.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include <string>

ChessBoard::ChessBoard() : m_selectedPieceIndex(-1)
{
    //Pions
    for (int i = 8; i < 16; i++)
        m_board[i] = std::make_unique<Pawn>(Color::Black);
    for (int i = 48; i < 56; i++)
        m_board[i] = std::make_unique<Pawn>(Color::White);

    //Tours
    m_board[0] = std::make_unique<Rook>(Color::Black);
    m_board[7] = std::make_unique<Rook>(Color::Black);
    m_board[56] = std::make_unique<Rook>(Color::White);
    m_board[63] = std::make_unique<Rook>(Color::White);

    //Cavaliers
    m_board[1] = std::make_unique<Knight>(Color::Black);
    m_board[6] = std::make_unique<Knight>(Color::Black);
    m_board[57] = std::make_unique<Knight>(Color::White);
    m_board[62] = std::make_unique<Knight>(Color::White);

    // Fous
    m_board[2] = std::make_unique<Bishop>(Color::Black);
    m_board[5] = std::make_unique<Bishop>(Color::Black);
    m_board[58] = std::make_unique<Bishop>(Color::White);
    m_board[61] = std::make_unique<Bishop>(Color::White);

    // Dames
    m_board[3] = std::make_unique<Queen>(Color::Black);
    m_board[59] = std::make_unique<Queen>(Color::White);

    // Rois
    m_board[4] = std::make_unique<King>(Color::Black);
    m_board[60] = std::make_unique<King>(Color::White);
}

void ChessBoard::display_board()
{
    ImVec4 whiteColor = ImVec4(238.0f / 255.0f, 238.0f / 255.0f, 212.0f / 255.0f, 1.0f); // #EEEED4
    ImVec4 blackColor = ImVec4(86.0f / 255.0f, 151.0f / 255.0f, 147.0f / 255.0f, 1.0f);  // #569793
    ImVec4 hoverColor = ImVec4(23.0f / 255.0f, 229.0f / 255.0f, 135.0f / 255.0f, 1.0f); // #17E587
    ImVec4 selectedColor = ImVec4(255.0f / 255.0f, 217.0f / 255.0f, 102.0f / 255.0f, 1.0f); // Jaune pour la sélection
    ImVec4 moveHighlightColor = ImVec4(50.0f / 255.0f, 205.0f / 255.0f, 50.0f / 255.0f, 1.0f); // Vert pour les mouvements

    std::array<Piece*, 64> boardPtrs{};
    for (size_t i = 0; i < 64; ++i) {
        boardPtrs[i] = m_board[i] ? m_board[i].get() : nullptr;
    }

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            int index = x * 8 + y;
            ImGui::PushID(index);

            std::vector<int> possibleMoves;
            if (m_selectedPieceIndex != -1 && m_board[m_selectedPieceIndex]) {
                possibleMoves = m_board[m_selectedPieceIndex]->get_possible_moves(m_selectedPieceIndex, boardPtrs);
            }

            ImVec4 backgroundColor = ((x + y) % 2 == 0) ? whiteColor : blackColor;

            if (std::find(possibleMoves.begin(), possibleMoves.end(), index) != possibleMoves.end()) {
                backgroundColor = moveHighlightColor;
            }

            if (index == m_selectedPieceIndex) {
                backgroundColor = selectedColor;
            }

            ImGui::PushStyleColor(ImGuiCol_Button, backgroundColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);

            std::string label = "";
            ImVec4 textColor = ImVec4(0, 0, 0, 1);
            if (m_board[index])
            {
                switch (m_board[index]->get_type()) {
                    case PieceType::Pawn:
                        label = (m_board[index]->get_color() == Color::White) ? "p" : "o";
                        break;
                    case PieceType::Rook:
                        label = (m_board[index]->get_color() == Color::White) ? "r" : "t";
                        break;
                    case PieceType::Knight:
                        label = (m_board[index]->get_color() == Color::White) ? "n" : "m";
                        break;
                    case PieceType::Bishop:
                        label = (m_board[index]->get_color() == Color::White) ? "b" : "v";
                        break;
                    case PieceType::Queen:
                        label = (m_board[index]->get_color() == Color::White) ? "q" : "w";
                        break;
                    case PieceType::King:
                        label = (m_board[index]->get_color() == Color::White) ? "k" : "l";
                        break;
                    default:
                        label = "";
                        break;
                }
            }
            
            if (m_chessFont) {
                ImGui::PushFont(m_chessFont);
                ImGui::PushStyleColor(ImGuiCol_Text, textColor);
            }

            if (ImGui::Button(label.c_str(), ImVec2{70.f, 70.f})) {
                if (m_board[index] && m_board[index]->get_color() == m_current_color) {
                    m_selectedPieceIndex = index;
                }
                else if (
                    m_selectedPieceIndex != -1 &&
                    std::find(possibleMoves.begin(), possibleMoves.end(), index) != possibleMoves.end()
                ) {
                    m_board[index] = std::move(m_board[m_selectedPieceIndex]);
                    m_selectedPieceIndex = -1;
                
                    m_current_color = (m_current_color == Color::White) ? Color::Black : Color::White;
                }
            }

            if (m_chessFont) {
                ImGui::PopFont();
                ImGui::PopStyleColor();
            }

            ImGui::PopStyleColor(2);
            if (y != 7) 
                ImGui::SameLine();
            ImGui::PopID();
        }
    }
}