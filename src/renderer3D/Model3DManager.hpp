#pragma once
#include <unordered_map>
#include "Model3D.hpp"
#include "chess2D/Piece.hpp"

class Model3DManager {
public:
    //chessboard
    void init_chessboard();
    //pieces
    void clear_pieces_positions_in_board();
    void init_pieces_positions_in_board(std::array<std::unique_ptr<Piece>, 64>& board);
    //models (pieces + chessboard)
    void load_all_meshes();
    void render(glmax::Shader& shader) const;

private:
    Model3D                                m_chessboard;
    std::unordered_map<PieceType, Model3D> m_pieces;
};
