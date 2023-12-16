#include "common.h"
#include <string>

namespace SCM24 
{
    bool is_offensive_lineman_not_center(PlayerTag player_tag)
    {
            return  player_tag == PlayerTag::LT ||
                    player_tag == PlayerTag::LG ||
                    player_tag == PlayerTag::RG ||
                    player_tag == PlayerTag::RT;
    }

    float dir_factor(Direction direction) 
    {
        return direction == Direction::RIGHT ? 1 : -1;
    }

    Direction opposite(Direction direction) 
    {
        return direction == Direction::RIGHT ? Direction::LEFT : Direction::RIGHT;
    }

    std::string get_direction_str(  Direction direction, DirectionStringLength direction_string_length,
                                    DirectionStringCapitalization direction_string_capitalization) 
    {    
        if (direction == Direction::RIGHT) 
        {
            switch (direction_string_length) 
            {
                case DirectionStringLength::SINGLE_LETTER:
                {
                    switch (direction_string_capitalization) 
                    {
                        case DirectionStringCapitalization::FIRST_LETTER: return "R";
                        case DirectionStringCapitalization::LOWER_CASE: return "r";
                        default: return "R";
                    }
                }
                case DirectionStringLength::SHORT:
                {
                    switch (direction_string_capitalization) 
                    {
                        case DirectionStringCapitalization::FIRST_LETTER: return "Rt";
                        case DirectionStringCapitalization::LOWER_CASE: return "rt";
                        default: return "RT";
                    }
                }
                default: 
                {
                    switch (direction_string_capitalization) 
                    {
                        case DirectionStringCapitalization::FIRST_LETTER: return "Right";
                        case DirectionStringCapitalization::LOWER_CASE: return "right";
                        default: return "RIGHT";
                    }
                }
            }
        } 
        else 
        {
            switch (direction_string_length) 
            {
                case DirectionStringLength::SINGLE_LETTER:
                {
                    switch (direction_string_capitalization) 
                    {
                        case DirectionStringCapitalization::FIRST_LETTER: return "L";
                        case DirectionStringCapitalization::LOWER_CASE: return "l";
                        default: return "L";
                        
                    }
                }
                case DirectionStringLength::SHORT:
                {
                    switch (direction_string_capitalization) 
                    {
                        case DirectionStringCapitalization::FIRST_LETTER: return "Lt";
                        case DirectionStringCapitalization::LOWER_CASE: return "lt";
                        default: return "LT";
                        
                    }
                }
                default: // DirectionStringLength::FULL
                {
                    switch (direction_string_capitalization) 
                    {
                        case DirectionStringCapitalization::FIRST_LETTER: return "Left";
                        case DirectionStringCapitalization::LOWER_CASE: return "left";
                        default: return "LEFT";
                    }
                }
            }
        }
    }
 
    Player::Player(PlayerTag player_tag, PlayerSide player_side, float x, float y)
    {
        this->player_tag = player_tag;
        this->player_side = player_side;
        pos.x = x;
        pos.y = y;
    }

    void Player::set_position(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }
    
    void Player::set_position(Vector2 position)
    {
        pos = position;
    }
}