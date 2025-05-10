#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846

using namespace std;

// Global variables.
static float R = 40.0; 
static float X = 50.0; 
static float Y = 50.0; 
static int numVertices = 100; 
static int direction = 1; 
static float scaleSpeed = 0.5; 

// Drawing routine.
void drawScene(void)
{
    float t = 0;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.6f, 0.2f, 0.8f); 

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= numVertices; ++i)
    {
        glVertex2f(X + R * cos(t), Y + R * sin(t));
        t += 2 * PI / numVertices;
    }
    glEnd();

    glFlush();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); 
}

// Window resize routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Animation timer callback.
void animate(int value)
{
    R += direction * scaleSpeed;

    if (R >= 45.0) direction = -1;
    if (R <= 10.0) direction = 1;

    glutPostRedisplay();
    glutTimerFunc(16, animate, 0); // ~60 FPS
}

// Keyboard input handling.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: 
        exit(0);
        break;
    case ' ': 
        if (scaleSpeed == 0) scaleSpeed = 0.5;
        else scaleSpeed = 0;
        break;
    }
}

// Interaction instructions.
void printInteraction()
{
    cout << "Interaction:\n";
    cout << "Press SPACE to pause/resume\n";
    cout << "Press ESC to exit\n";
}

int main(int argc, char** argv)
{
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pulsating Circle");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();
    glutTimerFunc(0, animate, 0);
    glutMainLoop();
}