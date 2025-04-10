#pragma once
#include <unordered_map>
#include "Model3D.hpp"
#include "chess2D/Piece.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "renderer3D/utils.hpp"

//m_pieces
//{PAWN : {matrice_1, matrice_2,...}, BISHOP : {matrice_1, matrice_2,...},.....}


class Model3DManager{
    public:
    void clear_pieces_positions_in_board();
    void init_pieces_positions_in_board(std::array<std::unique_ptr<Piece>, 64>& board);
    void load_all_meshes();
    void render(glmax::Shader& shader) const;
    private:
        Model3D m_chessboard;
        std::unordered_map<PieceType, Model3D> m_pieces;
};

