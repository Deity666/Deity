#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<stdlib.h>  
#include <iostream>
#include <algorithm>
using namespace std;
GLint x30, y30, x31, y31;
void DDA_Line(int x0, int y0, int xEnd, int yEnd);//DDA画直线方式
void DDA_Line_display(void);//DDA画直线方式绘图显示
void Bresenham_line(float x11, float y11, float x22, float y22);//Bresenham画直线方式
void Bresenham_line_display();//Bresenham画直线方式绘图显示
void myInit(void);//背景渲染初始化
void Init();
void MidpointLine1();// 0≤k≤1
void MidpointLine2();//-1≤k≤0
void MidpointLine3();//k>1 
void MidpointLine4();//k＜-1  
int main(int argc, char* argv[])
{
	int x;
	cout << "请选择方式" << endl;
	cout << "1:DDA" << endl;
	cout << "2:Bresenham" << endl;
	cout << "3:中点" << endl;
	cout << "其他数字:退出" <<endl;
	cin >> x;
	if (x == 1)
	{
		cout << "DDA方式" << endl;
		glutInit(&argc, argv);                          // 初始化
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // 单缓冲窗口，RGB颜色模式
		glutInitWindowSize(500, 400);                  // 创建窗口
		glutInitWindowPosition(500, 100);              // // 窗口位置
		glutCreateWindow("DDA");                     // 窗口名词
		glutDisplayFunc(DDA_Line_display);                       // 绘制方法
		myInit();                                       // 初始化
		glutMainLoop();                                 // 循环渲染
	}
	else if (x == 2)
	{
		cout << "Bresenham算法方式" << endl;
		glutInit(&argc, argv); //初始化glut
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // 单缓冲窗口，RGB颜色模式
		glutInitWindowSize(1000, 800);                  // 创建窗口
		glutInitWindowPosition(500, 100);              //窗口位置
		gluOrtho2D(50.0, 50.0, 50.0, 50.0);             // //用来指定屏幕区域对应的模型坐标范围(left, right, bottom, top)
		glutCreateWindow("Bresenham算法"); //创建窗口并赋予title
		glutDisplayFunc(Bresenham_line_display);//调用renderScene把绘制传送到窗口
		glutMainLoop(); //进入循环等待
	}
	else if (x == 3)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(500, 100);
		glutInitWindowSize(500, 500);
		glutCreateWindow("中点画线法");
		Init();
		printf("请输入起点坐标和中点坐标:\n");
		scanf_s("%d%d%d%d", &x30, &y30, &x31, &y31);

		GLfloat k = GLfloat(y31 - y30) / GLfloat(x31 - x30);

		if (k >= 0 && k <= 1)
			glutDisplayFunc(MidpointLine1);
		else if (k >= -1 && k <= 0)
			glutDisplayFunc(MidpointLine2);
		else if (k > 1)
			glutDisplayFunc(MidpointLine3);
		else
			glutDisplayFunc(MidpointLine4);
		glutMainLoop();
	}
	else return 0;
	return(0);
}
void DDA_Line_display(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);  // 清除当前可写的颜色缓冲
	glViewport(0, 0, 400, 300);   // 视口矩形的范围(x, y, width, height)

	/*DDA_Line(10, 30, 70, 30);//画五角星
	DDA_Line(70, 30, 30, 50);
	DDA_Line(30, 50,40,10);
	DDA_Line( 40, 10,50,50);
	DDA_Line(50, 50,10,30);*/
	int n;
	cout << "请输入直线条数" << endl;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x0, y0, x1, y1;
		cout << "请输入第" << i << "条直线起始点坐标和终点坐标：" << endl;
		cin >> x0 >> y0 >> x1 >> y1;
		DDA_Line(x0, y0, x1, y1);
	}

}

void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);// 设置背景颜色黑色
	glColor3f(0.0, 1.0, 0.0);                       // 设置点颜色绿色
	//gluOrtho2D(-100.0, 100.0, -100.0, 100.0);             // 用来指定屏幕区域对应的模型坐标范围(left, right, bottom, top)
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);                     // 在进行变换前把当前矩阵设置为单位矩阵
}

void DDA_Line(int x0, int y0, int x1, int y1) {
	int dx, dy, ep, k;
	float x, y, xIncre, yIncre;
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;
	if (abs(dx) > abs(dy)) // k < 1
		ep = abs(dx);
	else ep = abs(dy);// k > 1
	xIncre = (float)dx / (float)ep;
	yIncre = (float)dy / (float)ep;
	glPointSize(5.0);//每个点的大小为5个像素
	glBegin(GL_POINTS);            // 开始画点
	glVertex3f(x0, y0, 0);		   // 画起点
	for (k = 0; k <= ep; k++) {
		glVertex2i(int(x + 0.5), int(y + 0.5));
		x += xIncre;
		y += yIncre;
	}
	glVertex3f(x, y, 0);	   // 画终点
	glEnd();
	glFlush();
}
void Bresenham_line(float x11, float y11, float x22, float y22)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//绘制坐标轴
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);//设置坐标轴颜色，红色
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glEnd();
	float x, y, dx, dy;
	x = x11; y = y11;
	float k, e;
	dx = abs(x22 - x11);
	dy = abs(y22 - y11);
	k = dy / dx;
	e = -dx;
	int s1 = x22 > x11 ? 1 : -1;
	int s2 = y22 > y11 ? 1 : -1;
	bool flag = false; //默认|k|<1
	if (dy > dx) { //|k|>1的情况
		int temp = dx;
		dx = dy;
		dy = temp;
		flag = true;
	}
	for (int i = 0; i < dx; i++)
	{
		glPointSize(5.0);//每个点的大小为5个像素
		glBegin(GL_POINTS);
		glColor3f(0, 0, 1);//设置图形颜色蓝色
		glVertex2f(x / 25, y / 25);
		glEnd();
		if (e >= 0)
		{
			if (!flag)		// 当斜率 < 1 时，选取上下象素点
				y += s2;
			else					// 当斜率 > 1 时，选取左右象素点
				x += s1;
			e -= 2 * dx;
		}
		if (!flag)
			x += s1;				// 当斜率 < 1 时，选取 x 为步长
		else
			y += s2;				// 当斜率 > 1 时，选取 y 为步长
		e += 2 * dy;
	}
	glFlush();
}

void Bresenham_line_display() {
	int x11, y11, x22, y22;
	cout << "请输入直线起始点坐标和终点坐标：" << endl;
	cin >> x11 >> y11 >> x22 >> y22;
	Bresenham_line(x11, y11, x22, y22);
}
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10, 10, -10, 10);
}

// 0≤k≤1
void MidpointLine1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5.0);//每个点的大小为5个像素
	GLint a, b, d, d1, d2, x, y;
	a = y30 - y31;
	b = x31 - x30;
	d = 2 * a + b;
	d1 = 2 * a;
	d2 = 2 * (a + b);
	x = x30;
	y = y30;
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	while (x < x31)
	{
		if (d > 0)
		{
			x++;
			d += d1;
		}

		else
		{
			x++;
			y++;
			d += d2;
		}

		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();

	}
	glFlush();
}

//-1≤k≤0
void MidpointLine2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(5.0);//每个点的大小为5个像素
	GLint a, b, d, d1, d2, x, y;
	a = y30 - y31;
	b = x31 - x30;
	d = 2 * a - b;
	d2 = 2 * a;
	d1 = 2 * (a - b);
	x = x30;
	y = y30;

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

	while (x < x31)
	{
		if (d > 0)
		{
			x++;
			y--;
			d += d1;
		}

		else
		{
			x++;
			d += d2;
		}

		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();

	}
	glFlush();
}

//k>1  
void MidpointLine3()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 1.0f);
	glPointSize(5.0);//每个点的大小为5个像素
	GLint a, b, d1, d2, d, x, y;
	a = y30 - y31;
	b = x31 - x30;
	d = a + 2 * b;
	d1 = 2 * (a + b);
	d2 = 2 * b;
	x = x30;
	y = y30;

	while (y < y31)
	{
		if (d < 0)
		{
			y++;
			d += d2;
		}
		else
		{
			y++;
			x++;
			d += d1;
		}
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();

	}
	glFlush();
}

//k＜-1  
void MidpointLine4()
{
	glClear(GL_COLOR_BUFFER_BIT);// 清除当前可写的颜色缓冲
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0);//每个点的大小为5个像素
	GLint a, b, d1, d2, d, x, y;
	a = y30 - y31;
	b = x31 - x30;
	d = a - 2 * b;
	d1 = -2 * b;
	d2 = 2 * (a - b);
	x = x30;
	y = y30;

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

	while (y < y31)
	{
		if (d < 0)
		{
			x++;
			y--;
			d += d2;
		}
		else
		{
			y--;
			d += d1;
		}
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();

	}
	glFlush();
}