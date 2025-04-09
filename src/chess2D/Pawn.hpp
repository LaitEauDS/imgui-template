#pragma once
#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Color color);
    std::vector<int> get_possible_moves(int position, const std::array<Piece*, 64>& board) const;
    char get_symbol() const;
};
