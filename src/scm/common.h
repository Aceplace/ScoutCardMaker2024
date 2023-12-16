#pragma once
#include <string>
#include "raylib.h"

namespace SCM24 
{
    enum class PlayerSide {OFFENSE = 0, DEFENSE = 1};
    enum class PlayerTag {NONE, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, LT, LG, OC,  RG, RT, OQ, S1, S2, S3, S4, S5};

    bool is_offensive_lineman_not_center(PlayerTag player_tag);

    enum class Direction {RIGHT, LEFT, FORWARD};
    enum class DirectionStringLength { SINGLE_LETTER, SHORT, FULL};
    enum class DirectionStringCapitalization { FIRST_LETTER, LOWER_CASE, UPPER_CASE};
    enum BallHash { LEFT = 0, MOF = 1, RIGHT = 2};

    float dir_factor(Direction direction);
    Direction opposite(Direction direction);

    std::string get_direction_str(  Direction direction, DirectionStringLength direction_string_length,
                                    DirectionStringCapitalization direction_string_capitalization);
    

    class Player
    {
        public:

        PlayerTag player_tag;
        PlayerSide player_side;
        Vector2 pos;
        
        Player(PlayerTag player_tag, PlayerSide player_side, float x = 0, float y = 0);
        void set_position(float x, float y);
        void set_position(Vector2 position);
    };
}