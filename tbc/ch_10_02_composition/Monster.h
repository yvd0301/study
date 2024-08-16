//
// Created by davidlee on 2024/08/16.
//

#ifndef CH_10_02_COMPOSITION_MONSTER_H
#define CH_10_02_COMPOSITION_MONSTER_H

#include <iostream>
#include <string>
#include "Position2D.h"


class Monster{
private:
    std::string m_name;
    Position2D m_location;
public:

    Monster(const std::string name_in, const Position2D &pos_in)
        : m_name(name_in), m_location(pos_in)
    {

    }

    void moveTo(const Position2D & pos_target)
    {
        m_location.set(pos_target);
    }

    friend std::ostream & operator << (std::ostream & out, const Monster & monster)
    {
        out << monster.m_name << " " << monster.m_location;
        return out;
    }
};



#endif //CH_10_02_COMPOSITION_MONSTER_H
