#include "Bishop.hpp"
#include "Piece.hpp"

Bishop::Bishop(Color color) : Piece(color, PieceType::Bishop) {}

std::vector<int> Bishop::get_possible_moves(int position, const std::array<Piece*, 64>& board) const {
    std::vector<int> moves;
    int row = position / 8;
    int col = position % 8;

    std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& dir : directions) {
        int newRow = row;
        int newCol = col;

        while (true) {
            newRow += dir.first;
            newCol += dir.second;

            if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) {
                break;
            }

            int newPos = newRow * 8 + newCol;

            if (board[newPos]) {
                if (board[newPos]->get_color() != m_color) {
                    moves.push_back(newPos);
                }
                break;
            }

            moves.push_back(newPos);
        }
    }

    return moves;
}

char Bishop::get_symbol() const {
    return (m_color == Color::White) ? 'B' : 'b';
}
