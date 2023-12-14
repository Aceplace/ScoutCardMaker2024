#include "raylib.h"

int main() {
    // Determin the Game Window Width and Height
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Initialize the Window
    InitWindow(screenWidth, screenHeight, "Scout Card Maker");

    // Setting the Frames Per Second
    SetTargetFPS(60);

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/) {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText("Congrats Dude", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
