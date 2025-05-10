#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

using namespace std;

static int width, height;
static float pointSize = 3.0;

class Point
{
public:
    Point(int x, int y) : xVal(x), yVal(y) {}
    void drawPoint() const; 
private:
    int xVal, yVal;
    static float size;
};

float Point::size = pointSize;

void Point::drawPoint() const
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2i(xVal, yVal);
    glEnd();
}

class Line
{
public:
    Line(int x1, int y1, int x2, int y2)
        : x1(x1), y1(y1), x2(x2), y2(y2) {}
    void drawLine() const; 
private:
    int x1, y1, x2, y2;
};

void Line::drawLine() const
{
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

vector<Point> points;
vector<Line> lines;
static bool isFirstPoint = false;
static int tempX, tempY;

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    for (const auto& point : points)
        point.drawPoint();

    for (const auto& line : lines)
        line.drawLine();

    glFlush();
}

void mouseControl(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int currentX = x;
        int currentY = height - y;

        if (!isFirstPoint)
        {
            tempX = currentX;
            tempY = currentY;
            points.emplace_back(tempX, tempY);
            isFirstPoint = true;
        }
        else
        {
            points.emplace_back(currentX, currentY);
            lines.emplace_back(tempX, tempY, currentX, currentY);
            isFirstPoint = false;
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        exit(0);

    glutPostRedisplay();
}

void setup()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
    width = w;
    height = h;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
    if (key == 27) exit(0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ramin Joshang Practice 17");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseControl);
    glewExperimental = GL_TRUE;
    glewInit();
    setup();
    glutMainLoop();
    return 0;
}