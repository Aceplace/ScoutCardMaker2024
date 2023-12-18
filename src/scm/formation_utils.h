#pragma once
#include <vector>
#include "common.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <optional>

namespace SCM24
{
    enum DirectionOrientation { OUTSIDE_ACROSS, OUTSIDE_IN, INSIDE_OUT };

    void set_offense_and_defense_into_default_pro_positions(std::vector<Player>& players)
    {
        for (Player& player: players)
        {
            switch (player.player_tag)
            {
                case PlayerTag::D1:
                    player.set_position(6, 1);
                    break;
                case PlayerTag::D2:
                    player.set_position(10, 1);
                    break;
                case PlayerTag::D3:
                    player.set_position(-2, 1);
                    break;
                case PlayerTag::D4:
                    player.set_position(-10, 1);
                    break;
                case PlayerTag::D5:
                    player.set_position(14, 2);
                    break;
                case PlayerTag::D6:
                    player.set_position(2, 4);
                    break;
                case PlayerTag::D7:
                    player.set_position(-6, 4);
                    break;
                case PlayerTag::D8:
                    player.set_position(12, 7);
                    break;
                case PlayerTag::D9:
                    player.set_position(-14, 7);
                    break;
                case PlayerTag::D10:
                    player.set_position(36, 3);
                    break;
                case PlayerTag::D11:
                    player.set_position(-36, 3);
                    break;
                case PlayerTag::LT:
                    player.set_position(-8, -1);
                    break;
                case PlayerTag::LG:
                    player.set_position(-4, -1);
                    break;
                case PlayerTag::OC:
                    player.set_position(0, -1);
                    break;
                case PlayerTag::RG:
                    player.set_position(4, -1);
                    break;
                case PlayerTag::RT:
                    player.set_position(8, -1);
                    break;
                case PlayerTag::OQ:
                    player.set_position(0, -2);
                    break;
                case PlayerTag::S1:
                    player.set_position(0, -7);
                    break;
                case PlayerTag::S2:
                    player.set_position(0, -5);
                    break;
                case PlayerTag::S3:
                    player.set_position(-36, -1);
                    break;
                case PlayerTag::S4:
                    player.set_position(12, -1);
                    break;
                case PlayerTag::S5:
                    player.set_position(36, -2);
                    break;
                case PlayerTag::NONE:
                default:
                    throw std::out_of_range("Unknown Player Tag");
            }
        }
    }

    std::vector<Player> create_offense_and_or_defense_players(bool create_offense_players, bool create_defense_players)
    {
        std::vector<Player> result;
        if (create_offense_players)
        {
            result.push_back(Player(PlayerTag::LT, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::LG, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::OC, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::RG, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::RT, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::OQ, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::S1, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::S2, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::S3, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::S4, PlayerSide::OFFENSE));
            result.push_back(Player(PlayerTag::S5, PlayerSide::OFFENSE));
        }

        if (create_defense_players)
        {
            result.push_back(Player(PlayerTag::D1, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D2, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D3, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D4, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D5, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D6, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D7, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D8, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D9, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D10, PlayerSide::DEFENSE));
            result.push_back(Player(PlayerTag::D11, PlayerSide::DEFENSE));
        }

        set_offense_and_defense_into_default_pro_positions(result);
        return result;
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

    std::vector<Player> get_offense_players(std::vector<Player>& players)
    {
        std::vector<Player> result;
        std::copy_if(players.begin(), players.end(), std::back_inserter(result), [](const Player& player) {
            return player.player_side == PlayerSide::OFFENSE;
        });
        return result;
    }

    std::vector<Player> get_players_ordered(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation)
    {
        std::vector<Player> offense_players = get_offense_players(players);

        bool negate_x = false;
        if (direction_orientation == DirectionOrientation::OUTSIDE_ACROSS || direction_orientation == DirectionOrientation::OUTSIDE_IN)
        {
            if (direction == Direction::RIGHT)
                negate_x = true;
        }
        else
        {
            if (direction == Direction::LEFT)
                negate_x = true;
        }

        auto sort_players = [negate_x](const Player& a, const Player& b) {
            if (negate_x) 
            {
                if (a.pos.x < b.pos.x)
                    return false;
                if (b.pos.x < a.pos.x)
                    return true;
                return a.pos.y <= b.pos.y;
            }
            else 
            {
                if (a.pos.x < b.pos.x)
                    return true;
                if (b.pos.x < a.pos.x)
                    return false;
                return a.pos.y >= b.pos.y;
            }
        };

        std::sort(offense_players.begin(), offense_players.end(), offense_players);

        if (direction_orientation == DirectionOrientation::OUTSIDE_IN || direction_orientation == DirectionOrientation::INSIDE_OUT)
        {
            float center_x = get_player_with_tag(offense_players, PlayerTag::OC).pos.x;
            std::vector<Player> result;
            std::copy_if(players.begin(), players.end(), std::back_inserter(result), 
                [direction, center_x](const Player& player) { 
                    return direction == Direction::RIGHT ? player.pos.x >= center_x : player.pos.x <= center_x;
                }
            );
            return result;
        }

        return offense_players;
    }

    std::vector<Player> get_backfield(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation)
    {
        std::vector<Player> players_ordered = get_players_ordered(players, direction, direction_orientation);
        float center_x = get_player_with_tag(players, PlayerTag::OC).pos.x;

        std::vector<Player> result;
        std::copy_if(players.begin(), players.end(), std::back_inserter(result),
            [direction, center_x](const Player& player) { 
                return player.pos.x >= center_x - 10 && player.pos.x <= center_x + 10 && !is_offensive_lineman_not_center(player.player_tag);
            }
        );

        return result;
    }

    struct AttachedBoundaries 
    {
        int left_boundary;
        int right_boundary;
    };

    AttachedBoundaries get_attached_boundaries(std::vector<Player>& players)
    {
        AttachedBoundaries result;

        const int ATTACH_DISTANCE = 3;
        const int STARTING_DISTANCE = 8;
        players = get_offense_players(players);
        int center_x = get_player_with_tag(players, PlayerTag::OC).pos.x;
        int core_left = center_x - STARTING_DISTANCE - ATTACH_DISTANCE;
        int core_right = center_x + STARTING_DISTANCE + ATTACH_DISTANCE;
        for (int i = 1; i <= 11; i++)
        {
            for (Player player: players)
            {
                if (player.pos.x >= core_left - ATTACH_DISTANCE && player.pos.x <= core_right + ATTACH_DISTANCE && player.pos.y > -3)
                {
                    core_left = std::min(core_left, (int)player.pos.x - ATTACH_DISTANCE);
                    core_right = std::max(core_right, (int)player.pos.x + ATTACH_DISTANCE);
                }
            }
        }
        result.left_boundary = core_left;
        result.right_boundary = core_right;

        return result;
    }


    std::vector<Player> get_detached_players(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation)
    {
        std::vector<Player> players_ordered = get_players_ordered(players, direction, direction_orientation);
        AttachedBoundaries core = get_attached_boundaries(players_ordered);
        int center_x = get_player_with_tag(players, PlayerTag::OC).pos.x;

        std::vector<Player> result;
        std::copy_if(players.begin(), players.end(), std::back_inserter(result),
            [core, center_x](const Player& player) { 
                return player.pos.x <= core.left_boundary || player.pos.x >= core.right_boundary;
            }
        );
        return result;   
    }

    bool tag_within_players(const std::vector<Player>& players, PlayerTag player_tag)
    {
        for (size_t i = 0; i < players.size(); i++)
        {
            if (players[i].player_tag == player_tag)
                return true;
        }
        return false;   
    }

    std::vector<Player> get_attached_players(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation)
    {
        std::vector<Player> players_ordered = get_players_ordered(players, direction, direction_orientation);
        std::vector<Player> backfield_players = get_backfield(players, direction, direction_orientation);
        AttachedBoundaries core = get_attached_boundaries(players_ordered);

        std::vector<Player> result;
        std::copy_if(players_ordered.begin(), players_ordered.end(), std::back_inserter(result), 
            [core, &backfield_players](const Player& player) { 
                return  player.pos.x > core.left_boundary && 
                        player.pos.x < core.right_boundary &&
                        !is_offensive_lineman_not_center(player.player_tag) &&
                        !tag_within_players(backfield_players, player.player_tag);
            }
        );

        return result;
    }

    std::vector<Player> get_receivers(std::vector<Player> players, Direction direction, DirectionOrientation direction_orientation)
    {
        std::vector<Player> backfield_players = get_backfield(players, Direction::RIGHT, DirectionOrientation::OUTSIDE_ACROSS);
        std::vector<Player> players_ordered = get_players_ordered(players, direction, direction_orientation);

        std::vector<Player> result;
        std::copy_if(players_ordered.begin(), players_ordered.end(), std::back_inserter(result), 
            [&backfield_players](const Player& player) { 
                return  !tag_within_players(backfield_players, player.player_tag) &&
                        !is_offensive_lineman_not_center(player.player_tag);
            }
        );

        return result;
    }

    Direction player_side(std::vector<Player> players, PlayerTag player_tag)
    {
        float center_x = get_player_with_tag(players, PlayerTag::OC).pos.x;
        float player_x = get_player_with_tag(players, player_tag).pos.x;
        return player_x > center_x ? Direction::RIGHT : Direction::LEFT;
    }

    std::optional<Direction> get_receiver_strength(std::vector<Player> players)
    {
        int receivers_left = get_receivers(players, Direction::LEFT, DirectionOrientation::OUTSIDE_IN).size();
        int receivers_right = get_receivers(players, Direction::RIGHT, DirectionOrientation::OUTSIDE_IN).size();

        if (receivers_right > receivers_left)
            return Direction::RIGHT;
        if (receivers_left > receivers_right)
            return Direction::LEFT;
        return std::nullopt;
    }

    std::optional<Direction> get_attached_strength(std::vector<Player> players)
    {
        int attached_left = get_attached_players(players, Direction::LEFT, DirectionOrientation::OUTSIDE_IN).size();
        int attached_right = get_attached_players(players, Direction::RIGHT, DirectionOrientation::OUTSIDE_IN).size();

        if (attached_right > attached_left)
            return Direction::RIGHT;
        if (attached_left > attached_right)
            return Direction::LEFT;
        return std::nullopt;
    }

    std::optional<Direction> get_offset_back_strength(std::vector<Player> players)
    {
        int offset_backs_to_left = get_backfield(players, Direction::LEFT, DirectionOrientation::OUTSIDE_IN).size();
        int offset_backs_to_right = get_backfield(players, Direction::RIGHT, DirectionOrientation::OUTSIDE_IN).size();

        if (offset_backs_to_right > offset_backs_to_left)
            return Direction::RIGHT;
        if (offset_backs_to_left > offset_backs_to_right)
            return Direction::LEFT;
        return std::nullopt;
    }

    std::vector<Player> offense_players(std::vector<Player> players)
    {
        std::vector<Player> result;
        std::copy_if(players.begin(), players.end(), std::back_inserter(result),
            [](const Player& player) { 
                return player.player_side == PlayerSide::OFFENSE;
            }
        );

        return result;
    }
}
