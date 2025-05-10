#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <string>

#pragma comment(lib, "glew32.lib")

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

int exerciseIndex = 0;
const int TOTAL_EXERCISES = 8;
std::string exerciseNames[TOTAL_EXERCISES] = {
    "2.27: Sine Curve",
    "2.28: Ellipse",
    "2.29: Letter A",
    "2.30: Number 8",
    "2.31: Torus Approximation",
    "2.32: Cone",
    "2.33: Slide Curve",
    "2.34: Crescent Moon"
};

void drawSineCurve() {
    const float PI = 3.14159f;
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.5f, 1.0f);
    for (int i = 0; i <= 200; ++i) {
        float x = -PI + i * (2 * PI / 200);
        glVertex2f(x, sin(x));
    }
    glEnd();
}

void drawEllipse() {
    const float PI = 3.14159f;
    int segments = 100;
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.5f);
    for (int i = 0; i <= segments; ++i) {
        float t = 2 * PI * i / segments;
        glVertex2f(0.6f * cos(t), 0.3f * sin(t));
    }
    glEnd();
}

void drawLetterA() {
    glColor3f(0.0f, 0.8f, 0.8f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.3f, -0.5f);
    glVertex2f(0.18f, -0.2f);
    glVertex2f(-0.18f, -0.2f);
    glVertex2f(-0.3f, -0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.0f, 0.3f);
    glVertex2f(0.1f, 0.0f);
    glEnd();
}

void drawNumber8() {
    const float PI = 3.14159f;
    int segments = 100;

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.5f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2 * PI * i / segments;
        glVertex2f(0.3f * cos(theta), 0.3f + 0.3f * sin(theta));
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2 * PI * i / segments;
        glVertex2f(0.3f * cos(theta), -0.3f + 0.3f * sin(theta));
    }
    glEnd();
}

void drawTorusApproximation() {
    const float PI = 3.14159f;
    int segments = 100;
    int sides = 6;

    glColor3f(0.5f, 0.0f, 0.8f);
    for (int i = 0; i < sides; ++i) {
        float a1 = 2 * PI * i / sides;
        float a2 = 2 * PI * (i + 1) / sides;

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= segments; ++j) {
            float theta = 2 * PI * j / segments;
            float x1 = (0.6f + 0.2f * cos(a1)) * cos(theta);
            float y1 = 0.2f * sin(a1);
            float x2 = (0.6f + 0.2f * cos(a2)) * cos(theta);
            float y2 = 0.2f * sin(a2);

            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        glEnd();
    }
}

void drawCone() {
    const float PI = 3.14159f;
    int segments = 100;

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.7f, 0.7f);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2 * PI * i / segments;
        glVertex2f(0.5f * cos(angle), -0.5f + 0.5f * sin(angle));
    }
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i <= segments; i += 10) {
        float angle = 2 * PI * i / segments;
        glVertex2f(0.5f * cos(angle), -0.5f + 0.5f * sin(angle));
        glVertex2f(0.0f, 0.5f);
    }
    glEnd();
}

void drawSlideCurve() {
    glBegin(GL_LINE_STRIP);
    glColor3f(0.8f, 0.2f, 0.2f);
    for (int i = 0; i <= 100; ++i) {
        float x = -1.0f + i * (2.0f / 100);
        float y = 1.0f - x * x;
        glVertex2f(x, y - 0.5f);
    }
    glEnd();
}

void drawCrescentMoon() {
    const float PI = 3.14159f;
    int segments = 100;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2 * PI * i / segments;
        glVertex2f(0.4f * cos(theta), 0.4f * sin(theta));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.2f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2 * PI * i / segments;
        glVertex2f(0.3f + 0.4f * cos(theta), 0.4f * sin(theta));
    }
    glEnd();
}

void renderText(float x, float y, const std::string& text) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    renderText(-0.9f, 0.9f, exerciseNames[exerciseIndex]);

    switch (exerciseIndex) {
    case 0: drawSineCurve(); break;
    case 1: drawEllipse(); break;
    case 2: drawLetterA(); break;
    case 3: drawNumber8(); break;
    case 4: drawTorusApproximation(); break;
    case 5: drawCone(); break;
    case 6: drawSlideCurve(); break;
    case 7: drawCrescentMoon(); break;
    }

    renderText(-0.9f, -0.9f, "Use LEFT/RIGHT arrows to navigate");

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

    if (w <= h) {
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w);
    }
    else {
        gluOrtho2D(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

void specialKeyInput(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        exerciseIndex = (exerciseIndex + 1) % TOTAL_EXERCISES;
    }
    else if (key == GLUT_KEY_LEFT) {
        exerciseIndex = (exerciseIndex - 1 + TOTAL_EXERCISES) % TOTAL_EXERCISES;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ramin Joshang Practice 13");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;
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
