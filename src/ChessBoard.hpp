#pragma once
#include <imgui.h>
#include <array>
#include "Piece.hpp"


class ChessBoard{
    private:
    std::array<std::unique_ptr<Piece>, 64> m_board;
    Color m_current_color = Color::White;

    public:
    ChessBoard();
    void display_board();
};
