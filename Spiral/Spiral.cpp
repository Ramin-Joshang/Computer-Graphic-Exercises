#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 

#include <cmath>
#include <ctime>

#define PI 3.14159265358979323846

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float CENTER_X = WINDOW_WIDTH / 2.0f;
const float CENTER_Y = WINDOW_HEIGHT / 2.0f;

const int TOTAL_POINTS = 3000;
const int TURNS = 30;
const float MAX_RADIUS = 250.0f;
const float MIN_RADIUS = 10.0f;

float angleOffset = 0.0f;
float drawProgress = 0.0f;
bool drawingComplete = false;
float rotationSpeed = 0.5f;

void setup() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.5f);
}

void drawSpiral() {
    glClear(GL_COLOR_BUFFER_BIT);

    int pointsToDraw = int(TOTAL_POINTS * drawProgress);

    glBegin(GL_LINE_STRIP);
    glColor3f(0.6f, 0.2f, 0.8f);

    for (int i = 0; i < pointsToDraw; i++) {
        float radius = MAX_RADIUS - (MAX_RADIUS - MIN_RADIUS) * (i / (float)TOTAL_POINTS);

        float theta = TURNS * 2 * PI * (i / (float)TOTAL_POINTS) + angleOffset;

        float x = CENTER_X + radius * cos(theta);
        float y = CENTER_Y + radius * sin(theta);

        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    if (!drawingComplete) {
        drawProgress += 0.002f;
        if (drawProgress >= 1.0f) {
            drawProgress = 1.0f;
            drawingComplete = true;
        }
    }

    angleOffset += rotationSpeed * 0.5f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Animated Spiral Drawing");

    setup();
    glutDisplayFunc(drawSpiral);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}