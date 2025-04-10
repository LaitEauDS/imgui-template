#include "Model3DManager.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

void Model3DManager::clear_pieces_positions_in_board()
{
    for (auto& [type, model] : m_pieces)
    {
        model.clear_data();
    }
}

void Model3DManager::init_chessboard()
{
    m_chessboard.push_data({.model_matrix = glm::mat4(1.0f), .color = Color::White});
}

void Model3DManager::init_pieces_positions_in_board(std::array<std::unique_ptr<Piece>, 64>& board)
{
    clear_pieces_positions_in_board();

    for (size_t i{0}; i < board.size(); i++)
    {
        if (board[i])
        {
            PieceType piece_type    = board[i]->get_type();
            Color     piece_color   = board[i]->get_color();
            glm::vec2 position2D    = from_index_to_2D_pos(i);
            glm::vec3 position3D    = from_2D_pos_to_3D_pos(position2D);
            glm::mat4 piece_matrice = glm::translate(glm::mat4(1.0f), position3D);
            //
            m_pieces[piece_type].push_data({.model_matrix = piece_matrice, .color = piece_color});
        }
    }
}

void Model3DManager::load_all_meshes()
{
    // chessboard
    m_chessboard.load_mesh("chessboard/chessboard.obj", "chessboard");
    m_chessboard.setup_buffers();

    // pieces
    for (auto& [type, model] : m_pieces)
    {
        if (type == PieceType::Pawn)
            model.load_mesh("pawn/pawn.obj", "pawn");
        else if (type == PieceType::Bishop)
            model.load_mesh("bishop/bishop.obj", "bishop");
        else if (type == PieceType::Knight)
            model.load_mesh("knight/knight.obj", "knight");
        else if (type == PieceType::Rook)
            model.load_mesh("rook/rook.obj", "rook");
        else if (type == PieceType::Queen)
            model.load_mesh("queen/queen.obj", "queen");
        else if (type == PieceType::King)
            model.load_mesh("king/king.obj", "king");
        model.setup_buffers();
    }
}

void Model3DManager::render(glmax::Shader& shader) const
{
    //render chessboard
    m_chessboard.render(shader);
    //render pieces
    for (const auto& [type, model] : m_pieces)
    {
        model.render(shader);
    }
}