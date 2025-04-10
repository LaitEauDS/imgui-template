#include "Model3DManager.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

//Nettoyer les positions (model matrices) des pièces sur l'échiquier avant chaque mise à jour
void Model3DManager::clear_pieces_positions_in_board()
{
    for (auto& [type, model] : m_pieces)
    {
        model.clear_data();
    }
}

//On initialise la modèle matrice de l'échiquier
void Model3DManager::init_chessboard()
{
    m_chessboard.push_data({.model_matrix = glm::mat4(1.0f)});
}

// On initialise les modèles matrices de chaque pièce sur l'échiquier (Pion = 16, Fou = 4, Cavalier = 4, Tour = 4, Dame = 2, Roi = 2)
void Model3DManager::init_pieces_positions_in_board(std::array<std::unique_ptr<Piece>, 64>& board)
{
    clear_pieces_positions_in_board();

    for (int i{0}; i < board.size(); i++)
    {
        // Si la case contient une pièce, on lui attribue une matrice modèle.
        if (board[i])
        {
            PieceType piece_type    = board[i]->get_type();
            Color     piece_color   = board[i]->get_color();
            glm::vec2 position2D    = from_index_to_2D_pos(i);
            glm::vec3 position3D    = from_2D_pos_to_3D_pos(position2D);
            glm::mat4 piece_matrice = glm::translate(glm::mat4(1.0f), position3D);
            //
            m_pieces[piece_type].push_data({.index_board = i, .model_matrix = piece_matrice, .color = piece_color});
        }
    }
}

// Charger tous les modèles (mesh) pour les pièces et l'échiquier
void Model3DManager::load_all_meshes()
{
    // Charge le mesh de l'échiquier (1 fois uniquement à l'initialisation)
    m_chessboard.load_mesh("chessboard/chessboard.obj", "chessboard");
    m_chessboard.setup_buffers();

    //Charger tous les meshs des pièces (6 fois uniquement à l'initialisation)
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

        //Après avoir chargé le mesh, on configure les buffers (VBO, EBO, VAO) pour chaque pièce
        model.setup_buffers();
    }
}

//On bouge la pièce (on met à jour sa matrice modèle) en fonction de sa nouvelle position 3D
void Model3DManager::move_piece(PieceType piece_type, glm::vec3 new_pos, int index)
{
    m_pieces[piece_type].move(new_pos, index);
}


//On render l'échiquier et toutes les pièces
void Model3DManager::render(glmax::Shader& shader) const
{
    // render chessboard
    m_chessboard.render(shader);
    // render pieces
    for (const auto& [type, model] : m_pieces)
    {
        model.render(shader);
    }
}