///////////////////////////////////////////////////////////////////////////////////////
// hemisphere_sliced.cpp - با قاچ شرق به غرب و شکاف بین‌شان
///////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

#define PI 3.14159265

using namespace std;

static float R = 5.0;
static int p = 30, q = 30;       // Resolution
static float gapAngle = 5.0;     // زاویه شکاف بین قاچ‌ها (درجه)
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;

// رسم نیم‌کره به صورت قاچ‌های شرق به غرب با یک شکاف
void drawScene(void)
{
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.2, 0.4, 0.8);

    // رسم نیم‌کره به دو قسمت
    for (i = 0; i < p; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (j = 0; j <= q; j++)
        {
            // زاویه‌های طولی (theta) از 0 تا 360 درجه برای تقسیم در راستای شرق به غرب
            float theta = (float)i / p * 360.0;   // زاویه طولی
            float thetaNext = (float)(i + 1) / p * 360.0;

            // زاویه‌های عرضی (phi) از 0 تا PI/2 برای نیم‌کره
            float phi = (float)j / q * PI / 2.0;
            float phiNext = (float)(j + 1) / q * PI / 2.0;

            // محاسبه مختصات نقاط در نیم‌کره
            float x1 = R * cos(phiNext) * cos(theta);
            float y1 = R * sin(phiNext);
            float z1 = R * cos(phiNext) * sin(theta);

            float x2 = R * cos(phi) * cos(theta);
            float y2 = R * sin(phi);
            float z2 = R * cos(phi) * sin(theta);

            // رسم نقاط برای نیم‌کره
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);

            // همچنین برای زاویه بعدی (thetaNext)
            x1 = R * cos(phiNext) * cos(thetaNext);
            y1 = R * sin(phiNext);
            z1 = R * cos(phiNext) * sin(thetaNext);

            x2 = R * cos(phi) * cos(thetaNext);
            y2 = R * sin(phi);
            z2 = R * cos(phi) * sin(thetaNext);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    // رسم شکاف بین قاچ‌ها
    glColor3f(1.0, 0.0, 0.0);  // رنگ شکاف به قرمز
    glLineWidth(3.0);  // ضخامت خط شکاف بیشتر می‌شود

    // رسم شکاف در امتداد محور x (شرق به غرب)
    glBegin(GL_LINES);
    glVertex3f(R, 0.0, 0.0); // نقطه اول (شرق)
    glVertex3f(-R, 0.0, 0.0); // نقطه دوم (غرب)
    glEnd();

    glFlush();
}

void setup(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: exit(0); break;
    case '+': p++; q++; glutPostRedisplay(); break;
    case '-': if (p > 3) p--; if (q > 3) q--; glutPostRedisplay(); break;
    case 'z': Zangle += 5.0; if (Zangle > 360.0) Zangle -= 360.0; glutPostRedisplay(); break;
    case 'Z': Zangle -= 5.0; if (Zangle < 0.0) Zangle += 360.0; glutPostRedisplay(); break;
    default: break;
    }
}

void specialKeyInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT: Yangle += 5.0; if (Yangle > 360.0) Yangle -= 360.0; break;
    case GLUT_KEY_LEFT:  Yangle -= 5.0; if (Yangle < 0.0) Yangle += 360.0; break;
    case GLUT_KEY_UP:    Xangle += 5.0; if (Xangle > 360.0) Xangle -= 360.0; break;
    case GLUT_KEY_DOWN:  Xangle -= 5.0; if (Xangle < 0.0) Xangle += 360.0; break;
    default: break;
    }
    glutPostRedisplay();
}

void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Use arrow keys to rotate the hemisphere." << endl;
    cout << "Press + or - to change mesh resolution." << endl;
    cout << "Press z/Z to rotate around Z-axis." << endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sliced Hemisphere with a Gap");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();
    printInteraction();
    glutMainLoop();
}
