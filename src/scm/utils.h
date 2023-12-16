#pragma once
#include <raylib.h>
#include "common.h"
#include <vector>
#include <stdexcept>
#include <sstream>

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

}