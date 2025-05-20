#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 

static int M = 100;
static int direction = 0;

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.6f, 0.2f, 0.8f);
    glLineWidth(2);

    glBegin(GL_LINE_STRIP);
    for (int i = -M; i <= M; ++i) {
        float x, y;

        switch (direction) {
        case 0:
            x = 50.0 + 50.0 * i / M;
            y = 50.0 + 50.0 * (i * i) / (M * M);
            break;
        case 1:
            x = 50.0 + 50.0 * (i * i) / (M * M);
            y = 50.0 + 50.0 * i / M;
            break;
        case 2:
            x = 50.0 + 50.0 * i / M;
            y = 50.0 - 50.0 * (i * i) / (M * M);
            break;
        case 3:
            x = 50.0 - 50.0 * (i * i) / (M * M);
            y = 50.0 + 50.0 * i / M;
            break;
        }
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

void keyInput(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case ' ':
        direction = (direction + 1) % 4;
        glutPostRedisplay();
        break;
    }
}

void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotated Parabola");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();
}