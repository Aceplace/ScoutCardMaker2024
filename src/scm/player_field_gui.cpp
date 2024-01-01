#include "player_field_gui.h"
#include <my_utils.h>

namespace SCM24
{

const float PlayerFieldGui::PLAYER_WIDTH_OFFENSE = 2.5;
const float PlayerFieldGui::PLAYER_HEIGHT_OFFENSE = 0.6;
const float PlayerFieldGui::TAG_WIDTH_OFFENSE = 1.4;
const float PlayerFieldGui::TAG_HEIGHT_OFFENSE = 0.6;
const float PlayerFieldGui::TAG_WIDTH_DEFENSE = 1.6;
const float PlayerFieldGui::TAG_HEIGHT_DEFENSE = 0.8;

const Color PlayerFieldGui::PLAYER_UNSELECTED_COLOR_OFFENSE = LIGHTGRAY;
const Color PlayerFieldGui::PLAYER_SELECTED_COLOR_OFFENSE = SKYBLUE;
const Color PlayerFieldGui::PLAYER_UNSELECTED_COLOR_DEFENSE = BLACK;
const Color PlayerFieldGui::PLAYER_SELECTED_COLOR_DEFENSE = RED;

bool contains_player(std::vector<SelectedPlayerInfo> selected_player_infos, Player* player)
{
    for (int i = 0; i < selected_player_infos.size(); i++)
    {
        if (selected_player_infos[i].player == player)
            return true;
    }
    
    return false;
}

SelectedPlayerInfo* get_selected_player_info_for_player(std::vector<SelectedPlayerInfo> selected_player_infos, Player *player)
{
    for (SelectedPlayerInfo& selected_player_info: selected_player_infos)
    {
        if (selected_player_info.player == player)
            return &selected_player_info;
    }
    return nullptr;
}

void remove_player(std::vector<SelectedPlayerInfo> selected_player_infos, Player* player)
{
    for (int i = 0; i < selected_player_infos.size(); i++)
    {
        if (selected_player_infos[i].player == player)
        {
            selected_player_infos.erase(selected_player_infos.begin() + i);
            break;
        }
    }
}

bool PlayerFieldGui::is_mouse_position_within_player(Player* found_player)
{
    for (int i = 0; i < gui_players.size(); i++)
    {
        if (point_in_ellipse(_mouse_pos_field, v2(gui_players[i]->pos.x, gui_players[i]->pos.y), PLAYER_WIDTH_OFFENSE / 2.0, PLAYER_HEIGHT_OFFENSE / 2.0))
        {
            found_player = gui_players[i];
            return true;
        }
    }

    found_player = nullptr;
    return false;
}

void PlayerFieldGui::draw_player(Player *player/*, Color4? dot_color_for_player*/)
{
    Color player_color;
    if (player->player_side == PlayerSide::OFFENSE)
        player_color = contains_player(player_field_gui_state.selected_players, player) ? PlayerFieldGui::PLAYER_SELECTED_COLOR_OFFENSE : PlayerFieldGui::PLAYER_UNSELECTED_COLOR_OFFENSE;
    else
        player_color = contains_player(player_field_gui_state.selected_players, player) ? PLAYER_SELECTED_COLOR_DEFENSE : PLAYER_UNSELECTED_COLOR_DEFENSE;

    if (player->player_side == PlayerSide::OFFENSE)
    {
        DrawEllipse(player->pos.x, player->pos.y, PLAYER_WIDTH_OFFENSE / 2, PLAYER_HEIGHT_OFFENSE / 2, player_color);
        // MCYGraphics.draw_immediate_text(PlayerFieldGuiConstants.PLAYER_LABEL_MAP[player.player_tag], player.pos.X, player.pos.Y, PlayerFieldGuiConstants.TAG_WIDTH_OFFENSE, PlayerFieldGuiConstants.TAG_HEIGHT_OFFENSE, Color4.Black);
        // if (dot_color_for_player != null)
        //     MCYGraphics.draw_immediate_rectangle(player.pos.X, player.pos.Y, 0.3f, 0.3f, dot_color_for_player.Value);        
    }
    else
    {
        // MCYGraphics.draw_immediate_text(PlayerFieldGuiConstants.PLAYER_LABEL_MAP[player.player_tag], player.pos.X, player.pos.Y, PlayerFieldGuiConstants.TAG_WIDTH_DEFENSE, PlayerFieldGuiConstants.TAG_HEIGHT_DEFENSE, player_color);
    }
}

void PlayerFieldGui::handle_input_for_field_and_render_select_box()
{

}

void PlayerFieldGui::update_and_render()
{
    handle_input_for_field_and_render_select_box();
    
    for (Player* player : gui_players)
        draw_player(player);
}


}