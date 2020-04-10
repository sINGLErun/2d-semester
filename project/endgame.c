#include "project.h"
//#define FPS 100

/*
void ball (void);
void print_ball (void);
void move_ball (int s, int x, int y);
*/

/*
 *	- Вообще чтоб все круто-классно было, нужно вынести все переменные сюда, типо радиуса шара, и другого барахла
 *	
 */

double speed = 0.06;   //сделайте с этим что-нибудь, мне аж самому плохо
double x_ball = 0;

int XW = 800;
int YW = 600;

void crush_ball (forest tr);

int main (int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(XW,YW);
	glutCreateWindow("chilly snow");

	for (int i = 0; i < TREE_NUM; i++) //делаем лес (может надо пониже (x) создавать, чтоб еще на следующие хватало)
	plant_tree(i, (rand()%24 - 20));

	glClearColor(0.847, 0.901, 1, 1.0);
	glutDisplayFunc(chilly_snow);
	glutTimerFunc(0, timer, 0); //эта фигня отвечает за перересовку экрана
	
	glutSpecialFunc(move_ball); //glutKeyboardFunc(); //функция которая позволяет работать с клавиатурой
	glutReshapeFunc(reshape);
	glutMainLoop();

}

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
		crush_ball(tree[i]); //тут надо проверить столкнулись ли мы с чем нибудь? Лучше в одном цикле это все проворачивать
	}
	glutSwapBuffers();
}

void print_tree (forest tr) //работает 
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
	/*  Задачи:
	 *  - Почаще прорисовывать шар, чтобы движение не казалось дёрганым
	 *
	 *
	 */

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
	/* - описание треугольника прекращения
	 *	if (x_ball > 3/1.7*(XW/YW)*(XW/YW)*tree[i].x + tree[i].y && x_ball < -3/1.7*(XW/YW)*(XW/YW)*tree[i].x + tree[i].y)
	 * 
	 * Что нужно сделать: 
	 * 1) Дерево приближается треугольником с общей вершиной (х,у)
	 * 2) Находится пересечение дерева с линией движения шара
	 * 3) Центр линии смещается к центру дерева!
	 * 4) Проверяется попал ли шар в линию
	 *
	 *	  Тут можно просто чистить экран  и на нем писать, мол игра закончена, вместо "ваш счет" будем слепливать свою строку из слов "ваш счет" и еще счета
	 *	  Это условие хорошее, но тут есть баг: можно пройти шаром ровно через центр дерева и не засчитается касание
	 *	  Пометка: Баг может быть связан с самим алгоритмом прохода через дерево,  у нас смотрится как линия проходящая через центр шара пересекает деревья
	 */


	float l = (tr.y - 2.5)*0.7/2.9;	//ширина/2 линии пересечения дерева (1), (2) //шар может у основания дерева пролазить
	if ( ( ((x_ball + 0.5 >= tr.x - l) && (x_ball <= tr.x - l)) || ((x_ball - 0.5 <= tr.x + l) && (x_ball >= tr.x + l)) ) && ((tr.y >= 2.5) && (tr.y <= 2.5 + 3*tr.size ))) //(3), (4) //так блять, это условие всегда верное //конченый, ты иначе рисовал точно такое же дерево
	{
		char _meters[1000000]; //переводит цифру в текст [макисмальное количество]
		int m = (int)((speed - 0.04)*10000);
		itoa(m, _meters, 10); //~так, тут надо над переводными множителями посидеть
		char message[1000050] = "Your score:  ";
		strcat(message, _meters);
		MessageBox(NULL,message, "GAME OVER", 0); //у меня комплексная длинна
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
	XW = w; YW = h;				  //так можно сохранять соотношения строн на обьектах (пока только на шаре, есть идея, но не дописано)
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
		if (tree[i].y - 3.5*XW/YW*tree[i].size > 10) plant_tree(i, -10); //надо, чтоб деревья за фоном пропадали //посмотрите в файле бэкграунд, там нет такой проблемы //деревья перестали пропадать
	}
	speed += speed_add;
}