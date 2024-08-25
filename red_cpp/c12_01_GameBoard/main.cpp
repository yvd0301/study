#include <iostream>
#include <memory>
#include <utility>
#include "GameBoard.h"

class ChessPiece: public GamePiece
{
public:
    std::unique_ptr<GamePiece> clone() const override
    {
        std::cout<< "ChessPiece clone() start" << std::endl;
        // Call the copy constructor to copy this instance
        return std::make_unique<ChessPiece>(*this);
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;

    GameBoard chessBoard{8,8};

    auto pawn { std::make_unique<ChessPiece>() };

    chessBoard.at(0, 0) = std::move(pawn);

    chessBoard.at(0,1) = std::make_unique<ChessPiece>();

    chessBoard.at(0,1) = nullptr;

    return 0;
}
