#pragma once
#include <imgui.h>
#include <array>
#include <memory>
#include "Piece.hpp"


class ChessBoard{
    private:
    std::array<std::unique_ptr<Piece>, 64> m_board;
    int m_selectedPieceIndex;
    Color m_current_color = Color::White;
    ImFont* m_chessFont = nullptr;
    

    public:
    ChessBoard();
    void display_board();
    void setFont(ImFont* font) { m_chessFont = font; }
};
