#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#include <cmath>
#include <ctime>
#include <string>

#define M_PI 3.14159265358979323846

// Hand angles
float hourAngle = 0.0f;
float minuteAngle = 0.0f;
float secondAngle = 0.0f;

// Draw text at specific position and angle
void drawText(const char* text, float x, float y, float angle) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(-angle+90, 0.0f, 0.0f, 1.0f);  // Rotate with hand
    glScalef(0.0006f, 0.0006f, 1.0f);     // Adjust size

    for (int i = 0; text[i] != '\0'; i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}

// Draw clock numbers (1 to 12)
void drawClockNumbers() {
    char number[3];
    const float radius = 0.75f;
    const float scale = 0.0007f;

    for (int i = 1; i <= 12; i++) {
        float angle = static_cast<float>(-i * 30.0 + 90.0);
        float radian = angle * static_cast<float>(M_PI) / 180.0f;
        float x = cos(radian) * radius;
        float y = sin(radian) * radius;

        sprintf_s(number, sizeof(number), "%d", i);

        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glScalef(scale, scale, 1.0f);

        float width = 0;
        for (const char* p = number; *p; p++) {
            width += glutStrokeWidth(GLUT_STROKE_ROMAN, *p);
        }

        glTranslatef(-width / 2.0f, -50.0f, 0.0f);

        for (const char* p = number; *p; p++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
        glPopMatrix();
    }
}

// Draw clock hand
void drawHand(float length, float angle, float width) {
    float radian = (-angle + 90.0f) * static_cast<float>(M_PI) / 180.0f;
    float x = cos(radian) * length;
    float y = sin(radian) * length;

    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw clock circle
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float radian = static_cast<float>(i * M_PI) / 180.0f;
        glVertex2f(cos(radian) * 0.9f, sin(radian) * 0.9f);
    }
    glEnd();

    // Draw numbers
    glColor3f(0.7f, 0.7f, 0.7f);
    drawClockNumbers();

    // Get current time
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);

    char timeStr[9];  // "HH:MM:SS"
    sprintf_s(timeStr, sizeof(timeStr), "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    // Compute angles
    hourAngle = static_cast<float>((timeinfo.tm_hour % 12 + timeinfo.tm_min / 60.0) * 30.0);
    minuteAngle = static_cast<float>(timeinfo.tm_min * 6.0);
    secondAngle = static_cast<float>(timeinfo.tm_sec * 6.0);

    // Draw hour hand (no text)
    glColor3f(1.0f, 0.0f, 0.0f);
    drawHand(0.5f, hourAngle, 3.0f);

    // Draw minute hand (no text)
    glColor3f(0.0f, 1.0f, 0.0f);
    drawHand(0.7f, minuteAngle, 2.0f);

    // Draw second hand with digital time
    glColor3f(0.0f, 0.0f, 1.0f);
    drawHand(0.8f, secondAngle, 1.0f);

    // Display time string on second hand
    float radian = (-secondAngle + 90.0f) * static_cast<float>(M_PI) / 180.0f;
    float textX = cos(radian) * 0.40f;
    float textY = sin(radian) * 0.40f;
    drawText(timeStr, textX, textY, secondAngle);

    glutSwapBuffers();
}

// Reshape
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = static_cast<float>(w) / static_cast<float>(h);
    if (w >= h) {
        glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1.0);
    }
    else {
        glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

// Timer
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Analog Clock with Digital Time on Second Hand");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}