#ifndef CHILLY_SNOW_H
#define CHILLY_SNOW_H

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define speed_add 0.00005
#define pi 3.14159265
#define TREE_NUM 15
#define FPS 60

typedef struct
{
	float x;
	float y;
	float size;
} forest;

forest tree[TREE_NUM]; //вообще это можно постараться спрятать в чили_сноу

void plant_tree (int i, double y_pos);
void move_ball (int s, int x, int y);
void print_tree (forest tr);
void crush_ball (forest tr);
void reshape (int w, int h);
void create_forest (void);
void chilly_snow (void);
void print_ball (void);
void background (void);
void timer (int t);

#endif