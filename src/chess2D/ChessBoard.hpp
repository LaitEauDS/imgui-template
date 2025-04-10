#pragma once
#include <imgui.h>
#include <array>
#include <memory>
#include <optional>
#include "Piece.hpp"

struct Move {
    PieceType piece_type_to_move;
    int from;
    int to;
};

class ChessBoard {
private:
    std::array<std::unique_ptr<Piece>, 64> m_board;
    //
    int         m_selectedPieceIndex;
    Color       m_current_color      = Color::White;
    ImFont*     m_chessFont          = nullptr;
    bool        m_gameOver           = false;
    std::string m_winnerMessage      = "";
    bool        m_showVictoryPopup   = false;
    bool        m_showPromotionPopup = false;
    int         m_pawnToPromoteIndex = -1;
    Color       m_promotionColor;
    //Move for renderer 3D
    std::optional<Move> m_move = std::nullopt;

public:
    ChessBoard();
    void                                    display_board();
    void                                    setFont(ImFont* font) { m_chessFont = font; }
    std::array<std::unique_ptr<Piece>, 64>& get_board() { return m_board; };
    std::optional<Move>                    &get_move() { return m_move; };
    
};
