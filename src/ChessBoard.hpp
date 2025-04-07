#pragma once
#include <imgui.h>
#include <array>
#include <memory>
#include "Piece.hpp"


class ChessBoard{
    private:
    std::array<std::unique_ptr<Piece>, 64> m_board;
    int m_selectedPieceIndex;
    Color m_current_color = Color::White;
    ImFont* m_chessFont = nullptr;
    bool m_gameOver = false;
    std::string m_winnerMessage = "";
    bool m_showVictoryPopup = false;
    bool m_showPromotionPopup = false;
    int m_pawnToPromoteIndex = -1;
    Color m_promotionColor;  

    public:
    ChessBoard();
    void display_board();
    void setFont(ImFont* font) { m_chessFont = font; }
};
