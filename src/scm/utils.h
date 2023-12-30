#pragma once
#include <raylib.h>
#include "common.h"
#include <vector>

namespace SCM24
{

Vector2 get_mirrored_x_vector_if(Vector2 value, bool mirror_x);
Player& get_player_with_tag(std::vector<Player>& players, PlayerTag player_tag);
bool point_in_ellipse(Vector2 pos, Vector2 pos_ellipse_center, float a, float b);

}