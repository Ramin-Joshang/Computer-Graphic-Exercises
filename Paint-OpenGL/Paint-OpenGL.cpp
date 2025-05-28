#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <iostream>
#include <cmath>
#include <string.h>
#include<time.h>
#include<vector>
#include<stdio.h>
#pragma comment(lib, "glew32.lib")

using namespace std;

void printString(int x, int y, void* font, const char* str);
void translatePoint(float x, float y);
bool IsAbove(float x, float y);
void scalePoint(float x, float y);
void rotationPoint(float x, float y);
float NormX(float x);
float  NormY(float x);
float FracX(float x);
float FracY(float x);

#define M_PI 3.14159265358979323846
const int MAX = 50;

typedef struct {
	float x;
	float y;
} Point;


Point p1, p2, p3;
float ang = 5;
//float angEllip = 10;
bool First = FALSE;
int window_w;
int window_h;
float NormCor_trans_start_x = 0, NormCor_trans_start_y = 0;
bool dragging = false, Scalling_special = false;
struct Color
{
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
};


// Shape structure
struct Shape
{
	string type;
	float startX, startY;
	float endX, endY;
	float pointSize;
	float lineWidth;
	bool isFilled = false;
	bool isActivated = false;
	Color color;
	float rotated = 0;
	float focusX = 0;
	float focusY = 0;
	std::vector<Point> pencilPoints;

};

typedef struct {
	int shapeNo;
	Point Cordinate[10000];
} ShapeInfo;


Color color;
Shape shapeList[MAX];
ShapeInfo shapeinfo[MAX];
vector<float> Vx[MAX];
vector<float> Vy[MAX];

int shapeCount = 0;
int currentColor = -1;

enum DRAW_MODE
{
	NONE, POINT_MODE, LINE_MODE,
	W_TRIANGLE_MODE, F_TRIANGLE_MODE, W_RECTANGLE_MODE, F_RECTANGLE_MODE, W_CIRCLE_MODE, F_CIRCLE_MODE, RightTriangle_Mode, Pencil_mode
};

bool TRANSLATION = FALSE, ROTATION = FALSE, SCALING = FALSE;

enum RIGHT_CLICK_MENU
{
	CLEAR, EXIT, Undo
};

enum COLOR_CODE
{
	RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, BLACK
};

DRAW_MODE mode = NONE;

float point_size = 1.0;
float line_width = 1.0;

void handleStartDraw(float x, float y)
{
	if (mode == NONE)
	{
		return;
	}
	else
	{
		dragging = true;

		shapeList[shapeCount].isActivated = true;

		if (mode == POINT_MODE)
		{
			shapeList[shapeCount].type = "Point";
		}
		if (mode == LINE_MODE)
		{
			shapeList[shapeCount].type = "Line";
		}
		if (mode == W_TRIANGLE_MODE || mode == F_TRIANGLE_MODE)
		{
			if (mode == F_TRIANGLE_MODE)
			{
				shapeList[shapeCount].isFilled = true;
			}
			else
			{
				shapeList[shapeCount].isFilled = false;
			}

			shapeList[shapeCount].type = "Triangle";
		}
		if (mode == W_RECTANGLE_MODE || mode == F_RECTANGLE_MODE)
		{
			if (mode == F_RECTANGLE_MODE)
			{
				shapeList[shapeCount].isFilled = true;
			}
			else
			{
				shapeList[shapeCount].isFilled = false;
			}

			shapeList[shapeCount].type = "Rectangle";
		}
		if (mode == W_CIRCLE_MODE || mode == F_CIRCLE_MODE)
		{
			if (mode == F_CIRCLE_MODE)
			{
				shapeList[shapeCount].isFilled = true;
			}
			else
			{
				shapeList[shapeCount].isFilled = false;
			}

			shapeList[shapeCount].type = "Circle";
		}
		if (mode == RightTriangle_Mode)
		{
			shapeList[shapeCount].type = "RightTriangle";
			shapeList[shapeCount].isFilled = false;
		}


		shapeList[shapeCount].startX = x;
		shapeList[shapeCount].startY = y;
		shapeList[shapeCount].endX = x;
		shapeList[shapeCount].endY = y;

		shapeList[shapeCount].pointSize = point_size;
		shapeList[shapeCount].lineWidth = line_width;

		shapeList[shapeCount].color.r = color.r;
		shapeList[shapeCount].color.g = color.g;
		shapeList[shapeCount].color.b = color.b;

		shapeCount++;
	}
}

void handleContinueDraw(float x, float y)
{

	int current = shapeCount - 1;

	if (!dragging)
	{
		return;
	}


	if (shapeCount >= 0 && (TRANSLATION == TRUE || ROTATION == TRUE || SCALING == TRUE))
	{
		if (TRANSLATION == TRUE)
		{
			translatePoint(x, y);
			printf("Trans---\n");
		}
		else if (SCALING == TRUE)
		{
			scalePoint(x, y);
			printf("scale---\n");
		}
		else if (ROTATION == TRUE)
		{
			printf("acess\n");
			rotationPoint(x, y);
		}
	}
	else
	{
		shapeList[current].endX = x;
		shapeList[current].endY = y;
	}


	glutPostRedisplay();
}

void handleFinishDraw(float x, float y)
{
	if (!dragging)
	{
		return;
	}

	int current = shapeCount - 1;

	dragging = false;
	if (Scalling_special)
	{
		TRANSLATION = FALSE;
		SCALING = TRUE;
		ROTATION = FALSE;
	}


	if (!(shapeCount > 0 && (TRANSLATION == TRUE || ROTATION == TRUE || SCALING == TRUE)))
	{
		if (shapeList[current].startX == shapeList[current].endX && shapeList[current].startX == shapeList[current].endY)
		{
			shapeCount--;
		}
	}


	glutPostRedisplay();
}

void clearPrimitives()
{
	shapeCount = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	glutPostRedisplay();
}


void colorMenu(int code)
{
	if (code == RED) {
		color.r = 1.0;
		color.g = 0.0;
		color.b = 0.0;
	}
	else if (code == GREEN)
	{
		color.r = 0.0;
		color.g = 1.0;
		color.b = 0.0;
	}
	else if (code == BLUE)
	{
		color.r = 0.0;
		color.g = 0.0;
		color.b = 1.0;
	}
	else if (code == CYAN)
	{
		color.r = 0.0;
		color.g = 1.0;
		color.b = 1.0;
	}
	else if (code == MAGENTA)
	{
		color.r = 1.0;
		color.g = 0.0;
		color.b = 1.0;
	}
	else if (code == YELLOW)
	{
		color.r = 1.0;
		color.g = 1.0;
		color.b = 0.0;
	}
	else if (code == WHITE)
	{
		color.r = 1.0;
		color.g = 1.0;
		color.b = 1.0;
	}
	else if (code == BLACK)
	{
		color.r = 0.0;
		color.g = 0.0;
		color.b = 0.0;
	}

	int current = shapeCount - 1;


	if (shapeList[current].isActivated)
	{
		shapeList[current].color.r = color.r;
		shapeList[current].color.g = color.g;
		shapeList[current].color.b = color.b;
	}

	glutPostRedisplay();
}


void lineWidthMenu(int width)
{
	if (width == 1.0)
	{
		line_width = 1.0;
	}
	else if (width == 2.0)
	{
		line_width = 2.0;
	}
	else if (width == 3.0)
	{
		line_width = 3.0;
	}
	else if (width == 4.0) {
		line_width = 4.0;
	}
	else if (width == 5.0)
	{
		line_width = 5.0;
	}
	else if (width == 6.0)
	{
		line_width = 6.0;
	}

	int current = shapeCount - 1;

	if (shapeList[current].isActivated)
	{
		shapeList[current].lineWidth = line_width;
	}

	glutPostRedisplay();
}

void TransformationType(int type)
{

	if (type == 1.0)
	{
		TRANSLATION = TRUE;
		SCALING = FALSE;
		ROTATION = FALSE;

	}
	else if (type == 2.0)
	{
		SCALING = TRUE;
		TRANSLATION = FALSE;
		ROTATION = FALSE;
	}
	else if (type == 3.0)
	{
		ROTATION = TRUE;
		SCALING = FALSE;
		TRANSLATION = FALSE;

		int current = shapeCount - 1;
		float shape_start_x = NormX(shapeList[current].startX);
		float shape_start_y = NormY(shapeList[current].startY);
		float shape_end_x = NormX(shapeList[current].endX);
		float shape_end_y = NormY(shapeList[current].endY);

		if (shapeList[current].type == "Point")
		{
			shapeList[current].focusX = (shape_end_x);
			shapeList[current].focusY = (shape_end_y);
		}
		else if (shapeList[current].type == "Line" || shapeList[current].type == "Triangle" && shapeList[current].isFilled == TRUE)  //Line

		{
			shapeList[current].focusX = (shape_start_x + shape_end_x) / 2;
			shapeList[current].focusY = (shape_start_y + shape_end_y) / 2;

			p1.x = shapeList[current].focusX;
			p1.y = shapeList[current].focusY;
		}
		p2.x = shape_start_x;
		p2.y = shape_start_y;
		p3.x = shape_end_x;
		p3.y = shape_end_y;
	}
	else if (type == 4.0)
	{
		TRANSLATION = FALSE;
		SCALING = FALSE;
		ROTATION = FALSE;
	}
}

// Right-click menu
void rightClickMenu(int option)
{
	switch (option)
	{
	case CLEAR:	// Clear	
		clearPrimitives();
		Scalling_special = FALSE;
		break;

	case EXIT: // Exit
		exit(0);

	case Undo:	// Clear	
		if (shapeCount > 0)
		{
			shapeCount--;
		}
		break;
	}
}

void createMouseMenu()
{
	int c_menu, ps_menu, lw_menu, tf_menu;

	/*glutAddMenuEntry("1.0", 1.0);
	glutAddMenuEntry("2.0", 2.0);
	glutAddMenuEntry("3.0", 3.0);
	glutAddMenuEntry("4.0", 4.0);
	glutAddMenuEntry("5.0", 5.0);
	glutAddMenuEntry("6.0", 6.0);*/

	lw_menu = glutCreateMenu(lineWidthMenu);
	glutAddMenuEntry("1.0", 1.0);
	glutAddMenuEntry("2.0", 2.0);
	glutAddMenuEntry("3.0", 3.0);
	glutAddMenuEntry("4.0", 4.0);
	glutAddMenuEntry("5.0", 5.0);
	glutAddMenuEntry("6.0", 6.0);


	glutCreateMenu(rightClickMenu);
	glutAddSubMenu("Line width", lw_menu);
	glutAddMenuEntry("Clear", CLEAR);
	glutAddMenuEntry("Exit", EXIT);
	glutAddMenuEntry("Undo", Undo);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void selectMode(int x, int y, int modifiers)
{
	if (y > window_h - 50)
	{
		mode = LINE_MODE;
	}
	else if (y > window_h - 100)
	{
		mode = W_TRIANGLE_MODE;
	}
	else if (y > window_h - 150)
	{
		mode = F_TRIANGLE_MODE;
	}
	else if (y > window_h - 200)
	{
		mode = W_RECTANGLE_MODE;
	}
	else if (y > window_h - 250)
	{
		mode = F_RECTANGLE_MODE;
	}
	else if (y > window_h - 300)
	{
		mode = W_CIRCLE_MODE;
	}
	else if (y > window_h - 350)
	{
		mode = F_CIRCLE_MODE;
	}
	else if (y > window_h - 400)
	{
		mode = RightTriangle_Mode;
	}

	int paletteX = 0;
	int paletteY = window_h - 415;
	int boxSize = 15;
	int spacing = 3;
	int numColors = 8;
	int rectWidth = 70;


	for (int i = 0; i < numColors; i++)
	{
		if (x >= paletteX && x <= paletteX + rectWidth && y >= paletteY && y <= paletteY + boxSize)
		{
			currentColor = i;
			switch (i)
			{
			case 0: colorMenu(RED); break;
			case 1: colorMenu(GREEN); break;
			case 2: colorMenu(BLUE); break;
			case 3: colorMenu(YELLOW); break;
			case 4: colorMenu(CYAN); break;
			case 5: colorMenu(MAGENTA); break;
			case 6: colorMenu(WHITE); break;
			case 7: colorMenu(BLACK); break;
			}
			break;
		}

		paletteY -= (boxSize + spacing);
	}
}

void drawSelected()
{
	if (mode == NONE)
	{
		return;
	}
	else if (mode == LINE_MODE)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 2);
		glVertex2i(49, window_h - 2);
		glVertex2i(49, window_h - 49);
		glVertex2i(2, window_h - 49);
		glEnd();
	}
	else if (mode == W_TRIANGLE_MODE) {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 51);
		glVertex2i(49, window_h - 51);
		glVertex2i(49, window_h - 99);
		glVertex2i(2, window_h - 99);
		glEnd();
	}
	else if (mode == F_TRIANGLE_MODE)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 101);
		glVertex2i(49, window_h - 101);
		glVertex2i(49, window_h - 149);
		glVertex2i(2, window_h - 149);
		glEnd();
	}
	else if (mode == W_RECTANGLE_MODE) {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 151);
		glVertex2i(49, window_h - 151);
		glVertex2i(49, window_h - 198);
		glVertex2i(2, window_h - 198);
		glEnd();
	}
	else if (mode == W_CIRCLE_MODE)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 251);
		glVertex2i(49, window_h - 251);
		glVertex2i(49, window_h - 298);
		glVertex2i(2, window_h - 298);
		glEnd();
	}
	else if (mode == RightTriangle_Mode)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 350);
		glVertex2i(49, window_h - 350);
		glVertex2i(49, window_h - 398);
		glVertex2i(2, window_h - 398);
		glEnd();
	}
	else if (mode == F_CIRCLE_MODE)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 301);
		glVertex2i(49, window_h - 301);
		glVertex2i(49, window_h - 348);
		glVertex2i(2, window_h - 348);
		glEnd();
	}
	else if (mode == F_RECTANGLE_MODE)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, window_h - 201);
		glVertex2i(49, window_h - 201);
		glVertex2i(49, window_h - 248);
		glVertex2i(2, window_h - 248);
		glEnd();
	}

	int paletteX = 0;
	int paletteY = window_h - 415;
	int boxSize = 15;
	int spacing = 3;
	int numColors = 8;

	int rectWidth = 70;

	for (int i = 0; i < numColors; i++) {
		if (currentColor == i)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			glVertex2i(paletteX, paletteY);
			glVertex2i(paletteX + rectWidth, paletteY);
			glVertex2i(paletteX + rectWidth, paletteY + boxSize);
			glVertex2i(paletteX, paletteY + boxSize);
		}
		paletteY -= (boxSize + spacing);
	}
}

void printString(int x, int y, void* font, const char* str)
{
	//char* c;
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2i(x, y);
	for (int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glColor3f(1.0f, 1.0f, 1.0f);
}

void drawMenuIcon()
{

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(10, window_h - 25);
	glVertex2i(40, window_h - 35);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(25, window_h - 60);
	glVertex2i(10, window_h - 90);
	glVertex2i(40, window_h - 90);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(25, window_h - 115);
	glVertex2i(10, window_h - 140);
	glVertex2i(40, window_h - 140);
	glEnd();


	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(10, window_h - 165);
	glVertex2i(40, window_h - 165);
	glVertex2i(40, window_h - 190);
	glVertex2i(10, window_h - 190);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(10, window_h - 215);
	glVertex2i(40, window_h - 215);
	glVertex2i(40, window_h - 240);
	glVertex2i(10, window_h - 240);
	glEnd();

	int segment = 300;
	float twoPI = M_PI * 2.0;
	float radius = 15.0;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < segment; i++)
	{
		glVertex2f(25 + (radius * cos(i * twoPI / segment)),
			(window_h - 270) + (radius * sin(i * twoPI / segment)));
	}

	glEnd();


	//glColor3f(0.0, 0.0, 0.0);
	//glBegin(GL_LINE_LOOP);
	//glVertex2i(15, window_h - 210);
	//glVertex2i(15, window_h - 240);
	//glVertex2i(40, window_h - 240);
	//glEnd();

	//glColor3f(0.0, 0.0, 0.0);
	//glBegin(GL_LINE_LOOP);
	//glVertex2i(15, window_h - 251);
	//glVertex2i(15, window_h - 251);
	//glVertex2i(40, window_h - 291);
	//glEnd();

	printString(0.5, window_h - 315, GLUT_BITMAP_TIMES_ROMAN_10, "filled circle");


	printString(0, window_h - 365, GLUT_BITMAP_TIMES_ROMAN_10, "Rightringle");

	int paletteX = 0;
	int paletteY = window_h - 415;
	int boxSize = 15;
	int spacing = 3;
	int numColors = 8;


	Color paletteColors[] = {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0},
		{1.0, 1.0, 0.0},
		{0.0, 1.0, 1.0},
		{1.0, 0.0, 1.0},
		{1.0, 1.0, 1.0},
		{0.0, 0.0, 0.0}
	};

	int rectWidth = 70;

	for (int i = 0; i < numColors; i++) {
		glColor3f(paletteColors[i].r, paletteColors[i].g, paletteColors[i].b);

		glBegin(GL_QUADS);

		glVertex2i(paletteX, paletteY);
		glVertex2i(paletteX + rectWidth, paletteY);
		glVertex2i(paletteX + rectWidth, paletteY + boxSize);
		glVertex2i(paletteX, paletteY + boxSize);

		glEnd();

		paletteY -= (boxSize + spacing);
	}
}

void drawPaintMenu()
{
	glColor3f(0.7, 0.7, 0.7);
	glRectf(0, 0, 50, window_h);

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_LINES);

	glVertex2i(1, 1);
	glVertex2i(50, 1);

	glVertex2i(1, 1);
	glVertex2i(1, window_h);

	glVertex2i(50, 1);
	glVertex2i(50, window_h);

	glVertex2i(1, window_h - 1);
	glVertex2i(50, window_h - 1);

	int distance = 50;

	for (int i = 1; i <= 8; i++)
	{
		glVertex2i(1, window_h - distance);
		glVertex2i(50, window_h - distance);

		distance = distance + 50;
	}

	glEnd();
}

void drawInterface()
{
	drawPaintMenu();

	drawSelected();

	drawMenuIcon();

	glutPostRedisplay();
}

float NormX(float x)
{
	x = x * (window_w - 50) + 50;
	return x;
}

float NormY(float y)
{
	y = (float)(window_h - y * window_h);
	return y;
}

float FracX(float x)
{
	x = (float)(x - 50) / (window_w - 50);
	return x;
}

float FracY(float y)
{

	y = (float)(window_h - y) / window_h;
	return y;
}

//float X(float ang, float h, float k, float x, float y)
//{
//	
//	ang = (ang * 3.14) / 180.0;                 //angle in radians  
//	float  result = 0;
//	result = x * cos(ang) - y * sin(ang) + (h - cos(ang) * h + sin(ang) * k);
//	ang = ang * 180 / 3.14;
//	return result;
//
//}
//float Y(float ang, float h, float k, float x, float y)
//{
//	printf("angle\n");
//	//ang = (ang * 3.14) / 180.0;
//	//float result= sin(ang) * x + cos(ang) * y + (-h * sin(ang) - k * cos(ang) + k);  
//	//ang = ang * 180 / 3.14;
//	//return result;
//	ang = (ang * 3.14) / 180.0;                 //angle in radians  
//	float result = 0;
//	result = x * sin(ang) + y * cos(ang) + (k - sin(ang) * h - cos(ang) * k);
//	ang = ang * 180 / 3.14;
//	return result;
//}

Point rotate(Point p, Point c, float angle) {
	ang = (ang * 3.14) / 180.0;
	Point ptemp;  ptemp.x = 0; ptemp.y = 0;
	ptemp.x = p.x * cos(ang) - p.y * sin(ang) + (c.x - cos(ang) * c.x + sin(ang) * c.y);
	ptemp.y = p.x * sin(ang) + p.y * cos(ang) + (c.y - sin(ang) * c.x - cos(ang) * c.y);
	ang = ang * 180 / 3.14;
	return ptemp;
}

Point rotateEllip(Point p, Point c, float ang) {
	ang = (ang * 3.14) / 180.0;
	Point ptemp;  ptemp.x = 0; ptemp.y = 0;
	ptemp.x = p.x * cos(ang) - p.y * sin(ang) + (c.x - cos(ang) * c.x + sin(ang) * c.y);
	ptemp.y = p.x * sin(ang) + p.y * cos(ang) + (c.y - sin(ang) * c.x - cos(ang) * c.y);
	ang = ang * 180 / 3.14;
	return ptemp;
}

void rotationPoint(float x, float y)
{
	int current = shapeCount - 1;


	if (shapeList[current].type == "Line" || shapeList[current].type == "Triangle" && shapeList[current].isFilled == TRUE)

	{

		int current = shapeCount - 1;
		p1.x = shapeList[current].focusX;
		p1.y = shapeList[current].focusY;

		float shape_start_x = NormX(shapeList[current].startX);
		float shape_start_y = NormY(shapeList[current].startY);
		float shape_end_x = NormX(shapeList[current].endX);
		float shape_end_y = NormY(shapeList[current].endY);
		p3.x = shape_start_x;
		p3.y = shape_start_y;

		p2.x = shape_end_x;
		p2.y = shape_end_y;


		p3 = rotate(p3, p1, ang);
		p2 = rotate(p2, p1, ang);
		printf("p1:%f  %f  ; p2:%f  %f;  p3:%f   %f\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);

		shapeList[current].startX = FracX(p2.x);
		shapeList[current].startY = FracY(p2.y);
		shapeList[current].endX = FracX(p3.x);
		shapeList[current].endY = FracY(p3.y);
	}
	else
	{
		int current = shapeCount - 1;
		if (ROTATION == TRUE && dragging == TRUE)
		{

			shapeList[current].rotated += 1;
		}


	}

}

void translatePoint(float x, float y)
{
	if (IsAbove(x, y))
	{
		glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	}

	int current = shapeCount - 1;

	float NormCor_trans_last_x = NormX(x);
	float NormCor_trans_last_y = NormY(y);


	float Tx = NormCor_trans_last_x - NormCor_trans_start_x;
	float Ty = NormCor_trans_last_y - NormCor_trans_start_y;

	NormCor_trans_start_x = NormCor_trans_last_x;
	NormCor_trans_start_y = NormCor_trans_last_y;




	float NormCor_shape_start_x = NormX(shapeList[current].startX);
	NormCor_shape_start_x += Tx;
	shapeList[current].startX = FracX(NormCor_shape_start_x);

	float NormCor_shape_start_y = NormY(shapeList[current].startY);
	NormCor_shape_start_y += Ty;
	shapeList[current].startY = FracY(NormCor_shape_start_y);


	float NormCor_shape_last_x = NormX(shapeList[current].endX);
	NormCor_shape_last_x += Tx;
	shapeList[current].endX = FracX(NormCor_shape_last_x);


	float NormCor_shape_last_y = NormY(shapeList[current].endY);
	NormCor_shape_last_y += Ty;
	shapeList[current].endY = FracY(NormCor_shape_last_y);

}

bool IsAbove(float x, float y)
{
	int current;

	current = shapeCount - 1;
	if (shapeList[current].type == "Line" || shapeList[current].type == "Triangle" && shapeList[current].isFilled == TRUE)
	{


		float cursor_x;
		float cursor_y;
		cursor_x = NormX(x);
		cursor_y = NormY(y);
		float shape_start_x = NormX(shapeList[current].startX);
		float shape_start_y = NormY(shapeList[current].startY);
		float shape_end_x = NormX(shapeList[current].endX);
		float shape_end_y = NormY(shapeList[current].endY);
		float left_side = ((cursor_x - shape_start_x) / (shape_start_x - shape_end_x));
		float right_side = ((cursor_y - shape_start_y) / (shape_start_y - shape_end_y));
		float d = (right_side - left_side);

		if (d > -.04 && d < .04)
		{
			return TRUE;
			printf("%f\n", right_side - left_side);
		}
		else
		{
			return FALSE;
		}


		return TRUE;
	}


}

void scalePoint(float x, float y)
{

	int current = shapeCount - 1;
	float NormCor_trans_last_x = NormX(x);
	float NormCor_trans_last_y = NormY(y);

	float NormCor_shape_start_x = NormX(shapeList[current].startX);
	float NormCor_shape_start_y = NormY(shapeList[current].startY);
	float NormCor_shape_last_x = NormX(shapeList[current].endX);
	float NormCor_shape_last_y = NormY(shapeList[current].endY);


	float a = abs(NormCor_shape_start_x - NormCor_shape_last_x);
	float b = abs(NormCor_shape_start_y - NormCor_shape_last_y);
	float C1 = NormCor_shape_last_x, C2 = NormCor_shape_last_y;

	if (shapeList[current].type == "Line" || shapeList[current].type == "Triangle" && shapeList[current].isFilled == TRUE)
	{
		float S1 = sqrt(pow((NormCor_trans_start_x - NormCor_shape_start_x), 2) + pow((NormCor_trans_start_y - NormCor_shape_start_y), 2));
		float S2 = sqrt(pow((NormCor_trans_last_x - NormCor_shape_last_x), 2) + pow((NormCor_trans_last_y - NormCor_shape_last_y), 2));

		printf("s1:%f  s2:%f\n", S1, S2);

		if (S1 < S2) {

			if (S1 >= 0.0 && S1 <= 4)
			{

				std::swap(shapeList[current].startX, shapeList[current].endX);
				std::swap(shapeList[current].startY, shapeList[current].endY);

				TRANSLATION = FALSE;
				SCALING = FALSE;
				ROTATION = FALSE;
				handleContinueDraw(x, y);
				TRANSLATION = FALSE;
				SCALING = TRUE;
				ROTATION = FALSE;
			}

		}
		else
		{

			if (S2 >= 0.00 && S2 <= 4)
			{

				TRANSLATION = FALSE;
				SCALING = FALSE;
				ROTATION = FALSE;
				handleContinueDraw(x, y);
				Scalling_special = TRUE;
			}


		}
	}
	else if (shapeList[current].type == "Circle")
	{
		float r = sqrt(pow((NormCor_shape_start_x - NormCor_shape_last_x), 2) + pow((NormCor_shape_start_y - NormCor_shape_last_y), 2));
		float d = pow(r, 2) - (pow((NormCor_shape_start_x - NormCor_trans_start_x), 2) + pow((NormCor_shape_start_y - NormCor_trans_start_y), 2));
		float v = abs(sqrt(d));
		printf("%f\n", (sqrt(v)));
		if (v >= 0 && v < 30)
		{
			TRANSLATION = FALSE;
			SCALING = FALSE;
			ROTATION = FALSE;
			handleContinueDraw(x, y);
			printf("I am here \n");
			Scalling_special = TRUE;
		}



	}
	else if (shapeList[current].type == "Point")
	{

		printf("hiiiii\n");
		float x_pos, x_neg, y_pos, y_neg;
		float x_diff1 = (NormCor_shape_last_x + a) - NormCor_trans_start_x;
		float y_diff = abs(NormCor_shape_last_y - NormCor_trans_start_y);
		float x_diff2 = (NormCor_shape_last_x - a) - NormCor_trans_start_x;


		if (abs(x_diff1) >= 0 && abs(x_diff1) <= 20 && y_diff >= 0 && y_diff <= 20)
		{
			TRANSLATION = FALSE;
			SCALING = TRUE;
			ROTATION = FALSE;

			shapeList[current].endX = FracX(NormCor_trans_start_x - a);
			NormCor_trans_start_x = (NormCor_trans_last_x);

		}

		if (abs(x_diff2) >= 0 && abs(x_diff2) <= 20 && y_diff >= 0 && y_diff <= 20)
		{
			TRANSLATION = FALSE;
			SCALING = TRUE;
			ROTATION = FALSE;

			shapeList[current].startX = FracX(NormCor_trans_start_x);
			NormCor_trans_start_x = (NormCor_trans_last_x);



		}
	}

}

void DDA_line(float xs, float ys, float xe, float ye, int i)
{

	if (shapeCount > 0 && (TRANSLATION == TRUE || ROTATION == TRUE || SCALING == TRUE))
	{

		if (xs > 1 || ys > 1)
		{
		}
	}


	if (!(shapeCount > 0 && (TRANSLATION == TRUE || ROTATION == TRUE || SCALING == TRUE)))
	{

		if (xs > 1 || ys > 1)
		{
		}
	}
	glLineWidth(shapeList[i].lineWidth);

	xs = xs * (window_w - 50) + 50;
	xe = xe * (window_w - 50) + 50;

	ys = (float)(window_h - ys * window_h);
	ye = (float)(window_h - ye * window_h);

	float dy, dx, step, x, y, k, Xin, Yin;
	dx = xe - xs;
	dy = ye - ys;

	if (abs(dx) > abs(dy))
	{
		step = abs(dx);
	}
	else
	{
		step = abs(dy);
	}


	Xin = (dx) / step;
	Yin = (dy) / step;

	x = xs;
	y = ys;
	float wx = (float)(x - 50) / (window_w - 50);
	float wy = (float)(window_h - y) / window_h;
	glBegin(GL_LINE_STRIP);
	glVertex2f(wx, wy);




	float X[1000], Y[1000];
	step = step;
	for (int k = 1; k <= int(step); k++)
	{
		x = x + Xin;
		y = y + Yin;

		wx = (float)(x - 50) / (window_w - 50);
		wy = (float)(window_h - y) / window_h;


		glVertex2f(wx, wy);
	}
	glEnd();

}

void bresenham_line(float x1, float y1, float x2, float y2, int i)
{
	float x, y, dx, dy, dx1, dy1, px, py, xe, ye;

	glLineWidth(shapeList[i].lineWidth);

	x1 = NormX(x1);
	x2 = NormX(x2);

	y1 = NormY(y1);
	y2 = NormY(y2);

	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	glBegin(GL_LINE_STRIP);
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}

		float wx = (float)(x - 50) / (window_w - 50);
		float wy = (float)(window_h - y) / window_h;
		glVertex2f(wx, wy);

		printf(" x: %f  y:%f\n", wx, wy);
		for (int j = 0; x < xe; j++)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}

			float wx = (float)(x - 50) / (window_w - 50);
			float wy = (float)(window_h - y) / window_h;
			glVertex2f(wx, wy);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		float wx = (float)(x - 50) / (window_w - 50);
		float wy = (float)(window_h - y) / window_h;
		glVertex2f(wx, wy);

		for (int j = 0; y < ye; j++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}

			float wx = (float)(x - 50) / (window_w - 50);
			float wy = (float)(window_h - y) / window_h;
			glVertex2f(wx, wy);

		}
	}
	glEnd();

}

void drawPrimitives()
{
	for (int i = 0; i < shapeCount; i++)
	{
		glColor3f(shapeList[i].color.r, shapeList[i].color.g, shapeList[i].color.b);

		if (shapeList[i].type == "Point")
		{
		}
		else if (shapeList[i].type == "Line")
		{
			glLineWidth(shapeList[i].lineWidth);
			DDA_line(shapeList[i].startX, shapeList[i].startY, shapeList[i].endX, shapeList[i].endY, i);
		}
		else if (shapeList[i].type == "Rectangle")
		{
			if (shapeList[i].isFilled)
			{
				glBegin(GL_QUADS);
				glVertex2f(shapeList[i].startX, shapeList[i].startY);
				glVertex2f(shapeList[i].startX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].startY);
				glEnd();
			}
			else {
				glLineWidth(shapeList[i].lineWidth);
				glBegin(GL_LINE_LOOP);
				glVertex2f(shapeList[i].startX, shapeList[i].startY);
				glVertex2f(shapeList[i].startX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].startY);
				glEnd();
			}
		}
		else if (shapeList[i].type == "Triangle")
		{
			if (shapeList[i].isFilled)
			{
				glBegin(GL_TRIANGLES);
				glVertex2f(shapeList[i].startX, shapeList[i].startY);
				glVertex2f(((shapeList[i].endX - shapeList[i].startX) / 2) + shapeList[i].startX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].startY);
				glEnd();
			}
			else
			{
				glLineWidth(shapeList[i].lineWidth);
				glBegin(GL_LINE_LOOP);
				glVertex2f(shapeList[i].startX, shapeList[i].startY);
				glVertex2f(((shapeList[i].endX - shapeList[i].startX) / 2) + shapeList[i].startX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].startY);
				glEnd();
			}
		}

		else if (shapeList[i].type == "RightTriangle")
		{
			if (shapeList[i].isFilled) {
				glBegin(GL_TRIANGLES);
				glVertex2f(shapeList[i].startX, shapeList[i].startY);
				glVertex2f(shapeList[i].startX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].startY);
				glEnd();
			}
			else
			{
				glLineWidth(shapeList[i].lineWidth);
				glBegin(GL_LINE_LOOP);
				glVertex2f(shapeList[i].startX, shapeList[i].startY);
				glVertex2f(shapeList[i].startX, shapeList[i].endY);
				glVertex2f(shapeList[i].endX, shapeList[i].startY);
				glEnd();
			}
		}
		else if (shapeList[i].type == "Circle")
		{
			float centerX = shapeList[i].startX;
			float centerY = shapeList[i].startY;
			float radius = sqrt(pow(shapeList[i].endX - shapeList[i].startX, 2) + pow(shapeList[i].endY - shapeList[i].startY, 2));

			if (shapeList[i].isFilled)
			{
				glBegin(GL_TRIANGLE_FAN);
				glVertex2f(centerX, centerY);
				int numSegments = 500;
				for (int j = 0; j <= numSegments; ++j)
				{
					float theta = 2.0f * M_PI * float(j) / float(numSegments);
					float x = radius * cos(theta);
					float y = radius * sin(theta);
					glVertex2f(centerX + x, centerY + y);
				}
				glEnd();
			}
			else
			{
				glBegin(GL_LINE_LOOP);
				int numSegments = 500;
				for (int j = 0; j < numSegments; ++j)
				{
					float theta = 2.0f * M_PI * float(j) / float(numSegments);
					float x = radius * cos(theta);
					float y = radius * sin(theta);
					glVertex2f(centerX + x, centerY + y);
				}
				glEnd();
			}
		}


	}
}

void initArea(float x1, float x2, float y1, float y2)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(x1, x2, y1, y2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, window_w, 0, window_h);
}

void display()
{
	glClearColor(1, 1, 1, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(50, 0, window_w - 50, window_h);

	initArea(0, 1, 0, 1);

	drawPrimitives();

	glViewport(0, 0, 50, window_h);

	initArea(0, 51, 0, window_h);

	drawInterface();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glClearColor(0.8, 0.8, 0.8, 0.8);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	glFlush();

	window_w = w;
	window_h = h;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (x < 50 && state == GLUT_DOWN)
		{
			selectMode(x, window_h - y, glutGetModifiers());
			TRANSLATION = FALSE;
			SCALING = FALSE;
			ROTATION = FALSE;
			Scalling_special = false;
		}

		float wx, wy;

		wx = (float)(x - 50) / (window_w - 50);
		wy = (float)(window_h - y) / window_h;


		if (shapeCount > 0 && state == GLUT_DOWN && (TRANSLATION == TRUE || ROTATION == TRUE || SCALING == TRUE))
		{
			int current = shapeCount - 1;
			for (int i = 0; i <= current; i++)
			{
			}


			NormCor_trans_start_x = wx * (window_w - 50) + 50;
			NormCor_trans_start_y = (float)(window_h - wy * window_h);

			dragging = TRUE;

		}


		else if (state == GLUT_DOWN && !(TRANSLATION == TRUE || ROTATION == TRUE || SCALING == TRUE))
		{
			shapeList[shapeCount - 1].isActivated = false;
			glutSetCursor(GLUT_CURSOR_INHERIT);
			handleStartDraw(wx, wy);
		}
		else
		{


			handleFinishDraw(wx, wy);


		}
	}
}

void motion(int x, int y)
{
	if (dragging)
	{
		float wx, wy;

		wx = (float)(x - 50) / (window_w - 50);
		wy = (float)(window_h - y) / window_h;



		handleContinueDraw(wx, wy);
	}
}

void PassiveMove(int x, int y)
{

	float window_width = glutGet(GLUT_WINDOW_WIDTH);
	float window_height = glutGet(GLUT_WINDOW_HEIGHT);

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	float wx = (float)(x - 50) / (window_w - 50);
	float wy = (float)(window_h - y) / window_h;

	if (IsAbove(FracX(x), FracY(y)))
	{

	}

	if (x > 50)
	{

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(150, 50);
	glutCreateWindow("paint");
	init();

	createMouseMenu();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(PassiveMove);
	glutMainLoop();
	return 0;
}