#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <cmath>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <cstdio>
#pragma comment(lib, "glew32.lib")

const float PI = 3.14159265358979323846f;
const int WINDOW_SIZE = 400;

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void drawCircle(float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * PI * float(i) / float(segments);
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

void drawHand(float length, float width, float angle) {
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, length);
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    time_t rawTime;
    time(&rawTime);
    struct tm* timeInfo = localtime(&rawTime);

    int hours = timeInfo->tm_hour % 12;
    int minutes = timeInfo->tm_min;
    int seconds = timeInfo->tm_sec;

    float secondAngle = 360.0f - seconds * 6.0f;
    float minuteAngle = 360.0f - minutes * 6.0f;
    float hourAngle = 360.0f - (hours * 30.0f + minutes * 0.5f);

    glColor3f(0.8f, 0.8f, 0.8f);
    drawCircle(0.9f, 100);

    glColor3f(0.6f, 0.6f, 0.6f);
    for (int i = 0; i < 12; ++i) {
        glPushMatrix();
        glRotatef(i * 30.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.85f);
        glVertex2f(0.0f, 0.95f);
        glEnd();
        glPopMatrix();
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 1; i <= 12; ++i) {
        float angleDeg = 90.0f - i * 30.0f;
        float angleRad = angleDeg * PI / 180.0f;

        float x = 0.78f * cos(angleRad);
        float y = 0.78f * sin(angleRad);

        float offset = (i >= 10) ? 0.04f : 0.025f;
        glRasterPos2f(x - offset, y - 0.025f);

        if (i >= 10)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + (i % 10));
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    drawHand(0.8f, 2.0f, secondAngle);

    glColor3f(0.9f, 0.9f, 0.9f);
    drawHand(0.7f, 4.0f, minuteAngle);

    glColor3f(0.2f, 0.6f, 1.0f);
    drawHand(0.5f, 6.0f, hourAngle);

    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    float secAngleRad = (360.0f - secondAngle) * PI / 180.0f;
    float tipX = 0.8f * sin(secAngleRad);
    float tipY = 0.8f * cos(secAngleRad);

    float boxWidth = 0.3f;
    float boxHeight = 0.1f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(tipX - boxWidth / 2, tipY + boxHeight / 2);
    glVertex2f(tipX + boxWidth / 2, tipY + boxHeight / 2);
    glVertex2f(tipX + boxWidth / 2, tipY - boxHeight / 2);
    glVertex2f(tipX - boxWidth / 2, tipY - boxHeight / 2);
    glEnd();

    char timeText[9];
    sprintf(timeText, "%02d:%02d:%02d", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(tipX - 0.12f, tipY - 0.03f);
    for (int i = 0; timeText[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, timeText[i]);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;
    if (aspect > 1.0) {
        glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    }
    else {
        glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);
    }
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutCreateWindow("Ramin Joshang Practice-12");

    glewInit();

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
