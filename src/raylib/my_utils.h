#pragma once
#include "raylib.h"

Vector2 get_mirrored_x_vector_if(Vector2 value, bool mirror_x);
bool point_in_ellipse(Vector2 pos, Vector2 pos_ellipse_center, float a, float b);
Vector2 v2(float x, float y);
