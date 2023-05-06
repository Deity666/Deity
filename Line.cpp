#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<stdlib.h>  
#include <iostream>
#include <algorithm>
using namespace std;
GLint x30, y30, x31, y31;
void DDA_Line(int x0, int y0, int xEnd, int yEnd);//DDA��ֱ�߷�ʽ
void DDA_Line_display(void);//DDA��ֱ�߷�ʽ��ͼ��ʾ
void Bresenham_line(float x11, float y11, float x22, float y22);//Bresenham��ֱ�߷�ʽ
void Bresenham_line_display();//Bresenham��ֱ�߷�ʽ��ͼ��ʾ
void myInit(void);//������Ⱦ��ʼ��
void Init();
void MidpointLine1();// 0��k��1
void MidpointLine2();//-1��k��0
void MidpointLine3();//k>1 
void MidpointLine4();//k��-1  
int main(int argc, char* argv[])
{
	int x;
	cout << "��ѡ��ʽ" << endl;
	cout << "1:DDA" << endl;
	cout << "2:Bresenham" << endl;
	cout << "3:�е�" << endl;
	cout << "��������:�˳�" <<endl;
	cin >> x;
	if (x == 1)
	{
		cout << "DDA��ʽ" << endl;
		glutInit(&argc, argv);                          // ��ʼ��
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // �����崰�ڣ�RGB��ɫģʽ
		glutInitWindowSize(500, 400);                  // ��������
		glutInitWindowPosition(500, 100);              // // ����λ��
		glutCreateWindow("DDA");                     // ��������
		glutDisplayFunc(DDA_Line_display);                       // ���Ʒ���
		myInit();                                       // ��ʼ��
		glutMainLoop();                                 // ѭ����Ⱦ
	}
	else if (x == 2)
	{
		cout << "Bresenham�㷨��ʽ" << endl;
		glutInit(&argc, argv); //��ʼ��glut
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // �����崰�ڣ�RGB��ɫģʽ
		glutInitWindowSize(1000, 800);                  // ��������
		glutInitWindowPosition(500, 100);              //����λ��
		gluOrtho2D(50.0, 50.0, 50.0, 50.0);             // //����ָ����Ļ�����Ӧ��ģ�����귶Χ(left, right, bottom, top)
		glutCreateWindow("Bresenham�㷨"); //�������ڲ�����title
		glutDisplayFunc(Bresenham_line_display);//����renderScene�ѻ��ƴ��͵�����
		glutMainLoop(); //����ѭ���ȴ�
	}
	else if (x == 3)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(500, 100);
		glutInitWindowSize(500, 500);
		glutCreateWindow("�е㻭�߷�");
		Init();
		printf("���������������е�����:\n");
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
	//glClear(GL_COLOR_BUFFER_BIT);  // �����ǰ��д����ɫ����
	glViewport(0, 0, 400, 300);   // �ӿھ��εķ�Χ(x, y, width, height)

	/*DDA_Line(10, 30, 70, 30);//�������
	DDA_Line(70, 30, 30, 50);
	DDA_Line(30, 50,40,10);
	DDA_Line( 40, 10,50,50);
	DDA_Line(50, 50,10,30);*/
	int n;
	cout << "������ֱ������" << endl;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x0, y0, x1, y1;
		cout << "�������" << i << "��ֱ����ʼ��������յ����꣺" << endl;
		cin >> x0 >> y0 >> x1 >> y1;
		DDA_Line(x0, y0, x1, y1);
	}

}

void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);// ���ñ�����ɫ��ɫ
	glColor3f(0.0, 1.0, 0.0);                       // ���õ���ɫ��ɫ
	//gluOrtho2D(-100.0, 100.0, -100.0, 100.0);             // ����ָ����Ļ�����Ӧ��ģ�����귶Χ(left, right, bottom, top)
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);                     // �ڽ��б任ǰ�ѵ�ǰ��������Ϊ��λ����
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
	glPointSize(5.0);//ÿ����Ĵ�СΪ5������
	glBegin(GL_POINTS);            // ��ʼ����
	glVertex3f(x0, y0, 0);		   // �����
	for (k = 0; k <= ep; k++) {
		glVertex2i(int(x + 0.5), int(y + 0.5));
		x += xIncre;
		y += yIncre;
	}
	glVertex3f(x, y, 0);	   // ���յ�
	glEnd();
	glFlush();
}
void Bresenham_line(float x11, float y11, float x22, float y22)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//����������
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);//������������ɫ����ɫ
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
	bool flag = false; //Ĭ��|k|<1
	if (dy > dx) { //|k|>1�����
		int temp = dx;
		dx = dy;
		dy = temp;
		flag = true;
	}
	for (int i = 0; i < dx; i++)
	{
		glPointSize(5.0);//ÿ����Ĵ�СΪ5������
		glBegin(GL_POINTS);
		glColor3f(0, 0, 1);//����ͼ����ɫ��ɫ
		glVertex2f(x / 25, y / 25);
		glEnd();
		if (e >= 0)
		{
			if (!flag)		// ��б�� < 1 ʱ��ѡȡ�������ص�
				y += s2;
			else					// ��б�� > 1 ʱ��ѡȡ�������ص�
				x += s1;
			e -= 2 * dx;
		}
		if (!flag)
			x += s1;				// ��б�� < 1 ʱ��ѡȡ x Ϊ����
		else
			y += s2;				// ��б�� > 1 ʱ��ѡȡ y Ϊ����
		e += 2 * dy;
	}
	glFlush();
}

void Bresenham_line_display() {
	int x11, y11, x22, y22;
	cout << "������ֱ����ʼ��������յ����꣺" << endl;
	cin >> x11 >> y11 >> x22 >> y22;
	Bresenham_line(x11, y11, x22, y22);
}
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10, 10, -10, 10);
}

// 0��k��1
void MidpointLine1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5.0);//ÿ����Ĵ�СΪ5������
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

//-1��k��0
void MidpointLine2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(5.0);//ÿ����Ĵ�СΪ5������
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
	glPointSize(5.0);//ÿ����Ĵ�СΪ5������
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

//k��-1  
void MidpointLine4()
{
	glClear(GL_COLOR_BUFFER_BIT);// �����ǰ��д����ɫ����
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0);//ÿ����Ĵ�СΪ5������
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