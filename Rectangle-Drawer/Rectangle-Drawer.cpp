#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib")
#include <cmath>

#define MAX_SHAPES 100

struct Shape
{
    float x1, y1, x2, y2;
    bool exists = false;
    bool isRectangle;
};

Shape shapes[MAX_SHAPES];
int shapeCount = 0;
bool drawing = false;
float startX, startY;
float endX, endY;

void drawShape(float x1, float y1, float x2, float y2)
{

    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.6f, 0.2f, 0.8f);
    glLineWidth(3);

    for (int i = 0; i < shapeCount; i++)
    {
        if (shapes[i].exists)
        {
            drawShape(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2);
        }
    }

    if (drawing)
    {
        drawShape(startX, startY, endX, endY);
    }

    glFlush();
}

void setup()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

float screenToGlX(int x) { return x * 100.0f / glutGet(GLUT_WINDOW_WIDTH); }
float screenToGlY(int y) { return (glutGet(GLUT_WINDOW_HEIGHT) - y) * 100.0f / glutGet(GLUT_WINDOW_HEIGHT); }

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            drawing = true;
            startX = screenToGlX(x);
            startY = screenToGlY(y);
            endX = startX;
            endY = startY;
        }
        else if (state == GLUT_UP)
        {
            drawing = false;

            if (shapeCount < MAX_SHAPES)
            {
                bool isRectangle = (startX != endX) && (startY != endY);
                shapes[shapeCount++] = {startX, startY, endX, endY, true, isRectangle};
            }
        }
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    if (drawing)
    {
        endX = screenToGlX(x);
        endY = screenToGlY(y);
        glutPostRedisplay();
    }
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);

    if (key == 8 && shapeCount >= 0)
    {
        shapes[shapeCount - 1].exists = false;
        shapeCount--;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Interactive Rectangle Drawer");

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
}