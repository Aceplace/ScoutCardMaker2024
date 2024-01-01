#pragma once
#include "common.h"
#include <vector>

namespace SCM24
{

enum class PlayerFieldGuiMode 
{
    DEFAULT,
    PANNING,
    RECTANGLE_SELECT,
    MOVING_PLAYERS
};

struct SelectedPlayerInfo
{
    Player *player;
    Vector2 prev_pos;
};

struct PlayerFieldGuiState 
{
    float s_x1;
    float s_y1;
    float s_x2;
    float s_y2;

    std::vector<SelectedPlayerInfo> selected_players;    
};

bool contains_player(std::vector<SelectedPlayerInfo> selected_player_infos, Player* player);
SelectedPlayerInfo* get_selected_player_info_for_player(std::vector<SelectedPlayerInfo> selected_player_infos, Player *player);
void remove_player(std::vector<SelectedPlayerInfo> selected_player_infos, Player* player);

class PlayerFieldGui 
{
    static const float PLAYER_WIDTH_OFFENSE;
    static const float PLAYER_HEIGHT_OFFENSE;
    static const float TAG_WIDTH_OFFENSE;
    static const float TAG_HEIGHT_OFFENSE;
    static const float TAG_WIDTH_DEFENSE;
    static const float TAG_HEIGHT_DEFENSE;
    static const Color PLAYER_UNSELECTED_COLOR_OFFENSE;
    static const Color PLAYER_SELECTED_COLOR_OFFENSE;
    static const Color PLAYER_UNSELECTED_COLOR_DEFENSE;
    static const Color PLAYER_SELECTED_COLOR_DEFENSE;

public:
    PlayerFieldGuiState player_field_gui_state;
    Vector2 _mouse_pos_field;
    std::vector<Player*> gui_players;
    bool was_in_default_state;

    bool is_mouse_position_within_player(Player* found_player);
    void draw_player(Player *player/*, Color4? dot_color_for_player*/);
    void handle_input_for_field_and_render_select_box();

    virtual void update_and_render();
};

}