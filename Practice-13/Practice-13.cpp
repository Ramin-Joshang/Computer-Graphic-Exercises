#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <string>

#pragma comment(lib, "glew32.lib")

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const float PI = 3.14159f;

int exerciseIndex = 0;
const int TOTAL_EXERCISES = 10;


void drawSineCurve() {
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 200; ++i) {
        float x = -PI + i * (2 * PI / 200);
        glVertex2f(x, sin(x));
    }
    glEnd();
}

void drawEllipse() {
    glColor3f(1.0f, 0.0f, 0.5f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; ++i) {
        float t = 2 * PI * i / 100;
        glVertex2f(0.6f * cos(t), 0.3f * sin(t));
    }
    glEnd();
}

void drawLetterA() {
    glColor3f(0.0f, 0.8f, 0.8f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.5f); glVertex2f(0.0f, 0.6f); glVertex2f(0.5f, -0.5f);
    glVertex2f(0.3f, -0.5f); glVertex2f(0.18f, -0.2f);
    glVertex2f(-0.18f, -0.2f); glVertex2f(-0.3f, -0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1f, 0.0f); glVertex2f(0.0f, 0.3f); glVertex2f(0.1f, 0.0f);
    glEnd();
}

void drawNumber8() {
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; ++i) {
        float t = 2 * PI * i / 100;
        glVertex2f(0.3f * cos(t), 0.3f + 0.3f * sin(t));
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; ++i) {
        float t = 2 * PI * i / 100;
        glVertex2f(0.3f * cos(t), -0.3f + 0.3f * sin(t));
    }
    glEnd();
}

void drawTorusApproximation() {
    glColor3f(0.5f, 0.0f, 0.8f);
    for (int i = 0; i < 6; ++i) {
        float a1 = 2 * PI * i / 6, a2 = 2 * PI * (i + 1) / 6;
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= 100; ++j) {
            float t = 2 * PI * j / 100;
            float x1 = (0.6f + 0.2f * cos(a1)) * cos(t);
            float y1 = 0.2f * sin(a1);
            float x2 = (0.6f + 0.2f * cos(a2)) * cos(t);
            float y2 = 0.2f * sin(a2);
            glVertex2f(x1, y1); glVertex2f(x2, y2);
        }
        glEnd();
    }
}

void drawCone() {
    glColor3f(0.0f, 0.7f, 0.7f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; ++i)
        glVertex2f(0.5f * cos(2 * PI * i / 100), -0.5f + 0.5f * sin(2 * PI * i / 100));
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i <= 100; i += 10) {
        float angle = 2 * PI * i / 100;
        glVertex2f(0.5f * cos(angle), -0.5f + 0.5f * sin(angle));
        glVertex2f(0.0f, 0.5f);
    }
    glEnd();
}

void drawSlideCurve() {
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; ++i) {
        float x = -1.0f + i * 2.0f / 100;
        glVertex2f(x, 0.5f - x * x);
    }
    glEnd();
}

void drawCrescentMoon() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 100; ++i)
        glVertex2f(0.4f * cos(2 * PI * i / 100), 0.4f * sin(2 * PI * i / 100));
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.2f, 0.0f);
    for (int i = 0; i <= 100; ++i)
        glVertex2f(0.3f + 0.4f * cos(2 * PI * i / 100), 0.4f * sin(2 * PI * i / 100));
    glEnd();
}

void drawCube() {
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_LINE_LOOP); glVertex2f(-0.4f, -0.4f); glVertex2f(0.4f, -0.4f); glVertex2f(0.4f, 0.4f); glVertex2f(-0.4f, 0.4f); glEnd();
    glBegin(GL_LINE_LOOP); glVertex2f(-0.2f, -0.2f); glVertex2f(0.6f, -0.2f); glVertex2f(0.6f, 0.6f); glVertex2f(-0.2f, 0.6f); glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.4f, -0.4f); glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.4f, -0.4f); glVertex2f(0.6f, -0.2f);
    glVertex2f(0.4f, 0.4f); glVertex2f(0.6f, 0.6f);
    glVertex2f(-0.4f, 0.4f); glVertex2f(-0.2f, 0.6f);
    glEnd();
}

void drawRectangularPrism() {
    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_LINE_LOOP); glVertex2f(-0.6f, -0.3f); glVertex2f(0.3f, -0.3f); glVertex2f(0.3f, 0.3f); glVertex2f(-0.6f, 0.3f); glEnd();
    glBegin(GL_LINE_LOOP); glVertex2f(-0.4f, -0.1f); glVertex2f(0.5f, -0.1f); glVertex2f(0.5f, 0.5f); glVertex2f(-0.4f, 0.5f); glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.6f, -0.3f); glVertex2f(-0.4f, -0.1f);
    glVertex2f(0.3f, -0.3f); glVertex2f(0.5f, -0.1f);
    glVertex2f(0.3f, 0.3f); glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.6f, 0.3f); glVertex2f(-0.4f, 0.5f);
    glEnd();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (exerciseIndex) {
    case 0: drawSineCurve(); break;
    case 1: drawEllipse(); break;
    case 2: drawLetterA(); break;
    case 3: drawNumber8(); break;
    case 4: drawTorusApproximation(); break;
    case 5: drawCone(); break;
    case 6: drawSlideCurve(); break;
    case 7: drawCrescentMoon(); break;
    case 8: drawCube(); break;
    case 9: drawRectangularPrism(); break;
    }

    glutSwapBuffers();
}

void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) gluOrtho2D(-1.0, 1.0, -1.0 * h / w, 1.0 * h / w);
    else gluOrtho2D(-1.0 * w / h, 1.0 * w / h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int, int) {
    if (key == 27) exit(0);
}

void specialKeyInput(int key, int, int) {
    if (key == GLUT_KEY_RIGHT)
        exerciseIndex = (exerciseIndex + 1) % TOTAL_EXERCISES;
    else if (key == GLUT_KEY_LEFT)
        exerciseIndex = (exerciseIndex - 1 + TOTAL_EXERCISES) % TOTAL_EXERCISES;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL 2D Shapes Demo");

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed.\n";
        return 1;
    }

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    setup();
    glutMainLoop();
    return 0;
}
