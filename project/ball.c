#include "project.h"
//#define FPS 100

/*

void ball (void);
void print_ball (void);
void move_ball (int s, int x, int y);

*/

double speed = 0.025;   //сделайте с этим что-нибудь, мне аж самому плохо
double x_ball = 0;

int XW = 800;
int YW = 600;

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
	return 0;
}

void chilly_snow () //каждый раз когда вызывается эта функция рисуется один кадр
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	print_ball();
	for (int i = 0; i < TREE_NUM; i++) print_tree(tree[i]);
	//тут надо проверить столкнулись ли мы с чем нибудь?

	glutSwapBuffers();
}

void print_tree (forest tr) //работает 
{
	/*	Задачи: 
	 *	- пока все деревья зеленые, можно изменение их цвета связать с увеличением скорости
	 *	- можно добавить отношения, чтоб сохранять соотношения сторон на деревьях. Соотношения сохраняются, только у меня вторая точка куда-то теряется
	 *	! Заметка: вытянутые деревья получше
	 *	- В этой же функции можно добавить дереву тень
	 */

	glBegin(GL_POLYGON);

		glColor3f(0.258, 0.603, 0.345);
		glVertex2f(tr.x, tr.y); //вершина дерева;
		glVertex2f(tr.x - 1.2*YW/XW*tr.size, tr.y - XW/YW*tr.size); // tr.x - 1.1*600/800tr.size
		glVertex2f(tr.x - 0.1*YW/XW*tr.size, tr.y - XW/YW*tr.size);
		glVertex2f(tr.x - 1.9*YW/XW*tr.size, tr.y - 3*XW/YW*tr.size);
		
		glColor3f(0.133, 0.545, 0.133);
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

void plant_tree (int i, double y_pos)
{
	tree[i].size = 0.1*(rand()%2) + 0.3;		   //рандомные препятствия и размер деревьев!!! //для первого кадра это конечно хорошо, но если они 60 раз в секунду будут обновляться, это уже странно
	tree[i].x = (rand()%20 - 10) + 3*tree[i].size; //придется сделать проверку, чтоб вас рандом не убивал с первых секунд //проблема контрится корейским рандомом на первой части
	tree[i].y = y_pos;
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

void move_ball (int s, int x, int y) //принимает символ который введен и позицию мыши x y 
{
	switch(s)
	{
		case GLUT_KEY_RIGHT: x_ball += 1.7*speed; break;
		case GLUT_KEY_LEFT: x_ball -= 1.7*speed; break;
	}
}

void reshape (int w, int h)
{
	glViewport(0, 0, w, h);
	XW = w; YW = h;				  //так можно сохранять соотношения строн на обьектах (пока только на шаре)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10); //чем больше делений, тем более подробно можно все описать
	glMatrixMode(GL_MODELVIEW);
}

void timer (int t) //тут используем это чтобы тянуть фон наверх
{
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 0);

	for (int i = 0; i < TREE_NUM; i++)
	{
		tree[i].y += speed;
		if (tree[i].y - 3.3*tree[i].size > 10) plant_tree(i, -10);
	}
	speed += speed_add;
}