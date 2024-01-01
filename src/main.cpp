#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>

#include "raylib/my_utils.cpp"
#include "scm/utils.cpp"
#include "scm/common.cpp"
#include "scm/formation.cpp"
#include "scm/formation_utils.cpp"
#include "scm/player_field_gui.cpp"
#include "scm/formation_edit_gui.cpp"

using namespace SCM24;

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
