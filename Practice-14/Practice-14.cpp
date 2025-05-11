#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

int shapeIndex = 0;
const int maxShapes = 2;

void drawCube() {
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-10, -10, 10);
    glVertex3f(10, -10, 10);
    glVertex3f(10, 10, 10);
    glVertex3f(-10, -10, 10);
    glVertex3f(10, 10, 10);
    glVertex3f(-10, 10, 10);
    // Other cube faces go here...
    glEnd();
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(0, 15, 0);
    glVertex3f(-10, -10, 10);
    glVertex3f(10, -10, 10);
    glVertex3f(0, 15, 0);
    glVertex3f(10, -10, 10);
    glVertex3f(10, -10, -10);
    glVertex3f(0, 15, 0);
    glVertex3f(10, -10, -10);
    glVertex3f(-10, -10, -10);
    glVertex3f(0, 15, 0);
    glVertex3f(-10, -10, -10);
    glVertex3f(-10, -10, 10);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex3f(-10, -10, 10);
    glVertex3f(10, -10, 10);
    glVertex3f(10, -10, -10);
    glVertex3f(-10, -10, -10);
    glEnd();
}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    switch (shapeIndex) {
    case 0:
        drawCube();
        break;
    case 1:
        drawPyramid();
        break;
    }

    glFlush();
}

void setup(void)
{
    glClearColor(0.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT) {
        shapeIndex = (shapeIndex + 1) % maxShapes;
    }
    else if (key == GLUT_KEY_LEFT) {
        shapeIndex = (shapeIndex - 1 + maxShapes) % maxShapes;
    }
    glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y)
{
    if (key == 27) exit(0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polyhedron Viewer");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeys);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
