#include <cmath>

#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 

#define PI 3.14159265358979323846

float R = 5.0; 
int p = 60; 
int q = 50; 
float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; 
float offset = 0.0;

// Drawing routine.
void drawScene(void)
{
    int  i, j;

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.0, 0.0, -10.0);

    // Commands to turn the hemisphere.
    glRotatef(Xangle, 1.0, 0.0, 0.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.6, 0.2, 0.8);

    for (j = 10; j < 21; j++)
    {
        for (i = 0; i <= p; i++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                R * sin((float)(j + 1) / q * PI / 2.0) - offset,
                R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
            glVertex3f(R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                R * sin((float)j / q * PI / 2.0) - offset,
                R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
        }

    }
    glEnd();
    for (j = 25; j < 50; j++)
    {
        for (i = 0; i <= p; i++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                R * sin((float)(j + 1) / q * PI / 2.0) + offset,
                R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
            glVertex3f(R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                R * sin((float)j / q * PI / 2.0) + offset,
                R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
        }

    }
    glEnd();
    for (j = 0; j < 15; j++)
    {
        for (i = 0; i <= p; i++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                R * sin((float)(j + 1) / q * PI / 2.0) - 2,
                R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
            glVertex3f(R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                R * sin((float)j / q * PI / 2.0) - 2,
                R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
        }

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
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'P':
        p += 1;
        glutPostRedisplay();
        break;
    case 'p':
        if (p > 3) p -= 1;
        glutPostRedisplay();
        break;
    case 'Q':
        q += 1;
        glutPostRedisplay();
        break;
    case 'q':
        if (q > 3) q -= 1;
        glutPostRedisplay();
        break;
    case 'd':
        Xangle += 5.0;
        if (Xangle > 360.0) Xangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'a':
        Xangle -= 5.0;
        if (Xangle < 0.0) Xangle += 360.0;
        glutPostRedisplay();
        break;
    case 'w':
        Yangle += 5.0;
        if (Yangle > 360.0) Yangle -= 360.0;
        glutPostRedisplay();
        break;
    case 's':
        Yangle -= 5.0;
        if (Yangle < 0.0) Yangle += 360.0;
        glutPostRedisplay();
        break;
    case 'e':
        Zangle += 5.0;
        if (Zangle > 360.0) Zangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        Zangle -= 5.0;
        if (Zangle < 0.0) Zangle += 360.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}


// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hemisphere.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
