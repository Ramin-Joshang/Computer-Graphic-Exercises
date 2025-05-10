#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 


#define PI 3.14159265

using namespace std;

// Frustum parameters
float leftVal = -5.0;
float rightVal = 5.0;
float bottomVal = -5.0;
float topVal = 5.0;
float nearVal = 5.0;
float farVal = 100.0;

// Camera position and rotation
float camX = 0.0, camY = 0.0, camZ = -60.0; 
float camRotX = 0.0, camRotY = 0.0;  

// Drawing routine.
void drawScene(void)
{
    float R = 20.0; 
    float t; 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.6f, 0.2f, 0.8f);
    glLineWidth(2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(camX, camY, camZ);

    glRotatef(camRotX, 1.0, 0.0, 0.0);
    glRotatef(camRotY, 0.0, 1.0, 0.0);  

    glBegin(GL_LINE_STRIP);
    for (t = -10 * PI; t <= 10 * PI; t += PI / 20.0)
        glVertex3f(R * cos(t), R * sin(t), t);
    glEnd();

    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
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
        camZ += step;
        break;
    case 'q':  
        camZ -= step;
        break;
    case 'r':
        camX = 0.0;
        camY = 0.0;
        camZ = -60.0;
        camRotX = 0.0;
        camRotY = 0.0;
        leftVal = -5.0;
        rightVal = 5.0;
        bottomVal = -5.0;
        topVal = 5.0;
        nearVal = 5.0;
        farVal = 100.0;
        break;
    }

    glutPostRedisplay();
    resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// Special keyboard input for arrow keys
void specialKeyInput(int key, int x, int y)
{
    float step = 1.0; 

    switch (key)
    {
    case GLUT_KEY_UP:  
        camY += step;
        break;
    case GLUT_KEY_DOWN: 
        camY -= step;
        break;
    case GLUT_KEY_LEFT: 
        camX -= step;
        break;
    case GLUT_KEY_RIGHT:
        camX += step;
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

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ramin Joshang Practice-9");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
