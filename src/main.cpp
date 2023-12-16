#include "scm/common.cpp"
#include "scm/formation.cpp"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    // Determin the Game Window Width and Height
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Initialize the Window
    InitWindow(screenWidth, screenHeight, "Scout Card Maker");

    // Setting the Frames Per Second
    SetTargetFPS(60);

    Rectangle window_area = {0, 0, 200, 30};

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/) {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText("Congrats Dude", 190, 200, 20, LIGHTGRAY);

        GuiWindowBox(window_area, "Test Gui Window Box");

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
