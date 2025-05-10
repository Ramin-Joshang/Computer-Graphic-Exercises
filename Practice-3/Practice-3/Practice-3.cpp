#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SHAPES 500
#define M_PI 3.14159265358979323846

struct Shape {
    GLenum type;
    float x, y;
    float color[3];
    float size;
    float velocityX, velocityY;
    int sides;
    float rotation;
    float rotationSpeed;
};

Shape shapes[MAX_SHAPES];
int numbShpes = MAX_SHAPES;

float randomFloat(float min, float max) {
    return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

GLenum randomType() {
    GLenum types[] = {
        GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,
        GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN,
        GL_POLYGON };
    return types[rand() % 8];
}

void update(int value) {
    for (int i = 0; i < numbShpes; i++) {
        shapes[i].x += shapes[i].velocityX;
        shapes[i].y += shapes[i].velocityY;

        shapes[i].rotation += shapes[i].rotationSpeed * 0.01f;
        if (shapes[i].rotation > 2 * M_PI) {
            shapes[i].rotation -= 2 * M_PI;
        }

        if (shapes[i].x < shapes[i].size * 0.5f || shapes[i].x > 100.0f - shapes[i].size * 0.5f) {
            shapes[i].velocityX *= -1;
            shapes[i].color[0] = randomFloat(0.2f, 1.0f);
            shapes[i].color[1] = randomFloat(0.2f, 1.0f);
            shapes[i].color[2] = randomFloat(0.2f, 1.0f);
        }

        if (shapes[i].y < shapes[i].size * 0.5f || shapes[i].y > 100.0f - shapes[i].size * 0.5f) {
            shapes[i].velocityY *= -1;
            shapes[i].color[0] = randomFloat(0.2f, 1.0f);
            shapes[i].color[1] = randomFloat(0.2f, 1.0f);
            shapes[i].color[2] = randomFloat(0.2f, 1.0f);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void setup(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    srand(time(0));
    for (int i = 0; i < numbShpes; i++) {
        shapes[i].type = randomType();
        shapes[i].x = randomFloat(15.0f, 85.0f);
        shapes[i].y = randomFloat(15.0f, 85.0f);
        shapes[i].size = randomFloat(5.0f, 10.0f);
        shapes[i].color[0] = randomFloat(0.2f, 1.0f);
        shapes[i].color[1] = randomFloat(0.2f, 1.0f);
        shapes[i].color[2] = randomFloat(0.2f, 1.0f);
        shapes[i].velocityX = randomFloat(-1.5, 1.5);
        shapes[i].velocityY = randomFloat(-1.5, 1.5);
        shapes[i].sides = 3 + rand() % 7;
        shapes[i].rotation = 0.0f;
        shapes[i].rotationSpeed = randomFloat(-3.0f, 3.0f);
    }
}

void drawPoint(Shape& shape) {
    glPointSize(shape.size);
    glBegin(GL_POINTS);
    glVertex2f(shape.x, shape.y);
    glEnd();
}

void drawShape(Shape& shape) {
    int vertexCount = 3; 

    if (shape.type == GL_LINES || shape.type == GL_LINE_STRIP || shape.type == GL_LINE_LOOP) {
        vertexCount = 4;
    }
    else if (shape.type == GL_POLYGON) {
        vertexCount = shape.sides;
    }

    glBegin(shape.type);

    for (int i = 0; i < vertexCount; i++) {
        float angle;

        
        if (shape.type == GL_LINES || shape.type == GL_LINE_STRIP || shape.type == GL_LINE_LOOP) {
            angle = M_PI * i / 2.0f;
        }
        else {
            angle = 2.0f * M_PI * i / vertexCount + shape.rotation;
        }

        glVertex2f(shape.x + cos(angle) * shape.size * 0.5f,
            shape.y + sin(angle) * shape.size * 0.5f);
    }

    glEnd();
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < numbShpes; i++) {
        glColor3fv(shapes[i].color);

        if (shapes[i].type == GL_POINTS) {
            drawPoint(shapes[i]);
        }
        else {
            drawShape(shapes[i]);
        }
    }

    glFlush();
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
    switch (key) {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Optimized Shapes");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();
    glutTimerFunc(0, update, 0);
    glutMainLoop();
}