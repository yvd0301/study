#ifndef CH_10_02_COMPOSITION_POSITION2D_H
#define CH_10_02_COMPOSITION_POSITION2D_H

#include <iostream>

class Position2D
{
private:
    int m_x;
    int m_y;

public:
    Position2D(const int & x_in, const int & y_in)
            : m_x(x_in), m_y(y_in)
    {

    }
    // TODO: overload operator =

    void set(const int & x_target, const int & y_target)
    {
        m_x = x_target;
        m_y = y_target;
    }

    void set(const Position2D & pos_target)
    {
        set(pos_target.m_x, pos_target.m_y);
        // m_x = pos_target.m_x;
        // m_y = pos_target.m_y;
    }

    friend std::ostream & operator << (std::ostream & out, const Position2D &pos)
    {
        out << pos.m_x << " " << pos.m_x;
        return out;
    }
};

#endif //CH_10_02_COMPOSITION_POSITION2D_H
