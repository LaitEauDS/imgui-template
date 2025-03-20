#pragma once
#include "Piece.hpp"

class Knight : public Piece {
public:
    Knight(Color color);
    std::vector<int> get_possible_moves(int position, const std::array<Piece*, 64>& board) const;
    char get_symbol() const;
};
