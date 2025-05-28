// transform.cpp
#include "transform.h"
#include "utils.h"
#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>

extern int window_w;
extern int window_h;
extern Shape shapeList[];
extern int shapeCount;
extern float NormCor_trans_start_x;
extern float NormCor_trans_start_y;
extern bool dragging;
extern bool Scalling_special;
bool TRANSLATION = false, ROTATION = false, SCALING = false;

Point p1, p2, p3;
float ang = 5;

Point rotate(Point p, Point c, float angle) {
    angle = angle * PI / 180.0f;
    Point result;
    result.x = p.x * cos(angle) - p.y * sin(angle) + (c.x - cos(angle) * c.x + sin(angle) * c.y);
    result.y = p.x * sin(angle) + p.y * cos(angle) + (c.y - sin(angle) * c.x - cos(angle) * c.y);
    return result;
}

void rotationPoint(float x, float y) {
    int current = shapeCount - 1;
    if (shapeList[current].type == SHAPE_LINE || (shapeList[current].type == SHAPE_TRIANGLE && shapeList[current].isFilled)) {
        p1.x = shapeList[current].focusX;
        p1.y = shapeList[current].focusY;

        float startX = NormX(shapeList[current].startX);
        float startY = NormY(shapeList[current].startY);
        float endX = NormX(shapeList[current].endX);
        float endY = NormY(shapeList[current].endY);

        p3 = { startX, startY };
        p2 = { endX, endY };

        p3 = rotate(p3, p1, ang);
        p2 = rotate(p2, p1, ang);

        shapeList[current].startX = FracX(p2.x);
        shapeList[current].startY = FracY(p2.y);
        shapeList[current].endX = FracX(p3.x);
        shapeList[current].endY = FracY(p3.y);
    } else if (ROTATION && dragging) {
        shapeList[current].rotated += 1.0f;
    }
}

void translatePoint(float x, float y) {
    int current = shapeCount - 1;

    float newX = NormX(x);
    float newY = NormY(y);
    float dx = newX - NormCor_trans_start_x;
    float dy = newY - NormCor_trans_start_y;

    NormCor_trans_start_x = newX;
    NormCor_trans_start_y = newY;

    shapeList[current].startX = FracX(NormX(shapeList[current].startX) + dx);
    shapeList[current].startY = FracY(NormY(shapeList[current].startY) + dy);
    shapeList[current].endX = FracX(NormX(shapeList[current].endX) + dx);
    shapeList[current].endY = FracY(NormY(shapeList[current].endY) + dy);
}

bool IsAbove(float x, float y) {
    int current = shapeCount - 1;
    if (shapeList[current].type != SHAPE_LINE && !(shapeList[current].type == SHAPE_TRIANGLE && shapeList[current].isFilled))
        return false;

    float cx = NormX(x);
    float cy = NormY(y);
    float sx = NormX(shapeList[current].startX);
    float sy = NormY(shapeList[current].startY);
    float ex = NormX(shapeList[current].endX);
    float ey = NormY(shapeList[current].endY);

    float left = (cx - sx) / (sx - ex);
    float right = (cy - sy) / (sy - ey);
    float diff = right - left;

    return (diff > -0.04f && diff < 0.04f);
}
