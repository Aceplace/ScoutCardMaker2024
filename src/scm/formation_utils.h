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

    struct AttachedBoundaries 
    {
        int left_boundary;
        int right_boundary;
    };
    
    void set_offense_and_defense_into_default_pro_positions(std::vector<Player>& players);

    std::vector<Player> create_offense_and_or_defense_players(bool create_offense_players, bool create_defense_players);

    Player& get_player_with_tag(std::vector<Player>& players, PlayerTag player_tag);

    std::vector<Player> get_offense_players(std::vector<Player>& players);

    std::vector<Player> get_players_ordered(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation);
    
    std::vector<Player> get_backfield(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation);
    

    AttachedBoundaries get_attached_boundaries(std::vector<Player>& players);

    std::vector<Player> get_detached_players(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation);

    bool tag_within_players(const std::vector<Player>& players, PlayerTag player_tag);

    std::vector<Player> get_attached_players(std::vector<Player>& players, Direction direction, DirectionOrientation direction_orientation);

    std::vector<Player> get_receivers(std::vector<Player> players, Direction direction, DirectionOrientation direction_orientation);

    Direction player_side(std::vector<Player> players, PlayerTag player_tag);

    std::optional<Direction> get_receiver_strength(std::vector<Player> players);

    std::optional<Direction> get_attached_strength(std::vector<Player> players);
    
    std::optional<Direction> get_offset_back_strength(std::vector<Player> players);
    
    std::vector<Player> offense_players(std::vector<Player> players);
}
