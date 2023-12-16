#pragma once
#include <string>
#include "raylib.h"

namespace ScoutCardMaker2024 
{
    enum class PlayerSide {OFFENSE = 0, DEFENSE = 1};
    enum class PlayerTag {NONE, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, LT, LG, OC,  RG, RT, OQ, S1, S2, S3, S4, S5};

    bool is_offensive_lineman_not_center(PlayerTag player_tag);

    enum class Direction {RIGHT, LEFT, FORWARD};
    enum class DirectionStringLength { SINGLE_LETTER, SHORT, FULL};
    enum class DirectionStringCapitalization { FIRST_LETTER, LOWER_CASE, UPPER_CASE};


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



/*

using OpenTK.Mathematics;

namespace ScoutCardMaker2023.scm;

public enum PlayerSide {OFFENSE = 0, DEFENSE = 1}
public enum PlayerTag {NONE, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, LT, LG, OC,  RG, RT, OQ, S1, S2, S3, S4, S5}

public static class PlayerTagExtensions
{
    public static bool is_offensive_lineman_not_center(this PlayerTag player_tag)
    {
        return player_tag is PlayerTag.LT or PlayerTag.LG or PlayerTag.RG or PlayerTag.RT;
    }
}

public enum Direction {RIGHT, LEFT, FORWARD}
public enum DirectionStringLength { SINGLE_LETTER, SHORT, FULL}
public enum DirectionStringCapitalization { FIRST_LETTER, LOWER_CASE, UPPER_CASE}

public static class DirectionExtensions
{
    public static float dir_factor(this Direction direction)
    {
        return direction == Direction.RIGHT ? 1 : -1;
    }
    
    public static Direction opposite(this Direction direction)
    {
        return direction == Direction.RIGHT ? Direction.LEFT : Direction.RIGHT;
    }

    public static string get_direction_str(this Direction direction, DirectionStringLength direction_string_length, DirectionStringCapitalization direction_string_capitalization)
    {
        if (direction == Direction.RIGHT)
        {
            return direction_string_length switch
            {
                DirectionStringLength.SINGLE_LETTER => direction_string_capitalization switch
                {

                    DirectionStringCapitalization.FIRST_LETTER => "R",
                    DirectionStringCapitalization.LOWER_CASE => "r",
                    DirectionStringCapitalization.UPPER_CASE => "R",
                    _ => throw new ArgumentOutOfRangeException(nameof(direction_string_capitalization), direction_string_capitalization, null)
                },
                DirectionStringLength.SHORT => direction_string_capitalization switch
                {

                    DirectionStringCapitalization.FIRST_LETTER => "Rt",
                    DirectionStringCapitalization.LOWER_CASE => "rt",
                    DirectionStringCapitalization.UPPER_CASE => "RT",
                    _ => throw new ArgumentOutOfRangeException(nameof(direction_string_capitalization), direction_string_capitalization, null)
                },
                _ => direction_string_capitalization switch
                {

                    DirectionStringCapitalization.FIRST_LETTER => "Right",
                    DirectionStringCapitalization.LOWER_CASE => "right",
                    DirectionStringCapitalization.UPPER_CASE => "RIGHT",
                    _ => throw new ArgumentOutOfRangeException(nameof(direction_string_capitalization), direction_string_capitalization, null)
                }
            };

        }
        
        return direction_string_length switch
        {
            DirectionStringLength.SINGLE_LETTER => direction_string_capitalization switch
            {

                DirectionStringCapitalization.FIRST_LETTER => "L",
                DirectionStringCapitalization.LOWER_CASE => "l",
                DirectionStringCapitalization.UPPER_CASE => "L",
                _ => throw new ArgumentOutOfRangeException(nameof(direction_string_capitalization), direction_string_capitalization, null)
            },
            DirectionStringLength.SHORT => direction_string_capitalization switch
            {

                DirectionStringCapitalization.FIRST_LETTER => "Lt",
                DirectionStringCapitalization.LOWER_CASE => "lt",
                DirectionStringCapitalization.UPPER_CASE => "LT",
                _ => throw new ArgumentOutOfRangeException(nameof(direction_string_capitalization), direction_string_capitalization, null)
            },
            _ => direction_string_capitalization switch
            {

                DirectionStringCapitalization.FIRST_LETTER => "Left",
                DirectionStringCapitalization.LOWER_CASE => "left",
                DirectionStringCapitalization.UPPER_CASE => "LEFT",
                _ => throw new ArgumentOutOfRangeException(nameof(direction_string_capitalization), direction_string_capitalization, null)
            }
        };
    }
}

public class Player
{
    public PlayerTag player_tag;
    public PlayerSide player_side;
    public Vector2 pos;
    
    public Player(PlayerTag player_tag, PlayerSide player_side, float x = 0, float y = 0)
    {
        this.player_tag = player_tag;
        this.player_side = player_side;
        pos.X = x;
        pos.Y = y;
    }

    public void set_position(float x, float y)
    {
        pos.X = x;
        pos.Y = y;
    }
    
    public void set_position(Vector2 position)
    {
        pos = position;
    }
}



*/