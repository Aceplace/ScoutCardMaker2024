#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>
#include "common.h"
#include <vector>
#include <optional>
#include "utils.h"

namespace SCM24 
{
    struct PlayerFormationInfo
    {
        Vector2 position;
    };

    class Subformation
    {
        public:
        PlayerFormationInfo lg_info;
        PlayerFormationInfo lt_info;
        PlayerFormationInfo oc_info;
        PlayerFormationInfo rg_info;
        PlayerFormationInfo rt_info;
        PlayerFormationInfo oq_info;
        PlayerFormationInfo s1_info;
        PlayerFormationInfo s2_info;
        PlayerFormationInfo s3_info;
        PlayerFormationInfo s4_info;
        PlayerFormationInfo s5_info;

        Subformation();
    };

    enum class SubformationType {FIELD, BOUNDARY, MOF};
    enum class QBDefaultSnapType { UNDER_CENTER, SHOTGUN };

    class Formation
    {
        public:

        std::string name;
        std::string tags;
        Subformation field_subformation;
        Subformation mof_subformation;
        Subformation boundary_subformation;
        bool lt_affected;
        bool lg_affected;
        bool oc_affected;
        bool rg_affected;
        bool rt_affected;
        bool oq_affected;
        bool s1_affected;
        bool s2_affected;
        bool s3_affected;
        bool s4_affected;
        bool s5_affected;

        Formation(std::string name = "Default");

        void record_player_position_into_subformation(SubformationType subformation_type, Player player);

        bool is_player_tag_marked_as_affected(PlayerTag player_tag);

        std::optional<Vector2> get_player_position_from_subformation(Direction subformation_direction, 
            SubformationType subformation_type, PlayerTag player_tag);

        void set_player_positions_from_hash_direction(std::vector<Player>& players_to_update, 
            BallHash ball_hash, Direction formation_direction, QBDefaultSnapType qb_default_snap_type);

        std::string to_string();
    };


    class FormationLibrary
    {
        public:
        std::vector<Formation> formations;
        
        Formation* get_formation_by_name(std::string name);  
        bool contains_formation_with_name(std::string name);
    };
}