#include "stdio.h"
#include "display.h"
#include "io.h"
#include "common.h"
#include "Windows.h"


typedef //������Ʈ �ǹ�
struct {
	char object;
	int color_num;
	int blood;
	int cost;
} OBJECT;

typedef //����
struct {
	char object;
	int color_num;
	int cost;
	int people;
	int move;
	int demage;
	int war_time;
	int blood;
	int see;

} UNIT;

typedef //�����
struct {
	char object;
	int color_num;
	int move;
	int war_time;
} SANDWARM;

typedef //��
struct {
	char object;
	int color_num;
} ROCK;

typedef
struct { //�����̽�
	int color_num;
	int much;
} SPICE;


//�ʱ� �ǹ� + ����
//player
OBJECT player_B;
UNIT  player_H;

//AI
OBJECT  AI_B;
UNIT  AI_H;

//��
OBJECT rock;

//����
OBJECT plate_1;
OBJECT plate_2;

//�����̽�
SPICE spice_1;
SPICE spice_2;

//�����
SANDWARM sandwarm_1;
SANDWARM sandwarm_2;

//�ǹ�
OBJECT dormitory; //����
OBJECT garage; //â��
OBJECT barracks; //����
OBJECT shelter; //����ó
OBJECT arena; //������
OBJECT factory; //����

//����
UNIT premen; //������
UNIT soldier; //����
UNIT fighter; //����
UNIT tank; //������

void key_ready_build(OBJECT* dormitory, OBJECT* garage, OBJECT* barracks, OBJECT* shelter, OBJECT* arena, OBJECT* factory);
void key_ready_unit(UNIT* premen, UNIT* soldier, UNIT* fighter, UNIT* tank);


void key_ready_build(OBJECT* dormitory, OBJECT* garage, OBJECT* barracks, OBJECT* shelter, OBJECT* arena, OBJECT* factory) {
	dormitory->object = "D";
	dormitory->color_num = 15;
	dormitory->blood = 10;
	dormitory->cost = 2;

	garage->object = "G";
	garage->color_num = 15;
	garage->blood = 10;
	garage->cost = 4;

	barracks->object = "B";
	barracks->color_num = 15;
	barracks->blood = 20;
	barracks->cost = 4;

	shelter->object = "S";
	shelter->color_num = 15;
	shelter->blood = 30;
	shelter->cost = 5;

	arena->object = "A";
	arena->color_num = 15;
	arena->blood = 15;
	arena->cost = 3;

	factory->object = "F";
	factory->color_num = 15;
	factory->blood = 30;
	factory->cost = 5;
}


void key_ready_unit(UNIT* premen, UNIT* soldier, UNIT* fighter, UNIT* tank) {
	premen->object = "p";
	premen->cost = 5;
	premen->people = 2;
	premen->move = 400;
	premen->demage = 15;
	premen->war_time = 200;
	premen->blood = 25;
	premen->see = 8;

	soldier->object = "s";
	soldier->cost = 1;
	soldier->people = 1;
	soldier->move = 1000;
	soldier->demage = 5;
	soldier->war_time = 800;
	soldier->blood = 15;
	soldier->see = 1;

	fighter->object = "f";
	fighter->cost = 1;
	fighter->people = 1;
	fighter->move = 1200;
	fighter->demage = 6;
	fighter->war_time = 600;
	fighter->blood = 10;
	fighter->see = 1;

	tank->object = "t";
	tank->cost = 12;
	tank->people = 5;
	tank->move = 3000;
	tank->demage = 40;
	tank->war_time = 4000;
	tank->blood = 60;
	tank->see = 4;
}
