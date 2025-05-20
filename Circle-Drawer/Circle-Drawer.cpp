#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#include <cmath>

#define PI 3.14159265358979323846
#define MAX_CIRCLES 100 
struct Circle {
    float x, y, r;
    bool exists = false;
};

Circle circles[MAX_CIRCLES];
int circleCount = 0;
bool drawing = false;
float startX, startY;
float currentRadius = 0.0f;

void drawCircle(float cx, float cy, float r) {
    int numSegments = 100;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * PI * i / numSegments;
        float dx = cx + r * cosf(theta);
        float dy = cy + r * sinf(theta);
        glVertex2f(dx, dy);
    }
    glEnd();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.6f, 0.2f, 0.8f);
    glLineWidth(3);

    for (int i = 0; i < circleCount; i++) {
        if (circles[i].exists) {
            drawCircle(circles[i].x, circles[i].y, circles[i].r);
        }
    }

    if (drawing) {
        drawCircle(startX, startY, currentRadius);
    }

    glFlush();
}

void setup() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

float screenToGlX(int x) { return x * 100.0f / glutGet(GLUT_WINDOW_WIDTH); }
float screenToGlY(int y) { return (glutGet(GLUT_WINDOW_HEIGHT) - y) * 100.0f / glutGet(GLUT_WINDOW_HEIGHT); }

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            drawing = true;
            startX = screenToGlX(x);
            startY = screenToGlY(y);
            currentRadius = 0.0f;
        }
        else if (state == GLUT_UP) {
            drawing = false;
            if (circleCount < MAX_CIRCLES) {
                circles[circleCount++] = { startX, startY, currentRadius, true };
            }
        }
        glutPostRedisplay();
    }
}

void motion(int x, int y) {
    if (drawing) {
        float currentX = screenToGlX(x);
        float currentY = screenToGlY(y);
        currentRadius = sqrtf((currentX - startX) * (currentX - startX) +
            (currentY - startY) * (currentY - startY));
        glutPostRedisplay();
    }
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {
    if (key == 27) exit(0);

    if (key == 8 && circleCount >= 0) {
        circles[circleCount - 1].exists = false;
        circleCount--;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Interactive Circle Drawer");

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
}