#include "Knight.hpp"
#include "Piece.hpp"

Knight::Knight(Color color) : Piece(color, PieceType::Knight) {}

std::vector<int> Knight::get_possible_moves(int position, const std::array<Piece*, 64>& board) const {
    std::vector<int> moves;
    int row = position / 8;
    int col = position % 8;

    std::vector<std::pair<int, int>> knightMoves = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (const auto& move : knightMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            int newPos = newRow * 8 + newCol;
            if (!board[newPos] || board[newPos]->get_color() != m_color) {
                moves.push_back(newPos);
            }
        }
    }

    return moves;
}

char Knight::get_symbol() const {
    return (m_color == Color::White) ? 'N' : 'n';
}
