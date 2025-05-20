#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")  
#include <cstdlib>
#include <cmath>

#define PI 3.14159265358979324

static float R = 40.0;
static float X = 50.0;
static float Y = 50.0;
static int numVertices = 3;
static int direction = 1;

void drawScene(void)
{
    float t = 0;
    int i;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.6f, 0.2f, 0.8f);

    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < numVertices; ++i)
    {
        glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
        t += 2 * PI / numVertices;
    }
    glEnd();

    glFlush();
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
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

void animate(int value)
{
    numVertices += direction;

    if (numVertices >= 100)
    {
        numVertices = 100;
        direction = -1;
    }
    else if (numVertices <= 3)
    {
        numVertices = 3;
        direction = 1;
    }

    glutPostRedisplay();
    glutTimerFunc(100, animate, 0);
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC key
        exit(0);
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Growing/Shrinking Polygon");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutTimerFunc(0, animate, 0);

    glutMainLoop();
}