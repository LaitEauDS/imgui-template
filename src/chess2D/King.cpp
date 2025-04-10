#include "King.hpp"
#include "Piece.hpp"

King::King(Color color) : Piece(color, PieceType::King) {}

std::vector<int> King::get_possible_moves(int position, const std::array<Piece*, 64>& board) const {
    std::vector<int> moves;
    int row = position / 8;
    int col = position % 8;

    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, 
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} 
    };

    for (const auto& dir : directions) {
        int newRow = row + dir.first;
        int newCol = col + dir.second;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            int newPos = newRow * 8 + newCol;

            if (!board[newPos] || board[newPos]->get_color() != m_color) {
                moves.push_back(newPos);
            }
        }
    }

    return moves;
}

char King::get_symbol() const {
    return (m_color == Color::White) ? 'K' : 'k';
}
