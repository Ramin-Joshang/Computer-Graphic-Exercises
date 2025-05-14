#include <cstdlib>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 

#define PI 3.14159265

// Frustum parameters
int leftVal = -5;
int rightVal = 5;
int bottomVal = -5;
int topVal = 5;
int nearVal = 5;
int farVal = 100;

// Camera position and rotation
int camRotX = 0, camRotY = 0, camRotZ = 0;

// Drawing routine.
void drawScene(void)
{
    float R = 5.0;
    float t;

    glClear(GL_COLOR_BUFFER_BIT );
    glColor3f(0.6f, 0.2f, 0.8f);
    glLineWidth(2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(camRotX, 1.0, 0.0, 0.0);
    glRotatef(camRotY, 0.0, 1.0, 0.0);
    glRotatef(camRotZ, 0.0, 0.0, 1.0);

    glBegin(GL_LINE_STRIP);
    for (t = -50 * PI; t <= 50 * PI; t += PI / 20.0)
        glVertex3f(R * cos(t), R * sin(t), t);
    glEnd();

    glFlush();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(leftVal, rightVal, bottomVal, topVal, nearVal, farVal);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    float step = 1.0;
    float rotationStep = 5.0;

    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'a':
        camRotY -= rotationStep;
        break;
    case 'd':
        camRotY += rotationStep;
        break;
    case 's':
        camRotX += rotationStep;
        break;
    case 'w':
        camRotX -= rotationStep;
        break;
    case 'e':
        camRotZ += rotationStep;
        break;
    case 'q':
        camRotZ -= rotationStep;
        break;
    case '2':
        topVal -= step;
        break;
    case '8':
        topVal += step;
        break;
    case '6':
        rightVal += step;
        break;
    case '4':
        rightVal -= step;
        break;
    case '9':
        nearVal += step;
        break;
    case '1':
        nearVal -= step;
        break;
    case 'r':
        camRotX = 0;
        camRotY = 0;
        camRotZ = 0;
        leftVal = -5;
        rightVal = 5;
        bottomVal = -5;
        topVal = 5;
        nearVal = 5;
        farVal = 100;
        break;
    }

    glutPostRedisplay();
    resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ramin Joshang Practice-9");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
