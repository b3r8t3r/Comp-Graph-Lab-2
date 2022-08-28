#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>

int points[100][100];

const int view_side_size = 20;
const int period = 50;
const int side_size = 600;


struct color_t
{
	double r, g, b, a;
	void setThis() const
	{
		const color_t& color = *this;
		glColor4d(color.r, color.g, color.b, color.a);
	}
};

const color_t black = { 0, 0, 0, 1 };
const color_t red = { 1, 0, 0, 1 };
const color_t green = { 0,255,0,1 };
const color_t blue = { 0,0,255,1 };
const color_t yellow = { 255,255,0,1 };
const color_t purple = { 255,0,255,1 };
const color_t light_blue = { 0,255,255,1 };

void DrawFatPixel(int x, int y, color_t color = black)
{
	color.setThis();
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y - 0.5);
	glVertex2d(x - 0.5, y + 0.5);
	glVertex2d(x + 0.5, y + 0.5);
	glVertex2d(x + 0.5, y - 0.5);
	glEnd();
}

void DrawCell()
{
	glLineWidth(1);
	black.setThis();

	for (int i = -view_side_size; i <= view_side_size; ++i)
	{
		glBegin(GL_LINES);
		glVertex2f(i + 0.5f, -view_side_size + .0f);
		glVertex2f(i + 0.5f, view_side_size + .0f);
		glVertex2f(-view_side_size + .0f, i + 0.5f);
		glVertex2f(view_side_size + .0f, i + 0.5f);
		glEnd();
	}
}

void DrawAxes()
{
	glLineWidth(2);
	glColor3b(1, 1, 0);
	glBegin(GL_LINES);
	glVertex2i(-view_side_size, 0);
	glVertex2i(view_side_size, 0);
	glVertex2i(0, -view_side_size);
	glVertex2i(0, view_side_size);
	glEnd();
}

void DrawBrezenhemLine(int x1, int x2, int y1, int y2, color_t color = red)
{
	int error = 0, lasty = -100, x = x1, y = y1;
	int px = abs(x2 - x1);
	int py = abs(y2 - y1);
	int deltaerr = (px >= py) ? py : px;
	//int deltaerr = px;
	//int deltaerr =  py;
	while (((x2 >= x1 && x <= x2) || (x2 < x1 && x >= x2))
		&& ((y2 >= y1 && y <= y2) || (y2 < y1 && y >= y2)))
	{
		for (int a = x + 50; a < 100; a++)
		{
			if (a > x + 50)
			{
				if (lasty == y)
				{
					break;
				}
				if (x2 < x1 && y2 < y1 && y == y1)
				{
					break;
				}
				if (points[a][y + 50] == 1) points[a][y + 50] = 0;
				else  points[a][y + 50] = 1;
			}
		}

		lasty = y;

		DrawFatPixel(x, y, color);	//Отвечает за отрисовку

		error = error + deltaerr;
		if (px >= py)
		{
			if (2 * error >= deltaerr)
			{
				if (y2 < y1)
				{
					//y--;
				}
				else y++;
				error = error - px;
			}
			if (x2 > x1) x++;
			else if (x2 < x1) x--;
		}
		else
		{
			if (2 * error >= deltaerr)
			{
				if (x2 > x1) x++;
				else if (x2 < x1) x--;
				error = error - py;
			}
			if (y2 > y1) y++;
			else if (y2 < y1) y--;
		}
	}
}

void DrawPolygon(const int tick){
	for (int y = 0; y < 100 && y < tick/2; y++){
		for (int x = 0; x < 100; x++){
			if (points[x][y] == 1){
				DrawFatPixel(x - 50, y - 50, green);
			}
		}
	}
}

void Draw(const int tick) {
	for (int grade = 0; grade <= 25 && grade < tick/16; grade++) {
		
		for (int i = -grade; i <=grade; i++){
			for (int j = -grade; j <= grade; j++) {
				if (points[i+50][j+50] == 1) DrawFatPixel(i, j, light_blue);
			}
		}
	}
}

void Display()
{
	int t = 2;
	glClear(GL_COLOR_BUFFER_BIT);
	int x1 = -7 * t, y1 = -7 * t,
		x2 = 7 * t, y2 = -5 * t,
		x3 = 8 * t, y3 = 7 * t,
		x4 = -4 * t, y4 = 8 * t,
		x5 = -8 * t, y5 = 2 * t,
		x6 = -6 * t, y6 = -3 * t,

		x7 = -1 * t, y7 = 3 * t,
		x8 = -3 * t, y8 = -3 * t,
		x9 = 3 * t, y9 = -2 * t;
	static int tick = 0;
	tick++;
	// Вычисляем закрашиваемые пиксели; Отрисовка непосредственно контура фигуры
	DrawBrezenhemLine(x1, x2, y1, y2);
	DrawBrezenhemLine(x2, x3, y2, y3);
	DrawBrezenhemLine(x3, x4, y3, y4);
	DrawBrezenhemLine(x4, x5, y4, y5);
	DrawBrezenhemLine(x5, x6, y5, y6);
	DrawBrezenhemLine(x6, x1, y6, y1);
	int a = 0;
	switch (a) {
		case 0: {
			DrawPolygon(tick);
			DrawBrezenhemLine(x1, x2, y1, y2, red);
			DrawBrezenhemLine(x2, x3, y2, y3, red);
			DrawBrezenhemLine(x3, x4, y3, y4, red);
			DrawBrezenhemLine(x4, x5, y4, y5, red);
			DrawBrezenhemLine(x5, x6, y5, y6, red);
			DrawBrezenhemLine(x6, x1, y6, y1, red);
			break;
		}
		case 1: {
			Draw(tick);
			DrawBrezenhemLine(x1, x2, y1, y2, blue);
			DrawBrezenhemLine(x2, x3, y2, y3, blue);
			DrawBrezenhemLine(x3, x4, y3, y4, blue);
			DrawBrezenhemLine(x4, x5, y4, y5, blue);
			DrawBrezenhemLine(x5, x6, y5, y6, blue);
			DrawBrezenhemLine(x6, x1, y6, y1, blue);
			//DrawAxes();
			break;
		}
	}

	DrawBrezenhemLine(x7, x8, y7, y8);
	DrawBrezenhemLine(x8, x9, y8, y9);
	DrawBrezenhemLine(x9, x7, y9, y7);
	switch (a) {
		case 0: {
			DrawPolygon(tick);
			DrawBrezenhemLine(x7, x8, y7, y8, red);
			DrawBrezenhemLine(x8, x9, y8, y9, red);
			DrawBrezenhemLine(x9, x7, y9, y7, red);
			break;
		}
		case 1: {
			Draw(tick);
			DrawBrezenhemLine(x7, x8, y7, y8, blue);
			DrawBrezenhemLine(x8, x9, y8, y9, blue);
			DrawBrezenhemLine(x9, x7, y9, y7, blue);
			break;
		}
	}

	
	DrawAxes();
	DrawCell();
	glFlush();
}


void timf(int value)
{
	glutPostRedisplay();
	glutTimerFunc(period, timf, 0);
}

void Initialize()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-view_side_size, view_side_size, -view_side_size, view_side_size, -1.0, 1.0);
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			points[x][y] = 0;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(side_size, side_size);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("АБ-021");
	Initialize();
	glutDisplayFunc(Display);
	glutTimerFunc(period, timf, 0);
	glutMainLoop();
	return 0;
}
