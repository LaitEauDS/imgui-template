#pragma once
#include "Piece.hpp"
#include <vector>

class Rook : public Piece {
public:
    Rook(Color color);
    std::vector<int> get_possible_moves(int position, const std::array<Piece*, 64>& board) const;
    char get_symbol() const;
};
