// shape.h
#pragma once

#include <string>
#include <vector>

struct Point
{
    float x;
    float y;
};

struct Color
{
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
};

enum ShapeType
{
    SHAPE_NONE,
    SHAPE_POINT,
    SHAPE_LINE,
    SHAPE_TRIANGLE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_RIGHT_TRIANGLE
};

struct Shape
{
    ShapeType type = SHAPE_NONE;
    float startX = 0.0f, startY = 0.0f;
    float endX = 0.0f, endY = 0.0f;
    float pointSize = 1.0f;
    float lineWidth = 1.0f;
    bool isFilled = false;
    bool isActivated = false;
    Color color;
    float rotated = 0.0f;
    float focusX = 0.0f;
    float focusY = 0.0f;
    std::vector<Point> pencilPoints;
};

struct ShapeInfo
{
    int shapeNo = 0;
    Point Cordinate[10000];
};

constexpr int MAX_SHAPES = 50;
extern Shape shapeList[MAX_SHAPES];
extern ShapeInfo shapeinfo[MAX_SHAPES];
extern int shapeCount;
