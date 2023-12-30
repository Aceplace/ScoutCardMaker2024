#pragma once
#include "utils.h"

#include <stdexcept>
#include <sstream>
#include <cassert>

namespace SCM24
{

Vector2 get_mirrored_x_vector_if(Vector2 value, bool mirror_x)
{
    value.x = mirror_x ? value.x * -1 : value.x;
    return value;
}

Player& get_player_with_tag(std::vector<Player>& players, PlayerTag player_tag)
{
    for (Player& player: players)
    {
        if (player.player_tag == player_tag)
        {
            return player;
        }
    }
    
    std::ostringstream err_msg;
    err_msg << "Player tag " << static_cast<int>(player_tag) << " doesn't appear in the list of players";
    throw std::invalid_argument(err_msg.str());
}

bool point_in_ellipse(Vector2 pos, Vector2 pos_ellipse_center, float a, float b)
{
    return (((pos.x - pos_ellipse_center.x) * (pos.x - pos_ellipse_center.x)) / (a * a)) +
        (((pos.y - pos_ellipse_center.y) * (pos.y - pos_ellipse_center.y)) / (b * b)) <= 1;
}

}