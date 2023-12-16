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

        Subformation()
        {
            lt_info.position = {-8, -1};
            lg_info.position = {-4, -1};
            oc_info.position = { 0, -1};
            rg_info.position = { 4, -1};
            rt_info.position = { 8, -1};
            oq_info.position = { 0, -2};
            s1_info.position = { 0, -7};
            s2_info.position = { 0, -5};
            s3_info.position = {36, -1};
            s4_info.position = {12, -1};
            s5_info.position = {36, -2};
        }
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

        Formation(std::string name = "Default")
        {
            this->name = name;
            tags = "";

            field_subformation.lt_info.position = Vector2Add(field_subformation.lt_info.position, (Vector2){-18, 0});
            field_subformation.lg_info.position = Vector2Add(field_subformation.lg_info.position, (Vector2){-18, 0});
            field_subformation.oc_info.position = Vector2Add(field_subformation.oc_info.position, (Vector2){-18, 0});
            field_subformation.rg_info.position = Vector2Add(field_subformation.rg_info.position, (Vector2){-18, 0});
            field_subformation.rt_info.position = Vector2Add(field_subformation.rt_info.position, (Vector2){-18, 0});
            field_subformation.oq_info.position = Vector2Add(field_subformation.oq_info.position, (Vector2){-18, 0});
            field_subformation.s1_info.position = Vector2Add(field_subformation.s1_info.position, (Vector2){-18, 0});
            field_subformation.s2_info.position = Vector2Add(field_subformation.s2_info.position, (Vector2){-18, 0});
            field_subformation.s4_info.position = Vector2Add(field_subformation.s4_info.position, (Vector2){-18, 0});
            field_subformation.s3_info.position = Vector2Add(field_subformation.s3_info.position, (Vector2){-8, 0});
            field_subformation.s5_info.position = Vector2Add(field_subformation.s5_info.position, (Vector2){-14, 0});
            
            boundary_subformation.lt_info.position = Vector2Add(boundary_subformation.lt_info.position, (Vector2){18, 0});
            boundary_subformation.lg_info.position = Vector2Add(boundary_subformation.lg_info.position, (Vector2){18, 0});
            boundary_subformation.oc_info.position = Vector2Add(boundary_subformation.oc_info.position, (Vector2){18, 0});
            boundary_subformation.rg_info.position = Vector2Add(boundary_subformation.rg_info.position, (Vector2){18, 0});
            boundary_subformation.rt_info.position = Vector2Add(boundary_subformation.rt_info.position, (Vector2){18, 0});
            boundary_subformation.oq_info.position = Vector2Add(boundary_subformation.oq_info.position, (Vector2){18, 0});
            boundary_subformation.s1_info.position = Vector2Add(boundary_subformation.s1_info.position, (Vector2){18, 0});
            boundary_subformation.s2_info.position = Vector2Add(boundary_subformation.s2_info.position, (Vector2){18, 0});
            boundary_subformation.s4_info.position = Vector2Add(boundary_subformation.s4_info.position, (Vector2){18, 0});
            boundary_subformation.s3_info.position = Vector2Add(boundary_subformation.s3_info.position, (Vector2){14, 0});
            boundary_subformation.s5_info.position = Vector2Add(boundary_subformation.s5_info.position, (Vector2){8, 0});
        }

        void record_player_position_into_subformation(SubformationType subformation_type, Player player)
        {
            Subformation subformation;
            switch (subformation_type)
            {
                case SubformationType::FIELD: 
                    subformation = field_subformation;
                    break;
                case SubformationType::BOUNDARY: 
                    subformation = boundary_subformation;
                    break;
                default: // SubformationType::MOF
                    subformation = mof_subformation;
            }

            switch (player.player_tag)
            {
                case PlayerTag::LT:
                    subformation.lt_info.position = player.pos;
                    break;
                case PlayerTag::LG:
                    subformation.lg_info.position = player.pos;
                    break;
                case PlayerTag::OC:
                    subformation.oc_info.position = player.pos;
                    break;
                case PlayerTag::RG:
                    subformation.rg_info.position = player.pos;
                    break;
                case PlayerTag::RT:
                    subformation.rt_info.position = player.pos;
                    break;
                case PlayerTag::OQ:
                    subformation.oq_info.position = player.pos;
                    break;
                case PlayerTag::S1:
                    subformation.s1_info.position = player.pos;
                    break;
                case PlayerTag::S2:
                    subformation.s2_info.position = player.pos;
                    break;
                case PlayerTag::S3:
                    subformation.s3_info.position = player.pos;
                    break;
                case PlayerTag::S4:
                    subformation.s4_info.position = player.pos;
                    break;
                case PlayerTag::S5:
                    subformation.s5_info.position = player.pos;
                    break;
                case PlayerTag::NONE:
                case PlayerTag::D1:
                case PlayerTag::D2:
                case PlayerTag::D3:
                case PlayerTag::D4:
                case PlayerTag::D5:
                case PlayerTag::D6:
                case PlayerTag::D7:
                case PlayerTag::D8:
                case PlayerTag::D9:
                case PlayerTag::D10:
                case PlayerTag::D11:
                default:
            }
        }

        bool is_player_tag_marked_as_affected(PlayerTag player_tag)
        {
            switch (player_tag)
            {
                case PlayerTag::LT:
                    return lt_affected;
                case PlayerTag::LG:
                    return lg_affected;
                case PlayerTag::OC:
                    return oc_affected;
                case PlayerTag::RG:
                    return rg_affected;
                case PlayerTag::RT:
                    return rt_affected;
                case PlayerTag::OQ:
                    return oq_affected;
                case PlayerTag::S1:
                    return s1_affected;
                case PlayerTag::S2:
                    return s2_affected;
                case PlayerTag::S3:
                    return s3_affected;
                case PlayerTag::S4:
                    return s4_affected;
                case PlayerTag::S5:
                    return s5_affected;
                case PlayerTag::NONE:
                case PlayerTag::D1:
                case PlayerTag::D2:
                case PlayerTag::D3:
                case PlayerTag::D4:
                case PlayerTag::D5:
                case PlayerTag::D6:
                case PlayerTag::D7:
                case PlayerTag::D8:
                case PlayerTag::D9:
                case PlayerTag::D10:
                case PlayerTag::D11:
                default:
                    return false;
            }
        }

        std::optional<Vector2> get_player_position_from_subformation(Direction subformation_direction, SubformationType subformation_type, PlayerTag player_tag)
        {
            Subformation subformation;
            switch (subformation_type)
            {
                case SubformationType::FIELD:
                    subformation = field_subformation;
                    break;
                case SubformationType::BOUNDARY:
                    subformation = boundary_subformation;
                    break;
                default: // SubformationType::MOF
                    subformation = mof_subformation;
            }

            switch (player_tag)
            {
                case PlayerTag::LT:
                    return subformation_direction == Direction::LEFT ? get_mirrored_x_vector_if(subformation.rt_info.position, true) : subformation.lt_info.position;
                case PlayerTag::LG:
                    return subformation_direction == Direction::LEFT ? get_mirrored_x_vector_if(subformation.rg_info.position, true) : subformation.lg_info.position;
                case PlayerTag::OC:
                    return get_mirrored_x_vector_if(subformation.oc_info.position, subformation_direction == Direction::LEFT);
                case PlayerTag::RG:
                    return subformation_direction == Direction::LEFT ? get_mirrored_x_vector_if(subformation.lg_info.position, true) : subformation.rg_info.position;
                case PlayerTag::RT:
                    return subformation_direction == Direction::LEFT ? get_mirrored_x_vector_if(subformation.lt_info.position, true) : subformation.rt_info.position;
                case PlayerTag::OQ:
                    return get_mirrored_x_vector_if(subformation.oq_info.position, subformation_direction == Direction::LEFT);
                case PlayerTag::S1:
                    return get_mirrored_x_vector_if(subformation.s1_info.position, subformation_direction == Direction::LEFT);
                case PlayerTag::S2:
                    return get_mirrored_x_vector_if(subformation.s2_info.position, subformation_direction == Direction::LEFT);
                case PlayerTag::S3:
                    return get_mirrored_x_vector_if(subformation.s3_info.position, subformation_direction == Direction::LEFT);
                case PlayerTag::S4:
                    return get_mirrored_x_vector_if(subformation.s4_info.position, subformation_direction == Direction::LEFT);
                case PlayerTag::S5:
                    return get_mirrored_x_vector_if(subformation.s5_info.position, subformation_direction == Direction::LEFT);
                case PlayerTag::D1:
                case PlayerTag::D2:
                case PlayerTag::D3:
                case PlayerTag::D4:
                case PlayerTag::D5:
                case PlayerTag::D6:
                case PlayerTag::D7:
                case PlayerTag::D8:
                case PlayerTag::D9:
                case PlayerTag::D10:
                case PlayerTag::D11:
                case PlayerTag::NONE:
                default:
                    return std::nullopt;
            }
        }

        void set_player_positions_from_hash_direction(std::vector<Player>& players_to_update, BallHash ball_hash, Direction formation_direction, QBDefaultSnapType qb_default_snap_type)
        {

            SubformationType subformation_type;
            switch (ball_hash) 
            {
                case BallHash::LEFT:
                    subformation_type = (formation_direction == Direction::RIGHT) ? SubformationType::FIELD : SubformationType::BOUNDARY;
                    break;
                case BallHash::RIGHT:
                    subformation_type = (formation_direction == Direction::LEFT) ? SubformationType::FIELD : SubformationType::BOUNDARY;
                    break;
                default:
                    subformation_type = SubformationType::MOF;
                    break;
            }

            for (auto& player: players_to_update)
            {
                if (is_player_tag_marked_as_affected(player.player_tag))
                {
                    std::optional pos = get_player_position_from_subformation(formation_direction, subformation_type, player.player_tag);
                    if (pos)
                        player.pos = *pos;
                }
            }

            if (!oc_affected)
            {
                if (ball_hash == BallHash::LEFT)
                    get_player_with_tag(players_to_update, PlayerTag::OC).set_position(-18, -1);
                else if (ball_hash == BallHash::RIGHT)
                    get_player_with_tag(players_to_update, PlayerTag::OC).set_position(18, -1);
                else if (ball_hash == BallHash::MOF)
                    get_player_with_tag(players_to_update, PlayerTag::OC).set_position(0, -1);
            }
            float center_x = get_player_with_tag(players_to_update, PlayerTag::OC).pos.x;
            
            if (!lt_affected)
                get_player_with_tag(players_to_update, PlayerTag::LT).set_position(center_x - 8, -1);
            if (!lg_affected)
                get_player_with_tag(players_to_update, PlayerTag::LG).set_position(center_x - 4, -1);
            if (!rg_affected)
                get_player_with_tag(players_to_update, PlayerTag::RG).set_position(center_x + 4, -1);
            if (!rt_affected)
                get_player_with_tag(players_to_update, PlayerTag::RT).set_position(center_x + 8, -1);
            if (!oq_affected)
            {
                Player oq_player = get_player_with_tag(players_to_update, PlayerTag::OQ); 
                if (qb_default_snap_type == QBDefaultSnapType::UNDER_CENTER)
                    oq_player.set_position(center_x, -2);
                else
                    oq_player.set_position(center_x, -5);
                
            }
        }


    };
}

/*
using MCYOpenTK;
using OpenTK.Mathematics;

namespace ScoutCardMaker2023.scm;

[Serializable]


[Serializable]



    
    

    

    

    public Vector2? get_player_position_from_subformation(Direction subformation_direction, SubformationType subformation_type, PlayerTag player_tag)
    {
        Subformation subformation = subformation_type switch
        {
            SubformationType.FIELD => field_subformation,
            SubformationType.BOUNDARY => boundary_subformation,
            SubformationType.MOF => mof_subformation,
            _ => throw new ArgumentOutOfRangeException(nameof(subformation_type), subformation_type, null)
        };

        switch (player_tag)
        {
            case PlayerTag.LT:
                return subformation_direction == Direction.LEFT ? subformation.rt_info.position.get_mirrored_x_vector_if(true) : subformation.lt_info.position;
            case PlayerTag.LG:
                return subformation_direction == Direction.LEFT ? subformation.rg_info.position.get_mirrored_x_vector_if(true) : subformation.lg_info.position;
            case PlayerTag.OC:
                return subformation.oc_info.position.get_mirrored_x_vector_if(subformation_direction == Direction.LEFT);
            case PlayerTag.RG:
                return subformation_direction == Direction.LEFT ? subformation.lg_info.position.get_mirrored_x_vector_if(true) : subformation.rg_info.position;
            case PlayerTag.RT:
                return subformation_direction == Direction.LEFT ? subformation.lt_info.position.get_mirrored_x_vector_if(true) : subformation.rt_info.position;
            case PlayerTag.OQ:
                return subformation.oq_info.position.get_mirrored_x_vector_if(subformation_direction == Direction.LEFT);
            case PlayerTag.S1:
                return subformation.s1_info.position.get_mirrored_x_vector_if(subformation_direction == Direction.LEFT);
            case PlayerTag.S2:
                return subformation.s2_info.position.get_mirrored_x_vector_if(subformation_direction == Direction.LEFT);
            case PlayerTag.S3:
                return subformation.s3_info.position.get_mirrored_x_vector_if(subformation_direction == Direction.LEFT);
            case PlayerTag.S4:
                return subformation.s4_info.position.get_mirrored_x_vector_if(subformation_direction == Direction.LEFT);
            case PlayerTag.S5:
                return subformation.s5_info.position.get_mirrored_x_vector_if(subformation_direction == Direction.LEFT);
            case PlayerTag.D1:
            case PlayerTag.D2:
            case PlayerTag.D3:
            case PlayerTag.D4:
            case PlayerTag.D5:
            case PlayerTag.D6:
            case PlayerTag.D7:
            case PlayerTag.D8:
            case PlayerTag.D9:
            case PlayerTag.D10:
            case PlayerTag.D11:
            case PlayerTag.NONE:
            default:
                return null;
        }
    }

    public override string ToString()
    {
        return name;
    }

    public Formation clone()
    {
        Formation result = new(name)
        {
            field_subformation = field_subformation.clone(),
            mof_subformation = mof_subformation.clone(),
            boundary_subformation = boundary_subformation.clone(),
            tags = tags,
            lt_affected = lt_affected,
            lg_affected = lg_affected,
            oc_affected = oc_affected,
            rg_affected = rg_affected,
            rt_affected = rt_affected,
            oq_affected = oq_affected,
            s1_affected = s1_affected,
            s2_affected = s2_affected,
            s3_affected = s3_affected,
            s4_affected = s4_affected,
            s5_affected = s5_affected,
        };
        
        return result;
    }
}


[Serializable]
public class FormationLibrary
{
    public List<Formation> formations;
    
    public FormationLibrary()
    {
        formations = new List<Formation>();
    }

    public Formation? get_formation_by_name(string name)
    {
        foreach (Formation formation in formations)
        {
            if (string.Equals(formation.name, name, StringComparison.OrdinalIgnoreCase))
            {
                return formation;
            }
        }
        return null;
    }
    
    public bool contains_formation_with_name(string name)
    {
        foreach (Formation formation in formations)
        {
            if (string.Equals(formation.name, name, StringComparison.OrdinalIgnoreCase))
            {
                return true;
            }
        }
        return false;
    }
}

*/