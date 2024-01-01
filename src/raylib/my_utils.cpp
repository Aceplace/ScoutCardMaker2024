#include "my_utils.h"

Vector2 get_mirrored_x_vector_if(Vector2 value, bool mirror_x)
{
    value.x = mirror_x ? value.x * -1 : value.x;
    return value;
}

bool point_in_ellipse(Vector2 pos, Vector2 pos_ellipse_center, float a, float b)
{
    return (((pos.x - pos_ellipse_center.x) * (pos.x - pos_ellipse_center.x)) / (a * a)) +
        (((pos.y - pos_ellipse_center.y) * (pos.y - pos_ellipse_center.y)) / (b * b)) <= 1;
}

Vector2 v2(float x, float y)
{
    Vector2 result = { x, y };
    return result;
}