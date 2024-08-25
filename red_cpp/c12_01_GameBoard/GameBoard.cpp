#include <stdexcept>
#include <utility>
#include <format>
#include <iostream>

#include "GameBoard.h"


using namespace std;

GameBoard::GameBoard(size_t width, size_t height) : m_width{width}, m_height{height}
{
    std::cout << "GameBoard(size_t width, size_t height) start" << std::endl;

    m_cells.resize(m_width);
    for(auto& column : m_cells){
        column.resize(m_height);
    }
}

GameBoard::GameBoard(const GameBoard& src)
        : GameBoard{ src.m_width, src.m_height }
{
    // The ctor-initializer of this constructor delegates first to the
    // non-copy constructor to allocate the proper amount of memory.

    // The next step is to copy the data.
    for (size_t i{ 0 }; i < m_width; i++) {
        for (size_t j{ 0 }; j < m_height; j++) {
            if (src.m_cells[i][j])
                m_cells[i][j] = src.m_cells[i][j]->clone();
        }
    }
}

void GameBoard::verifyCoordinate(size_t x, size_t y) const
{
    if (x >= m_width) {
        //throw std::out_of_range { std::format("{} must be less than {}.", x, m_width) };
        std::cout << x << "must be less than " << m_width << std::endl;
    }
    if (y >= m_height) {
        //throw std::out_of_range { std::format("{} must be less than {}.", y, m_height) };
        std::cout << y << "must be less than " << m_height << std::endl;
    }
}

void swap(GameBoard& first, GameBoard& second) noexcept
{
    first.swap(second);
}


void GameBoard::swap(GameBoard& other) noexcept
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

GameBoard& GameBoard::operator=(const GameBoard& rhs)
{
    // Copy-and-swap idiom
    GameBoard temp{ rhs }; // Do all the work in a temporary instance
    swap(temp);   // Commit the work with only non-throwing operations
    return *this;
}

const unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y) const
{
    std::cout<< "GameBoard::at(size_t x, size_t y) 11 const start" << std::endl;
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y)
{
    std::cout<< "GameBoard::at(size_t x, size_t y) 22 start" << std::endl;
    return const_cast<unique_ptr<GamePiece>&>(as_const(*this).at(x, y));
}