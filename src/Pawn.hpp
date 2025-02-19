#pragma once
#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color, PieceType::Pawn) {}
    std::vector<int> get_possible_moves(int position)
    {
        std::vector<int> moves;
        int direction = (m_color == Color::White) ? -8 : 8;
        moves.push_back(position + direction);
        return moves;
    }
};