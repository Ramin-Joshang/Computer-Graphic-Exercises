#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#pragma comment(lib, "glew32.lib")

#define MAX_SHAPES 100

struct Shape {
    float x1, y1, x2, y2; 
    bool exists = false;
    bool isRectangle; 
    float color[3];
};

Shape shapes[MAX_SHAPES];
int shapeCount = 0;
bool drawing = false;
float startX, startY;
float endX, endY;
int currentShape = 0;
float currentColor[3] = { 0.6f, 0.2f, 0.8f }; 

void drawCircle(float cx, float cy, float r) {
    int numSegments = 100;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * i / numSegments;
        float dx = cx + r * cosf(theta);
        float dy = cy + r * sinf(theta);
        glVertex2f(dx, dy);
    }
    glEnd();
}

void drawShape(float x1, float y1, float x2, float y2, bool isRectangle) {
    if (isRectangle) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }
    else {
        float radius = sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / 2;
        float centerX = (x1 + x2) / 2;
        float centerY = (y1 + y2) / 2;
        drawCircle(centerX, centerY, radius);
    }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(currentColor); 
    glLineWidth(3);

    for (int i = 0; i < shapeCount; i++) {
        if (shapes[i].exists) {
            glColor3fv(shapes[i].color);  
            drawShape(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].isRectangle);
        }
    }


    if (drawing) {
        glColor3fv(currentColor); 
        drawShape(startX, startY, endX, endY, currentShape == 1); 
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
            endX = startX;
            endY = startY;
        }
        else if (state == GLUT_UP) {
            drawing = false;

            if (shapeCount < MAX_SHAPES) {
                bool isRectangle = (currentShape == 1);  
                shapes[shapeCount++] = { startX, startY, endX, endY, true, isRectangle, { currentColor[0], currentColor[1], currentColor[2] } };
            }
        }
        glutPostRedisplay();
    }
}

void motion(int x, int y) {
    if (drawing) {
        endX = screenToGlX(x);
        endY = screenToGlY(y);
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

    if (key == 8 && shapeCount > 0) {  
        shapes[shapeCount - 1].exists = false;
        shapeCount--;
        glutPostRedisplay();
    }

}

// Choose Color
void setColor(int option) {
    switch (option) {
    case 1: currentColor[0] = 1.0f; currentColor[1] = 0.0f; currentColor[2] = 0.0f; break; // Red
    case 2: currentColor[0] = 0.0f; currentColor[1] = 1.0f; currentColor[2] = 0.0f; break; // Green
    case 3: currentColor[0] = 0.0f; currentColor[1] = 0.0f; currentColor[2] = 1.0f; break; // Blue
    case 4: currentColor[0] = 1.0f; currentColor[1] = 1.0f; currentColor[2] = 0.0f; break; // Yellow
    case 5: currentColor[0] = 1.0f; currentColor[1] = 0.5f; currentColor[2] = 0.0f; break; // Orange
    case 6: currentColor[0] = 0.5f; currentColor[1] = 0.0f; currentColor[2] = 0.5f; break; // Purple
    case 7: currentColor[0] = 0.0f; currentColor[1] = 1.0f; currentColor[2] = 1.0f; break; // Cyan
    }
}

void setShape(int option) {
    currentShape = option;
}

void createMenu() {
    int shapeMenu = glutCreateMenu(setShape);
    glutAddMenuEntry("Circle", 0);  
    glutAddMenuEntry("Rectangle", 1);  

    int colorMenu = glutCreateMenu(setColor);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Orange", 5);
    glutAddMenuEntry("Purple", 6);
    glutAddMenuEntry("Cyan", 7);

    int mainMenu = glutCreateMenu(NULL);
    glutAddSubMenu("Shape", shapeMenu);
    glutAddSubMenu("Color", colorMenu);
    glutAddMenuEntry("Quit", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ramin Joshang Practice 16");

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    createMenu();  

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
}
