#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

using namespace std;

#define M_PI 3.14159265358979323846  // تعریف M_PI به صورت دستی

float radius = 10.0f; // شعاع نیم‌دایره

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // پاک کردن صفحه
    glColor3f(0.6f, 0.2f, 0.8f);  // رنگ نیم‌دایره

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -50.0);  // حرکت به وسط صفحه

    // رسم نیم‌دایره (فقط نیمه بالایی دایره)
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // مرکز دایره
    for (float angle = 0.0f; angle <= 180.0f; angle += 1.0f) {
        float rad = angle * M_PI / 180.0f;  // تبدیل زاویه به رادیان
        glVertex2f(radius * cos(rad), radius * sin(rad));  // نقاط روی نیم‌دایره
    }
    glEnd();

    glutSwapBuffers();  // نمایش به‌روزرسانی
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // پس‌زمینه سفید
    glEnable(GL_DEPTH_TEST);  // فعال‌سازی عمق برای نمایش درست اشیاء
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);  // تنظیم اندازه صفحه‌نمایش
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);  // تنظیم فضای دید
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Half Circle in the Center");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
