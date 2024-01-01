#include "formation_edit_gui.h"
#include "formation_utils.h"
#include "../raylib/my_utils.h"

namespace SCM24
{

FormationEditGui::FormationEditGui(/*SCMGui scm_gui,*/ FormationLibrary* formation_library/*, std::string formation_library_path, std::string formation_library_save_message*/)
{
    // _scm_gui = scm_gui;
    _field_players = create_offense_and_or_defense_players(true, false);
    _mof_players = create_offense_and_or_defense_players(true, false);
    _boundary_players = create_offense_and_or_defense_players(true, false);
    _formation_library = formation_library;
    // _formation_library_path = formation_library_path;
    // _formation_library_save_message = formation_library_save_message;

    #pragma region Field Player Default Positions in Editor
    for (Player& player: _field_players)
    {
        switch (player.player_tag)
        {
            case PlayerTag::LT:
                player.set_position(-26, -1);
                break;
            case PlayerTag::LG:
                player.set_position(-22, -1);
                break;
            case PlayerTag::OC:
                player.set_position(-18, -1);
                break;
            case PlayerTag::RG:
                player.set_position(-14, -1);
                break;
            case PlayerTag::RT:
                player.set_position(-10, -1);
                break;
            case PlayerTag::OQ:
                player.set_position(-18, -2);
                break;
            case PlayerTag::S1:
                player.set_position(-18, -7);
                break;
            case PlayerTag::S2:
                player.set_position(-18, -5);
                break;
            case PlayerTag::S3:
                player.set_position(-40, -1);
                break;
            case PlayerTag::S4:
                player.set_position( -6, -1);
                break;
            case PlayerTag::S5:
                player.set_position( 20, -2);
                break;
        }
        gui_players.push_back(&player);
        player.pos = Vector2Add(player.pos, v2(0, 15));
    }
    #pragma endregion
    
    #pragma region MOF Player Default Positions in Editor
    for (Player& player: _mof_players)
    {
        switch (player.player_tag)
        {
            case PlayerTag::LT:
                player.set_position( -8, -1);
                break;
            case PlayerTag::LG:
                player.set_position( -4, -1);
                break;
            case PlayerTag::OC:
                player.set_position(  0, -1);
                break;
            case PlayerTag::RG:
                player.set_position(  4, -1);
                break;
            case PlayerTag::RT:
                player.set_position(  8, -1);
                break;
            case PlayerTag::OQ:
                player.set_position(  0, -2);
                break;
            case PlayerTag::S1:
                player.set_position(  0, -7);
                break;
            case PlayerTag::S2:
                player.set_position(  0, -5);
                break;
            case PlayerTag::S3:
                player.set_position(-36, -1);
                break;
            case PlayerTag::S4:
                player.set_position( 12, -1);
                break;
            case PlayerTag::S5:
                player.set_position( 36, -2);
                break;
        }
        gui_players.push_back(&player);
    }
    #pragma endregion

    #pragma region Boundary Player Default Positions in Editor
    for (Player& player: _boundary_players)
    {
        switch (player.player_tag)
        {
            case PlayerTag::LT:
                player.set_position( 10, -1);
                break;
            case PlayerTag::LG:
                player.set_position( 14, -1);
                break;
            case PlayerTag::OC:
                player.set_position( 18, -1);
                break;
            case PlayerTag::RG:
                player.set_position( 22, -1);
                break;
            case PlayerTag::RT:
                player.set_position(  26, -1);
                break;
            case PlayerTag::OQ:
                player.set_position(  18, -2);
                break;
            case PlayerTag::S1:
                player.set_position(  18, -7);
                break;
            case PlayerTag::S2:
                player.set_position(  18, -5);
                break;
            case PlayerTag::S3:
                player.set_position(-20, -1);
                break;
            case PlayerTag::S4:
                player.set_position( 30, -1);
                break;
            case PlayerTag::S5:
                player.set_position( 40, -2);
                break;
        }
        gui_players.push_back(&player);
        player.pos = Vector2Add(player.pos, v2(0, -15));
    }
    #pragma endregion
}

}