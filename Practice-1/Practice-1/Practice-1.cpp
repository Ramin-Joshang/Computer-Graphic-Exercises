#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#include <cstdlib>
#include <ctime>

#define NUMBER_OF_CURVES 50
#define ANIMATION_DELAY 1

struct BezierCurve {
    float cp[4][2];
    float vel[4][2];
    float color[3];
};

BezierCurve curves[NUMBER_OF_CURVES];
int windowWidth = 800, windowHeight = 800;
bool paused = false;

float randFloat(float min, float max) {
    return min + (max - min) * rand() / RAND_MAX;
}

void initCurves() {
    srand(time(0));
    for (int i = 0; i < NUMBER_OF_CURVES; i++) {
        for (int j = 0; j < 4; j++) {
            curves[i].cp[j][0] = randFloat(10, 90);
            curves[i].cp[j][1] = randFloat(10, 90);
            curves[i].vel[j][0] = randFloat(-0.15, 0.15);
            curves[i].vel[j][1] = randFloat(-0.15, 0.15);
        }
        curves[i].color[0] = randFloat(0.2, 1.0);
        curves[i].color[1] = randFloat(0.2, 1.0);
        curves[i].color[2] = randFloat(0.2, 1.0);
    }
}

void update(int value) {
    if (!paused) {
        for (int i = 0; i < NUMBER_OF_CURVES; i++) {
            for (int j = 0; j < 4; j++) {
                curves[i].cp[j][0] += curves[i].vel[j][0];
                curves[i].cp[j][1] += curves[i].vel[j][1];

                if (curves[i].cp[j][0] < 0 || curves[i].cp[j][0] > 100) {
                    curves[i].vel[j][0] *= -1;
                    curves[i].cp[j][0] = curves[i].cp[j][0] < 0 ? 0 : 100;
                }

                if (curves[i].cp[j][1] < 0 || curves[i].cp[j][1] > 100) {
                    curves[i].vel[j][1] *= -1;
                    curves[i].cp[j][1] = curves[i].cp[j][1] < 0 ? 0 : 100;
                }
            }
        }
        glutPostRedisplay();
    }
    glutTimerFunc(ANIMATION_DELAY, update, 0);
}

void drawCurve(BezierCurve* curve) {
    glBegin(GL_LINE_STRIP);
    // Bernstein polynomial
    // B(t) = (1 - t) ^ 3 P_0 + 3t(1 - t) ^ 2 P_1 + 3t ^ 2(1 - t) P_2 + t ^ 3 P_3
    for (int i = 0; i <= 50; i++) {
        float t = i / 50.0f;
        float mt = 1 - t;
        float x = mt * mt * mt * curve->cp[0][0] +
            3 * mt * mt * t * curve->cp[1][0] +
            3 * mt * t * t * curve->cp[2][0] +
            t * t * t * curve->cp[3][0];

        float y = mt * mt * mt * curve->cp[0][1] +
            3 * mt * mt * t * curve->cp[1][1] +
            3 * mt * t * t * curve->cp[2][1] +
            t * t * t * curve->cp[3][1];
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < NUMBER_OF_CURVES; i++) {
        glColor3fv(curves[i].color);
        drawCurve(&curves[i]);
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: exit(0);
    case ' ': paused = !paused; break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Ramin Joshang Practice 1");

    initCurves();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    //glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glClearColor(0.0, 0.0, 0.0,0.0);
    glLineWidth(5.0f);

    glutMainLoop();
    return 0;
}