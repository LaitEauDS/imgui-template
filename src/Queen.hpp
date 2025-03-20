#pragma once
#include "Piece.hpp"

class Queen : public Piece {
public:
    Queen(Color color);
    std::vector<int> get_possible_moves(int position, const std::array<Piece*, 64>& board) const;
    char get_symbol() const;
};
