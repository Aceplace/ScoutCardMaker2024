#pragma once
#include "utils.h"

#include <stdexcept>
#include <sstream>
#include <cassert>

namespace SCM24
{



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