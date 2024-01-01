#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "rlgl.h"
#include "raymath.h"

#include <vector>

#include "scm/utils.cpp"
#include "scm/common.cpp"
#include "scm/formation.cpp"
#include "scm/formation_utils.cpp"

using namespace SCM24;

Vector2 v2(float x, float y)
{
    Vector2 result = { x, y };
    return result;
}

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

class PlayerFieldGui 
{
    const float PLAYER_WIDTH_OFFENSE = 2.5;
    const float PLAYER_HEIGHT_OFFENSE = 0.6;
    const float TAG_WIDTH_OFFENSE = 1.4;
    const float TAG_HEIGHT_OFFENSE = 0.6;
    const float TAG_WIDTH_DEFENSE = 1.6;
    const float TAG_HEIGHT_DEFENSE = 0.8;
    
    const Color PLAYER_UNSELECTED_COLOR_OFFENSE = LIGHTGRAY;
    const Color PLAYER_SELECTED_COLOR_OFFENSE = SKYBLUE;
    const Color PLAYER_UNSELECTED_COLOR_DEFENSE = BLACK;
    const Color PLAYER_SELECTED_COLOR_DEFENSE = RED;

public:
    PlayerFieldGuiState player_field_gui_state;
    Vector2 _mouse_pos_field;
    std::vector<Player*> gui_players;
    bool was_in_default_state;

    bool is_mouse_position_within_player(Player* found_player)
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

    void draw_player(Player *player/*, Color4? dot_color_for_player*/)
    {
        Color player_color;
        if (player->player_side == PlayerSide::OFFENSE)
            player_color = contains_player(player_field_gui_state.selected_players, player) ? PLAYER_SELECTED_COLOR_OFFENSE : PLAYER_UNSELECTED_COLOR_OFFENSE;
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

    void handle_input_for_field_and_render_select_box()
    {

    }

    virtual void update_and_render()
    {
        handle_input_for_field_and_render_select_box();
        
        for (Player* player : gui_players)
            draw_player(player);
    }
};

class FormationEditGui : public PlayerFieldGui
{
public:
    // const float _FORMATION_DETAILS_HEIGHT = 115f;
    // const float _AFFECTED_PLAYER_CHECKBOX_SPACING = 10;
    // const float _LIST_BOX_WIDTH = 200.0f;    
    std::vector<Player> _field_players;
    std::vector<Player> _mof_players;
    std::vector<Player> _boundary_players;
    // SCMGui _scm_gui;
    // float _menubar_height;

    // int _formations_list_selection_index;
    FormationLibrary* _formation_library;
    std::string _formation_library_path;
    std::string _formation_library_save_message;
    // std::vector<std::string[]> _formation_listbox_items;   
    std::string _formation_name = "";
    std::string _formation_tags = "";
    bool _lt_affected;
    bool _lg_affected;
    bool _oc_affected;
    bool _rg_affected;
    bool _rt_affected;
    bool _oq_affected;
    bool _s1_affected;
    bool _s2_affected;
    bool _s3_affected;
    bool _s4_affected;
    bool _s5_affected;

    FormationEditGui(/*SCMGui scm_gui,*/ FormationLibrary* formation_library/*, std::string formation_library_path, std::string formation_library_save_message*/)
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
};

enum class FieldType { HIGH_SCHOOL, COLLEGE, NFL };

void draw_field(FieldType field_type) 
{
    const float _FIELD_LEFT_SIDELINE_X = -54;
    const float _FIELD_RIGHT_SIDELINE_X = 54;
    const float _FIELD_LEFT_SIDELINE_YARD_MARKS_X1 = -53.5;
    const float _FIELD_LEFT_SIDELINE_YARD_MARKS_X2 = -52.5;
    const float _FIELD_RIGHT_SIDELINE_YARD_MARKS_X1 = 52.5;
    const float _FIELD_RIGHT_SIDELINE_YARD_MARKS_X2 = 53.5;

    
    const float _LEFT_HASH_X_HIGH_SCHOOL = -18;
    const float _RIGHT_HASH_X_HIGH_SCHOOL = 18;

    const float _LEFT_HASH_X_COLLEGE = -16;
    const float _RIGHT_HASH_X_COLLEGE = 16;

    const float _LEFT_HASH_X_NFL = -12;
    const float _RIGHT_HASH_X_NFL = 12;

    const float _MIDDLE_NUMBERS_LEFT_X = -38;
    const float _MIDDLE_NUMBERS_RIGHT_X = 38;

    Color line_color = WHITE;

    float left_hash_x;
    float right_hash_x;

    if (field_type == FieldType::HIGH_SCHOOL)
    {
        left_hash_x = _LEFT_HASH_X_HIGH_SCHOOL;
        right_hash_x = _RIGHT_HASH_X_HIGH_SCHOOL;
    }
    else if (field_type == FieldType::COLLEGE)
    {
        left_hash_x = _LEFT_HASH_X_COLLEGE;
        right_hash_x = _RIGHT_HASH_X_COLLEGE;
    }
    else // if (field_type == FieldType::NFL)
    {
        left_hash_x = _LEFT_HASH_X_NFL;
        right_hash_x = _RIGHT_HASH_X_NFL;
    }
    
    for (float y = -50; y <= 50; y += 5) 
        DrawLineV(v2(_FIELD_LEFT_SIDELINE_X, y), v2(_FIELD_RIGHT_SIDELINE_X, y), line_color);

    for (float y = -45; y <= 45; y += 5) 
    {
        DrawLineV(v2(left_hash_x, y), v2(left_hash_x, y), line_color);
        DrawLineV(v2(right_hash_x, y + 0.5), v2(right_hash_x, y - 0.5), line_color);
    }

    for (int yi = -49; yi <= 49; yi++)
    {
        if (yi % 5 == 0)
        {
            continue;
        }

        float y = (float)yi;

        DrawLineV(v2(_FIELD_LEFT_SIDELINE_YARD_MARKS_X1, y), v2(_FIELD_LEFT_SIDELINE_YARD_MARKS_X2, y), line_color);
        DrawLineV(v2(_FIELD_RIGHT_SIDELINE_YARD_MARKS_X1, y), v2(_FIELD_RIGHT_SIDELINE_YARD_MARKS_X2, y), line_color);
        
        DrawLineV(v2(left_hash_x - 1, y), v2(left_hash_x, y), line_color);
        DrawLineV(v2(right_hash_x, y), v2(right_hash_x + 1, y), line_color);           
    }

    DrawLineV(v2(_FIELD_LEFT_SIDELINE_X, -60), v2(_FIELD_RIGHT_SIDELINE_X, -60), line_color);
    DrawLineV(v2(_FIELD_LEFT_SIDELINE_X, 60), v2(_FIELD_RIGHT_SIDELINE_X, 60), line_color);
    DrawLineV(v2(_FIELD_LEFT_SIDELINE_X, -60), v2(_FIELD_LEFT_SIDELINE_X, 60), line_color);
    DrawLineV(v2(_FIELD_RIGHT_SIDELINE_X, -60), v2(_FIELD_RIGHT_SIDELINE_X, 60), line_color);
}

Matrix get_map_matrix(float x1_old, float x2_old, float x1_new, float x2_new, float y1_old, float y2_old, float y1_new, float y2_new)
{
    float scaleX = (x2_new - x1_new) / (x2_old - x1_old);
    float scaleY = (y2_new - y1_new) / (y2_old - y1_old);

    float translateX = (x2_old - x1_old) / 2.0f;
    float translateY = (y2_old - y1_old) / 2.0f;

    Matrix result = { 0 };
    Matrix matOrigin = MatrixTranslate(translateX, translateY, 0.0f);
    Matrix matScale = MatrixScale(scaleX, scaleY, 1.0f);

    result = MatrixMultiply(matOrigin, matScale);

    return result;
}

Matrix MYGetCameraMatrix2D(Camera2D camera)
{
    Matrix matTransform = { 0 };
    // The camera in world-space is set by
    //   1. Move it to target
    //   2. Rotate by -rotation and scale by (1/zoom)
    //      When setting higher scale, it's more intuitive for the world to become bigger (= camera become smaller),
    //      not for the camera getting bigger, hence the invert. Same deal with rotation.
    //   3. Move it by (-offset);
    //      Offset defines target transform relative to screen, but since we're effectively "moving" screen (camera)
    //      we need to do it into opposite direction (inverse transform)

    // Having camera transform in world-space, inverse of it gives the modelview transform.
    // Since (A*B*C)' = C'*B'*A', the modelview is
    //   1. Move to offset
    //   2. Rotate and Scale
    //   3. Move by -target
    Matrix matOrigin = MatrixTranslate(-camera.target.x, -camera.target.y, 0.0f);
    Matrix matRotation = MatrixRotate((Vector3){ 0.0f, 0.0f, 1.0f }, camera.rotation*DEG2RAD);
    Matrix matScale = MatrixScale(camera.zoom, camera.zoom, 1.0f);
    Matrix matTranslation = MatrixTranslate(camera.offset.x, camera.offset.y, 0.0f);

    matTransform = MatrixMultiply(MatrixMultiply(matOrigin, MatrixMultiply(matScale, matRotation)), matTranslation);

    return matTransform;
}

int main() {
    const int screen_width = 800;
    const int screen_height = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screen_width, screen_height, "Scout Card Maker");

    SetTargetFPS(60);

    Rectangle window_area = {0, 0, 200, 30};

    FormationLibrary formation_library;

    FormationEditGui formation_edit_gui(&formation_library);

    Camera2D camera = {};
    camera.target = { -56, -60 };
    camera.zoom = 5;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        
        ClearBackground(GREEN);

        Matrix map_matrix = get_map_matrix(-58, 58, 0, GetScreenWidth(), -65, 65, 0, GetScreenHeight()); 
        rlSetMatrixModelview(map_matrix);
        draw_field(FieldType::HIGH_SCHOOL);
        // DrawEllipse(0, 0, 2, 2, BLUE);

        formation_edit_gui.update_and_render();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}
