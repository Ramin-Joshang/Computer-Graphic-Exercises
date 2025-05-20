#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846
#define MAX_TRAILS 100 

using namespace std;

struct CircleStep {
    float radius;
    float alpha = 0.3f;
};

CircleStep trails[MAX_TRAILS];
int trailCount = 0;

float currentRadius = 45.0f;
const float centerX = 50.0f;
const float centerY = 50.0f;
const float stepSize = 2.0f;
const float stepDelay = 300;
const float maxRadius = 45.0f;
const float minRadius = 3.0f;
int direction = -1;

void drawCircle(float x, float y, float radius, float r, float g, float b, float alpha) {
    glBegin(GL_LINE_LOOP);
    glColor4f(r, g, b, alpha);
    for (int i = 0; i <= 100; ++i) {
        float angle = 2.0f * PI * float(i) / 100.0f;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < trailCount; ++i) {
        drawCircle(centerX, centerY,
            trails[i].radius,
            0.7f, 0.7f, 0.7f,
            trails[i].alpha);
    }

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.6f, 0.2f, 0.8f, 1.0f);
    for (int i = 0; i <= 100; ++i) {
        float angle = 2.0f * PI * float(i) / 100.0f;
        glVertex2f(centerX + currentRadius * cos(angle), centerY + currentRadius * sin(angle));
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    if (trailCount < MAX_TRAILS) {
        trails[trailCount++] = { currentRadius };
    }

    currentRadius += direction * stepSize;

    if (currentRadius <= minRadius || currentRadius >= maxRadius) {
        direction *= -1;
    }

    glutPostRedisplay();
    glutTimerFunc(stepDelay, update, 0);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void resizeWindow(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 100.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle Animation with Trail");

    glewExperimental = GL_TRUE;
    glewInit();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(handleKeyboard);

    init();
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}