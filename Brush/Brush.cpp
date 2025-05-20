#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#include <cstdlib>
#include <vector>

using namespace std;

static int width, height;
static bool isDrawing = false;

class Point {
public:
    Point(int x, int y) : xVal(x), yVal(y) {}
    int x() const { return xVal; }
    int y() const { return yVal; }
private:
    int xVal, yVal;
};

vector<vector<Point>> strokes;
vector<Point> currentStroke;

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.6, 0.2, 0.8);
    glLineWidth(3);

    for (const auto& stroke : strokes) {
        glBegin(GL_LINE_STRIP);
        for (const auto& pt : stroke)
            glVertex2i(pt.x(), pt.y());
        glEnd();
    }

    if (isDrawing && !currentStroke.empty()) {
        glBegin(GL_LINE_STRIP);
        for (const auto& pt : currentStroke)
            glVertex2i(pt.x(), pt.y());
        glEnd();
    }

    glFlush();
}

void mouseControl(int button, int state, int x, int y) {
    int yCorrected = height - y;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDrawing = true;
            currentStroke.clear();
            currentStroke.push_back(Point(x, yCorrected));
        }
        else if (state == GLUT_UP) {
            isDrawing = false;
            if (!currentStroke.empty())
                strokes.push_back(currentStroke);
            currentStroke.clear();
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        exit(0);

    glutPostRedisplay();
}

void motion(int x, int y) {
    if (isDrawing) {
        int yCorrected = height - y;
        currentStroke.push_back(Point(x, yCorrected));
        glutPostRedisplay();
    }
}

void setup() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
    width = w;
    height = h;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Brush");

    glewExperimental = GL_TRUE;
    glewInit();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseControl);
    glutMotionFunc(motion);

    setup();
    glutMainLoop();
    return 0;
}
