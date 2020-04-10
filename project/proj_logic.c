#include "project.h"

double speed = 0.1;
double x_ball = 0;

extern int XW;
extern int YW;

void plant_tree (int i, double y_pos)
{
	tree[i].size = 0.1*(rand()%2) + 0.3;		   //рандомные препятствия и размер деревьев!!! //для первого кадра это конечно хорошо, но если они 60 раз в секунду будут обновляться, это уже странно
	tree[i].x = (rand()%20 - 10) + 3*tree[i].size; //придется сделать проверку, чтоб вас рандом не убивал с первых секунд //проблема контрится корейским рандомом на первой части
	tree[i].y = y_pos;
}

void chilly_snow () //каждый раз когда вызывается эта функция рисуется один кадр
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	print_ball();
	for (int i = 0; i < TREE_NUM; i++)
	{
		print_tree(tree[i]);
		crush_ball(tree[i]);
	}
	glutSwapBuffers();
}

void print_tree (forest tr) 
{
	/*	Задачи: 
	 *	- пока все деревья зеленые, можно изменение их цвета связать с увеличением скорости
	 *	- Нужно соотношение вида dx/XW= dx'/XW' => dx' = dx* XW/XW' = dx *800/XW
	 *	! Заметка: вытянутые деревья получше
	 *	- В этой же функции можно добавить дереву тень
	 */

	glBegin(GL_POLYGON);

		glColor3f(0.258, 0.603, 0.345); //(1, 0.603, 0.345)
		glVertex2f(tr.x, tr.y); //вершина дерева;
		glVertex2f(tr.x - 1.2*YW/XW*tr.size, tr.y - XW/YW*tr.size); // tr.x - 1.1*600/800tr.size
		glVertex2f(tr.x - 0.1*YW/XW*tr.size, tr.y - XW/YW*tr.size);
		glVertex2f(tr.x - 1.9*YW/XW*tr.size, tr.y - 3*XW/YW*tr.size);
		
		glColor3f(0.133, 0.545, 0.133); //(1, 0.545, 0.133)
		glVertex2f(tr.x + 1.9*YW/XW*tr.size, tr.y - 3*XW/YW*tr.size);
		glVertex2f(tr.x + 0.1*YW/XW*tr.size, tr.y - XW/YW*tr.size);
		glVertex2f(tr.x + 1.2*YW/XW*tr.size, tr.y - XW/YW*tr.size);
		glVertex2f(tr.x, tr.y);

	glEnd();

	glBegin(GL_POLYGON); //добавим дереву ножку

		glColor3f(0.407, 0.133, 0.011);
		glVertex2f(tr.x - 0.2*YW/XW*tr.size, tr.y - 3*XW/YW*tr.size);
		glVertex2f(tr.x - 0.2*YW/XW*tr.size, tr.y - 3.3*XW/YW*tr.size);
		glVertex2f(tr.x + 0.2*YW/XW*tr.size, tr.y - 3.3*XW/YW*tr.size);
		glVertex2f(tr.x + 0.2*YW/XW*tr.size, tr.y - 3*XW/YW*tr.size);

	glEnd();
}

void print_ball (void)
{
	glBegin(GL_POLYGON);

	glColor3f(1, 0.113, 0.027);	
	for(float i = 0; i <= 2*pi; i+=pi/180)
	{
		if (i > 11*pi/6) glColor3f(1, 0.113, 0.027);
		glVertex2f(x_ball + 0.5*YW/XW*cos(i), 2.5 + 0.5*sin(i));

		if (i > 4*pi/3)
		{
			glColor3f(0.866, 0.078, 0.094);
			glVertex2f(x_ball + 0.5*YW/XW*cos(i), 2.5 + 0.5*sin(i));
		}	
	}

	glEnd();
}

void crush_ball (forest tr)
{
	/* Что нужно сделать: 
	 *  1) Дерево приближается треугольником с общей вершиной (х,у)
	 *  2) Находится длинна/2 линии пересечения дерева с линией движения шара
	 *  3) Центр линии смещается к центру дерева!
	 *  4) Проверяется попал ли шар в линию
	 *
	 * Баги:
	 * - Это условие хорошее, но тут есть баг: можно пройти шаром ровно через центр дерева и не засчитается касание. Сейчас так не получается
	 * - Возникает однако следующая проблема: шар может пролазить у основания дерева
	 *
	 *	  Тут можно просто чистить экран  и на нем писать, мол игра закончена, вместо "ваш счет" будем слепливать свою строку из слов "ваш счет" и еще счета
	 */

	float l = (tr.y - 2.5)*0.9/3;	//(1), (2)
	if ( ( ((x_ball + 0.5 >= tr.x - l) && (x_ball <= tr.x - l)) || ((x_ball - 0.5 <= tr.x + l) && (x_ball >= tr.x + l)) ) && ((tr.y >= 2.5) && (tr.y <= 2.5 + 3*tr.size ))) //(3), (4)
	{
		char _meters[1000000];
		int m = (int)((speed - 0.04)*10000);
		itoa(m, _meters, 10); //~так, тут надо над переводными множителями посидеть
		char message[1000050] = "Your score:  ";
		strcat(message, _meters);
		MessageBox(NULL,message, "GAME OVER", 0);
		exit(0); 
	}
}

void move_ball (int s, int x, int y)
{
	switch(s)
	{
		case GLUT_KEY_RIGHT: x_ball += 1.6*speed*FPS/100; break;
		case GLUT_KEY_LEFT: x_ball -= 1.6*speed*FPS/100; break;
	}
}

void reshape (int w, int h)
{
	glViewport(0, 0, w, h);
	XW = w; YW = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void timer (int t)
{
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 0); //вообще лучше увеличивать частоту прорисовки шара, потому что он начинает двигаться рывками

	for (int i = 0; i < TREE_NUM; i++)
	{
		tree[i].y += speed*FPS/100;
		if (tree[i].y - 3.5*XW/YW*tree[i].size > 10) plant_tree(i, -10);
	}
	speed += speed_add;
}