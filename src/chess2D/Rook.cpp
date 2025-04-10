#include "Rook.hpp"
#include "Piece.hpp"

Rook::Rook(Color color) : Piece(color,PieceType::Rook) {}

std::vector<int> Rook::get_possible_moves(int position, const std::array<Piece*, 64>& board) const {
    std::vector<int> moves;
    int row = position / 8;
    int col = position % 8;

    // top
    for (int x = row - 1; x >= 0; x--) {
        int newPos = x * 8 + col;
        if (board[newPos]) {
            if (board[newPos]->get_color() != this->get_color()) moves.push_back(newPos);
            break;
        }
        moves.push_back(newPos);
    }

    // bottom
    for (int x = row + 1; x < 8; x++) {
        int newPos = x * 8 + col;
        if (board[newPos]) {
            if (board[newPos]->get_color() != this->get_color()) moves.push_back(newPos);
            break;
        }
        moves.push_back(newPos);
    }

    // left
    for (int c = col - 1; c >= 0; --c) {
        int newPos = row * 8 + c;
        if (board[newPos]) {
            if (board[newPos]->get_color() != this->get_color()) moves.push_back(newPos);
            break;
        }
        moves.push_back(newPos);
    }

    // right
    for (int c = col + 1; c < 8; ++c) {
        int newPos = row * 8 + c;
        if (board[newPos]) {
            if (board[newPos]->get_color() != this->get_color()) moves.push_back(newPos);
            break;
        }
        moves.push_back(newPos);
    }

    return moves;
}

char Rook::get_symbol() const {
    return (m_color == Color::White) ? 'R' : 'r';
}
