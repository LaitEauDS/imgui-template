#pragma once
#include <iostream>

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum class Color {
    White,
    Black
};

class Piece {
    protected:
    Color m_color;
    PieceType m_type;

    public:
    Piece(Color color, PieceType type) : m_color(color), m_type(type) {}
    ~Piece() = default;

    virtual std::vector<int> get_possible_moves(int position, const std::array<Piece*, 64>& board) const = 0;

    char get_symbol() const;

    Color get_color() const { return m_color; }
    PieceType get_type() const { return m_type; }
};