#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

float orthoLeft = 0.0f;
float orthoRight = 100.0f;
float orthoTop = 0.0f;
float orthoBottom = 100.0f;
float orthoNear = -1.0f;
float orthoFar = 1.0f;
float step = 5.0f;

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.5, 0.0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(20.0, 20.0);
    glVertex2f(50.0, 80.0);
    glVertex2f(80.0, 20.0);
    glEnd();

    glFlush();
}

void setup(void)
{
    glClearColor(0.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(orthoLeft, orthoRight, orthoTop, orthoBottom, orthoNear, orthoFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'w':
    case 'W':
        orthoTop += step;
        break;
    case 'z':
    case 'Z':
        orthoTop -= step;
        break;
    case 'a':
    case 'A':
        orthoRight += step;
        break;
    case 'd':
    case 'D':
        orthoRight -= step;
        break;
    case 'r':
    case 'R':
        orthoNear += step;
        break;
    case 's':
    case 'S':
        orthoNear -= step;
        break;
    case 'p':
        orthoRight = 100.0f;
        orthoTop = 0.0f;
        orthoNear = -1.0f;
        break;

    }
    int currentWidth = glutGet(GLUT_WINDOW_WIDTH);
    int currentHeight = glutGet(GLUT_WINDOW_HEIGHT);
    resize(currentWidth, currentHeight);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("experimentPoints.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}