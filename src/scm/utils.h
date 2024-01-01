#pragma once
#include <raylib.h>
#include "common.h"
#include <vector>

namespace SCM24
{
Player& get_player_with_tag(std::vector<Player>& players, PlayerTag player_tag);
}