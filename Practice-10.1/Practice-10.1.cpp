#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

using namespace std;

// Ball Postition and Speed
float posX = 10.0f;
float posY = 90.0f;
float velX = 0.5f;
float velY = 0.0f;

// Phisical Confing
float gravity = -0.3f;
float bounceFactor = 0.8f;
float floorY = 10.0f;

float radius = 5.0f;
bool isStopped = false;

float rotationAngle = 0.0f;

void update(int value);

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.6f, 0.2f, 0.8f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(posX, posY, 0.0);
    glRotatef(rotationAngle, 0.0, 0.0, 1.0);
    glutWireSphere(radius, 30, 30);
    glPopMatrix();

    glFlush();
}

void resetBall(int value)
{
    posX = 10.0f;
    posY = 90.0f;
    velX = 0.5f;
    velY = 0.0f;
    isStopped = false;
    glutTimerFunc(10, update, 0);
}

void update(int value)
{
    if (isStopped)
    {
        glutTimerFunc(3000, resetBall, 0);
        return;
    }

    velY += gravity;
    posY += velY;
    posX += velX;

    rotationAngle += velX * 30.0f;
    if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;

    // برخورد با کف
    if (posY - radius < floorY)
    {
        posY = floorY + radius;
        velY = -velY * bounceFactor;

        if (fabs(velY) < 0.5f)
        {
            velY = 0.0f;
            velX = 0.0f;
            isStopped = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -10.0, 10.0); 
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ramin Joshang Practice 10.1");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();
    glutTimerFunc(10, update, 0);

    glutMainLoop();
}
