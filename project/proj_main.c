#include "project.h"

/* Дополнение:
 *	! Дополнительные тени (это возмонжно быстро получиться с помощью градиента полигона)
 *  - Добавить полосу счетчика пути
 *	- Меню
 *	- Добавление камней
 *	- Дописать инерцию шару
 *	- Добавить след от шара. C иннерционными переменными можно связять след от шара
 *
 *  g++ -o test -Wall test.c -mwindows glut32.lib -lopengl32 -lglu32
 */

int XW = 800;
int YW = 600;

int main (int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(XW,YW);
	glutCreateWindow("chilly snow");
	
	for (int i = 0; i < TREE_NUM; i++)
	plant_tree(i, (rand()%24 - 20));

	glClearColor(0.847, 0.901, 1, 1.0);
	glutDisplayFunc(chilly_snow);

	glutTimerFunc(0, timer, 0);
	
	glutSpecialFunc(move_ball);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}