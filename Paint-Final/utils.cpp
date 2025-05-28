// utils.cpp
#include "include/utils.h"
#include <GL/freeglut.h>
#include <cstring>

extern int window_w;
extern int window_h;

float NormX(float x)
{
    return x * (window_w - 50) + 50;
}

float NormY(float y)
{
    return (float)(window_h - y * window_h);
}

float FracX(float x)
{
    return (float)(x - 50) / (window_w - 50);
}

float FracY(float y)
{
    return (float)(window_h - y) / window_h;
}

void printString(int x, int y, void *font, const char *str)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(x, y);
    for (int i = 0; i < std::strlen(str); i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}
