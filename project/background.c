#include "project.h"

/*
#define TREE_NUM 15

typedef struct
{
	float x;
	float y;
	float size;
} forest;

forest tree[TREE_NUM]; //пассивная агрессия таким людям //вообще это можно спрятать в мэйн //может лучше в чили_сноу
double speed = 0.03;   //сделайте с этим что-нибудь, мне аж самому плохо
					   //тут надо перепридумать движение

void plant_tree (int i, double y_pos);
void print_tree (forest tree);
void reshape (int w, int h);
void create_forest (void);
void chilly_snow (void);
void background (void);
void timer (int t);
*/

int main (int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800,600);
	glutCreateWindow("chilly snow");
	
	for (int i = 0; i < TREE_NUM; i++) //делаем лес (может надо пониже (x) создавать, чтоб еще на следующие хватало)
	plant_tree(i, (rand()%24 - 20));

	glClearColor(0.847, 0.901, 1, 1.0);
	glutDisplayFunc(chilly_snow);

	//glutTimerFunc(0, timer, 0); //эта фигня отвечает за перересовку экрана
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}

void chilly_snow () //каждый раз когда вызывается эта функция рисуется один кадр
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	background(); //сначала надо отрисовать фон!
	
	glutSwapBuffers();
}

void background (void)
{
	//оставляем идею с пролистыванием полотна
	for (int i = 0; i < TREE_NUM; i++)
	{
		print_tree(tree[i]);
	}
}

void plant_tree (int i, double y_pos)
{
	tree[i].size = 0.1*(rand()%2) + 0.3;		   //рандомные препятствия и размер деревьев!!! //для первого кадра это конечно хорошо, но если они 60 раз в секунду будут обновляться, это уже странно
	tree[i].x = (rand()%20 - 10) + 3*tree[i].size; //"случайное" число от 0 до 10
	tree[i].y = y_pos; 							   //придется сделать проверку, чтоб вас рандом не убивал с первых секунд
}

void print_tree (forest tr) //заебись
{
	glBegin(GL_POLYGON);

		glColor3f(0.258, 0.603, 0.345); //пока все деревья зеленые, можно изменение их цвета связать с увеличением скорости
		glVertex2f(tr.x, tr.y); //вершина дерева;
		glVertex2f(tr.x - tr.size, tr.y - tr.size);
		glVertex2f(tr.x - 0.2*tr.size, tr.y - tr.size);
		glVertex2f(tr.x - 1.9*tr.size, tr.y - 3*tr.size);
		
		glColor3f(0.133, 0.545, 0.133);
		glVertex2f(tr.x + 1.9*tr.size, tr.y - 3*tr.size);
		glVertex2f(tr.x + 0.2*tr.size, tr.y - tr.size);
		glVertex2f(tr.x + 1.2*tr.size, tr.y - tr.size);
		glVertex2f(tr.x, tr.y);

	glEnd();

	glBegin(GL_POLYGON); //добавим дереву ножку

		glColor3f(0.407, 0.133, 0.011);
		glVertex2f(tr.x - 0.2*tr.size, tr.y - 3*tr.size);
		glVertex2f(tr.x - 0.2*tr.size, tr.y - 3.3*tr.size);
		glVertex2f(tr.x + 0.2*tr.size, tr.y - 3.3*tr.size);
		glVertex2f(tr.x + 0.2*tr.size, tr.y - 3*tr.size);

	glEnd();
}

void reshape (int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10); //чем больше делений, тем более подробно можно все описать
	glMatrixMode(GL_MODELVIEW);
}

void timer (int t) //тут используем это чтобы тянуть фон наверх
{
	glutPostRedisplay();
	glutTimerFunc(1000/100, timer, 0);

	for (int i = 0; i < TREE_NUM; i++)
	{
		tree[i].y += speed;
		if (tree[i].y - 3.3*tree[i].size > 10) plant_tree(i, -10); //блятб, как добавлять информацию на экран //дебил просто ты добавляешь не пойми сколько, и не факт что в точности будет равно 10
	}	
	speed += speed_add; //надо меньше скорости добавлять, слишком быстро становиться
}