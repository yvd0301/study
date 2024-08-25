#ifndef CH_12_01_GAMEBOARD_GAMEBOARD_H
#define CH_12_01_GAMEBOARD_GAMEBOARD_H

#include <cstddef>
#include <vector>
#include <memory>

class GamePiece
{
public:
    virtual ~GamePiece() = default;
    virtual std::unique_ptr<GamePiece> clone() const = 0;
};

class GameBoard
{
public:
    explicit GameBoard(size_t width = DefaultWidth, size_t height = DefaultHeight);

    GameBoard(const GameBoard& src); // copy constructor
    virtual ~GameBoard() = default; // virtual default destructor

    GameBoard& operator=(const GameBoard& rhs); // assignment operator 대입 연산자

    // 이동 생성자와 대입 연산자를 명시적으로 디폴트로 지정한다.
    GameBoard(GameBoard&& src) = default;
    GameBoard& operator=(GameBoard&& src) = default;

    std::unique_ptr<GamePiece>& at(size_t x, size_t y);
    const std::unique_ptr<GamePiece>& at(size_t x, size_t y) const;

    size_t getHeight() const { return m_height; }
    size_t getWidth() const { return m_width; }

    static const size_t DefaultWidth{ 10 };
    static const size_t DefaultHeight{10};

    void swap(GameBoard& other) noexcept;

private:

    void verifyCoordinate(size_t x, size_t y) const;

    std::vector< std::vector<std::unique_ptr<GamePiece> > > m_cells;
    size_t m_width {0}, m_height{0};

};
//export void swap(GameBoard& first, GameBoard& second) noexcept;

#endif //CH_12_01_GAMEBOARD_GAMEBOARD_H
