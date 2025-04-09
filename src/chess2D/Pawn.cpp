#include "Pawn.hpp"
#include "Piece.hpp"

Pawn::Pawn(Color color) : Piece(color, PieceType::Pawn) {}

std::vector<int> Pawn::get_possible_moves(int position, const std::array<Piece*, 64>& board) const {
    std::vector<int> moves;
    int direction = (m_color == Color::White) ? -8 : 8;

    int forward = position + direction;

    if (forward >= 0 && forward < 64 && board[forward] == nullptr) {
        moves.push_back(forward);

        int startRow = (m_color == Color::White) ? 6 : 1;
        int doubleForward = position + 2 * direction;
        if (position / 8 == startRow && board[doubleForward] == nullptr) {
            moves.push_back(doubleForward);
        }
    }

    int leftCapture = position + direction - 1;
    if (leftCapture >= 0 && leftCapture < 64 && (position % 8 != 0) && board[leftCapture] != nullptr && board[leftCapture]->get_color() != m_color) {
        moves.push_back(leftCapture);
    }

    int rightCapture = position + direction + 1;
    if (rightCapture >= 0 && rightCapture < 64 && (position % 8 != 7) && board[rightCapture] != nullptr && board[rightCapture]->get_color() != m_color) {
        moves.push_back(rightCapture);
    }

    return moves;
}

char Pawn::get_symbol() const {
    return (m_color == Color::White) ? 'P' : 'p';
}
