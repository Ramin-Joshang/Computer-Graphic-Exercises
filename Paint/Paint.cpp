#include <cstdlib>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

using namespace std;

#define INACTIVE 0
#define POINT 1
#define LINE 2
#define RECTANGLE 3
#define NUMBERPRIMITIVES 3

using namespace std;

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?

// Point class.
class Point
{
public:
    Point(int xVal, int yVal)
    {
        x = xVal; y = yVal;
    }
    void drawPoint(void); // Function to draw a point.
private:
    int x, y; // x and y co-ordinates of point.
    static float size; // Size of point.
};

float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::drawPoint()
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex3f(x, y, 0.0);
    glEnd();
}

// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator;

// Function to draw all points in the points array.
void drawPoints(void)
{
    // Loop through the points array drawing each point.
    pointsIterator = points.begin();
    while (pointsIterator != points.end())
    {
        pointsIterator->drawPoint();
        pointsIterator++;
    }
}

// Line class.
class Line
{
public:
    Line(int x1Val, int y1Val, int x2Val, int y2Val)
    {
        x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
    }
    void drawLine();
private:
    int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};

// Function to draw a line.
void Line::drawLine()
{
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    glEnd();
}

// Vector of lines.
vector<Line> lines;

// Iterator to traverse a Line array.
vector<Line>::iterator linesIterator;

// Function to draw all lines in the lines array.
void drawLines(void)
{
    // Loop through the lines array drawing each line.
    linesIterator = lines.begin();
    while (linesIterator != lines.end())
    {
        linesIterator->drawLine();
        linesIterator++;
    }
}

// Rectangle class.
class Rect
{
public:
    Rect(int x1Val, int y1Val, int x2Val, int y2Val)
    {
        x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
    }
    void drawRectangle();
private:
    int x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
};

// Function to draw a rectangle.
void Rect::drawRectangle()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(x1, y1, x2, y2);
}

// Vector of rectangles.
vector<Rect> rectangles;

// Iterator to traverse a Rect array.
vector<Rect>::iterator rectanglesIterator;

// Function to draw all rectangles in the rectangles array.
void drawRectangles(void)
{
    // Loop through the rectangles array drawing each rectangle.
    rectanglesIterator = rectangles.begin();
    while (rectanglesIterator != rectangles.end())
    {
        rectanglesIterator->drawRectangle();
        rectanglesIterator++;
    }
}

// Function to draw the menu bar at the top.
void drawMenuBar(void)
{
    glColor3f(0.7, 0.7, 0.7); // Light gray color for the menu bar.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, height - 50, width, height); // Create a rectangle for the menu bar.

    glColor3f(0.0, 0.0, 0.0); // Black for menu text.
    glRasterPos2f(20.0, height - 30);
    const char* menuText = "Paint - [P]oint, [L]ine, [R]ectangle, [G]rid Toggle, [C]lear";
    for (const char* c = menuText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Function to draw a grid.
void drawGrid(void)
{
    int i;

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x5555);
    glColor3f(0.75, 0.75, 0.75);

    glBegin(GL_LINES);
    for (i = 2; i <= 9; i++)
    {
        glVertex3f(i * 0.1 * width, 0.0, 0.0);
        glVertex3f(i * 0.1 * width, height, 0.0);
    }
    for (i = 1; i <= 9; i++)
    {
        glVertex3f(0.1 * width, i * 0.1 * height, 0.0);
        glVertex3f(width, i * 0.1 * height, 0.0);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawMenuBar(); // Draw the top menu bar.

    drawPoints();
    drawLines();
    drawRectangles();

    if (primitive == LINE || primitive == RECTANGLE)
        //if (pointCount == 1) drawTempPoint();
    if (isGrid) drawGrid();

    glutSwapBuffers();
}

// Mouse control routine.
void mouseControl(int button, int state, int x, int y)
{
    y = height - y; // Correct for OpenGL's origin being at the bottom-left.

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (x < 0.1 * width) // Left sidebar
        {
            // Handle menu selection based on y position
            if (y > height - 50 && y < height) primitive = POINT;
            else if (y > height - 100 && y < height - 50) primitive = LINE;
            else if (y > height - 150 && y < height - 100) primitive = RECTANGLE;
        }
        else // Canvas area
        {
            if (primitive == POINT) points.push_back(Point(x, y));
            else if (primitive == LINE)
            {
                if (pointCount == 0)
                {
                    tempX = x; tempY = y;
                    pointCount++;
                }
                else
                {
                    lines.push_back(Line(tempX, tempY, x, y));
                    pointCount = 0;
                }
            }
            else if (primitive == RECTANGLE)
            {
                if (pointCount == 0)
                {
                    tempX = x; tempY = y;
                    pointCount++;
                }
                else
                {
                    rectangles.push_back(Rect(tempX, tempY, x, y));
                    pointCount = 0;
                }
            }
        }
    }
    glutPostRedisplay();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
    width = w;
    height = h;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p': primitive = POINT; break;
    case 'l': primitive = LINE; break;
    case 'r': primitive = RECTANGLE; break;
    case 'g': isGrid = !isGrid; break;
    case 'c': points.clear(); lines.clear(); rectangles.clear(); break;
    case 27: exit(0); break; // ESC to exit
    default: break;
    }
    glutPostRedisplay();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Paint - OpenGL");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseControl);
    glutKeyboardFunc(keyInput);
    setup();
    glutMainLoop();
    return 0;
}
